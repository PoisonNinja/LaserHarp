#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <rtmidi/RtMidi.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "server.h"


#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0))

RtMidiOut *midiout;
std::vector<unsigned char> message;

bool chooseMidiPort( RtMidiOut *rtmidi )
{
  std::cout << "\nWould you like to open a virtual output port? [y/N] ";

  std::string keyHit;
  std::getline( std::cin, keyHit );
  if ( keyHit == "y" ) {
    rtmidi->openVirtualPort();
    return true;
  }

  std::string portName;
  unsigned int i = 0, nPorts = rtmidi->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No output ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
  }
  else {
    for ( i=0; i<nPorts; i++ ) {
      portName = rtmidi->getPortName(i);
      std::cout << "  Output port #" << i << ": " << portName << '\n';
    }

    do {
      std::cout << "\nChoose a port number: ";
      std::cin >> i;
    } while ( i >= nPorts );
  }

  std::cout << "\n";
  rtmidi->openPort( i );

  return true;
}

int
set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void
set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf("error %d setting term attributes", errno);
}

int midiCommand(int cmd, int note, int vel) {
    message[0] = cmd;
    message[1] = note;
    message[2] = vel;
    midiout->sendMessage(&message);
}

int noteOn(int ID) {
    switch (ID) {
    case 0:
      midiCommand(NOTEON, note1, VOLUME);
      break;
    case 1:
      midiCommand(NOTEON, note2, VOLUME);
      break;
    case 2:
      midiCommand(NOTEON, note3, VOLUME);
      break;
    case 3:
      midiCommand(NOTEON, note4, VOLUME);
      break;
    case 4:
      midiCommand(NOTEON, note5, VOLUME);
      break;
    case 5:
      midiCommand(NOTEON, note6, VOLUME);
      break;
    case 6:
      midiCommand(NOTEON, note7, VOLUME);
      break;
    case 7:
      midiCommand(NOTEON, note8, VOLUME);
      break;
    }
}

int main(int argc, char ** argv) {
    midiout = new RtMidiOut();
    char * serialport = "/dev/ttyACM0";
    int serial = open(serialport, O_RDONLY | O_NOCTTY);
    if (serial < 0) {
        printf("%s\n", "Error opening serial port");
        return -1;
    }
    set_interface_attribs(serial, B115200, 0);
    set_blocking(serial,0);
    chooseMidiPort(midiout);
    message.push_back(0);
    message.push_back(0);
    message.push_back(0); 
   char * pch;
    int id;
    int value;
    printf("%s\n", "Harp Server ready");
    while(1)
    {
        char buffer[100];
        ssize_t length = read(serial, &buffer, sizeof(buffer));
        if (length == -1)
        {
            printf("Error reading from serial port\n");
            break;
        }
        else if (length != 0 && length > 6)
        {
            buffer[length] = '\0';
            pch = strtok(buffer,",");
            id = atoi(pch);
            pch = strtok(NULL,",");
            value = atoi(pch);
            if (value > 700) {
                printf("Lights on for %d\n", id);
                noteOn(id);
            }
        }
    }
}

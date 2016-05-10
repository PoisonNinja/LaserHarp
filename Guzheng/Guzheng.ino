/* Code for laser GuZheng
 * Copyright (C) 2016 Jason Lu
 * 
 * Licensed under the MIT License
 */ 
 
/* Uncomment the define if you are using a wind instrument, such
 * as a trumpet or flute. It will disable several things that
 * are specific to string and percussion instruments. DO NOT
 * uncomment it if you are using a piano or string instrument! 
 */
// #define WIND

// Port I/O defines
#define THRESHOLD 500
#define LASTPORT 7
#define BUTTONPORT 2

// MIDI property defines
#define VOLUME 0x7F
#define DELAY 0

// MIDI command defines
#define NOTEON 0x90
#define NOTEOFF 0x80
#define CHANGEINSTRUMENT 0xC0
#define INSTRUMENT 0x39

// Values for different notes
// Currently a C scale, starting from middle C (C4)
int note8 = 0x48;
int note7 = 0x47;
int note6 = 0x45;
int note5 = 0x43;
int note4 = 0x41;
int note3 = 0x40;
int note2 = 0x3E;
int note1 = 0x3C;

/* Flag values for each laser. These values will operate on the bit
 * levels, directly with binary. They work together with the
 * lastNote variable to keep track of blocked lasers. 
 * Here, I use an AND operator to read if the value has been
 * set, and OR to set the value. */
uint8_t laserArray[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

/* Variable to keep track of the last played instrument. The real
 * data shows up when converted to binary, since we use binary
 * operator tricks. When the first laser is hit, it is 00000001. If
 * the second one is hit, then it is 00000010, and the third one is
 * 00000100, and so on. */
uint8_t lastNote = 0;

// Function to write notes over serial
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

// Function for playing note based on ID
void musicOn(int ID) {
  switch (ID) {
  case 0:
    noteOn(NOTEON, note1, VOLUME);
    break;
  case 1:
    noteOn(NOTEON, note2, VOLUME);
    break;
  case 2:
    noteOn(NOTEON, note3, VOLUME);
    break;
  case 3:
    noteOn(NOTEON, note4, VOLUME);
    break;
  case 4:
    noteOn(NOTEON, note5, VOLUME);
    break;
  case 5:
    noteOn(NOTEON, note6, VOLUME);
    break;
  case 6:
    noteOn(NOTEON, note7, VOLUME);
    break;
  case 7:
    noteOn(NOTEON, note8, VOLUME);
    break;
  default:
    // WTF? It shouldn't reach here, because that's an invalid ID
    noteOn(NOTEOFF, note1, 0x00);
    break;
  }
}

// Function for turning off a specific note based on ID
// Just a slightly modified version of musicOn()
void musicOff(int ID) {
  switch (ID) {
  case 0:
    noteOn(NOTEOFF, note1, 0x7F);
    break;
  case 1:
    noteOn(NOTEOFF, note2, 0x7F);
    break;
  case 2:
    noteOn(NOTEOFF, note3, 0x7F);
    break;
  case 3:
    noteOn(NOTEOFF, note4, 0x7F);
    break;
  case 4:
    noteOn(NOTEOFF, note5, 0x7F);
    break;
  case 5:
    noteOn(NOTEOFF, note6, 0x7F);
    break;
  case 6:
    noteOn(NOTEOFF, note7, 0x7F);
    break;
  case 7:
    noteOn(NOTEOFF, note8, 0x7F);
    break;
  default:
    // WTF? It shouldn't reach here, because that's an invalid ID
    noteOn(NOTEOFF, note1, 0x00);
    break;
  }
}

void setup()
{
  // Initialize serial at 115200 baud
  Serial.begin(115200);
  // Wait 1 second for ttymidi to come up
  delay(1000);
  // Set instrument to trumpet
  // 0xC0 is the change instrument command
  // 0x39 is the instrument ID in hex
#ifdef WIND
  Serial.write(CHANGEINSTRUMENT);
  Serial.write(INSTRUMENT);
#endif
}

void loop()
{
  // Main loop
  // 8 ports, from 0 to 7
  for (int i = 0; i <= LASTPORT; i++) {
    if(analogRead(i) > THRESHOLD) {
#ifndef WIND
      if (!(lastNote & (laserArray[i]))) {
#endif
        // Beam has been cut
        musicOn(i);
#ifndef WIND
        lastNote |= (laserArray[i]);
      }
#endif
    } else {
#ifndef WIND
      if ((lastNote & (laserArray[i]))) {
        lastNote &= ~(laserArray[i]);
      }
#endif
      // Hand is gone. Stop the sound
      musicOff(i);
    }
    // Delay 10 to prevent weird analog readings
    delay(DELAY);
  }
}

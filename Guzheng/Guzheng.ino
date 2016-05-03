/* Code for laser guzheng
 * Copyright (C) 2016 Jason Lu
 * 
 */
 
 
// Some defines
#define THRESHOLD 700
#define VOLUME 0x7F
#define LASTPORT 4
#define DELAY 10

// MIDI command defines
#define NOTEON 0x90
#define NOTEOFF 0x80
#define CHANGEINSTRUMENT 0xC0

// Values for different notes
int note8 = 0x68;
int note7 = 0x47;
int note6 = 0x45;
int note5 = 0x43;
int note4 = 0x41;
int note3 = 0x40;
int note2 = 0x3E;
int note1 = 0x3C;

void setup()
{
  // Initialize serial at 115200 baud
  Serial.begin(115200);
  // Wait 1 second for ttymidi to come up
  delay(1000);
  // Set instrument to trumpet
  // 0xC0 is the change instrument command
  // 0x39 is the instrument ID in hex
  Serial.write(CHANGEINSTRUMENT);
  Serial.write(0x39);
}

// Function for playing note based on ID
void musicOn(int ID) {
  switch (ID) {
  case 1:
    noteOn(NOTEON, note1, VOLUME);
    break;
  case 2:
    noteOn(NOTEON, note2, VOLUME);
    break;
  case 3:
    noteOn(NOTEON, note3, VOLUME);
    break;
  case 4:
    noteOn(NOTEON, note4, VOLUME);
    break;
  case 5:
    noteOn(NOTEON, note5, VOLUME);
    break;
  case 6:
    noteOn(NOTEON, note6, VOLUME);
    break;
  case 7:
    noteOn(NOTEON, note7, VOLUME);
    break;
  case 8:
    noteOn(NOTEON, note8, VOLUME);
    break;
  default:
    noteOn(NOTEOFF, note1, 0x00);
    break;
  }
}

// Function for turning off a specific note based on ID
// Just a slightly modified version of musicOn()
void musicOff(int ID) {
  switch (ID) {
  case 1:
    noteOn(NOTEOFF, note1, 0x7F);
    break;
  case 2:
    noteOn(NOTEOFF, note2, 0x7F);
    break;
  case 3:
    noteOn(NOTEOFF, note3, 0x7F);
    break;
  case 4:
    noteOn(NOTEOFF, note4, 0x7F);
    break;
  case 5:
    noteOn(NOTEOFF, note5, 0x7F);
    break;
  case 6:
    noteOn(NOTEOFF, note6, 0x7F);
    break;
  case 7:
    noteOn(NOTEOFF, note7, 0x7F);
    break;
  case 8:
    noteOn(NOTEOFF, note8, 0x7F);
    break;
  default:
    noteOn(NOTEOFF, note1, 0x00);
    break;
  }
}

void loop()
{
  // Main loop
  // 5 ports, from 0 to 4
  for (int i = 0; i <= LASTPORT; i++) {
    if(analogRead(i) > THRESHOLD) {
      // Beam has been cut
      // i+1 is because i is 0 indexed, but the ID starts with 1
      musicOn(i + 1);
    } else {
      // Hand is gone. Stop the sound
      musicOff(i + 1);
    }
    // Delay 10 to prevent weird analog readings
    delay(DELAY);
  }
}

// Function to write notes over serial
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}


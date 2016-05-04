/* Code for laser guzheng
 * Copyright (C) 2016 Jason Lu
 * 
 * Licensed under the MIT License
 */ 
 
/* Uncomment the define if you are using a wind instrument, such
 * as a trumpet or flute. It will disable several things that
 * are specific to string and percussion instruments. DO NOT
 * uncomment it if you are using a piano or string instrument! */
// #define WIND

// Port I/O defines
#define THRESHOLD 500
#define LASTPORT 4

// MIDI property defines
#define VOLUME 0x7F
#define DELAY 10

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

// Variable to keep track of which set of notes (lower or upper 4)
// Needed to work around limited lasers
int noteSet = 1;
/* Variable to keep track of the last played instrument. Used to
 * prevent continuous striking sounds on string and piano instruments
 * . Set to -1 when all strings have not been blocked, and 314 when
 * the noteSet laser is pressed. Otherwise, it is set to the last
 * playing laser, which will cause the Arduino to ignore the laser
 * until it is released again, thus preventing multiple hits */
// TODO: Switch to a bit flag, and support multiple strings
int lastNote = -1;

void setup()
{
  // Initialize serial at 115200 baud
  Serial.begin(115200);
  // Wait 1 second for ttymidi to come up
  delay(1000);
  // Set instrument to trumpet
  // 0xC0 is the change instrument command
  // 0x39 is the instrument ID in hex
  // Serial.write(CHANGEINSTRUMENT);
  // Serial.write(INSTRUMENT);
}

// Function for playing note based on ID
void musicOn(int ID) {
  if (noteSet == 1) {
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
    }
  } else if (noteSet == 2) {
    switch (ID) {
      case 1:
        noteOn(NOTEON, note5, VOLUME);
        break;
      case 2:
        noteOn(NOTEON, note6, VOLUME);
        break;
      case 3:
        noteOn(NOTEON, note7, VOLUME);
        break;
      case 4:
        noteOn(NOTEON, note8, VOLUME);
        break;
    }
  }
}

// Function for turning off a specific note based on ID
// Just a slightly modified version of musicOn()
void musicOff(int ID) {
  if (noteSet == 1) {
    switch (ID) {
      case 1:
        noteOn(NOTEOFF, note1, VOLUME);
        break;
      case 2:
        noteOn(NOTEOFF, note2, VOLUME);
        break;
      case 3:
        noteOn(NOTEOFF, note3, VOLUME);
        break;
      case 4:
        noteOn(NOTEOFF, note4, VOLUME);
        break;
    }
  } else if (noteSet == 2) {
    switch (ID) {
      case 1:
        noteOn(NOTEOFF, note5, VOLUME);
        break;
      case 2:
        noteOn(NOTEOFF, note6, VOLUME);
        break;
      case 3:
        noteOn(NOTEOFF, note7, VOLUME);
        break;
      case 4:
        noteOn(NOTEOFF, note8, VOLUME);
        break;
    }
  }
}

void loop()
{
  // Main loop
  // 5 ports, from 0 to 4
  for (int i = 0; i <= LASTPORT; i++) {
    if(analogRead(i) > THRESHOLD) {
#ifndef WIND
      if (lastNote != i) {
#endif
        // Beam has been cut
        // i+1 is because i is 0 indexed, but the ID starts with 1
        if (i < 4) {
          musicOn(i + 1);
#ifndef WIND
          lastNote = i;
#endif
        } else if (i == 4) {
#ifndef WIND
          if (lastNote != 314) {
#endif
            if (noteSet == 1) {
              noteSet = 2;
            } else {
              noteSet = 1;
            }
#ifndef WIND
            lastNote = 314;
          }
#endif
        }
#ifndef WIND
      }
#endif
    } else {
#ifndef WIND
      if (lastNote == i) {
        lastNote = -1;
      }
#endif
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


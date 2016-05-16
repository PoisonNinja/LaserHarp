/* Code for laser guzheng
 * Copyright (C) 2016 Jason Lu
 * 
 * Licensed under the MIT License
 * This code has NO WARRANTY! You are
 * responsible for anything that happens
 */ 

// Port I/O defines
#define THRESHOLD 700
#define LASTPORT 7
#define INSTRUMENTBUTTON 8
#define NOTEBUTTON 9

// MIDI property defines
#define VOLUME 0x7F
#define DELAY 0

// MIDI Instrument Array
#define NUMINSTRUMENTS 6

// MIDI command defines
#define NOTEON 0x90
#define NOTEOFF 0x80
#define CHANGEINSTRUMENT 0xC0

// Values for different notes
// Currently a C scale, starting from middle C (C4)
#define note8 0x48
#define note7 0x47
#define note6 0x45
#define note5 0x43
#define note4 0x41
#define note3 0x40
#define note2 0x3E
#define note1 0x3C

#define note9 0x48
#define note10 0x4A
#define note11 0x4C
#define note12 0x4D
#define note13 0x4F
#define note14 0x51
#define note15 0x53
#define note16 0x54

int r0 = 0;
int r1 = 0;
int r2 = 0;

int noteSet = 1;

int instrumentButtonState = 0;
int noteButtonState = 0;
int currentInstrument = 0;

// Piano, Harpsichord, Pizzacato strings, Flute, Violin, Accordian
// Sounds provided by MIDI synthesizer, so you may need to install it
int instrumentArray[NUMINSTRUMENTS] = {0x01, 0x07, 0x2E, 0x4A, 0x29, 0x16};

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
  // MIDI command ID, such as 0x80 (note off) or 0x90 (note on)
  Serial.write(cmd);
  // MIDI note pitch, such as 0x3C (C)
  Serial.write(pitch);
  // MIDI note volume, from 0x00 (mute) to 0x7F (max)
  Serial.write(velocity);
}

// Function for playing note based on ID
void musicOn(int ID) {
  if (noteSet == 1) {
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
  } else if (noteSet == 2) {
    switch (ID) {
    case 0:
      noteOn(NOTEON, note9, VOLUME);
      break;
    case 1:
      noteOn(NOTEON, note10, VOLUME);
      break;
    case 2:
      noteOn(NOTEON, note11, VOLUME);
      break;
    case 3:
      noteOn(NOTEON, note12, VOLUME);
      break;
    case 4:
      noteOn(NOTEON, note13, VOLUME);
      break;
    case 5:
      noteOn(NOTEON, note14, VOLUME);
      break;
    case 6:
      noteOn(NOTEON, note15, VOLUME);
      break;
    case 7:
      noteOn(NOTEON, note16, VOLUME);
      break;
    default:
      // WTF? It shouldn't reach here, because that's an invalid ID
      noteOn(NOTEOFF, note1, 0x00);
      break;
    }
  }
}
  
  // Function for turning off a specific note based on ID
  // Just a slightly modified version of musicOn()
void musicOff(int ID) {
  if (noteSet == 1) {
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
  } else if (noteSet == 2) {
    switch (ID) {
    case 0:
      noteOn(NOTEOFF, note9, VOLUME);
      break;
    case 1:
      noteOn(NOTEOFF, note10, VOLUME);
      break;
    case 2:
      noteOn(NOTEOFF, note11, VOLUME);
      break;
    case 3:
      noteOn(NOTEOFF, note12, VOLUME);
      break;
    case 4:
      noteOn(NOTEOFF, note13, VOLUME);
      break;
    case 5:
      noteOn(NOTEOFF, note14, VOLUME);
      break;
    case 6:
      noteOn(NOTEOFF, note15, VOLUME);
      break;
    case 7:
      noteOn(NOTEOFF, note16, VOLUME);
      break;
    default:
      // WTF? It shouldn't reach here, because that's an invalid ID
      noteOn(NOTEOFF, note1, 0x00);
      break;
    }
  }
}

void setup()
{
  // Initialize serial at 115200 baud
  Serial.begin(115200);
  // Set the 74HC4051 command ports
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  // Wait 1 second for ttymidi to come up
  // Could be unnecessary, but better safe than sorry
  delay(1000);
}

void loop()
{
  // Main loop
  // LASTPORT+1 ports, from 0 to LASTPORT
  for (int i = 0; i <= LASTPORT; i++) {
    /* The following three lines convert the port we want
     * into the correct bit selections for the 74HC4051. I'm
     * not really sure exactly how it works, but I'm pretty
     * sure it's some bit shifting
     */
    r0 = bitRead(i,0);
    r1 = bitRead(i,1);
    r2 = bitRead(i,2);
    // Select the correct input using the values we calculated above
    digitalWrite(2, r0);
    digitalWrite(3, r1);
    digitalWrite(4, r2);
    // Detect if the instrument selection button is pressed
    if(digitalRead(INSTRUMENTBUTTON) == HIGH) {
      /* Make sure that this is the first time that the button
       * has been pressed
       */
      if (instrumentButtonState == 0) {
        if (currentInstrument >= (NUMINSTRUMENTS - 1)) {
          // Max number of instruments, so wrap around to 0
          currentInstrument = 0;
        } else {
          // Select next instrument
          currentInstrument++;
        }
        // Send MIDI command to change instrument
        Serial.write(CHANGEINSTRUMENT);
        // Write the current instrument
        Serial.write(instrumentArray[currentInstrument]);
        // Set the button state so this won't fire when holding down
        // the button
        instrumentButtonState = 1;
      }
    } else {
      // Button is no longer pressed, so reset the button state.
      instrumentButtonState = 0;
    }
    // Detect if note button has been pressed
    if(digitalRead(NOTEBUTTON) == HIGH) {
      // Make sure that this is the first time that the button
      // has been pressed
      if (noteButtonState == 0) {
        // Swap the current note set
        // TODO: FIgure out a better way to do this
        if (noteSet == 1) {
          noteSet = 2;
        } else {
          noteSet = 1;
        }
        noteButtonState = 1;
      }
    } else {
      // Button is no longer pressed, so reset the button state.
      noteButtonState = 0;
    }
    if(analogRead(0) > THRESHOLD) {
      /* Apply the AND operator to the lastNote indicator and the
       * corresponding value from the laser array to check if the
       * laser bit has been set or not
       *
       * If it returns a non zero value, then that means it is set.
       * If it is a zero, then the bit has not been set yet */
      if (!(lastNote & (laserArray[i]))) {
        // Beam has been cut
        musicOn(i);
        /* Set the bit using the OR operator between lastNote and
         * the corresponding value from the laser array */
        lastNote |= (laserArray[i]);
      }
    } else {
      /* Check if the last note bit has been set or not using the
       * AND operator. This won't always be true because this section
       * of the code runs even if the beam hasn't been cut yet */
      if ((lastNote & (laserArray[i]))) {
        /* Unset the flag using the AND and invert operators */
        lastNote &= ~(laserArray[i]);
      }
      // Hand is gone. Stop the sound
      musicOff(i);
    }
    // Delay 10 to prevent weird analog readings
    delay(DELAY);
  }
}

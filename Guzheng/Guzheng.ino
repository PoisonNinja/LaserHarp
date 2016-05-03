/* Code for laser guzheng
 * Copyright (C) 2016 Jason Lu
 * 
 */
 
 
// Some defines
#define THRESHOLD 700

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
  Serial.write(0xC0);
  Serial.write(0x39);
}

// Function for playing note based on ID
void musicOn(int ID) {
  switch (ID) {
  case 1:
    noteOn(0x90, note1, 0x7F);
    break;
  case 2:
    noteOn(0x90, note2, 0x7F);
    break;
  case 3:
    noteOn(0x90, note3, 0x7F);
    break;
  case 4:
    noteOn(0x90, note4, 0x7F);
    break;
  case 5:
    noteOn(0x90, note5, 0x7F);
    break;
  case 6:
    noteOn(0x90, note6, 0x7F);
    break;
  case 7:
    noteOn(0x90, note7, 0x7F);
    break;
  case 8:
    noteOn(0x90, note8, 0x7F);
    break;
  default:
    noteOn(0x80, note1, 0x00);
    break;
  }
}

// Function for turning off a specific note based on ID
// Just a slightly modified version of musicOn()
void musicOff(int ID) {
  switch (ID) {
  case 1:
    noteOn(0x80, note1, 0x7F);
    break;
  case 2:
    noteOn(0x80, note2, 0x7F);
    break;
  case 3:
    noteOn(0x80, note3, 0x7F);
    break;
  case 4:
    noteOn(0x80, note4, 0x7F);
    break;
  case 5:
    noteOn(0x80, note5, 0x7F);
    break;
  case 6:
    noteOn(0x80, note6, 0x7F);
    break;
  case 7:
    noteOn(0x80, note7, 0x7F);
    break;
  case 8:
    noteOn(0x80, note8, 0x7F);
    break;
  default:
    noteOn(0x80, note1, 0x00);
    break;
  }
}

void loop()
{
  // Main loop
  // 5 ports, from 0 to 4
  for (int i = 0; i < 5; i++) {
    if(analogRead(i) > THRESHOLD) {
      // Beam has been cut
      // i+1 is because i is 0 indexed, but the ID starts with 1
      musicOn(i + 1);
    } else {
      // Hand is gone. Stop the sound
      musicOff(i + 1);
    }
    // Delay 10 to prevent weird analog readings
    delay(10);
  }
}

// Function to write notes over serial
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}


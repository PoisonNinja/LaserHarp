/* Code for Midi control using LED as sensor
 * Copyright (C) 2016 Jason Lu
 * 
 */

#define LEDPORT 5
#define NOTE 0x1E
#define DELAY 200
#define THRESHOLD 10

void setup() {
  Serial.begin(115200);
}

void loop(void) {
  int pinRead0 = analogRead(LEDPORT);
  if (pinRead0 < THRESHOLD) {
    noteOn(0x90, NOTE, 0x45);
  } else {
    noteOn(0x90, NOTE, 0x00);
  }
  delay(DELAY);
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

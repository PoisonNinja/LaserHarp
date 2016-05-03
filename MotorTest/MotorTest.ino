/* Code for motor based laser harp
 * Copyright (C) 2016 Jason Lu
 *
 * Some code was taken from stepper motor sample code
 *
 */

/*-----( Import needed libraries )-----*/
#include <Stepper.h> 

#define lightPin 5
#define laserPin 7
#define motorDelay 4
#define laserDelay 0
#define threshold 70
#define motorSpeed 700
#define stepSize 2

int note9 = 0x61;
int note8 = 0x63;
int note7 = 0x64;
int note6 = 0x66;
int note5 = 0x68;
int note4 = 0x70;
int note3 = 0x71;
int note2 = 0x40;
int note1 = 0x47;

Stepper small_stepper(32, 8, 10, 9, 11);

int  Steps2Take;
int current;
int stepID;
int light;

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  // Nothing  (Stepper Library sets pins as outputs)
  Serial.begin(115200);
  pinMode(laserPin, OUTPUT);
}/*--(end setup )---*/

void parsePosition() {
  switch (stepID) {
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
    noteOn(0x90, note1, 0x00);
    break;
  }
}       

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  for (int i = 1; i < 8; i++) {
    digitalWrite(laserPin, LOW);
    small_stepper.setSpeed(motorSpeed);
    small_stepper.step(stepSize);
    stepID = i;
    delay(motorDelay);
    digitalWrite(laserPin, HIGH);
    delay(laserDelay);
    light = analogRead(lightPin);
    //    if (light > threshold) {
    //      parsePosition();
    //    } else {
    //      noteOn(0x90, 0x1E, 0x00);
    //    }
    Serial.print("ID: ");
    Serial.print(stepID);
    Serial.print(" Value: ");
    Serial.println(light);
  }
  // delay(1000);
  for (int i = 8; i > 1; i--) {
    digitalWrite(laserPin, LOW);
    small_stepper.setSpeed(motorSpeed);
    small_stepper.step(-stepSize);
    stepID = i;
    delay(motorDelay);
    digitalWrite(laserPin, HIGH);
    delay(laserDelay);
    light = analogRead(lightPin);
    //    if (light > threshold) {
    //      parsePosition();
    //    } else {
    //      noteOn(0x90, 0x1E, 0x00);
    //    }
    Serial.print("ID: ");
    Serial.print(stepID);
    Serial.print(" Value: ");
    Serial.println(light);
  }
  // delay(2000);

}/* --(end main loop )-- */

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

/* ( THE END ) */


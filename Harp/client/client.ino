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
    Serial.print(i);
    Serial.print(',');
    Serial.print(analogRead(0));
    Serial.println(',');
  }
}

int note9 = 0x61;
int note8 = 0x63;
int note7 = 0x64;
int note6 = 0x66;
int note5 = 0x68;
int note4 = 0x70;
int note3 = 0x71;
int note2 = 0x40;
int note1 = 0x47;

int stepID;

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  // Nothing  (Stepper Library sets pins as outputs)
  Serial.begin(115200);
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
  for (int i = 2; i < 2; i++) {
    stepID = i + 1;
    if(analogRead(i) < 400) {
      parsePosition();
    } else {
      noteOn(0x90, note1, 0x00);
    }
    delay(100);
  }
}/* --(end main loop )-- */

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}


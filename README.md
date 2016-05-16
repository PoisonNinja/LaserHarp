# Laser Harp
Code for creating a laser harp (school project)

# Setup
Only supported on Ubuntu/Debian for now!
`./setup.sh`

# MidiTest
Hook up the Arduino to the computer, and flash the code. On the computer, run the following: `./connect.sh`

You should hear a piano scale going up on your computer

# MidiLEDSensor
Wire a LED into the Arduino as follows:
* A5 to the short leg of the LED
* Resistor from the long leg to another part of the breadboard
* Breadboard/resistor to GND

Flash the code, and run `./connect.sh`. Make sure you are in a bright room, and cover the LED. You should hear a note playing. Remove your hand to stop the notes.

If you want to use a different analog port, change the LEDPORT define. To change the note, change the NOTE define. To change the delay, change the DELAY define. To change the sensitivity of the LED, change the THRESHOLD define.

# Guzheng
The code for our final project. Wiring is complicated, so you will have to ask me for the wiring diagram.

Flash the code, and run `./connect.sh`.

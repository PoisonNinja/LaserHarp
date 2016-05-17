# Laser Harp
Code for creating a laser harp (school project)

# Setup
Only supported on systems with apt-get for now!
`./setup.sh`

# Usage
Connect the Arduino to the computer, and flash the code. Run `./connect.sh`, and hear the sound. 

To kill the programs, in a seperate terminal window, run `./kill.sh`. Make sure that you run this before unplugging the Arduino, or else you may experience sound glitches.

# MidiTest
A small utility to test out if MIDI is working or not.

You should hear a piano scale going upwards.

# MidiLEDSensor
Test code to control MIDI using a LED as a light sensor.

Wire a LED into the Arduino as follows:
* A5 to the short leg of the LED
* Resistor from the long leg to another part of the breadboard
* Breadboard/resistor to GND

Make sure you are in a bright room, and cover the LED. You should a piano tone.

If you want to use a different analog port, change the LEDPORT define. To change the note, change the NOTE define. To change the delay, change the DELAY define. To change the sensitivity of the LED, change the THRESHOLD define.

# MotorLaser
Code for the failed frameless harp idea. Currently is able to pulse the laser on and off in sync with the motor, drawing eight dots on the ceiling, and also has some code for reading detected sensor values. If you have a strong enough laser, this may work for you.

Wiring diagrams will have to be figured out by yourself, because I lost the diagrams.

Expected output is that it should play a note corresponding to the beam being cut.

# Guzheng
The code for our final project. The harp looks like the Chinese Guzheng, and was mainly inspired by it. It works well (assuming you built correctly), and has very little issues. It does have some latency, but it's very small.

A basic wiring diagram is available in the Guzheng folder, but it is incomplete, and you will have to figure out the rest of it.

Expected output is that it should play a note corresponding to the beam being cut.

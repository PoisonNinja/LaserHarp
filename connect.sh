#!/bin/bash

ttymidi -s /dev/ttyACM0 -v -n Arduino -b 115200 &
sleep 1
timidity -iA &
sleep 1
aconnect 128:0 129:0

#!/bin/bash

sudo apt-get install -fy timidity libasound2-dev arduino arduino-core
wget http://www.varal.org/ttymidi/ttymidi.tar.gz
tar xvf ttymidi.tar.gz
cd ttymidi
patch < ../ttymidi.patch
make
sudo cp ttymidi /usr/local/bin
cd ../
rm ttymidi/ -rf ttymidi.tar.gz

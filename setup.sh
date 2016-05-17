#!/bin/bash

function bail() {
    echo "An error occurred. Please check the messages to see what went wrong"
    exit 1
}

sudo apt-get install -fy timidity libasound2-dev arduino arduino-core || bail
wget http://www.varal.org/ttymidi/ttymidi.tar.gz || bail
tar xvf ttymidi.tar.gz || bail
cd ttymidi || bail
patch < ../ttymidi.patch || bail
make || bail
sudo cp ttymidi /usr/local/bin || bail
cd ../ 
rm ttymidi/ -rf ttymidi.tar.gz

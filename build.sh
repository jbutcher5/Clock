#!/usr/bin/env sh

arduino-cli compile -b arduino:avr:uno Clock.ino
arduino-cli upload -b arduino:avr:uno Clock.ino -p /dev/ttyACM0

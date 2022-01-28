Created by Chase A. Wood - 11/17/2020

Summary: This code controls a single ESP8266 and allows for two
unique waveforms to be generated without delays to one another.

REQUIREMENT: "arduino-timer" package by Michael Contreras must be installed. v2.2.0 used. Available: https://github.com/contrem/arduino-timer

Operation:
The program is initialized with default parameters shown below
and begins outputting waveforms immediately:

   Waveform 1: pulsewidth = 100 ms and period = 500 ms
   Waveform 2: pulsewidth = 400 ms and period = 1000 ms

Each iteration of the main loop:
 -Check for incoming serial data
 -Timers are incremented.

When new data arrives, the parsing function "newValues" first checks
that the format is correct (since MCU cannot handle exceptions), then
checks that data is in the correct format. Remember that data should
be in the following format:
   
   pulseWidthR1,periodR1,pulseWidthR2,periodR2

The MCU will check that period is larger than the pulsewidth for both
channels. If the opposite is the case, then the values will be swapped
to avoid a situation where you accidentally enter a > 100% duty cycle
mode of operation. This should not be an issue for this latest
version of MCU code, but the code remains as an added safety feature
if any data is to be transferred manually.

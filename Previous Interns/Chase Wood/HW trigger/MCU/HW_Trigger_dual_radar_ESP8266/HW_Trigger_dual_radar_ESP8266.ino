/*
 * Created by Chase A. Wood - 11/17/2020
 * 
 * Summary: This code controls a single ESP8266 and allows for two
 * unique waveforms to be generated without delays to one another.
 * 
 * REQUIREMENT: "arduino-timer" package by Michael Contreras must be installed. v2.2.0 used here.
 *                              https://github.com/contrem/arduino-timer
 * 
 * Operation:
 * The program is initialized with default parameters shown below
 * and begins outputting waveforms immediately:
 * 
 *    Waveform 1: pulsewidth = 100 ms and period = 500 ms
 *    Waveform 2: pulsewidth = 400 ms and period = 1000 ms
 * 
 * Each iteration of the main loop:
 *  -Check for incoming serial data
 *  -Timers are incremented.
 * 
 * When new data arrives, the parsing function "newValues" first checks
 * that the format is correct (since MCU cannot handle exceptions), then
 * checks that data is in the correct format. Remember that data should
 * be in the following format:
 *    
 *    pulseWidthR1,periodR1,pulseWidthR2,periodR2
 * 
 * The MCU will check that period is larger than the pulsewidth for both
 * channels. If the opposite is the case, then the values will be swapped
 * to avoid a situation where you accidentally enter a > 100% duty cycle
 * mode of operation. This should not be an issue for this latest
 * version of MCU code, but the code remains as an added safety feature
 * if any data is to be transferred manually.
 */

#include <arduino-timer.h>

#define signalOutR1 5 //pin D1 == pin GPIO5
#define signalOutR2 4 //pin D2 == pin GPIO4

//Global variables
double pulseWidthR1 = 100;         //ms
double periodR1 = 500;             //ms
double pulseWidthR2 = 400;         //ms
double periodR2 = 1000;            //ms
bool result;

//Timers
auto timer1 = timer_create_default();
auto timer2 = timer_create_default();

void setup() {
  Serial.begin(115200);
  pinMode(signalOutR1, OUTPUT);
  pinMode(signalOutR2, OUTPUT);
  timer1.in(periodR1, pulse1High);
  timer2.in(periodR2, pulse2High);
}

void loop() {
  //checking for new data incoming
  if(Serial.available()) {
    digitalWrite(signalOutR1, LOW);
    result = newValues(Serial.readStringUntil('\n'));
    Serial.flush();
    if (result == true) {
      Serial.println("Signal changed successfully, new values:");
      Serial.println("========================================");
      Serial.print("R1 pulse: ");
      Serial.println(pulseWidthR1);
      Serial.print("R1 period: ");
      Serial.println(periodR1);
      Serial.print("R2 pulse: ");
      Serial.println(pulseWidthR2);
      Serial.print("R2 period: ");
      Serial.println(periodR2);
    }
    else
      Serial.println("Error: Invalid data sent");
  }
  //increment both timers
  timer1.tick();
  timer2.tick();
}

bool pulse1High(void *) {
  digitalWrite(signalOutR1,HIGH);
  timer1.in(pulseWidthR1,pulse1Low);
  return true;
}

bool pulse1Low(void *) {
  digitalWrite(signalOutR1,LOW);
  timer1.in(periodR1-pulseWidthR1,pulse1High);
  return true;
}

bool pulse2High(void *) {
  digitalWrite(signalOutR2,HIGH);
  timer2.in(pulseWidthR2,pulse2Low);
  return true;
}

bool pulse2Low(void *) {
  digitalWrite(signalOutR2,LOW);
  timer2.in(periodR2-pulseWidthR2,pulse2High);
  return true;
}

bool newValues(String str) {
  int cnt = 0;
  //Arduino does not use exceptions. Must verify data format is correct.
  for(int i = 0; i < str.length(); i++) {
    if(str[i] == ',') {
      cnt++;
    }
  }
  Serial.println(str);
  //Data format is: pulseWidthR1,periodR1,pulseWidthR2,periodR2
  if (cnt == 3) {
    
    int idx0 = str.indexOf(',');
    int idx1 = str.indexOf(',',idx0 + 1);
    int idx2 = str.indexOf(',',idx1 + 1);
    
    double pulseWidthR1Temp = str.substring(0,idx0).toInt();
    double periodR1Temp = str.substring(idx0+1,idx1).toInt();
    double pulseWidthR2Temp = str.substring(idx1+1,idx2).toInt();
    double periodR2Temp = str.substring(idx2+1).toInt();

    //These checks should never be encountered unless you are sending to this mcu manually...
    if(pulseWidthR1Temp > periodR1Temp) {
      //Invalid config. to avoid MCU reset, swap variables before programming
      pulseWidthR1 = periodR1Temp;
      periodR1 = pulseWidthR1Temp;
      Serial.println("Warning: Parameters for pulse 1 sent in incorrect order. Values have been swapped to correct order.");
    }
    else {
      pulseWidthR1 = pulseWidthR1Temp;
      periodR1 = periodR1Temp;
    }
    if(pulseWidthR2Temp > periodR2Temp) {
      //Invalid config. to avoid MCU reset, swap variables before programming
      pulseWidthR2 = periodR2Temp;
      periodR2 = pulseWidthR2Temp;
      Serial.println("Warning: Parameters for pulse 2 sent in incorrect order. Values have been swapped to correct order.");
    }
    else {
      pulseWidthR2 = pulseWidthR2Temp;
      periodR2 = periodR2Temp;
    }
    return true;
  }
  return false;
}

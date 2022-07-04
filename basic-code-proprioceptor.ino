#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;
unsigned long timer = 0;
unsigned long oldtimer = 0;
int timelimit = 120000;
int step = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("DRV test");
  drv.begin();
  
  drv.selectLibrary(1);
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG);
  
  oldtimer = millis(); 
}

uint8_t effect = 1;

void loop() {
//  Serial.print("Effect #"); Serial.println(effect);


  // set the effect to playç
  switch(step){
    case 0:  
      drv.setWaveform(0, 82);  // play effect 
      drv.setWaveform(1, 0);       // end waveform
      drv.go(); // play the effect!
      step = 1;
      break;
    case 1:
      timer = millis() - oldtimer;
      drv.setWaveform(0, 64);  // play effect 
      drv.setWaveform(1, 0);       // end waveform
      drv.go(); // play the effect!
      if (timer > timelimit)
      {
        oldtimer = millis();
        step = 2;
      }
      break;
    case 2:
      timer = millis() - oldtimer;
      drv.setWaveform(0, 66);  // play effect 
      drv.setWaveform(1, 0);       // end waveform
      drv.go(); // play the effect!
      if (timer > timelimit)
      {
        oldtimer = millis();
        step = 0;
      }
      break;
    default:
    break;
  }

  // wait a bit
  //delay(10);
}

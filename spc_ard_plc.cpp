/*
  spc_ard_plc.cpp - Library for ARDUINO PLC
  Created by h.bendali, ... 4, 2020.
  Released into the public domain.
*/
#include "Arduino.h"
#include "spc_ard_plc.h"
#include <Wire.h> // for I2C components

void SPC_ARD_PLC::SPC_ARD_PLC(){
  Wire.begin();
  Serial.begin(9600);

#ifdef SPC_ARD_PLC_A10
  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);
  pinMode(RL3, OUTPUT);
  pinMode(RL4, OUTPUT);

  pinMode(DI1, INPUT);
  pinMode(DI2, INPUT);
  pinMode(DI3, INPUT);
  pinMode(DI4, INPUT);
  pinMode(DI5, INPUT);
  pinMode(DI6, INPUT);

  pinMode(AN1, INPUT);
  pinMode(AN2, INPUT);

  pinMode(INT, INPUT);
#endif

}

byte SPC_ARD_PLC::extRead(int i){
  Wire.requestFrom(extAdr[i], 1, true);
  extReg[i] = Wire.read();             // receive a byte as character
  return extReg[i];
}

void SPC_ARD_PLC::extWrite(int i, int value){
  Wire.beginTransmission(extAdr[i]);   // transmit to device Adr
  Wire.write(value);                   // sends value byte  
  Wire.endTransmission();              // stop transmitting
}

void SPC_ARD_PLC::extRef(){
  _extI++;
  if (_extI >= (sizeof(extAdr) / sizeof(extAdr[0]))){
    _extI=0;
  }
  extRead(_extI);
}


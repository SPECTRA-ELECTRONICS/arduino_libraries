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

void SPC_ARD_PLC::extInit(byte extAddr, byte model){
  if (model == 1){          // A10_8DI_6RO
    extWrite(extAddr, MCP23017_IODIRA, 0xff); // all for INPUT
  	extWrite(extAddr, MCP23017_IODIRB, 0xc0); // D0..D5 as OUTPUT, D6..D7 as OUTPUT  
  }else if (model == 2){    // A10_8DI_8RO
    extWrite(extAddr, MCP23017_IODIRA, 0xff); // all for INPUT
  	extWrite(extAddr, MCP23017_IODIRB, 0x00); // D0..D5 as OUTPUT, D6..D7 as OUTPUT  
  }else if (model == 3){    // A10_16DI
    extWrite(extAddr, MCP23017_IODIRA, 0xff); // all for INPUT
  	extWrite(extAddr, MCP23017_IODIRB, 0xff); // D0..D5 as OUTPUT, D6..D7 as OUTPUT  
  }else if (model == 4){    // A10_16RO
    extWrite(extAddr, MCP23017_IODIRA, 0x00); // all for INPUT
  	extWrite(extAddr, MCP23017_IODIRB, 0x00); // D0..D5 as OUTPUT, D6..D7 as OUTPUT  
  }
}

byte SPC_ARD_PLC::extRead(byte extAddr, byte regAddr){
  if (regAddr == 'A' || regAddr == 'B'){
    regAddr = MCP23017_GPIOA + regAddr -'A';
  }
	// read the current GPIO output latches
	Wire.beginTransmission(MCP23017_ADDRESS | extAddr);
	Wire.write(regAddr);
	Wire.endTransmission();
	Wire.requestFrom(MCP23017_ADDRESS | extAddr, 1);
	return Wire.read();
}

byte SPC_ARD_PLC::extReadPin(byte extAddr, byte regAddr, byte pin){
  return (extRead(extAddr, regAddr)>> pin) & 1;
}

void SPC_ARD_PLC::extWrite(byte extAddr, byte regAddr, byte regValue){
  if (regAddr == 'A' || regAddr == 'B'){
    regAddr = MCP23017_GPIOA + regAddr -'A';
  }
  // Write the register
	Wire.beginTransmission(MCP23017_ADDRESS | extAddr);
	Wire.write(regAddr);
	Wire.write(regValue);
	Wire.endTransmission();
}

void SPC_ARD_PLC::extWritePin(byte extAddr, byte regAddr, byte pin, byte pinValue){
  if (regAddr == 'A' || regAddr == 'B'){
    regAddr = MCP23017_OLATA + regAddr -'A';
  }
  // read the current GPIO output latches
	uint8_t regValue = extRead(extAddr, regAddr);
  // set the value for the particular bit
	bitWrite(regValue,pin,pinValue);
  extWrite(extAddr, regAddr, regValue);
}

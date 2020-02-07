/*
  spc_ard_plc.h - Library for ARDUINO PLC
  Created by h.bendali, ... 4, 2020.
  Released into the public domain.
*/
#ifndef SPC_ARD_PLC_h
#define SPC_ARD_PLC_h

#include "Arduino.h"

#define A10_8DI_6RO 1
#define A10_8DI_8RO 2
#define A10_16DI    3
#define A10_16RO    4

#define MCP23017_ADDRESS 0x20
// registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14
// -
#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15
// -
#define MCP23017_INT_ERR 255


#define _ON(pin)    digitalWrite(pin, HIGH)
#define _OFF(pin)   digitalWrite(pin, LOW)

class SPC_ARD_PLC
{
  public:
    void SPC_ARD_PLC();
    
    void extInit(byte extAddr, byte model);
    byte extRead(byte extAddr, byte extPort);
    byte extReadPin(byte extAddr, byte regAddr, byte pin);
    void extWrite(byte extAddr, byte regAddr, byte regValue);
    void extWritePin(byte extAddr, byte regAddr, byte pin, byte pinValue);
};

#endif

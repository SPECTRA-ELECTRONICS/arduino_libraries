/*
  spc_ard_plc.h - Library for ARDUINO PLC
  Created by h.bendali, ... 4, 2020.
  Released into the public domain.
*/
#ifndef SPC_ARD_PLC_h
#define SPC_ARD_PLC_h

#include "Arduino.h"

#define _ON(pin)    digitalWrite(pin, HIGH)
#define _OFF(pin)   digitalWrite(pin, LOW)

class SPC_ARD_PLC
{
  public:
    void SPC_ARD_PLC();
    
    byte extAdr[];
    byte extReg[];
    byte extRead(unsigned char i);
    void extWrite(int i, int value);
    void extRef();
  private:
    byte _extAdr=0;
    byte _plc=0;
};

#endif

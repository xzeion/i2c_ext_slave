#ifndef WireExtenderS_h
#define WireExtenderS_h
#include <Arduino.h>
#include <Wire.h>

class WireExtenderS{
    public:
        void begin(int addr);
        #define REGISTER(n,name,type) type name;
        #include "test.reg"
        #undef REGISTER

};

extern WireExtenderS weSlave;

#endif

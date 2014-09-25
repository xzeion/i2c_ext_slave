#ifndef WireExtenderS_h
#define WireExtenderS_h
#include <Arduino.h>
#include <Wire.h>

class WireExtenderS{
    public:
        WireExtenderS();
        ~WireExtenderS();
        void parse();
        void register_write();
        void register_select();    


};
#endif

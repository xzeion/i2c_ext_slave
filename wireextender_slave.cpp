//=================================
/* wireExtender_slave.cpp - Extends the wire.h library to allow for
multipul virtual registers in a single i2c device.
By Brian Gratton and James Bliss 07/27/14*/
//=================================

#include <Arduino.h>
#include <Wire.h>
#include <wireextender_slave.h>

int i2c_addr = 2;
int reg = 0;

WireExtenderS::WireExtenderS(){
    Wire.begin(i2c_addr);
    //Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
    //set var to determine device type
}

WireExtenderS::~WireExtenderS(){}

//---------------------------
typedef union {
    uint8_t bytes[sizeof(uint32_t)];
    uint8_t int8;
    uint16_t int16;
    uint32_t int32;
    double floatingPoint;
} message;
//---------------------------

void WireExtenderS::requestEvent(){ // write selected buffer to wire
    switch(reg){
    case 1:
       // Wire.write(message.int8);
    break;

    case 2:
       // Wire.write(message.int16);
    break;
    
    case 3:
       // Wire.write(message.int32);
    break;

    case 4:
       // Wire.write(message.floatingPoint);
    break;
    }
}


void WireExtenderS::receiveEvent(){ // take data in from wire
    message buffer;
    for(int i; i>2; i++){
        reg[i] = Wire.read();
    }

    uint8_t r;
    for(r; Wire.available(); r++){
        buffer.bytes[r] = Wire.read();
    }

}


void WireExtenderS::parse(){
    // Parse the data
    // 
}

void WireExtenderS::register_write(){
        
}

void WireExtenderS::register_select(){
      
}

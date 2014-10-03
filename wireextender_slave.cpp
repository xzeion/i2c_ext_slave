//=================================
/* wireExtender_slave.cpp - Extends the wire.h library to allow for
multipul virtual registers in a single i2c device.
By Brian Gratton and James Bliss 07/27/14*/
//=================================

#include <Arduino.h>
#include <Wire.h>
#include <wireextender_slave.h>

void requestEvent(void);
void receiveEvent(int);

WireExtenderS weSlave;

void WireExtenderS::begin(int addr){
    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
    //set var to determine device type
}




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


typedef union {
    uint8_t bytes[sizeof(double)];
    uint8_t val_uint8_t;
    uint16_t val_uint16_t;
    uint32_t val_uint32_t;
    double val_double;
} message;

typedef union {
    uint8_t bytes[sizeof(uint16_t)];
    uint16_t value;
} reg_buff;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

reg_buff reg_select;

void requestEvent(){
     
    message data_pass;

    switch(reg_select.value){
    #define REGISTER(n,name,type)\
    case n:\
        data_pass.val_##type = weSlave.name;\
        Wire.write(data_pass.bytes,sizeof(type));\
    break;
    #include "test.reg"
    #undef REGISTER

    }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void receiveEvent(int numBytes){ // take data in from wire

    for(size_t i; i<sizeof(uint16_t); i++){
      reg_select.bytes[i] = Wire.read();
    }
    Serial.println(reg_select.value); 
    
}





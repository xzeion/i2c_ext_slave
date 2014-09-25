//=================================
/* wireExtender_slave.cpp - Extends the wire.h library to allow for
multipul virtual registers in a single i2c device.
By Brian Gratton and James Bliss 07/27/14*/
//=================================

#include <Arduino.h>
#include <Wire.h>
#include <wireextender_slave.h>

int i2c_addr = 2;
int reg = 1;

void requestEvent(void);
void receiveEvent(int);

WireExtenderS::WireExtenderS(){
    Wire.begin(i2c_addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
    //set var to determine device type
}

WireExtenderS::~WireExtenderS(){}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

uint8_t message_8;

typedef union {
    uint8_t bytes[sizeof(uint16_t)];
    uint16_t int16;
} message_16;

typedef union {
    uint8_t bytes[sizeof(uint32_t)];
    uint32_t int32;
} message_32;

typedef union {
    uint8_t bytes[sizeof(double)];
    double floatingPoint;
} message_float;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void requestEvent(){ // write selected buffer to wire
    
    switch(reg){
    case 1:
        Wire.write((const char*)message_8,1);
    break;

    case 2:
        message_16 buffer_16;
        buffer_16.int16 = 161616;
        Wire.write((const char*)buffer_16.bytes,2);
    break;

    case 3:
        message_32 buffer_32;
        buffer_16.int16 = 32323232;
        Wire.write((const char*)buffer_16.bytes,4);
    break;

    case 4:
        message_float buffer_f;
        buffer_f.floatingPoint = 3.14;
        Wire.write((const char*)buffer_f.bytes,5);
    break;
    }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
typedef union {
    uint8_t bytes[sizeof(uint16_t)];
    uint16_t int16;
} regbuff;

void receiveEvent(int numBytes){ // take data in from wire
   // regbuff reg_num;
   // message buffer;

   /* for(int i; i>2; i++){
        reg_num.bytes[i] = Wire.read();
    }
    
    */
//TODO:If the wire is still Avialable then read in the message and write it to the register recieved
    char bytes[6];
    for(int r; r<6; r++){
       bytes[r] = Wire.read();
    }
    Serial.print(bytes);
    //call to function to decode message here and set registers as needed ect.
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void WireExtenderS::parse(){
    // Parse the data
    // 
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void WireExtenderS::register_write(){
        
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void WireExtenderS::register_select(){
      
}






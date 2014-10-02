//=================================
/* wireExtender_slave.cpp - Extends the wire.h library to allow for
multipul virtual registers in a single i2c device.
By Brian Gratton and James Bliss 07/27/14*/
//=================================

#include <Arduino.h>
#include <Wire.h>
#include <wireextender_slave.h>

int i2c_addr = 2;
int type_select = 0;

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

void requestEvent(){
    // Writes the selected message buffer to the wire
    // Recieve event always happens first to select the register
    switch(type_select){
    case 1:
        message_8 = 5;
        Wire.write(&message_8,sizeof(uint8_t));
    break;

    case 2:
        message_16 buffer_16;
        buffer_16.int16 = 16161;
        Wire.write((const char*)buffer_16.bytes,sizeof(uint16_t));
    break;

    case 3:
        message_32 buffer_32;
        buffer_32.int32 = 32323232;
        Wire.write((const char*)buffer_32.bytes,sizeof(uint32_t));
    break;

    case 4:
        message_float buffer_f;
        buffer_f.floatingPoint = 3.14;
        Wire.write((const char*)buffer_f.bytes,sizeof(double));
    break;
    }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
typedef union {
    uint8_t bytes[sizeof(uint16_t)];
    uint16_t int16;
} type_buff;

typedef union {
  uint8_t bytes[sizeof(uint32_t)];
  uint32_t int32;
} write_buff;

void receiveEvent(int numBytes){ // take data in from wire
    type_buff ts;

    for(int i; i<sizeof(uint16_t); i++){
      ts.bytes[i] = Wire.read();
    }
    Serial.println(ts.int16);
    type_select = ts.int16;
    //call function to set the data to register then remove previous line

    write_buff wb;
    for(int r; r<Wire.available(); r++){
       wb.bytes[r] = Wire.read();
    }
    
    Serial.println(wb.int32);
    //call to function to decode message here and set registers as needed ect.
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void WireExtenderS::register_write(){
        
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void WireExtenderS::register_select(){
  // set the register to be read 
  // set type_select to selected register type
  // if write buff has data write it to selected buffer
}






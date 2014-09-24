#include <Arduino.h>
// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <wireextender_slave.h>

WireExtenderS ext;

void setup()
{
      Serial.begin(9600);
      pinMode(13,OUTPUT);
}

void loop()
{
      digitalWrite(13,HIGH);
      delay(100);
      digitalWrite(13,LOW);
      delay(100);
      Serial.println("Slave is working");       
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
//void requestEvent()
//{
//      Wire.write("hello "); // respond with message of 6 bytes
                             // as expected by master
//}

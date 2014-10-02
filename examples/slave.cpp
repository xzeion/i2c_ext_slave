#include <Arduino.h>
// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire libraryk
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

int count;
void loop()
{
     // digitalWrite(13,HIGH);
     // delay(100);
     // digitalWrite(13,LOW);
     // delay(100);
     // Serial.print("Slave is working: ");       
     // count++;
     // Serial.println(count);
}


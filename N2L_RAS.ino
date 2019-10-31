// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module
// Tested on Arduino Mega, Duemilanova, Uno, Due, Teensy, ESP-12

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
// RH_ASK driver(2000, 4, 5, 0); // ESP8266 or ESP32: do not use pin 11 or 2

int lastState = 0;
const int SWITCH_PIN = 8;

void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init()) {
         Serial.println("init failed");
    } else {
         Serial.println("transmitter initialized");
    }

    pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop()
{
    
    int switchState = !digitalRead(SWITCH_PIN);
//    if (switchState != lastState) {
      const char *msg = switchState ? "ras:1;" : "ras:0;";
      Serial.print("sending message: ");
      Serial.println(msg);
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      lastState = switchState;
//    }
    delay(200);
}

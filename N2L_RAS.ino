// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module
// Tested on Arduino Mega, Duemilanova, Uno, Due, Teensy, ESP-12

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver(2000, 8); // ESP8266 or ESP32: do not use pin 11 or 2

int ledState = 0;
const int LED_PIN = 9;

void setup()
{
    Serial.begin(9600);	// Debugging only
    if (!driver.init())
         Serial.println("init failed");

    pinMode(LED_PIN, OUTPUT);

    digitalWrite(LED_PIN, 1);
    delay(1000);
    digitalWrite(LED_PIN, ledState);
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
    	char* command = strtok((char*)buf, ":");
      char* argument = strtok(NULL, ";");

      if (strcmp(command, "ras") == 0) {
        int enabled = strcmp(argument, "1") == 0;
        if (enabled != ledState) {
          digitalWrite(LED_PIN, enabled);
          ledState = enabled;
        }
      }
    }
}

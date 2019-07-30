/*
  TinyCircuits Rotary Switch Whisker Example Sketch

  This sketch will output the integer value selected on the
  Rotary Switch Whisker.

  Written 15 July 2019
  By Hunter Hykes
  Modified N/A
  By N/A

  https://TinyCircuits.com
*/

#include <Wire.h>
#include "SH7010.h"

#define NUM_POSITIONS 10 // number of positions on rotary switch
#define ROT_PORT 0 // port 0 on whisker board
SH7010 rotary = SH7010();

const int powerPin = 4;

#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

void setup() {
  Wire.begin();

  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  
  rotary.begin();
  rotary.init();
  selectPort(ROT_PORT);
  
  SerialMonitorInterface.begin(9600);
  delay(500);
}

void loop() {
  uint8_t rotaryValue = rotary.getPosition();
  SerialMonitorInterface.println(rotaryValue);

  delay(500);
}

void selectPort(int port) {
  Wire.beginTransmission(0x70);
  Wire.write(0x04 + port);
  Wire.endTransmission();
}

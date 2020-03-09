/*
  Rotary Example
  Prints the value of the direction the rotary arrow is pointing 0-9
  to the Serial Monitor

  Written by: Laveréna Wienclaw for TinyCircuits

  https://TinyCircuits.com
*/

#include <Wire.h>
#include <Wireling.h>
#include <SX1505.h>            // For interfacing with Joystick and Rotary Switch Wirelings

// Universal Serial Monitor Config
#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

/* * * * * * * * * * Rotary * * * * * * * * * */
#define ROT_PORT 0 
TinyRotary rotary = TinyRotary(); 
uint8_t rotaryValue;

void setup() {
  Wire.begin();
  Wireling.begin();

  /* * * * * * Rotary Init * * * * */
  Wireling.selectPort(ROT_PORT); 
  rotary.begin(); 

  SerialMonitorInterface.begin(9600);
  delay(500);
}

void loop() {
  rotaryValue = rotary.getPosition();
  writeToMonitor();
}

void writeToMonitor() {
  SerialMonitorInterface.println("Rotary: " + String(rotaryValue) + "\t");
  delay(100);
}

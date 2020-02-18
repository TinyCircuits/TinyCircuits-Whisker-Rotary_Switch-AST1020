/*
  TinyCircuits Rotary Switch/Joystick Wireling Example Sketch

  This sketch will output the integer value selected on the
  Rotary Switch Wireling along with the directional input
  from the Joystick Wireling.

  Written July 2019
  By Hunter Hykes
  Modified Feb 2020
  By Laveréna Wienclaw

  https://TinyCircuits.com
*/

#include <Wire.h>
#include <Wireling.h>
#include <TinierScreen.h>       // For interfacing with the 0.42" OLED
#include <TinyBuffer.h>         // For building a screen buffer for the 0.42" OLED
#include "font.h"
#include "SX1505.h"             // For interfacing with Joystick and Rotary Switch Wirelings

// Universal Serial Monitor Config
#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

#define USE_OLED true // set true if using 0.42" OLED to echo input, false if using Serial Monitor

/* * * * * * * * * * Rotary * * * * * * * * * */
#define ROT_PORT 0 
TinyRotary rotary = TinyRotary(); 
uint8_t rotaryValue;

/* * * * * * * * * * Joystick * * * * * * * * * */
#define JS_PORT 1 
TinyJoystick joystick = TinyJoystick(); 

/* * * * * * * * * * 0.42" OLED * * * * * * * * * */
#define OLED_PORT 3 
#define OLED_RST (uint8_t) A3 // OLED reset line, matches port number
TinierScreen display042 = TinierScreen(OLED042);
TinyBuffer screenBuffer042 = TinyBuffer(72, 40, colorDepth1BPP);

void setup() {
  Wire.begin();
  Wireling.begin();

  /* * * * * * Screen Init * * * * */
  pinMode(OLED_RST, OUTPUT);
  screenBuffer042.clear();
  digitalWrite(OLED_RST, LOW);
  delay(1);
  digitalWrite(OLED_RST, HIGH);
  Wireling.selectPort(OLED_PORT);
  display042.begin();
  Wire.setClock(1000000);
  screenBuffer042.setFont(thinPixel7_10ptFontInfo);

  /* * * * * * Rotary Init * * * * */
  Wireling.selectPort(ROT_PORT); 
  rotary.begin(); 

  /* * * * * * Joystick Init * * * * */
  Wireling.selectPort(JS_PORT); 
  joystick.begin(); 
  
  SerialMonitorInterface.begin(9600);
  delay(500);
}

void loop() {
  // Read Rotary
  Wireling.selectPort(ROT_PORT);
  rotaryValue = rotary.getPosition();

  // Read Joystick
  Wireling.selectPort(JS_PORT);
  joystick.getPosition();

  if(USE_OLED) {
    // Write the screen buffer
    Wireling.selectPort(OLED_PORT); // select the Wireling screen port
    screenBuffer042.clear();        // clear old screen contents
    writeRotaryNum();    
    writeJoystickPos();       
    display042.writeBuffer(screenBuffer042.getBuffer(), screenBuffer042.getBufferSize()); // write buffer to the screen
  } else {
    writeToMonitor();
  }
}

int x, y;
void writeRotaryNum() {
//  screenBuffer042.setCursor(x = 10, y = 10);
  screenBuffer042.setCursor(x = 35, y = 15);
  screenBuffer042.print(String(rotaryValue));
}

void writeJoystickPos() {
  if(joystick.up) {
    screenBuffer042.setCursor(x = 35, y = 5);
    screenBuffer042.print("^");
  }
  if(joystick.down) {
    screenBuffer042.setCursor(x = 35, y = 25);
    screenBuffer042.print("v");
  }
  if(joystick.left) {
    screenBuffer042.setCursor(x = 25, y = 15);
    screenBuffer042.print("<");
  }
  if(joystick.right) {
    screenBuffer042.setCursor(x = 47, y = 15);
    screenBuffer042.print(">");
  }
}

void writeToMonitor() {
  SerialMonitorInterface.print("Rotary: " + String(rotaryValue) + "\t");
  
  if(joystick.up) {
    SerialMonitorInterface.print("UP\t");
  }
  else if(joystick.down) {
    SerialMonitorInterface.print("DOWN\t");
  }
  else if(joystick.left) {
    SerialMonitorInterface.print("LEFT\t");
  }
  else if(joystick.right) {
    SerialMonitorInterface.print("RIGHT\t");
  }
  SerialMonitorInterface.println();
  delay(100);
}

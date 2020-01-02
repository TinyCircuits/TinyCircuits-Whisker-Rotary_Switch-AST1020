/*
  TinyCircuits Rotary Switch/Joystick Wireling Example Sketch

  This sketch will output the integer value selected on the
  Rotary Switch Wireling along with the directional input
  from the Joystick Wireling.

  Written 15 July 2019
  By Hunter Hykes
  Modified 01/02/2020
  By Hunter Hykes

  https://TinyCircuits.com
*/

#include <Wire.h>
#include <Wireling.h>
#include <TinierScreen.h>       // For interfacing with the 0.42" OLED
#include <TinyBuffer.h>         // For building a screen buffer for the 0.42" OLED
#include "font.h"
#include "WirelingInputs.h"     // For interfacing with Joystick and Rotary Switch Wirelings

// Universal Serial Monitor Config
#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

#define USE_OLED true // set true if using 0.42" OLED to echo input, false if using Serial Monitor

/* * * * * * * * * * Rotary * * * * * * * * * */
#define ROT_PORT 0 // port 0 on wireling board
TinyRotary rotary = TinyRotary(); // create new TinyRotary object
uint8_t rotaryValue;

/* * * * * * * * * * Joystick * * * * * * * * * */
#define JS_PORT 1 // port 1 on wireling board
TinyJoystick joystick = TinyJoystick(); // create new TinyJoystick object

/* * * * * * * * * * 0.42" OLED * * * * * * * * * */
#define OLED_PORT 3 // use Port 0 for screen
#define OLED_RST (uint8_t) A3 //OLED reset line
TinierScreen display042 = TinierScreen(OLED042);
TinyBuffer screenBuffer042 = TinyBuffer(72, 40, colorDepth1BPP);

void setup() {
  Wire.begin();
  Wireling.begin();

  /* * * * * * Screen Stuff * * * * */
  pinMode(OLED_RST, OUTPUT);
  screenBuffer042.clear();
  digitalWrite(OLED_RST, LOW);
  delay(1);
  digitalWrite(OLED_RST, HIGH);
  Wireling.selectPort(OLED_PORT);
  display042.begin();
  Wire.setClock(1000000);
  screenBuffer042.setFont(thinPixel7_10ptFontInfo);

  /* * * * * * Rotary Stuff * * * * */
  Wireling.selectPort(ROT_PORT); // select the Rotary Switch Wireling port
  rotary.begin(); // begin communications with rotary switch I/O expander
  rotary.init(); // initialize I/O expander

  /* * * * * * Joystick Stuff * * * * */
  Wireling.selectPort(JS_PORT); // select the Rotary Switch Wireling port
  joystick.begin(); // begin communications with rotary switch I/O expander
  joystick.init(); // initialize I/O expander
  
  SerialMonitorInterface.begin(9600);
  delay(500);
}

void loop() {
  // get rotary switch data
  Wireling.selectPort(ROT_PORT);
  rotaryValue = rotary.getPosition();

  // get joystick data
  Wireling.selectPort(JS_PORT);
  joystick.getPosition();

  if(USE_OLED) {
    // write the screen buffer
    Wireling.selectPort(OLED_PORT); // select the Wireling screen port
    screenBuffer042.clear();        // clear old screen contents
    writeNum();                     // add rotary switch number to buffer
    writePos();                     // add joystick direction to buffer
    display042.writeBuffer(screenBuffer042.getBuffer(), screenBuffer042.getBufferSize()); // write buffer to the screen
  } else {
    writeToMonitor();
  }
}

int x, y;
void writeNum() {
  screenBuffer042.setCursor(x = 10, y = 10);
  screenBuffer042.print(String(rotaryValue));
}

void writePos() {
  if(joystick.up) {
    screenBuffer042.setCursor(x = 10, y = 0);
    screenBuffer042.print("^");
  }
  if(joystick.down) {
    screenBuffer042.setCursor(x = 10, y = 20);
    screenBuffer042.print("v");
  }
  if(joystick.left) {
    screenBuffer042.setCursor(x = 0, y = 10);
    screenBuffer042.print("<");
  }
  if(joystick.right) {
    screenBuffer042.setCursor(x = 20, y = 10);
    screenBuffer042.print(">");
  }
}

void writeToMonitor() {
  SerialMonitorInterface.print("Rotary: " + String(rotaryValue) + "\t");
  
  if(joystick.up) {
    SerialMonitorInterface.print("UP\t");
  }
  if(joystick.down) {
    SerialMonitorInterface.print("DOWN\t");
  }
  if(joystick.left) {
    SerialMonitorInterface.print("LEFT\t");
  }
  if(joystick.right) {
    SerialMonitorInterface.print("RIGHT\t");
  }
  SerialMonitorInterface.println();
  delay(100);
}

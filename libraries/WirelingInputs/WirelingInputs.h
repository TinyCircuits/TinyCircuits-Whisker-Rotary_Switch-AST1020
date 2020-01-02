/*
WirelingInputs Arduino Library
Written 07/10/2019
By Hunter Hykes for TinyCircuits
Modified 01/02/2020
By Hunter Hykes

Written for use with the Rotary Switch and Joystick Wirelings
featuring the SX1505 I2C I/O Expander.
*/

/* * * * * * * * * * * * * * TinyJoystick * * * * * * * * * * * * * *
To use, declare a global instance of an TinyJoystick object,
	TinyJoystick js = TinyJoystick();

Then include the following in setup().
	js.begin();
	js.init();
	selectPort(JOYSTICK_PORT); // assign JOYSTICK_PORT to the port in use

In order to update readings from joystick, call getPosition() to read the
most recent data and then assess up, down, left, and right (true when pressed).
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * TinyRotary * * * * * * * * * * * * * * *
To use, declare a global instance of an TinyJoystick object,
	TinyRotary rotary = TinyRotary();

Then include the following in setup().
	rotary.begin();
	rotary.init();
	selectPort(ROTARY_PORT); // assign ROTARY_PORT to the port in use

In order to update readings from rotary switch, call getPosition() to read the
number 0-9 on the switch.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef WIRELINGINPUTS_h
#define WIRELINGINPUTS_h

// Definitions for SX1505 I2C I/O Expander
#define SX1505_I2CADDR			    0x20

#define SX1505_REG_DATA			    0x00
#define SX1505_REGDIR			      0x01	// 0 -> output, 1 -> input
#define SX1505_REG_PULLUP		    0x02 	// 0 -> pull-up disabled, 1 -> pull-up enabled
#define SX1505_REG_PULLDOWN		  0x03

#define SX1505_REG_INTMASK		  0x05
#define SX1505_REG_SENSE_HI		  0x06
#define SX1505_REG_SENSE_LO		  0x07
#define SX1505_REG_INT_SRC		  0x08
#define SX1505_REG_EVENT_STATUS	0x09
#define SX1505_REG_PLD_MODE		  0x10
#define SX1505_REG_PLD_T0		    0x11
#define SX1505_REG_PLD_T1		    0x12
#define SX1505_REG_PLD_T2		    0x13
#define SX1505_REG_PLD_T3		    0x14
#define SX1505_REG_PLD_T4		    0x15

// Definitions of direction bits
// NOTE: UP is the direction if pushing the
// joystick towards the whisker connector.
#define JOYSTICK_UP			  0x02 	// 185 raw
#define JOYSTICK_DOWN		  0x80 	// 59  raw
#define JOYSTICK_LEFT		  0x01 	// 186 raw
#define JOYSTICK_RIGHT		0x08 	// 179 raw
#define JOYSTICK_PRESS		0x10 	// 171 raw
#define JOYSTICK_NEUTRAL	0x44	// 187 raw

#include <inttypes.h>

class SH7010 {
public:
	SH7010(void);
	int begin(void);
	void write(uint8_t, uint8_t);
	uint8_t read(uint8_t);
	int init(void);
	uint8_t getRegData(void);
	//uint8_t getPosition(void);

	uint8_t value;
	uint8_t debug;
	uint8_t I2Caddress = 0;
};

class TinyJoystick : public SH7010 {
public:
	TinyJoystick(void);
  	void getPosition(void);
  	uint8_t active = 0;
	uint8_t up = 0;
	uint8_t down = 0;
	uint8_t left = 0;
	uint8_t right = 0;
};

class TinyRotary : public SH7010 {
public:
	TinyRotary(void);
	uint8_t getPosition(void);
};

#endif

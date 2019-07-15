/*
SH7010 Arduino Library
Written 07/10/2019
By Hunter Hykes for TinyCircuits

Written for use with the Rotary Switch Whisker featuring the
SX1505 I2C I/O Expander and the SH7010 8-Position Rotary Switch

To use, include the following in setup()
	rotary.begin();
	rotary.init();
	selectPort(ROTARY_PORT); // assign ROTARY_PORT to the port in use

You should also include the selectPort() function:
  void selectPort(int port) {
    Wire.beginTransmission(0x70);
    Wire.write(0x04 + port);
    Wire.endTransmission();
  }
*/

#ifndef SH7010_h
#define SH7010_h

// Definitions for SX1505 I2C I/O Expander
#define SX1505_I2CADDR			0x20

#define SX1505_REG_DATA			0x00
#define SX1505_REGDIR			0x01	// 0 -> output, 1 -> input
#define SX1505_REG_PULLUP		0x02 	// 0 -> pull-up disabled, 1 -> pull-up enabled
#define SX1505_REG_PULLDOWN		0x03

#define SX1505_REG_INTMASK		0x05
#define SX1505_REG_SENSE_HI		0x06
#define SX1505_REG_SENSE_LO		0x07
#define SX1505_REG_INT_SRC		0x08
#define SX1505_REG_EVENT_STATUS	0x09
#define SX1505_REG_PLD_MODE		0x10
#define SX1505_REG_PLD_T0		0x11
#define SX1505_REG_PLD_T1		0x12
#define SX1505_REG_PLD_T2		0x13
#define SX1505_REG_PLD_T3		0x14
#define SX1505_REG_PLD_T4		0x15

#include <inttypes.h>

class SH7010 {
public:
	SH7010(void);
	int begin(void);
	void write(uint8_t, uint8_t);
	uint8_t read(uint8_t);
	int init(void);
	uint8_t getRegData(void);
	uint8_t getPosition(void);

	uint8_t value;
	uint8_t debug;
	uint8_t I2Caddress = 0;
};

#endif

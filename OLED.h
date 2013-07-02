/*
 Arduino Library for 4D Systems uOLED-160-G1 (compatible with any other 4D System uOLED screen)
 go to http://www.4dsystems.com.au/product/1/3/4D_Intelligent_Display_Modules/uOLED_160_G2/ for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created July 2013
 by Jonathan Ruiz de Garibay

 */ 

#ifndef UOLED_h
#define UOLED_h

#include "Arduino.h"

#define OLED_INITDELAYMS		1000

// commands
#define	OLED_DETECT_BAUDRATE	0x55
#define	OLED_CLEAR				0x45
#define OLED_SETBACKCOLOR		0x42
#define OLED_SETPEN				0x70
#define	OLED_PIXEL				0x50
#define	OLED_LINE				0x4C
#define	OLED_CIRCLE				0x43
#define	OLED_RECTANGLE			0x72
#define	OLED_UNFORMATTEDCHAR	0x74
#define	OLED_CHAR				0x54
#define	OLED_UNFORMATTEDSTRING	0x53
#define	OLED_STRING				0x73
// extended commands
#define OLED_EXTENDED			0x40
#define OLED_IMAGEFROMSD		0x49
// font sizes
#define	OLED_FONT5X7			0x01
#define	OLED_FONT8X8			0x02
#define	OLED_FONT8X12			0x03
// pen modes
#define OLED_SOLIDPEN			0x00
#define OLED_WIREPEN			0x01
// image colour mode
#define OLED_COLOUR8BITS		0x08
#define OLED_COLOUR16BITS		0x10
// responses
#define OLED_ACK				0x06
#define OLED_NAK 				0x15

class OLED
{
	public:
		boolean begin(uint8_t rxPin, uint8_t txPin, uint8_t resetPin, uint16_t baudRate);
		void resetDisplay();
		boolean clear();
		boolean setBackcolor(unsigned int color);
		boolean setPen(uint8_t mode);
		boolean drawPixel(uint8_t x, uint8_t y, unsigned int color);
		boolean drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, unsigned int color);
		boolean drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, unsigned int color);
		boolean drawCircle(uint8_t x, uint8_t y, uint8_t radius, unsigned int color);
		boolean drawChar(uint8_t column, uint8_t row, uint8_t myChar, unsigned int color);
		boolean drawString(uint8_t column, uint8_t row, uint8_t fontSize, char *text, unsigned int color);
		boolean drawUnformattedString(uint8_t x, uint8_t y, uint8_t width, uint8_t height, char *myText, unsigned int color);
		boolean drawUnformattedChar(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t myChar, unsigned int color);
		boolean drawImageFromSD(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t colourMode, uint32_t imageAddress);

	private:
		uint8_t _resetPin;
		byte _getResponse();
};

#endif
/*
 Arduino Library for 4D Systems uOLED-160-G1 (compatible with any other 4D System uOLED screen)
 go to http://www.4dsystems.com.au/product/1/3/4D_Intelligent_Display_Modules/uOLED_160_G2/ for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created July 2013
 by Jonathan Ruiz de Garibay

 */ 

#include "Arduino.h"
#include "OLED.h"
#include <SoftwareSerial.h>

SoftwareSerial _softSerial(0, 0);

//
// begin
//
// This library use a Software Serial so, it is necesary to specified rx and tx pin, reset pin and baudrates.
boolean OLED::begin(uint8_t rxPin, uint8_t txPin, uint8_t resetPin, uint16_t baudRate){

	//init SoftwareSerial port
	_softSerial = SoftwareSerial(rxPin, txPin);
	_softSerial.begin(baudRate);
	_softSerial.listen();
	//init reset pin
	_resetPin = resetPin;
	pinMode(_resetPin, OUTPUT);
	digitalWrite(_resetPin, HIGH);
	//reset display and send autodetect baudrate command to uOLED
	resetDisplay();  
	delay(OLED_INITDELAYMS);
	_softSerial.write(OLED_DETECT_BAUDRATE); 
	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// resetDisplay
//
// Reset the display through reset pin.
void OLED::resetDisplay(){

	//generate a reset pulse for uOLED
	digitalWrite(_resetPin, LOW);
	delay(10);                  
	digitalWrite(_resetPin, HIGH);
	delay(10); 
}

//
// clear
//
// Clear screen with the background color.
boolean OLED::clear(){

	//send command
	_softSerial.write(OLED_CLEAR);
	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// setBackground
//
// Set the background color of the screen; and draw it.
boolean OLED::setBackcolor(unsigned int color){

	//send command
	_softSerial.write(OLED_SETBACKCOLOR);

	// Color
	_softSerial.write(color >> 8);				// MSB			
	_softSerial.write(color & 0xFF);				// LSB

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// setPen
//
// Set the pen mode for some objects (rectangle, circle...) for draw wire frame objects or solid objects
boolean OLED::setPen(uint8_t mode){

	//send command
	_softSerial.write(OLED_SETPEN);

	_softSerial.write(mode);						//pen mode

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// drawPixel
//
// Draw one pixel in (x,y) position in a certain colour
boolean OLED::drawPixel(uint8_t x, uint8_t y, unsigned int color){

	//send command
	_softSerial.write(OLED_PIXEL);

	_softSerial.write(x);						// X
	_softSerial.write(y);						// Y
	// Color
	_softSerial.write(color >> 8);				// MSB			
	_softSerial.write(color & 0xFF);				// LSB

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// drawPixel
//
// Draw line from (x1,y1) to (x2,y2) in a certain colour
boolean OLED::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, unsigned int color){

	//send command
	_softSerial.write(OLED_LINE);

	_softSerial.write(x1);						// X1
	_softSerial.write(y1);						// Y1
	_softSerial.write(x2);						// X2
	_softSerial.write(y2);						// Y2
	// Color
	_softSerial.write(color >> 8);				// MSB			
	_softSerial.write(color & 0xFF);				// LSB

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// drawRectangle
//
// Draw a rectangle in (x,y) position with (width, height) size in a certain colour
boolean OLED::drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, unsigned int color){

	//send command
	_softSerial.write(OLED_RECTANGLE); 

	_softSerial.write(x);						// X1
	_softSerial.write(y);						// Y1
	_softSerial.write(x + width);					// X2
	_softSerial.write(y + height);					// Y1
	// Color
	_softSerial.write(color >> 8);				// MSB			
	_softSerial.write(color & 0xFF);				// LSB				
	
	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// drawCircle
//
// Draw a circle in (x,y) position with radius in a certain colour
boolean OLED::drawCircle(uint8_t x, uint8_t y, uint8_t radius, unsigned int color){
    
  	//send command
	_softSerial.write(OLED_CIRCLE);

	_softSerial.write(x);						// X
	_softSerial.write(y);						// Y
	_softSerial.write(radius);					// Radius
	// Color
	_softSerial.write(color >> 8);				// MSB			
	_softSerial.write(color & 0xFF);				// LSB

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// drawChar
//
// Draw a char in (column,row) position in a certain colour
boolean OLED::drawChar(uint8_t column, uint8_t row, uint8_t myChar, unsigned int color){

	//send command
	_softSerial.write(OLED_CHAR);
	
    _softSerial.write(myChar);					// Char
    _softSerial.write(column);					// Colum
    _softSerial.write(row);						// Row
	// Color
	_softSerial.write(color >> 8);				// MSB			
	_softSerial.write(color & 0xFF);				// LSB

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// drawString
//
// Draw a string text in (column,row) position with font size in a certain colour
boolean OLED::drawString(uint8_t column, uint8_t row, uint8_t fontSize, char *myText, unsigned int color){

	//send command
	_softSerial.write(OLED_STRING);
        
    _softSerial.write(column); 					// Column    
	_softSerial.write(row); 						// Row
	_softSerial.write(fontSize); 				// Font Size
	// Color
	_softSerial.write(color >> 8);				// MSB			
	_softSerial.write(color & 0xFF);				// LSB
	//text
	for (int i = 0; i < strlen(myText) ; i++){
		_softSerial.print(myText[i]);		 	// Character to write
	}
	_softSerial.write((byte)0x00); 				// String terminator (always 0x00)

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// drawUnformattedChar
//
// Draw an unformatted char in (x,y) position with (width,height) size in a certain colour
boolean OLED::drawUnformattedChar(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t myChar, unsigned int color){

	//send command
	_softSerial.write(OLED_UNFORMATTEDCHAR);
	
    _softSerial.write(myChar);					// Char
    _softSerial.write(x);						// X
    _softSerial.write(y);						// Y
	// Color
	_softSerial.write(color >> 8);				// MSB			
	_softSerial.write(color & 0xFF);				// LSB
	_softSerial.write(width);					// Width
    _softSerial.write(height);					// Height

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// drawString
//
// Draw an unformatted string text in (x,y) position, (width, height) size in a certain colour
boolean OLED::drawUnformattedString(uint8_t x, uint8_t y, uint8_t width, uint8_t height, char *myText, unsigned int color){

	//send command
	_softSerial.write(OLED_UNFORMATTEDSTRING);
        
    _softSerial.write(x); 						// Column    
	_softSerial.write(y); 						// Row
	_softSerial.write(OLED_FONT8X8); 			// Font Size
	// Color
	_softSerial.write(color >> 8);				// MSB			
	_softSerial.write(color & 0xFF);				// LSB
	_softSerial.write(width); 					// Width
	_softSerial.write(height); 					// Height
	//text
	for (int i = 0; i < strlen(myText) ; i++){
		_softSerial.print(myText[i]);		 	// Character to write
	}
	_softSerial.write((byte)0x00); 				// String terminator (always 0x00)

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// drawImageFromSD
//
// Draw an image form microSD external memory; in (x,y) position, (width, height) size, with colour mode (8 or 16 bytes) in a certain colour.
// Image address has 3 bytes and 
boolean OLED::drawImageFromSD(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t colourMode, uint32_t imageAddress){

	//send extended command
	_softSerial.write(OLED_EXTENDED);
	_softSerial.write(OLED_IMAGEFROMSD);

	_softSerial.write(x); 						// X
	_softSerial.write(y); 						// Y
	_softSerial.write(width); 					// Width
	_softSerial.write(height); 					// Height
    _softSerial.write(colourMode); 				// Color mode
	//image address
	_softSerial.write(imageAddress >> 16);		// MSB
	_softSerial.write((imageAddress >> 8) & 0xFF);
	_softSerial.write(imageAddress & 0xFF);		// LSB

	//get responser from uOLED
	if (_getResponse() == OLED_ACK)
		return true;
	else
		return false;
}

//
// _getResponse
// Wait a maximum time of 50mS to the uOLED response
byte OLED::_getResponse()
{
	byte incomingByte = OLED_NAK;
	for (int i = 0; i < 50; i++){
		if (_softSerial.available()){
			incomingByte = _softSerial.read();
			break; 
		}
		delay(1); 
	}
	return incomingByte;
}
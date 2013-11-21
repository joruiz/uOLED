/*
  RectangleInMovement
  Draw a rectagle and move it around the the screen (160pxx128px).
  
  Connections:
    uOLED TX pin to pin 5 of Arduino
    uOLED RX pin to pin 6 of Arduino
    uOLED R pin to pin 7 of Arduino

  This example code is in the public domain.
 */
 
#include <SoftwareSerial.h>
#include <OLED.h>

#define RX_PIN      5
#define TX_PIN      6
#define RESET_PIN   7
#define BAUD_RATE   57600

OLED myOled;

void setup() {

  Serial.begin(9600);
  Serial.println("Start draw figures demo:");

  if (myOled.begin(RX_PIN, TX_PIN, RESET_PIN, BAUD_RATE))
    Serial.println("uOLED ready");
  else
    Serial.println("uOLED is not ready");
}

void loop() {

  Serial.println("Init movement");
  myOled.clear();
  for(int i = -30; i <= 160; i++){
  
    myOled.drawLine(i-1, 20, i-1, 40, 0x0000);
    myOled.drawLine(i + 30, 20, i + 30, 40, 0x07E0);
    delay(5);
  }
}

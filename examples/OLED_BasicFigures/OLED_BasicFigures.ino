/*
  BasicFigures
  Draw different figures in the screen (160pxx128px).
 
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

  if (myOled.begin(RX_PIN, TX_PIN, RESET_PIN, BAUD_RATE)){
    
    Serial.println("uOLED ready");
    myOled.clear();
    Serial.println("Draw lines");
    myOled.drawLine(0, 0, 160, 128, 0x001F);
    myOled.drawLine(0, 128, 160, 0, 0xF800);
    delay(200);
    Serial.println("Draw figure with pixels");
    for (int i = 20; i < 50; i++){
      myOled.drawPixel(i, 2, 0xF800);
      myOled.drawPixel(i, i -18, 0xF800);
    }
    delay(200);
    Serial.println("Draw normal rectangle");
    myOled.setPen(OLED_WIREPEN);
    myOled.drawRectangle(5, 50, 40, 20, 0x07E0);
    myOled.setPen(OLED_SOLIDPEN);
    delay(200);
    Serial.println("Draw fill circle");
    myOled.drawCircle (80, 100, 15, 0x7000);
  }
  else
    Serial.println("uOLED is not ready");
}

void loop() {

  delay(10);
}

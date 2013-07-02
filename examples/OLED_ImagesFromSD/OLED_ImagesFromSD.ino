/*
  ImagesFromSD
  Draw two imagee form external microSD memory in the screen (160pxx128px).
 
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
    Serial.println("Draw image number 1");
    myOled.drawImageFromSD(40, 50, 22, 22, OLED_COLOUR16BITS, 0x000000);
    delay(200);
    Serial.println("Draw image number 2");
    myOled.drawImageFromSD(100, 50, 22, 22, OLED_COLOUR16BITS, 0x000002);
  }
  else
    Serial.println("uOLED is not ready");
}

void loop() {

  delay(10);
}

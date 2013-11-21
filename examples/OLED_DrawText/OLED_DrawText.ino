/*
  DrawText
  Draw diferent texts in the screen (160pxx128px).
  
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
    Serial.println("Draw START DEMO string");
    myOled.drawString(1, 1, OLED_FONT8X8, "START DEMO", 0x001F);
    delay(200);
    Serial.println("Draw X char");
    myOled.drawChar(1, 4, 'X', 0xF800);
    delay(200);
    Serial.println("Draw UNFORMAT. unformatted string");
    myOled.drawUnformattedString(5, 50, 2, 2, "UNFORMAT.", 0x07E0);
    delay(200);

    Serial.println("Draw U unformatted char");
    myOled.drawUnformattedChar(5, 80, 3, 5, 'U', 0xFFFF);
    delay(200);

  }
  else
    Serial.println("uOLED is not ready");
}

void loop() {

  delay(10);
}

/*
 *  plant_moisture_detection
 *  
 *  Authored By: Brad Beacham
 *  Date: 26/01/2016
 *  
 *  
 *  Probably not ideal code but it seems to work so far
 *  
 *  Moisture Probe consists of 2 M3 Stainless steel bolts spaced 2cm apart placed into the dirt of the plant.
 *  Using analog input A1 with a 10k pull-down resistor.
 */

 /*
  * FUTURE PLANS:
  *     - Get out of prototype stage
  *     - Add LCD to display moisture
  *     - Add LDR photo sensor to dim LCD/LED when it's dark (bright lights are annoying yo)
  *     - Add Interior/Exterior Temprature + humidity
  */

#include "FastLED.h"
#define NUM_LEDS 1
#define DATA_PIN 2 // For PL9823 LED data pin

// Define the array of leds
CRGB leds[NUM_LEDS];

int ledStartRGB = 100; //96 = red
int ledBrightness = 80; //0 - 255

void setup() {
  Serial.begin(9600); 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() { 
  // read the input on analog pin 1:
  int moistureRAW = analogRead(A1);

  // print out the value you read:
  Serial.println(moistureRAW);

  // Filthy way of changing LED colour per moisture level.  Probably a cleaner way to do this.
  /* 
   *  NOTES FOR ME SO I CAN REMEMBER WHY I DO STUFF:
   *  As LED colours seemed to be opposite of FastLED documentation (ie 96 = red when documentation says it = green)
   *  The hue value starts at 96 for red, and as the max moisture value (in this case) is 400 and i've chosen to go up in
   *  steps of 50.  I simply decrement the hue value by (ledStartRGB/(numberOfStatements)) to get a nice clean transition.
  */
  
  if (moistureRAW == 0) {
    FastLED.showColor(CHSV(ledStartRGB, 255, ledBrightness)); 
  }
  else if (moistureRAW > 0 && moistureRAW < 50) {
    FastLED.showColor(CHSV(ledStartRGB - 10.6, 255, ledBrightness));
  }  
  else if (moistureRAW > 50 && moistureRAW < 100) {
    FastLED.showColor(CHSV(ledStartRGB - 21.2, 255, ledBrightness));
  }
  else if (moistureRAW > 100 && moistureRAW < 150) {
    FastLED.showColor(CHSV(ledStartRGB - 31.8, 255, ledBrightness));
  }
  else if (moistureRAW > 150 && moistureRAW < 200) {
    FastLED.showColor(CHSV(ledStartRGB - 42.4, 255, ledBrightness));
  }
  else if (moistureRAW > 200 && moistureRAW < 250) {
    FastLED.showColor(CHSV(ledStartRGB - 53, 255, ledBrightness));
  }
  else if (moistureRAW > 250 && moistureRAW < 300) {
    FastLED.showColor(CHSV(ledStartRGB - 63.6, 255, ledBrightness));
  }
  else if (moistureRAW > 300 && moistureRAW < 350) {
    FastLED.showColor(CHSV(ledStartRGB - 74.2, 255, ledBrightness));
  }
  else if (moistureRAW > 350 && moistureRAW < 400) {
    FastLED.showColor(CHSV(ledStartRGB - 84.8, 255, ledBrightness));
  }
  else if (moistureRAW > 400) {
    FastLED.showColor(CHSV(0, 255, ledBrightness));
  }  
  delay(1000);
}

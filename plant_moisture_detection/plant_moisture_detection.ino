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
 *  
 *  Button 1: A4 (+ 10k pull-down)
 *  Button 2: A5 (+ 10k pull-down)
 */

/*
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD R/W pin to Ground 
 * LCD VO pin (pin 3) to PWM pin 9
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 */

 /*
  * FUTURE PLANS:
  *     - Get out of prototype stage
  *     - Add LCD to display moisture - DONE
  *     - Add LDR photo sensor to dim LCD/LED when it's dark (bright lights are annoying yo) - DONE
  *     - Add Interior/Exterior Temprature + humidity
  */

#include "FastLED.h"
#include <LiquidCrystal.h>

#define NUM_LEDS 1
#define DATA_PIN 7 // For PL9823 LED data pin

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define the array of leds
CRGB leds[NUM_LEDS];

int menu = 1; //default startup screen
int submenu = 1; //default submenu screen
int moistureRAW; int LDR;
int ledStartRGB = 100; //96 = red
int ledBrightness; //0 - 255

void setup() {

  // declare pin 9 to be an output:
   pinMode(9, OUTPUT);  
   analogWrite(9, 50); //This sets the controst of the LED, can remove for a resistor to gain a digital input   
   // set up the LCD's number of columns and rows: 
   lcd.begin(16, 2);
  
  Serial.begin(9600);
  pinMode(6, OUTPUT); 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() { 
  // read the input on analog pin 1:
  int moistureRAW = analogRead(A1);
  int LDR = analogRead(A0);

  if (dark(LDR) == true) {
    ledBrightness = 30;
    digitalWrite(6, LOW);
  }
  else {
    ledBrightness = 100;
    digitalWrite(6, HIGH);
  }  

  switch (menu) {
    case 1:
      MoistureDisplay(ledBrightness, moistureRAW, submenu);
      break;
    case 2:
      lcd.clear();
      lcd.print("Menu 2");
      break;
    case 3:
      lcd.clear();
      lcd.print("Menu 3");
      break;
  }
  

  if (digitalRead(18) == HIGH) {
    delay(300);
    if (menu == 3){
      menu = 0;
    }
    menu++;
  }

  if (digitalRead(19) == HIGH) {
    delay(300);
    if (submenu == 2){
      submenu = 0;
    }
    submenu++;
  }

  delay(200); 
}

void MoistureDisplay(int ledBrightness, int moisture, int menutype) {
  //Display type either 1 (bar display) or 2 (numerical display)
  // Filthy way of changing LED colour per moisture level.  Probably a cleaner way to do this.
  /* 
   *  NOTES FOR ME SO I CAN REMEMBER WHY I DO STUFF:
   *  As LED colours seemed to be opposite of FastLED documentation (ie 96 = red when documentation says it = green)
   *  The hue value starts at 96 for red, and as the max moisture value (in this case) is 400 and i've chosen to go up in
   *  steps of 50.  I simply decrement the hue value by (ledStartRGB/(numberOfStatements)) to get a nice clean transition.
  */
 
  delay(100);
  lcd.clear();
  lcd.print(" Moisture Value ");
  lcd.setCursor(0, 1);
  // lcd.print(moistureRAW);
  
  if (moisture == 0) {
    switch (menutype) {
      case 1:
        lcd.print(" |------------|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }
    FastLED.showColor(CHSV(ledStartRGB, 255, ledBrightness));     
  }
  else if (moisture > 0 && moisture < 50) {
    switch (menutype) {
      case 1:
        lcd.print(" |X-----------|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 8, 255, ledBrightness));
  }  
  else if (moisture > 50 && moisture < 100) {
    switch (menutype) {
      case 1:
        lcd.print(" |-X----------|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 16, 255, ledBrightness));
  }
  else if (moisture > 100 && moisture < 150) {
    switch (menutype) {
      case 1:
        lcd.print(" |--X---------|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 24, 255, ledBrightness));
  }
  else if (moisture > 150 && moisture < 200) {
    switch (menutype) {
      case 1:
        lcd.print(" |---X--------|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 32, 255, ledBrightness));
  }
  else if (moisture > 200 && moisture < 250) {
    switch (menutype) {
      case 1:
        lcd.print(" |----X-------|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 40, 255, ledBrightness));
  }
  else if (moisture > 250 && moisture < 300) {
    switch (menutype) {
      case 1:
        lcd.print(" |-----X------|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 48, 255, ledBrightness));
  }
  else if (moisture > 300 && moisture < 350) {
    switch (menutype) {
      case 1:
        lcd.print(" |------X-----|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 56, 255, ledBrightness));
  }  
  else if (moisture > 350 && moisture < 400) {
    switch (menutype) {
      case 1:
        lcd.print(" |-------X----|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 64, 255, ledBrightness));
  }
  else if (moisture > 400 && moisture < 450) {
    switch (menutype) {
      case 1:
        lcd.print(" |--------X---|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 72, 255, ledBrightness));
  }
  else if (moisture > 450 && moisture < 500) {
    switch (menutype) {
      case 1:
        lcd.print(" |---------X--|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 80, 255, ledBrightness));
  }
  else if (moisture > 500 && moisture < 550) {
    switch (menutype) {
      case 1:
        lcd.print(" |----------X-|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(ledStartRGB - 88, 255, ledBrightness));
  }      
  else if (moisture > 600) {
    switch (menutype) {
      case 1:
        lcd.print(" |--MOIST-AF--|");
        break;
      case 2:
        lcd.print(moisture);
        break;
    }    
    FastLED.showColor(CHSV(0, 255, ledBrightness));
  }  
}

bool dark(int LDRvalue) {
  if (LDRvalue < 400) {
    return true;
  }
  else {
    return false;
  }
}


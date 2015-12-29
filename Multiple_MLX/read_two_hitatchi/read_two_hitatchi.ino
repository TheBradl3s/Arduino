#include <i2cmaster.h>
#include <LiquidCrystal.h>

// Original code by chrisramsay (http://www.chrisramsay.co.uk/posts/2014/09/arduino-and-multiple-mlx90614-sensors/)
// Modified by TheBradl3s

// Written for Arudino Uno
// I2C Blue - A4
// I2C Green - A5
// Use 4K7 ohm pull up resistors on both with 0.1uF bridging between + & - for I2c bus

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

// Hardcoded sensor addresses, change using https://github.com/TheBradl3s/Arduino/blob/master/MLX_chag_addr/MLX_chag_addr.ino
 byte Sensor1 = 0x01;
 byte Sensor2 = 0x02;

 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

 void setup(){

  // declare pin 9 to be an output:
   pinMode(9, OUTPUT);  
   analogWrite(9, 50);   
   // set up the LCD's number of columns and rows: 
   lcd.begin(16, 2);
   
   Serial.begin(9600);
   // Initialise the i2c bus, enable pullups and then wait
   i2c_init();
   PORTC = (1 << PORTC4) | (1 << PORTC5);
 }

 void loop(){
   delay(400);
   lcd.clear();
   lcd.print("Sensor 0x01: ");
   lcd.print(ReadTemp(Sensor1<<1), 0);
   lcd.print("c");
   
   lcd.setCursor(0, 1);
   
   lcd.print("Sensor 0x02: ");
   lcd.print(ReadTemp(Sensor2<<1), 0);
   lcd.print("c");  
 }

 float ReadTemp(byte Address) {
   int data_low = 0;
   int data_high = 0;
   int pec = 0;

   i2c_start_wait(Address + I2C_WRITE);
   // Address of temp bytes
   i2c_write(0x07);
   // Read - the famous repeat start
   i2c_rep_start(Address + I2C_READ);
   // Read 1 byte and then send ack (x2)
   data_low = i2c_readAck();
   data_high = i2c_readAck();
   pec = i2c_readNak();
   i2c_stop();

   // This converts high and low bytes together and processes the temperature
   // MSB is a error bit and is ignored for temperatures
   // Zero out the data
   float temp = 0x0000;
   // This masks off the error bit of the high byte, then moves it left
   // 8 bits and adds the low byte.
   temp = (float)(((data_high & 0x007F) << 8) + data_low);
   temp = (temp * 0.02) - 273.16;
   return temp;
 }

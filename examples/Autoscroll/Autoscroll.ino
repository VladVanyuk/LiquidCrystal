/*
  LiquidCrystal Library - Autoscroll

 Demonstrates the use of a 16x2 LCD display. The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch demonstrates the use of the autoscroll()
 and noAutoscroll() functions to make new text scroll or not.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K or 100K potentiometer:
   * ends to +5V and ground
   * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi
 modified 2 Feb 2024
 by Vladislav Vanyuk

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays#autoscroll-example
 https://github.com/arduino-libraries/LiquidCrystal
*/


// choose what connection type your display is
// #define TYPE_LCD
#define TYPE_LCD_I2C

// include the library code:
#include <LiquidCrystal_Base.h>

// virtual base class pointer to an object 
LiquidCrystal_Base *lcd;

#if (defined TYPE_LCD)
// initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd_normal(rs, en, d4, d5, d6, d7);

#elif (defined TYPE_LCD_I2C)
LiquidCrystal_I2C lcd_i2c(0x27, 16, 2) //(0x27, 20, 4)
#endif

void setup() {
  Serial.begin(9600);

#ifdef TYPE_LCD
  lcd = &lcd_normal;
  Serial.println("normal");
#elif defined (TYPE_LCD_I2C)
  lcd = &lcd_i2c;
  Serial.println("i2c");
#endif
  lcd->begin(20, 4);
  lcd->clear();
}

void loop() {
  // set the cursor to (0,0):
  lcd->setCursor(0, 0);
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd->print(thisChar);
    delay(500);
  }

  // set the cursor to (16,1):
  lcd->setCursor(16, 1);
  // set the display to automatically scroll:
  lcd->autoscroll();
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd->print(thisChar);
    delay(500);
  }
  // turn off automatic scrolling
  lcd->noAutoscroll();

  // clear screen for the next loop:
  lcd->clear();
}

#include "LiquidCrystal_Base.h"

// LCD address and geometry for LCD 1602
const byte lcdAddr_2004 = 0x27;  // Typical address of I2C backpack for 1602
const byte lcdCols_2004 = 20;    // Number of characters in a row of display
const byte lcdRows_2004 = 4;     // Number of lines of display
// LCD address and geometry for LCD 1602
const byte lcdAddr_1602 = 0x26;  // One of possible addresses of I2C backpack for 1602
const byte lcdCols_1602 = 16;    // Number of characters in a row of display
const byte lcdRows_1602 = 2;     // Number of lines of display
// Initialize library and setting LCD geometry
LiquidCrystal_I2C lcd_20_i2c(lcdAddr_2004, lcdCols_2004, lcdRows_2004);
LiquidCrystal_I2C lcd_16_i2c(lcdAddr_1602, lcdCols_1602, lcdRows_1602);


const int rs = A3, en = A5, d4 = A9, d5 = A10, d6 = A11, d7 = A12;
LiquidCrystal lcd_16_norm(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd_20_norm(8, 9, 4, 5, 6, 7);

void setupSixteen() {
  pinMode(A14, OUTPUT);
  pinMode(A13, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);

  digitalWrite(A14, LOW);
  digitalWrite(A13, HIGH);
  digitalWrite(A4, LOW);
  digitalWrite(A0, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A1, HIGH);

  // lcd_16_norm.begin(16, 2);
}


void setupTwenty() 
{
  pinMode(2, OUTPUT); 
  digitalWrite(2, HIGH);
}


// Demo constants
const int testDelayFast = 100;
const int testDelay = 500;  // Delay between tests in ms

const int testDelayLong = 1000;
const int demoDelay = 3000;  // Delay between demos in ms

const byte demoNumMin = 1;    // Range of demo tests
const byte demoNumMax = UINT8_MAX;

const byte charNumMin = 0;    // Code of first displayed character
const byte charNumMax = UINT8_MAX;  // Code of last displayed character

// Demo variables
byte col, row;
unsigned int demoNum, charNum;
char buffer[LCD_DEFAULT_COLS + 1];

LiquidCrystal_Base *lcd;

void setup() { 
  // Initialize one of LCD variants

  // lcd = &lcd_20_norm; //setupTwenty(); //lcd->begin();
	// lcd = &lcd_16_norm; //setupSixteen(); //lcd->init(); //lcd->begin(16, 2);
	// lcd = &lcd_20_i2c; //lcd->init();
  // lcd = &lcd_16_i2c; //lcd->begin();

}

void loop()
{
  demoNum = max(demoNumMin, 1);
  while(demoNum >= demoNumMin && demoNum <= demoNumMax) {
    lcd->clear();
    lcd->noCursor();
    lcd->noBlink();
    sprintf(buffer, "%u.", demoNum);
    lcd->print(buffer);
    
    switch (demoNum) {
      case 1:
        lcd->print(F("Hello World!"));
        break;
      case 2:
        lcd->print(F("Dash Cursor"));
        lcd->setCursor(0, 1);
        lcd->cursor();
        break;
      case 3:
        lcd->print (F("Block Cursor"));
        lcd->setCursor(0, 1);
        lcd->blink();
        break;
      case 4:
        lcd->print(F("No Cursor"));
        lcd->setCursor(0, 1);
        break;
      case 5:
        for (byte row=0; row < lcd->getRows(); row++) {
          lcd->print(F("Line "));
          lcd->print(row);
          delay(testDelay);
          lcd->setCursor(0, row + 1);
        }
        break;
      case 6:
        lcd->print(F("Positions"));
        
				for (byte row = 1; row < lcd->getRows(); row++) {
					lcd->setCursor(0, row);
        	for (byte col = 0; col < lcd->getCols(); col++) {
        	  lcd->write(col%10 + char('0'));
        	  delay(testDelayFast);
        	}
				}
        break;
      case 7:
        lcd->print(F("Clearing"));
				for (byte row = 1; row < lcd->getRows(); row++) {
				  lcd->setCursor(0, row);
          for (byte col = 0; col < lcd->getCols(); col++) {
            lcd->write(col%10 + char('0'));
          }
				}

        for (byte row = 1; row < lcd->getRows(); row++) {
          // Clear row
          for (byte cols = 0; cols < (lcd->getCols() / 2); cols++) {
            lcd->setCursor((lcd->getCols() / 2) - cols - 1, row);
            lcd->write(' ');
            lcd->setCursor((lcd->getCols() / 2) + cols, row);
            lcd->write(' ');
            delay(testDelayFast);
          }
        }
        break;
      case 8:
        lcd->print(F("Mem 0 to 255"));
        int current_pos = 1;
        for (unsigned int i = 0; i < 256; i++) {
          lcd->clear(current_pos);
          sprintf(buffer, "%03u 0x%02X %c", i, i, i);
          lcd->print(buffer);
          if (lcd->getCols() >= 20) {
            lcd->print(" B");
            lcd->print(i, BIN);
          }
          current_pos++;
          if (current_pos > 3)
          {
            current_pos = 1;
          }
          delay(testDelayLong);
        }
        break;  
      case 9:
        lcd->print(F("Characters"));
        lcd->cursor();
        charNum = charNumMin;
        while(charNum <= charNumMax) {
          row = 1;
          do {
            lcd->clear(row);
            col = 0;
            lcd->setCursor(col, row);
            do {
              lcd->write(char(charNum++));
              delay(testDelayFast);
            } while(++col < lcd->getCols() && charNum <= charNumMax);
          } while(++row < lcd->getRows() && charNum <= charNumMax);
        }        
        lcd->noCursor();
        break;
      
      default:
        demoNum = 0;
        continue;
    }
    delay(demoDelay);
    demoNum++;
  }
}
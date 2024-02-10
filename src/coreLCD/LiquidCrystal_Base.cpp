#include "LiquidCrystal_Base.h"

void LiquidCrystal_Base::init(uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize)
{
  _cols = lcd_cols;
  _rows = lcd_rows;

  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

  if (_rows > 1)
  {
    setBitFlag(_displayfunction, LCD_2LINE);
  }

  if ((charsize != LCD_5x8DOTS) && (_rows == 1))
  {
    setBitFlag(_displayfunction, LCD_5x10DOTS);
  }
}


void LiquidCrystal_Base::init(uint8_t mode = LCD_4BITMODE) 
{
  uint8_t charsize = LCD_5x8DOTS;
  
  // if (_displayfunction & LCD_5x10DOTS)
  if(checkBitFlag(_displayfunction, LCD_5x10DOTS))
  {
    charsize = LCD_5x10DOTS;
  }

   _displayfunction = mode | LCD_1LINE | charsize;

  if (_rows > 1)
  {
    setBitFlag(_displayfunction, LCD_2LINE);
  }

 // _displayfunction = mode | ((_rows > 1) ? LCD_2LINE : LCD_1LINE) | charsize;
}


void LiquidCrystal_Base::begin()
{
  // put the LCD into 4 bit or 8 bit mode
  // if (! (_displayfunction & LCD_8BITMODE))
  if(!checkBitFlag(_displayfunction, LCD_8BITMODE))
  {
       
    // this is according to the Hitachi HD44780 datasheet
    // figure 24, pg 46
    // we start in 8bit mode, try to set 4 bit mode
    send(0x03, INIT_MODE);
    delayMicroseconds(4500); // wait min 4.1ms

    // // second try
    send(0x03, INIT_MODE);
    delayMicroseconds(4500); // wait min 4.1ms

    // third go!
    send(0x03, INIT_MODE);
    delayMicroseconds(150);

    // finally, set to 4-bit interface
    send(0x02, INIT_MODE);
    delayMicroseconds(150);
  }
  else
  {
    // this is according to the Hitachi HD44780 datasheet
    // page 45 figure 23
    
    // Send function set command sequence
    command(LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(4500); // wait more than 4.1 ms

    // second try
    command(LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(150);

    // third go
    command(LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(150);
  }
  
  // set # lines, font size, etc.
  command(LCD_FUNCTIONSET | _displayfunction);

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  display();
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);

  home();
}

/********** high level commands, for the user! */
void LiquidCrystal_Base::clear()
{
  command(LCD_CLEARDISPLAY); // clear display, set cursor position to zero
  delayMicroseconds(2000);   // this command takes a long time!
}

// Clear particular segment of a row
void LiquidCrystal_Base::clear(uint8_t rowStart, uint8_t colStart, uint8_t colCnt) {
  // Maintain input parameters
  rowStart = constrain(rowStart, 0, _rows - 1);
  colStart = constrain(colStart, 0, _cols - 1);
  colCnt   = constrain(colCnt,   0, _cols - colStart);
  // Clear segment
  setCursor(colStart, rowStart);
  for (uint8_t i = 0; i < colCnt; i++) write(' ');
  // Go to segment start
  setCursor(colStart, rowStart);
}

void LiquidCrystal_Base::home()
{
  command(LCD_RETURNHOME); // set cursor position to zero
  delayMicroseconds(2000); // this command takes a long time!
}
// Turn the display on/off (quickly)
void LiquidCrystal_Base::noDisplay()
{
  clearBitFlag(_displaycontrol, LCD_DISPLAYON);
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_Base::display()
{
  setBitFlag(_displaycontrol, LCD_DISPLAYON);
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_Base::noCursor()
{
  clearBitFlag(_displaycontrol, LCD_CURSORON);
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_Base::cursor()
{
  setBitFlag(_displaycontrol, LCD_CURSORON);
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void LiquidCrystal_Base::noBlink()
{
  clearBitFlag(_displaycontrol, LCD_BLINKON);
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_Base::blink()
{
  setBitFlag(_displaycontrol, LCD_BLINKON);
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_Base::scrollDisplayLeft(void)
{
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LiquidCrystal_Base::scrollDisplayRight(void)
{
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal_Base::leftToRight(void)
{
  setBitFlag(_displaymode, LCD_ENTRYLEFT);
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_Base::rightToLeft(void)
{
  clearBitFlag(_displaymode, LCD_ENTRYLEFT);
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_Base::autoscroll(void)
{
  setBitFlag(_displaymode, LCD_ENTRYSHIFTINCREMENT);
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_Base::noAutoscroll(void)
{
  clearBitFlag(_displaymode, LCD_ENTRYSHIFTINCREMENT);
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_Base::createChar(uint8_t location, uint8_t charmap[])
{
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i = 0; i < 8; i++)
  {
    write(charmap[i]);
  }
}

void LiquidCrystal_Base::setCursor(uint8_t col, uint8_t row, uint8_t offsets[])
{
  if (row > _rows)
  {
    row = _rows - 1; // we count rows starting w/0
  }
  command(LCD_SETDDRAMADDR | (col + offsets[row]));
}

void LiquidCrystal_Base::printstr(const char c[])
{
  // This function is not identical to the function used for "real" I2C displays
  // it's here so the user sketch doesn't have to be changed
  print(c);
}

/*********** mid level commands, for sending data/cmds */

void LiquidCrystal_Base::command(uint8_t value)
{
	this->send(value, COMMAND);
}

size_t LiquidCrystal_Base::write(uint8_t value)
{
  this->send(value, DATA);
  return 1; // assume success
}
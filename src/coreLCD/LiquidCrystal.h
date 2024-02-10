#ifndef LIQUID_CRYSTAL_h
#define LIQUID_CRYSTAL_h

#include "LiquidCrystal_Base.h"

class LiquidCrystal : public LiquidCrystal_Base
{
public:
  LiquidCrystal(uint8_t rs, uint8_t enable,
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                uint8_t cols=LCD_DEFAULT_COLS, uint8_t rows=LCD_DEFAULT_ROWS,
                uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_8BITMODE);

  LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                uint8_t cols=LCD_DEFAULT_COLS, uint8_t rows=LCD_DEFAULT_ROWS,
                uint8_t charsize = LCD_5x8DOTS,uint8_t mode = LCD_8BITMODE);

  LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                uint8_t cols=LCD_DEFAULT_COLS, uint8_t rows=LCD_DEFAULT_ROWS,
                uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE);
                
  LiquidCrystal(uint8_t rs, uint8_t enable,
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                uint8_t cols=LCD_DEFAULT_COLS, uint8_t rows=LCD_DEFAULT_ROWS,
                uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE);


  ~LiquidCrystal();
  virtual void init(uint8_t lcd_cols = LCD_DEFAULT_COLS, uint8_t lcd_rows=LCD_DEFAULT_ROWS, uint8_t charsize = LCD_5x8DOTS);
  virtual void init(uint8_t mode, uint8_t rs, uint8_t rw, uint8_t enable,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

  virtual void begin();
  
  virtual void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE);

  void setCursor(uint8_t col, uint8_t row);

  void setRowOffsets(int row1, int row2, int row3, int row4);

  virtual void write4bits(uint8_t value);
  
  using Print::write;

private:
  void send(uint8_t value, uint8_t mode);
  void write8bits(uint8_t value);
  void pulseEnable();

  uint8_t _rs_pin;     // LOW: command. HIGH: character.
  uint8_t _rw_pin;     // LOW: write to LCD. HIGH: read from LCD.
  uint8_t _enable_pin; // activated by a HIGH pulse.
  uint8_t _data_pins[8];
  uint8_t _row_offsets[4];
  // uint8_t _initialized;
};

#endif

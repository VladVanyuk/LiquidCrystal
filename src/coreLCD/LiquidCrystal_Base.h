#ifndef LiquidCrystal_Base_h
#define LiquidCrystal_Base_h

#if (ARDUINO < 100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#ifdef __AVR__
   #include <avr/pgmspace.h>
// #define FAST_MODE
#endif

#include <inttypes.h>
#include <Print.h>

#include "LCD_defs.h"

#define LCD_DEFAULT_COLS 16
#define LCD_DEFAULT_ROWS 2

class LiquidCrystal_Base : public Print
{
public:
    ~LiquidCrystal_Base() = default;
    virtual void init(uint8_t lcd_cols,  uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS);
    virtual void init(uint8_t mode = LCD_4BITMODE); 
    virtual void begin();
#if (ARDUINO < 100)
    virtual void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE){};
#else
    virtual void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE) = 0;
#endif

    void clear();
    void clear(uint8_t rowStart, uint8_t colStart = 0, uint8_t colCnt = 255);
    void home();
    void noDisplay();
    void display();
    // void display(lcd_mode_t mode);
    void noBlink();
    void blink();
    void noCursor();
    void cursor();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void leftToRight();
    void rightToLeft();
    void autoscroll();
    void noAutoscroll();
    void createChar(uint8_t, uint8_t[]);
#ifdef __AVR__
    void createChar(uint8_t location, const char *charmap);
#endif
    void setCursor(uint8_t col, uint8_t row, uint8_t offsets[]);
    void printstr(const char[]);

    virtual void setCursor(uint8_t col, uint8_t row);
    virtual void command(uint8_t value);
    
#if (ARDUINO < 100)
    virtual void write(uint8_t value);
#else
    virtual size_t write(uint8_t value);
#endif

#if (ARDUINO < 100)
    virtual void write4bits(uint8_t value){};
    virtual void send(uint8_t value,  uint8_t mode){};
#else
    virtual void write4bits(uint8_t value) = 0;
    virtual void send(uint8_t value,  uint8_t mode) = 0;
#endif

    bool getMode() { return readBitFlag(_displayfunction, LCD_8BITMODE); }    
    uint8_t getCols() { return _cols; }
    uint8_t getRows() { return _rows; }
protected:

    uint8_t _cols = LCD_DEFAULT_COLS;
    uint8_t _rows = LCD_DEFAULT_ROWS;

    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;

	////Unsupported API functions (not implemented in this library)
	// void setContrast(uint8_t new_val);
	// void setDelay(int,int); //for asynchroneous, no delay funcrion
	// uint8_t init_bargraph(uint8_t graphtype);
	// void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
	// void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
	
    inline uint8_t status() { return _displayfunction; }
    inline void on(){ display(); }
	inline void off() { noDisplay(); }
    inline void blink_on() { blink(); } 
	inline void blink_off() { noBlink(); }
	inline void cursor_on() { cursor(); }
	inline void cursor_off() { noCursor(); }
	inline void printLeft() { rightToLeft(); }
	inline void printRight() { leftToRight(); }
	inline void shiftIncrement() { autoscroll(); }
	inline void shiftDecrement() { noAutoscroll(); }
    // virtual void write8bits(uint8_t value);
    // void writeNbits(uint8_t value, uint8_t numBits);
private:
    inline void setBitFlag(uint8_t& flagsGroup, const uint8_t& bitToSet) __attribute__((always_inline)) {
        flagsGroup |= bitToSet;
    }

    inline void clearBitFlag(uint8_t& flagsGroup, const uint8_t& bitToClear) __attribute__((always_inline)) {
        flagsGroup &= ~bitToClear;
    }

    inline bool readBitFlag(uint8_t& flagsGroup, const uint8_t& bitToRead) __attribute__((always_inline)) {
        return flagsGroup & bitToRead;
    }

    inline void writeBitFlag(uint8_t& flagsGroup, const uint8_t& bitToSet, const bool& flagValue) __attribute__((always_inline)) {
        if (flagValue) setBitFlag(flagsGroup, bitToSet);
        else clearBitFlag(flagsGroup, bitToSet);
    }

    inline bool checkBitFlag(uint8_t& flagsGroup, const uint8_t& bitToCheck) __attribute__((always_inline)) {
        return (flagsGroup & (1 << bitToCheck)) ? true : false;
    }
    
};

#endif

// #define LCD_BRIGHT100 0x00
// #define LCD_BRIGHT75 0x01
// #define LCD_BRIGHT50 0x02
// #define LCD_BRIGHT25 0x03
//void bright (uint8_t brg) { command (LCD_FUNCTIONSET | _displayfunction | brg); }
//  lcd.print(F("Cursor"));

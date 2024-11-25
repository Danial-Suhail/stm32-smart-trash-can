#ifndef LIQUIDCRYSTAL_I2C_H_
#define LIQUIDCRYSTAL_I2C_H_

#include "stm32f4xx_hal.h"

/* Command */
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

/* Entry Mode */
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/* Display On/Off */
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

/* Cursor Shift */
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

/* Function Set */
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

/* Backlight */
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

/* Enable Bit */
#define ENABLE 0x04

/* Read Write Bit */
#define RW 0x0

/* Register Select Bit */
#define RS 0x01

/* Device I2C Address */
#define DEVICE_ADDR     (0x26 << 1)

void Display2_Init(uint8_t rows);
void Display2_Clear();
void Display2_Home();
void Display2_NoDisplay();
void Display2_Display();
void Display2_NoBlink();
void Display2_Blink();
void Display2_NoCursor();
void Display2_Cursor();
void Display2_ScrollDisplayLeft();
void Display2_ScrollDisplayRight();
void Display2_PrintLeft();
void Display2_PrintRight();
void Display2_LeftToRight();
void Display2_RightToLeft();
void Display2_ShiftIncrement();
void Display2_ShiftDecrement();
void Display2_NoBacklight();
void Display2_Backlight();
void Display2_AutoScroll();
void Display2_NoAutoScroll();
void Display2_CreateSpecialChar(uint8_t, uint8_t[]);
void Display2_PrintSpecialChar(uint8_t);
void Display2_SetCursor(uint8_t, uint8_t);
void Display2_SetBacklight(uint8_t new_val);
void Display2_LoadCustomCharacter(uint8_t char_num, uint8_t *rows);
void Display2_PrintStr(const char[]);

#endif /* LIQUIDCRYSTAL_I2C_H_ */

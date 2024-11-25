#include "display2.h"
#include "display_variables.h"

extern I2C_HandleTypeDef hi2c1;


static void SendCommand(uint8_t);
static void SendChar(uint8_t);
static void Send(uint8_t, uint8_t);
static void Write4Bits(uint8_t);
static void ExpanderWrite(uint8_t);
static void PulseEnable(uint8_t);
static void DelayInit(void);
static void DelayUS(uint32_t);


void Display2_Init(uint8_t rows)
{
  dpRows = rows;

  dpBacklight = LCD_BACKLIGHT;

  dpFunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

  if (dpRows > 1)
  {
    dpFunction |= LCD_2LINE;
  }
  else
  {
    dpFunction |= LCD_5x10DOTS;
  }

  /* Wait for initialization */
  DelayInit();
  HAL_Delay(50);

  ExpanderWrite(dpBacklight);
  HAL_Delay(1000);

  /* 4bit Mode */
  Write4Bits(0x03 << 4);
  DelayUS(4500);

  Write4Bits(0x03 << 4);
  DelayUS(4500);

  Write4Bits(0x03 << 4);
  DelayUS(4500);

  Write4Bits(0x02 << 4);
  DelayUS(100);

  /* Display Control */
  SendCommand(LCD_FUNCTIONSET | dpFunction);

  dpControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  Display2_Display();
  Display2_Clear();

  /* Display Mode */
  dpMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  SendCommand(LCD_ENTRYMODESET | dpMode);
  DelayUS(4500);

  Display2_CreateSpecialChar(0, special1);
  Display2_CreateSpecialChar(1, special2);

  Display2_Home();
}

void Display2_Clear()
{
  SendCommand(LCD_CLEARDISPLAY);
  DelayUS(2000);
}

void Display2_Home()
{
  SendCommand(LCD_RETURNHOME);
  DelayUS(2000);
}

void Display2_SetCursor(uint8_t col, uint8_t row)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if (row >= dpRows)
  {
    row = dpRows-1;
  }
  SendCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void Display2_NoDisplay()
{
  dpControl &= ~LCD_DISPLAYON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void Display2_Display()
{
  dpControl |= LCD_DISPLAYON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void Display2_NoCursor()
{
  dpControl &= ~LCD_CURSORON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void Display2_Cursor()
{
  dpControl |= LCD_CURSORON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void Display2_NoBlink()
{
  dpControl &= ~LCD_BLINKON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void Display2_Blink()
{
  dpControl |= LCD_BLINKON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void Display2_ScrollDisplayLeft(void)
{
  SendCommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void Display2_ScrollDisplayRight(void)
{
  SendCommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void Display2_LeftToRight(void)
{
  dpMode |= LCD_ENTRYLEFT;
  SendCommand(LCD_ENTRYMODESET | dpMode);
}

void Display2_RightToLeft(void)
{
  dpMode &= ~LCD_ENTRYLEFT;
  SendCommand(LCD_ENTRYMODESET | dpMode);
}

void Display2_AutoScroll(void)
{
  dpMode |= LCD_ENTRYSHIFTINCREMENT;
  SendCommand(LCD_ENTRYMODESET | dpMode);
}

void Display2_NoAutoScroll(void)
{
  dpMode &= ~LCD_ENTRYSHIFTINCREMENT;
  SendCommand(LCD_ENTRYMODESET | dpMode);
}

void Display2_CreateSpecialChar(uint8_t location, uint8_t charmap[])
{
  location &= 0x7;
  SendCommand(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++)
  {
    SendChar(charmap[i]);
  }
}

void Display2_PrintSpecialChar(uint8_t index)
{
  SendChar(index);
}

void Display2_LoadCustomCharacter(uint8_t char_num, uint8_t *rows)
{
  Display2_CreateSpecialChar(char_num, rows);
}

void Display2_PrintStr(const char c[])
{
  while(*c) SendChar(*c++);
}

void Display2_SetBacklight(uint8_t new_val)
{
  if(new_val) Display2_Backlight();
  else Display2_NoBacklight();
}

void Display2_NoBacklight(void)
{
  dpBacklight=LCD_NOBACKLIGHT;
  ExpanderWrite(0);
}

void Display2_Backlight(void)
{
  dpBacklight=LCD_BACKLIGHT;
  ExpanderWrite(0);
}

static void SendCommand(uint8_t cmd)
{
  Send(cmd, 0);
}

static void SendChar(uint8_t ch)
{
  Send(ch, RS);
}

static void Send(uint8_t value, uint8_t mode)
{
  uint8_t highnib = value & 0xF0;
  uint8_t lownib = (value<<4) & 0xF0;
  Write4Bits((highnib)|mode);
  Write4Bits((lownib)|mode);
}

static void Write4Bits(uint8_t value)
{
  ExpanderWrite(value);
  PulseEnable(value);
}

static void ExpanderWrite(uint8_t _data)
{
  uint8_t data = _data | dpBacklight;
  HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDR, (uint8_t*)&data, 1, 10);
}

static void PulseEnable(uint8_t _data)
{
  ExpanderWrite(_data | ENABLE);
  DelayUS(20);

  ExpanderWrite(_data & ~ENABLE);
  DelayUS(20);
}

static void DelayInit(void)
{
  CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
  CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk;

  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
  DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

  DWT->CYCCNT = 0;

  /* 3 NO OPERATION instructions */
  __ASM volatile ("NOP");
  __ASM volatile ("NOP");
  __ASM volatile ("NOP");
}

static void DelayUS(uint32_t us) {
  uint32_t cycles = (SystemCoreClock/1000000L)*us;
  uint32_t start = DWT->CYCCNT;
  volatile uint32_t cnt;

  do
  {
    cnt = DWT->CYCCNT - start;
  } while(cnt < cycles);
}
#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#include "string.h"
#include "common.h"

/*
 * I2C LCD는 4bit 통신
 */

#define I2C_LCD_ADDRESS   (0x27<<1)
#define BACKLIGHT_ON      0x08

/* LCD Command */
#define DISPLAY_ON    0x0C
#define DISPLAY_OFF   0x08
#define CLEAR_DISPLAY 0x01      // delay 2ms
#define RETURN_HOME   0x02

extern const char *state[];
extern const char *prefix[];

void lcdCommand(uint8_t command);
void lcdData(uint8_t data);
void i2cLcd_Init();
void lcdString(char *str);
void moveCursor(uint8_t row, uint8_t col);
char* returnLcdString(const char *prefixStr, uint8_t stateIndex, uint8_t floor, uint8_t option);
void lcdStart(const char *upperPrefix, uint8_t stateIndex, uint8_t floor);
#endif /* INC_LCD_H_ */

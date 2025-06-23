#include "lcd.h"


extern I2C_HandleTypeDef hi2c1;

const char *state[] = {
    "^",
    "*",
    "v"
};

const char *prefix[] = {
    "Move to   ",
    "Arrived   "
};

void lcdCommand(uint8_t command)
{
	uint8_t high_nibble, low_nibble;
	uint8_t i2c_buffer[4];
	high_nibble = command & 0xf0;
	low_nibble = (command << 4) & 0xf0;
	i2c_buffer[0] = high_nibble | 0x04 | 0x08;  // en=1, rs=0, rw=0, backlight=1
	i2c_buffer[1] = high_nibble | 0x00 | 0x08;  // en=0, rs=0, rw=0, backlight=1
	i2c_buffer[2] = low_nibble  | 0x04 | 0x08;  // en=1, rs=0, rw=0, backlight=1
	i2c_buffer[3] = low_nibble  | 0x00 | 0x08;  // en=0, rs=0, rw=0, backlight=1
	while(HAL_I2C_Master_Transmit(&hi2c1, I2C_LCD_ADDRESS, i2c_buffer, 4, 100) != HAL_OK);
}

void lcdData(uint8_t data)
{
	uint8_t high_nibble, low_nibble;
	uint8_t i2c_buffer[4];
	high_nibble = data & 0xf0;
	low_nibble = (data << 4) & 0xf0;
	i2c_buffer[0] = high_nibble | 0x05 | 0x08;
	i2c_buffer[1] = high_nibble | 0x01 | 0x08;
	i2c_buffer[2] = low_nibble  | 0x05 | 0x08;
	i2c_buffer[3] = low_nibble  | 0x01 | 0x08;
	while(HAL_I2C_Master_Transmit(&hi2c1, I2C_LCD_ADDRESS, i2c_buffer, 4, 100) != HAL_OK);
}

void i2cLcd_Init()
{
	HAL_Delay(50);
	lcdCommand(0x33);
	HAL_Delay(5);
	lcdCommand(0x32);
	HAL_Delay(5);
	lcdCommand(0x28);
	HAL_Delay(5);
	lcdCommand(DISPLAY_ON);
	HAL_Delay(5);
	lcdCommand(0x06);
	HAL_Delay(5);
	lcdCommand(CLEAR_DISPLAY);  // 약 2ms 필요
	HAL_Delay(2);
}

void lcdString(char *str)
{
	while(*str)lcdData(*str++);
}

void moveCursor(uint8_t row, uint8_t col)
{
	lcdCommand(0x80 | row << 6 | col);
}

/**
 * @brief	LCD에 맞는 형태로 문자를 변환해주는함수
 * @note	LCD에 들어가기 알맞은 형태로 각 파라미터를 받아 숫자와 문자를 받아 혼합하여 칸에맞게 출력해주는함수
 * @param	prefixStr 첫번째줄에 들어가는 글자 prefix[0] ~ [1] 중 입력받으면 해당글자를 LCD 첫줄에 출력
 * 			prefix[0]은 Moving(움직이는중) prefix[1]은 Arrived(도착함)
 * @param	stateIndex는 기호 0,1,2 순서대로 다음 기호들을 의미 "^","*","v"
 * @param	floor는 층수를 의미함
 * @param	option은 0일경우에 LCD의 첫번째줄을 의미하고 1일경우에 LCD의 두번째줄을 의미함
 */
char* returnLcdString(const char *prefixStr, uint8_t stateIndex, uint8_t floor, uint8_t option) {
    static char result[32]; // 함수 밖으로 반환할 문자열은 static으로
    if(option)
    {
        snprintf(result, sizeof(result), "%s              %s",state[stateIndex], state[stateIndex]);
    }
    else
    {
        snprintf(result, sizeof(result), "%s %s%dF %s",state[stateIndex], prefixStr, floor, state[stateIndex]);
    }
    return result;
}

/*
 * @brief	LCD 시작함수
 * @note	LCD를 시작할때쓰는 함수이며 각 파라미터에 맞게 입력하면 기호와 상태(움직이는중, 도착)을 적용시킬수있음
 * @param	upperPrefix 첫번째줄에 들어가는 글자 prefix[0] ~ [1] 중 입력받으면 해당글자를 LCD 첫줄에 출력
 * 			prefix[0]은 Moving(움직이는중) prefix[1]은 Arrived(도착함)
 * @param	stateIndex는 기호 0,1,2 순서대로 다음 기호 출력 "^","*","v"
 * @param	floor는 층수를 의미함
 */
void lcdStart(const char *upperPrefix, uint8_t stateIndex, uint8_t floor)
{
    moveCursor(0, 0);
    lcdString(returnLcdString(upperPrefix, stateIndex, floor, 0));

    moveCursor(1, 0);
    lcdString(returnLcdString(stateIndex, stateIndex, floor, 1));
}

void lcdHandler()
{
	if(current_floor < target_floor)
	  {
		  lcdStart(prefix[0], 0, target_floor);
	  }

	  if(current_floor == target_floor)
	  {
		  lcdStart(prefix[1], 1, target_floor);
	  }

	  if(current_floor > target_floor)
	  {
		  lcdStart(prefix[0], 2, target_floor);
	  }
}

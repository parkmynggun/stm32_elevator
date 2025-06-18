/*
 * lcd.c
 *
 *  Created on: Jun 18, 2025
 *      Author: psh
 */

#include "lcd.h"

void lcd_send_cmd()
{

}

void lcd_init()
{
	HAL_Delay(50);
	lcd_send_cmd(0x30);
	HAL_Delay(5);
	lcd_send_cmd(0x30);
	HAL_Delay(1);
	lcd_send_cmd(0x30);
	HAL_Delay(10);
	lcd_send_cmd(0x20);	// 4bit mode
	HAL_Delay(10);
	HAL_Delay(10);
}

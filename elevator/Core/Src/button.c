#include "button.h"

BUTTON_CONTROL button[3]=
{
		{GPIOC, GPIO_PIN_8, 0},
		{GPIOC, GPIO_PIN_6, 0},
		{GPIOC, GPIO_PIN_5, 0}, //여기까지 1~3층
		{GPIOC, GPIO_PIN_9, 0},
		{GPIOB, GPIO_PIN_8, 0}	// 여기까지 위아래


};


bool  buttonGetPressed(uint8_t num)
{
	static uint32_t prevTime[3] = {0xffffffff};

	if(prevTime[num] == 0xffffffff)
	{
		prevTime[num] = HAL_GetTick();
	}

	bool ret = false;


	if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState)
	{
		uint32_t currTime = HAL_GetTick();

		if(currTime - prevTime[num] > 30)
		{
			if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState)
			{
				ret =true;
			}
			prevTime[num] = currTime;
		}

	}

	return ret;


}

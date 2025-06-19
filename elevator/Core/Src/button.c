#include "button.h"

BUTTON_CONTROL button[]=
{
		{GPIOC, GPIO_PIN_8, 0, BUTTON_TYPE_FLOOR},		//0
		{GPIOC, GPIO_PIN_6, 0, BUTTON_TYPE_FLOOR},		//1
		{GPIOC, GPIO_PIN_5, 0, BUTTON_TYPE_FLOOR}, 	//2  여기까지 1~3층 (GPIO핀)
		{GPIOC, GPIO_PIN_9, GPIO_PIN_RESET, BUTTON_TYPE_DIRECTION},	//3
		{GPIOB, GPIO_PIN_8, GPIO_PIN_RESET, BUTTON_TYPE_DIRECTION}	//4   여기까지 위아래 (EXTI핀)


};


bool  buttondebounce(uint8_t num)
{
	static uint32_t prevTime[5] = {0xffffffff};

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

bool buttongetpressed_floor(uint8_t num)	//층수 디바운싱 함수
			{
		if (num >= BUTTON_COUNT) return false;
		if (button[num].type != BUTTON_TYPE_FLOOR) return false;

		return buttondebounce(num);

			}

bool buttongetpressed_direction(uint8_t num)	//위아래 디바운싱 함수
	{
		if (num >= BUTTON_COUNT) return false;
		if (button[num].type != BUTTON_TYPE_DIRECTION) return false;

		return buttondebounce(num);
	}

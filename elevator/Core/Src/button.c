#include "button.h"

BUTTON_CONTROL button[]=
{
		{GPIOC, GPIO_PIN_8, GPIO_PIN_RESET, BUTTON_TYPE_FLOOR},		//0
		{GPIOC, GPIO_PIN_6, GPIO_PIN_RESET, BUTTON_TYPE_FLOOR},		//1
		{GPIOC, GPIO_PIN_5, GPIO_PIN_RESET, BUTTON_TYPE_FLOOR}, 		//2  여기까지 1~3층 (GPIO핀)
		{GPIOC, GPIO_PIN_9, GPIO_PIN_RESET, BUTTON_TYPE_DIRECTION},	//3
		{GPIOB, GPIO_PIN_8, GPIO_PIN_RESET, BUTTON_TYPE_DIRECTION}	//4   여기까지 위아래 (EXTI핀)


};

static bool buttonDebounce(uint8_t num)	//헬퍼 함수
{
	static uint32_t prevTime[BUTTON_COUNT] = { [0 ... BUTTON_COUNT-1] = 0xffffffff };

	if (num >= BUTTON_COUNT) return false;

	if (prevTime[num] == 0xffffffff)
		prevTime[num] = HAL_GetTick();

	bool ret = false;

	if (HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState)
	{
		uint32_t currTime = HAL_GetTick();

		if (currTime - prevTime[num] > 30)
		{
			if (HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState)
			{
				ret = true;
			}
			prevTime[num] = currTime;
		}
	}

	return ret;
}

bool  buttonGetPressed_Floor(uint8_t num)	//층수 디바운싱 함수
			{
		if (num >= BUTTON_COUNT) return false;
		if (button[num].type != BUTTON_TYPE_FLOOR) return false;

		return buttonDebounce(num);

			}

bool buttonGetPressed_Direction(uint8_t num)	//위아래 디바운싱 함수
	{
		if (num >= BUTTON_COUNT) return false;
		if (button[num].type != BUTTON_TYPE_DIRECTION) return false;

		return buttonDebounce(num);
	}

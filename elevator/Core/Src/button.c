#include "button.h"

BUTTON_CONTROL button[]=
{
		{GPIOC, GPIO_PIN_8, 0, BUTTON_TYPE_FLOOR},					//0
		{GPIOC, GPIO_PIN_6, 0, BUTTON_TYPE_FLOOR},					//1
		{GPIOC, GPIO_PIN_5, 0, BUTTON_TYPE_FLOOR}, 					//2  여기까지 1~3층 (GPIO핀)
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

//bool buttongetpressed_direction(uint8_t num)	//위아래 디바운싱 함수
//	{
//		if (num >= BUTTON_COUNT) return false;
//		if (button[num].type != BUTTON_TYPE_DIRECTION) return false;
//
//		return buttondebounce(num);
//	}

//
//uint8_t floor_request[3] = {0};		// target_floor에 저장하기 위해서 추가한 변수
//
//
//void target_floor_check()
//{
//
//	if (buttongetpressed_floor(0)) floor_request[0] = 1;
//	if (buttongetpressed_floor(1)) floor_request[1] = 1;
//	if (buttongetpressed_floor(2)) floor_request[2] = 1;
//
//	for (int i = 0; i < 3; i++)
//	{
//		if (floor_request[i])
//		{
//			target_floor = i + 1;  // i 0-2 → 층수 1-3
//			floor_request[target_floor - 1] = 0;	// 다음 층으로 넘어가기 위해 중복값 없애는 거
//			break;
//		}
//
//
//	}
//
//}

void target_floor_check()
{
    if (buttongetpressed_floor(0))
    {
        target_floor = 1;
    }
    else if (buttongetpressed_floor(1))
    {
        target_floor = 2;
    }
    else if (buttongetpressed_floor(2))
    {
        target_floor = 3;
    }
}



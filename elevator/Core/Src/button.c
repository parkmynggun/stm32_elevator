#include "button.h"

BUTTON_CONTROL button[]=
{
		{GPIOC, GPIO_PIN_8, 0, BUTTON_TYPE_FLOOR},
		{GPIOC, GPIO_PIN_6, 0, BUTTON_TYPE_FLOOR},
		{GPIOC, GPIO_PIN_5, 0, BUTTON_TYPE_FLOOR}, //여기까지 1~3층
		{GPIOC, GPIO_PIN_9, 0, BUTTON_TYPE_DIRECTION},
		{GPIOB, GPIO_PIN_8, 0, BUTTON_TYPE_DIRECTION}	// 여기까지 위아래


};

bool buttonDebounce(uint8_t num)	//헬퍼 함수
{

}

bool  buttonGetPressed_Floor(uint8_t num)	//층수 디바운싱 함수
{


}

bool buttonGetPressed_Direction(uint8_t num)	//위아래 디바운싱 함수
{

}

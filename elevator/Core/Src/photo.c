
#include "photo.h"


void Photo_Init();

uint8_t Photo_CurrentFloor()
{
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == GPIO_PIN_RESET) return 1;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14) == GPIO_PIN_RESET) return 2;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET) return 3;
	return 0;	// 감지 x
}


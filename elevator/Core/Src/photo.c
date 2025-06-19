
#include "photo.h"


void Photo_Init();

uint8_t current_floor()
{
	if(HAL_GPIO_ReadPin(Photo_Floor1_GPIO_PORT, GPIO_PIN_13) == GPIO_PIN_RESET) return 1;
	if(HAL_GPIO_ReadPin(Photo_Floor2_GPIO_PORT, GPIO_PIN_14) == GPIO_PIN_RESET) return 1;
	if(HAL_GPIO_ReadPin(Photo_Floor3_GPIO_PORT, GPIO_PIN_15) == GPIO_PIN_RESET) return 1;
	return 0;	// 감지 x
}


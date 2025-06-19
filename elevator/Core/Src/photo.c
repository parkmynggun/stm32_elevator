
#include "photo.h"


void Photo_Init();

uint8_t current_floor()
{
	// LOW가 되면 PTOHO 센서가 차단되어 해당 층에 있다는 의미
	if(HAL_GPIO_ReadPin(Photo_Floor1_GPIO_PORT, GPIO_PIN_13) == GPIO_PIN_RESET) return 1;
	if(HAL_GPIO_ReadPin(Photo_Floor2_GPIO_PORT, GPIO_PIN_14) == GPIO_PIN_RESET) return 2;
	if(HAL_GPIO_ReadPin(Photo_Floor3_GPIO_PORT, GPIO_PIN_15) == GPIO_PIN_RESET) return 3;
	return 0;	// 감지 x
}


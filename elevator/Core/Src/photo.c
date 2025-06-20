
#include "photo.h"


void Photo_Init()
{

}

uint8_t Photo_GetFloor()
{
	// PHOTO 센서가 차단되어 1 (HIGH)가 된다면 값을 리턴해줌.
	if(HAL_GPIO_ReadPin(Photo1_GPIO_PORT, Photo1_PIN) == GPIO_PIN_SET) return 1;
	if(HAL_GPIO_ReadPin(Photo2_GPIO_PORT, Photo2_PIN) == GPIO_PIN_SET) return 2;
	if(HAL_GPIO_ReadPin(Photo3_GPIO_PORT, Photo3_PIN) == GPIO_PIN_SET) return 3;
	return 0;	// 층 감지 x
}

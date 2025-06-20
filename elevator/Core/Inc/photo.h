

#ifndef INC_PHOTO_H_
#define INC_PHOTO_H_


#include "main.h"
#include "common.h"


// 핀 정의
#define Photo1_GPIO_PORT		GPIOA
#define Photo1_PIN				GPIO_PIN_9

#define Photo2_GPIO_PORT		GPIOA
#define Photo2_PIN				GPIO_PIN_10

#define Photo3_GPIO_PORT		GPIOA
#define Photo3_PIN				GPIO_PIN_11



void Photo_Init();			// GPIO 초기화
uint8_t Photo_GetFloor();	// 현재 감지된 층 반환 (1, 2, 3) , 없으면 0


#endif /* INC_PHOTO_H_ */

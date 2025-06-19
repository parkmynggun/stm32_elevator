

#ifndef INC_PHOTO_H_
#define INC_PHOTO_H_


#include "main.h"


// 핀 정의
#define Photo_Floor1_GPIO_PORT		GPIOB
#define Photo_Floor1_PIN			GPIO_PIN_13

#define Photo_Floor2_GPIO_PORT		GPIOB
#define Photo_Floor2_PIN			GPIO_PIN_14

#define Photo_Floor3_GPIO_PORT		GPIOB
#define Photo_Floor3_PIN			GPIO_PIN_15



void Photo_Init();
uint8_t current_floor();	// return 값 반환


#endif /* INC_PHOTO_H_ */

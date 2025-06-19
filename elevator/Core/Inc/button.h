#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "stdbool.h"

typedef enum {

    BUTTON_TYPE_FLOOR,		//층수
    BUTTON_TYPE_DIRECTION	//위아래

} ButtonType;

typedef struct
{

	GPIO_TypeDef		*port;
	uint16_t			pinNumber;
	GPIO_PinState		onState;
	ButtonType   	    type;



}BUTTON_CONTROL;


bool buttonDebounce(uint8_t num);

bool buttonGetPressed_Floor(uint8_t num);

bool buttonGetPressed_Direction(uint8_t num);

#endif /* INC_BUTTON_H_ */

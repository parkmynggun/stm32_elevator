#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_

#include "main.h"
#include "delay_us.h"

#define STEPS_PER_REVOLUTION 4096
#define DIR_CW                0
#define DIR_CCM               1

#define IN1_Pin               GPIO_PIN_1
#define IN1_GPIO_PORT         GPIOB

#define IN2_Pin               GPIO_PIN_15
#define IN2_GPIO_PORT         GPIOB

#define IN3_Pin               GPIO_PIN_14
#define IN3_GPIO_PORT         GPIOB

#define IN4_Pin               GPIO_PIN_13
#define IN4_GPIO_PORT         GPIOB

void stepMotor(uint8_t step);
void rotateSteps(uint16_t steps, uint8_t direction);
void rotateDegrees(uint8_t degrees, uint8_t direction);

#endif /* INC_STEPPER_H_ */

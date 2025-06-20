#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"

// 스텝퍼 모터  움직인 거리 관련 함수
extern uint8_t floors_to_move;

// 움직여야할 스텝
extern uint16_t steps_to_move;

// 초기화
void Motor_Init(void);

// 버튼 입력 처리
void Motor_HandleInput(void);

#endif

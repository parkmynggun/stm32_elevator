/*
 * common.h
 *
 *  Created on: Jun 19, 2025
 *      Author: psh
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include "main.h"

// 현재 층수 1,2,3
uint8_t current_floor;

// 목표 층수 1,2,3
uint8_t target_floor;

// 문 열림 여부 1이면 열림 0이면 닫힘
uint8_t is_door_open;


// 스텝퍼 모터  움직인 거리 관련 함수
uint8_t floors_to_move;


// 움직여야할 스텝
uint16_t steps_to_move;



#endif /* INC_COMMON_H_ */

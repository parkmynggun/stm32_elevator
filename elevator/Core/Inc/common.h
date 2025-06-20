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
extern uint8_t current_floor;

// 목표 층수 1,2,3
extern uint8_t target_floor;

// 문 열림 여부 1이면 열림 0이면 닫힘
extern uint8_t is_door_open;

#endif /* INC_COMMON_H_ */

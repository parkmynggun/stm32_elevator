/*
 * common.c
 *
 *  Created on: Jun 19, 2025
 *      Author: psh
 */


#include "common.h"

// 현재 층수 1,2,3
uint8_t current_floor = 0;

// 목표 층수 1,2,3
uint8_t target_floor = 0;
//타켓플로어가 층에 맞게 123으로 바뀌게 ㅏ하면 된다 멈추게?

// 문 열림 여부 1이면 열림 0이면 닫힘
uint8_t is_door_open = 0;


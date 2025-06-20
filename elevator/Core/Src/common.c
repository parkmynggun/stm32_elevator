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

// 문 열림 여부 1이면 열림 0이면 닫힘
uint8_t is_door_open = 0;

// 현재 lcd 메세지 상태
uint32_t current_msg = "";

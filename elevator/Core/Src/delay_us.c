#include "delay_us.h"

void delay_us(uint16_t us)
{

	__HAL_TIM_SET_COUNTER(&htim11, 0);  // 언더스코어 2개  // 타이머 카운터 초기화
	while (__HAL_TIM_GET_COUNTER(&htim11) < us);  // us 마이크로초 대기
}

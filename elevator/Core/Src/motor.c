#include "motor.h"
#include "stepper.h"
#include "tim.h"
#include "gpio.h"

#ifndef DIR_CW
#define DIR_CW 0  // 시계 방향
#endif

#ifndef DIR_CCW
#define DIR_CCW 1  // 반시계 방향
#endif
#define STEPS_PER_FLOOR 8200  // 예시값, 실제 값으로 조정하세요

static uint8_t is_door_open = 0;
static uint8_t is_door_off = 1;  // 초기 문 닫힘 상태
static uint8_t current_floor = 0;
static uint8_t target_floor = 0;

void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);  // 서보 PWM 시작
    HAL_TIM_Base_Start(&htim11);               // 기본 타이머 시작
    TIM3->CCR2 = 1600;                          // 서보 중립 위치
    HAL_Delay(500);
}

void Motor_HandleInput(void)
{
    // 버튼 상태 읽기 (풀업 회로라 눌리면 0)
    uint8_t btnDoorOpen = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
    uint8_t btnDoorClose = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);
    uint8_t btnFloor1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
    uint8_t btnFloor2 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
    uint8_t btnFloor3 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);

    // 문 열림 (닫혀 있을 때만 열림)
    if (btnDoorOpen == 0 && is_door_open == 0)
    {
        TIM3->CCR2 = 700;  // 문 열림 서보 위치
        HAL_Delay(500);
        is_door_open = 1;
        is_door_off = 0;
    }
    // 문 닫힘 (열려 있을 때만 닫힘)
    else if (btnDoorClose == 0 && is_door_off == 0)
    {
        TIM3->CCR2 = 2400; // 문 닫힘 서보 위치
        HAL_Delay(500);
        is_door_off = 1;
        is_door_open = 0;
    }

    // 층 버튼 눌림 감지 (우선순위 1->2->3)
    // 층 버튼 눌림 감지 (우선순위 1->2->3)
    if (btnFloor1 == 0)
        target_floor = 0;
    else if (btnFloor2 == 0)
        target_floor = 1;
    else if (btnFloor3 == 0)
        target_floor = 2;

    // 층 이동 처리
    if (current_floor < target_floor)
    {
        uint8_t floors_to_move = target_floor - current_floor;
        uint16_t steps_to_move = floors_to_move * STEPS_PER_FLOOR;

        rotateSteps(steps_to_move, DIR_CW);  // 위층 = 시계 방향
        current_floor = target_floor;        // 도착 층 갱신
    }
    else if (current_floor > target_floor)
    {
        uint8_t floors_to_move = current_floor - target_floor;
        uint16_t steps_to_move = floors_to_move * STEPS_PER_FLOOR;

        rotateSteps(steps_to_move, DIR_CCW); // 아래층 = 반시계 방향
        current_floor = target_floor;        // 도착 층 갱신
    }
}

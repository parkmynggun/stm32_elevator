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
#define STEPS_PER_FLOOR 7500  // 예시값, 실제 값으로 조정하세요

static uint8_t is_door_open = 0;
static uint8_t is_door_off = 1;  // 초기 문 닫힘 상태
//static uint8_t current_floor = 1;
//static uint8_t target_floor = 1;

extern uint8_t current_floor;
extern uint8_t target_floor;
void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);  // 서보 PWM 시작
    HAL_TIM_Base_Start(&htim11);               // 기본 타이머 시작
    TIM3->CCR2 = 700;                          // 서보 중립 위치
    HAL_Delay(500);
}

void Motor_HandleInput(void)
{
    // 버튼 상태 읽기 (풀업, 눌리면 0)
    uint8_t btnDoorOpen = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9);  // 문 열림 버튼 (PC8)
    uint8_t btnDoorClose = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8); // 문 닫힘 버튼 (PB9)
    uint8_t btnFloor1 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);    // 1층 버튼 (PC8)
    uint8_t btnFloor2 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);    // 2층 버튼 (PC6)
    uint8_t btnFloor3 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);    // 3층 버튼 (PC5)

    // 문 열림 (천천히 열기)
    if (btnDoorOpen == GPIO_PIN_RESET && is_door_open == 0)
    {
        for (uint16_t pos = 1700; pos >= 700; pos -= 5) // 닫힌 상태에서 열린 상태로 이동
        {
            TIM3->CCR2 = pos;
            HAL_Delay(20); // 조절: 더 작으면 빠르게, 더 크면 느리게
        }
        is_door_open = 1;
        is_door_off = 0;
    }

    // 문 닫힘 (천천히 닫기)
    else if (btnDoorClose == GPIO_PIN_RESET && is_door_off == 0)
    {
        for (uint16_t pos = 700; pos <= 1700; pos += 5) // 열린 상태에서 닫힌 상태로 이동
        {
            TIM3->CCR2 = pos;
            HAL_Delay(20);
        }
        is_door_off = 1;
        is_door_open = 0;
    }


    // 층 버튼 눌림 감지 (우선순위 1->2->3)
    if (btnFloor1 == GPIO_PIN_RESET)
        target_floor = 1;
    else if (btnFloor2 == GPIO_PIN_RESET)
        target_floor = 2;
    else if (btnFloor3 == GPIO_PIN_RESET)
        target_floor = 3;

    // 층 이동 처리
    if (current_floor < target_floor)

    { lcdHandler();

        uint8_t floors_to_move = target_floor - current_floor;
        uint16_t steps_to_move = floors_to_move * STEPS_PER_FLOOR;

        rotateSteps(steps_to_move, DIR_CW);
        current_floor = target_floor;

        lcdHandler();

    }
    else if (current_floor > target_floor)

    {lcdHandler();

        uint8_t floors_to_move = current_floor - target_floor;
        uint16_t steps_to_move = floors_to_move * STEPS_PER_FLOOR;

        rotateSteps(steps_to_move, DIR_CCW);
        current_floor = target_floor;

        lcdHandler();

    }
}

#include "motor.h"
#include "stepper.h"
#include "tim.h"
#include "gpio.h"

static uint8_t prevBtn1State = 0;
static uint8_t prevBtn2State = 0;
static uint8_t prevBtn3State = 0;
static uint8_t prevBtn4State = 0;

void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);  // 서보용
    HAL_TIM_Base_Start(&htim11);               // 딜레이 등 타이머
    TIM3->CCR2 = 1600;                          // 초기 서보 위치
    HAL_Delay(500);
}

void Motor_HandleInput(void)
{
    uint8_t btn1 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);   // -90도
    uint8_t btn2 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);   // 0도
    uint8_t btn3 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);   // +90도
    uint8_t btn4 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2);   // 스텝퍼

    if (btn1 == 0 && prevBtn1State == 1)
    {
        TIM3->CCR2 = 1600;  // -90도
        HAL_Delay(500);
    }
    else if (btn2 == 0 && prevBtn2State == 1)
    {
        TIM3->CCR2 = 700;  // 0도
        HAL_Delay(500);
    }
    else if (btn3 == 0 && prevBtn3State == 1)
    {
        TIM3->CCR2 = 2400;  // +90도
        HAL_Delay(500);
    }
    else if (btn4 == 0 && prevBtn4State == 1)
    {
        rotateDegrees(360, DIR_CW);  // 360도
        HAL_Delay(300);
    }

    prevBtn1State = btn1;
    prevBtn2State = btn2;
    prevBtn3State = btn3;
    prevBtn4State = btn4;
}

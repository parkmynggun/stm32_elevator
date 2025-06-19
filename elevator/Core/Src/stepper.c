#include "stepper.h"

static const uint8_t HALF_STEP_SEQ[8][4] =
{
    {1,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,1},
    {1,0,0,1}
};

void stepMotor(uint8_t step)
{
    HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_Pin, HALF_STEP_SEQ[step][0]);
    HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_Pin, HALF_STEP_SEQ[step][1]);
    HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_Pin, HALF_STEP_SEQ[step][2]);
    HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_Pin, HALF_STEP_SEQ[step][3]);
}

void rotateSteps(uint16_t steps, uint8_t direction)
{
    for (uint16_t i = 0; i < steps; i++)
    {
        uint8_t step;

        if (direction == DIR_CW)
        {
            step = i % 8; // 시계 방향
        }
        else
        {
            step = (7 - (i % 8)); // 반시계 방향
        }

        stepMotor(step);
        delay_us(1000); // 1ms
    }
}

void rotateDegrees(uint8_t degrees, uint8_t direction)
{
    uint16_t steps = (uint16_t)((uint32_t)(degrees * STEPS_PER_REVOLUTION) / 360);
    rotateSteps(steps, direction);
}

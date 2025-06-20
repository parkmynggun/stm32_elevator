#include "fnd.h"
#include "gpio.h"

// 7세그먼트 숫자 패턴 (0~9)
static const uint8_t seg_pattern[10] = {
    0b00111111,  // 0
    0b00000110,  // 1
    0b01011011,  // 2
    0b01001111,  // 3
    0b01100110,  // 4
    0b01101101,  // 5
    0b01111101,  // 6
    0b00000111,  // 7
    0b01111111,  // 8
    0b01101111   // 9
};

// PB5, PB4, PB3, PC0, PC1, PC3, PA0, PA1 핀을 7세그먼트 a~dp에 매핑
static GPIO_TypeDef* const SEG_GPIO_PORT[8] = {
    GPIOB, // a -> PB5
    GPIOB, // b -> PB4
    GPIOB, // c -> PB3
    GPIOC, // d -> PC0
    GPIOC, // e -> PC1
    GPIOC, // f -> PC3
    GPIOA, // g -> PA0
    GPIOA  // dp -> PA1
};

static const uint16_t SEG_GPIO_PIN[8] = {
    GPIO_PIN_5,  // a
    GPIO_PIN_4,  // b
    GPIO_PIN_3,  // c
    GPIO_PIN_0,  // d
    GPIO_PIN_1,  // e
    GPIO_PIN_3,  // f
    GPIO_PIN_0,  // g
    GPIO_PIN_1   // dp
};

void FND_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // GPIO 클럭은 gpio.c에서 활성화되어 있다고 가정

    // GPIOB 핀: PB5, PB4, PB3
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // GPIOC 핀: PC0, PC1, PC3
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // GPIOA 핀: PA0, PA1
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 초기화: 모든 세그먼트 OFF
    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(SEG_GPIO_PORT[i], SEG_GPIO_PIN[i], GPIO_PIN_RESET);
    }
}

void FND_Display(uint8_t num) {
    if (num > 9) return;

    uint8_t pattern = seg_pattern[num];

    for (uint8_t i = 0; i < 8; i++) {
        GPIO_PinState state = (pattern & (1 << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
        HAL_GPIO_WritePin(SEG_GPIO_PORT[i], SEG_GPIO_PIN[i], state);
    }
}

void FND_Start(void) {
	if(current_floor == 1)
	  {
		  FND_Display(1);
	  }
	  if(current_floor == 2)
	  {
		  FND_Display(2);
	  }
	  if(current_floor == 3)
	  {
		  FND_Display(3);
	  }
}

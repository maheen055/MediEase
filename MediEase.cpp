#include "stm32f4xx_hal.h"

#define BUTTON_PIN GPIO_PIN_0
#define BUTTON_PORT GPIOA
#define MOTOR_PIN GPIO_PIN_8
#define MOTOR_PORT GPIOB
#define BUZZER_PIN GPIO_PIN_9
#define BUZZER_PORT GPIOB
#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOA

int buttonPressed = 0;
int isOn = 0;

void GPIO_Init(void) {
      GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Configure the button pin as input with pull-up
    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);

    // Configure the motor pin as output
    GPIO_InitStruct.Pin = MOTOR_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MOTOR_PORT, &GPIO_InitStruct);

    // Configure the buzzer and LED pins as output
    GPIO_InitStruct.Pin = BUZZER_PIN | LED_PIN;
    HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}

int main(void) {
}

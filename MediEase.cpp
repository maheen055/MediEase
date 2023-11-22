#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

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
          // Initialize HAL Library
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize GPIO
    GPIO_Init();

    while (1) {
        // Check if the button is pressed
        if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_RESET) {
            // Button is pressed
            if (!buttonPressed) {
                // Button press detected
                buttonPressed = 1;

                // Toggle the state
                isOn = !isOn;

                // Move the motor 20 degrees
                if (isOn) {
                    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_SET);
                    HAL_Delay(1000); // Delay for 1 second (adjust as needed)
                    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_RESET);
                }

                // Toggle the buzzer and LED
                HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, isOn ? GPIO_PIN_SET : GPIO_PIN_RESET);
                HAL_GPIO_WritePin(LED_PORT, LED_PIN, isOn ? GPIO_PIN_SET : GPIO_PIN_RESET);
            }
        } else {
            buttonPressed = 0;
        }
    }

}

// File: gpio.c
// Configures the GPIO pins used by USART1.

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "stm32g474xx.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

// ****************************************************************************
// Function: gpio_init
// Description: Configures PC4 and PC5 as USART1 transmit and receive pins.
// Parameters: None
// Returns: None
// Design:
//   - Select alternate function 7 for USART1 on PC4 (TX) and PC5 (RX).
//   - Use alternate-function push-pull mode with internal pull-ups and low speed.
//   - Call HAL_GPIO_Init to apply the settings to GPIOC.
// ****************************************************************************
void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

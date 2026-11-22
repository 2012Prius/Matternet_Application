//  File: gpio.c
//  This file contains the GPIO setup for the UART1 driver.
//  Functions include:
//
//  init (TODO: Murilloc)

//Includes
#include "gpio.h"
#include "stm32g474xx.h"

// Macros
// Static Variables
// Functions

// ****************************************************************************
// Function: gpio_init
// Description: Configures PC4 as the USART1 transmit pin.
// Parameters: None
// Returns: None
// Design:
//   - TODO: Murilloc
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

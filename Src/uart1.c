//  File: uart1.c
//  Created by Cameron on 11/21/2026
//  This file contains all supporting functions for UART1 driver.
//  Functions include:
//
//  init (TODO: Murilloc)
//  TX (TODO: Murilloc)
//  RX (TODO: Murilloc)

//Includes
#include "uart1.h"

// Macros
// Static Variables
UART_HandleTypeDef uart1;
// Functions



// ****************************************************************************
// Function: uart1_init
// Description: Initializes UART1 peripheral with specified settings.
// Purpose: To initialize UART 1 Handle.
// Parameters: None
// Returns: None
// Design:
//   - 
// ****************************************************************************
void uart1_init(void)
{
    uart1.Instance = USART1;
    uart1.Init.BaudRate = 115200;
    uart1.Init.WordLength = UART_WORDLENGTH_8B;
    uart1.Init.StopBits = UART_STOPBITS_1;
    uart1.Init.Parity = UART_PARITY_NONE;
    uart1.Init.Mode = UART_MODE_TX_RX;
    uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart1.Init.OverSampling = UART_OVERSAMPLING_16;
    uart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    uart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    uart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if (HAL_UART_Init(&uart1) != HAL_OK)
    {
        //TODO: Murilloc - error handler
    }

}
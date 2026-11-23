// File: uart1.c
// Created by Cameron on 11/21/2026
// Initializes USART1 and provides blocking transmit through the HAL.

/* Includes ------------------------------------------------------------------*/
#include "uart1.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef uart1;

/* Private function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

// ****************************************************************************
// Function: uart1_init
// Description: Initializes USART1 for transmit and receive at 115200 baud.
// Parameters: None
// Returns: None
// Design:
//   - Use 8 data bits, no parity, and one stop bit without hardware flow control.
//   - Use 16x oversampling and a divide-by-1 clock prescaler.
//   - Disable one-bit sampling and leave advanced features unconfigured.
//   - Call HAL_UART_Init with the USART1 handle and halt on failure.
// ****************************************************************************
void uart1_init(void)
{
    uart1.Instance                    = USART1;
    uart1.Init.BaudRate               = 115200;
    uart1.Init.WordLength             = UART_WORDLENGTH_8B;
    uart1.Init.StopBits               = UART_STOPBITS_1;
    uart1.Init.Parity                 = UART_PARITY_NONE;
    uart1.Init.Mode                   = UART_MODE_TX_RX;
    uart1.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
    uart1.Init.OverSampling           = UART_OVERSAMPLING_16;
    uart1.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
    uart1.Init.ClockPrescaler         = UART_PRESCALER_DIV1;
    uart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if (HAL_UART_Init(&uart1) != HAL_OK)
    {
        while (1)
        {
            // Wait here if USART1 initialization fails.
        }
    }

}
// ****************************************************************************
// Function: uart1_tx
// Description: Transmits a buffer over USART1 in blocking mode.
// Parameters: pData - Buffer containing the bytes to transmit.
//             Size - Number of bytes to transmit.
//             Timeout - HAL timeout in milliseconds.
// Returns: The HAL transmit status.
// Design:
//   - Pass the buffer, length, and timeout to HAL_UART_Transmit.
//   - Return after transmission completes or HAL reports an error, busy state, or timeout.
// ****************************************************************************
HAL_StatusTypeDef uart1_tx(const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    return HAL_UART_Transmit(&uart1, pData, Size, Timeout);
}
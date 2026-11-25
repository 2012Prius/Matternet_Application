// File: uart_handle.c
// Created by Cameron on 11/21/2026
// Initializes USART1 and provides blocking transmit through the HAL.

/* Includes ------------------------------------------------------------------*/
#include "uart1.h"
#include "stm32g4xx_hal_uart.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef uart_handle;

/* Private function prototypes -----------------------------------------------*/
static void uart1_rx_callback_func(UART_HandleTypeDef *puart);
static void uart1_tx_callback_func(UART_HandleTypeDef *puart);
void USART1_IRQHandler(void);
static volatile bool rx_complete;
static volatile bool tx_complete;

/* Functions -----------------------------------------------------------------*/

// ****************************************************************************
// Function: uart_handle_init
// Description: Initializes USART1 for transmit and receive at 115200 baud.
// Parameters: None
// Returns: None
// Design:
//   - Use 8 data bits, no parity, and one stop bit without hardware flow control.
//   - Use 16x oversampling and a divide-by-1 clock prescaler.
//   - Disable one-bit sampling and leave advanced features unconfigured.
//   - Call HAL_UART_Init with the USART1 handle and halt on failure.
// ****************************************************************************
void uart_handle_init(void)
{
    uart_handle.Instance                    = USART1;
    uart_handle.Init.BaudRate               = 115200;
    uart_handle.Init.WordLength             = UART_WORDLENGTH_8B;
    uart_handle.Init.StopBits               = UART_STOPBITS_1;
    uart_handle.Init.Parity                 = UART_PARITY_NONE;
    uart_handle.Init.Mode                   = UART_MODE_TX_RX;
    uart_handle.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
    uart_handle.Init.OverSampling           = UART_OVERSAMPLING_16;
    uart_handle.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
    uart_handle.Init.ClockPrescaler         = UART_PRESCALER_DIV1;
    uart_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;



    if (HAL_UART_Init(&uart_handle) != HAL_OK)
    {
        while (1)
        {
            // TODO: Murilloc - implement Error handler
            // Wait here if USART1 initialization fails.
        }

    }


    // Define callback functions
    if (HAL_UART_RegisterCallback(&uart_handle, HAL_UART_RX_COMPLETE_CB_ID, uart1_rx_callback_func) != HAL_OK)
    {
        while (1)
        {
            // TODO: Murilloc - implement Error handler
            // Wait here if USART1 initialization fails.
        } 
    }
    if (HAL_UART_RegisterCallback(&uart_handle, HAL_UART_TX_COMPLETE_CB_ID, uart1_tx_callback_func) != HAL_OK)
    {
        while (1)
        {
            // TODO: Murilloc - implement Error handler
            // Wait here if USART1 initialization fails.
        }
    }

    //TODO: Murilloc- Should this variable be moved?
    rx_complete = false;
    tx_complete = false;
}
// ****************************************************************************
// Function: uart_handle_tx
// Description: Transmits a buffer over USART1 in blocking mode.
// Parameters: pData - Buffer containing the bytes to transmit.
//             Size - Number of bytes to transmit.
//             Timeout - HAL timeout in milliseconds.
// Returns: The HAL transmit status.
// Design:
//   - Pass the buffer, length, and timeout to HAL_UART_Transmit.
//   - Return after transmission completes or HAL reports an error, busy state, or timeout.
// ****************************************************************************
HAL_StatusTypeDef uart_handle_tx(const uint8_t *pData, uint16_t Size)
{
    return HAL_UART_Transmit_IT(&uart_handle, pData, Size);
}

HAL_StatusTypeDef uart_handle_rx(uint8_t *pData, uint16_t Size)
{
    return HAL_UART_Receive_IT(&uart_handle, pData, (uint16_t)Size);
}

void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uart_handle);
}

static void uart1_rx_callback_func(UART_HandleTypeDef *puart)
{
    rx_complete = true;
}

void set_rx_complete_status( bool status )
{
    rx_complete = status;
}

static void uart1_tx_callback_func(UART_HandleTypeDef *puart)
{
    tx_complete = true;
}

bool get_rx_complete_status( void )
{
    return rx_complete;
}
bool get_tx_complete_status( void )
{
    return tx_complete;
}
// File: uart1.h
// Declares the USART1 driver interface.

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "stm32g4xx.h"




/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function prototypes ----------------------------------------------*/
void uart_handle_init(void);
HAL_StatusTypeDef uart_handle_tx(const uint8_t *pData, uint16_t Size, uint32_t Timeout);
void uart1_rx(uint8_t *data, uint16_t len);



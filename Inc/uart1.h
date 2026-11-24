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
HAL_StatusTypeDef uart_handle_tx(const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef uart_handle_rx(uint8_t *pData, uint16_t Size);
bool get_rx_complete_status( void );
void set_rx_complete_status( bool status );
bool get_tx_complete_status( void );


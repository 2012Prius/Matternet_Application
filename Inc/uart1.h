// File: uart1.h
// Declares the USART1 driver interface.

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32g4xx.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function prototypes ----------------------------------------------*/
void uart1_init(void);
HAL_StatusTypeDef uart1_tx(const uint8_t *pData, uint16_t Size, uint32_t Timeout);
void uart1_rx(uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif
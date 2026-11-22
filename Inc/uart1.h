// Fill out the header file with the necessary includes and function prototypes for UART1 functionality
#include <stdint.h>
#include "stm32g4xx.h"

#ifdef __cplusplus
extern "C" {
#endif


// Function prototypes
void uart1_init(void);
void uart1_tx(const uint8_t *data, uint16_t len);
void uart1_rx(uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif
// File: gpio.h
// Declares the GPIO initialization interface.

#ifndef GPIO_H
#define GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx.h"


#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function prototypes ----------------------------------------------*/
void gpio_init(void);

#ifdef __cplusplus
}
#endif

#endif

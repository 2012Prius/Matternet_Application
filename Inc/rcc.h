// File: rcc.h
// Declares the RCC initialization interface.

#ifndef RCC_H
#define RCC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx.h"
#include "stm32g4xx_nucleo.h"


#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function prototypes ----------------------------------------------*/
void rcc_init(void);
void rcc_sys_clock_init(void);

#ifdef __cplusplus
}
#endif

#endif

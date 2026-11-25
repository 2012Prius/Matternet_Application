
  /**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
     STM32G4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user
         can eventually implement his proper time base source (a general purpose
         timer for example or other time source), keeping in mind that Time base
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization

  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rcc.h"
#include "gpio.h"
#include "stm32g4xx_nucleo.h"
#include "uart1.h"
#include "gpio.h"
#include <time.h>

/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

static bool rx_complete = false;
static bool tx_complete = false;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#if defined(__ICCARM__)
/* New definition from EWARM V9, compatible with EWARM8 */
int iar_fputc(int ch);
#define PUTCHAR_PROTOTYPE int iar_fputc(int ch)
#elif defined ( __CC_ARM ) || defined(__ARMCC_VERSION)
/* ARM Compiler 5/6*/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#elif defined(__GNUC__)
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif /* __ICCARM__ */



// ****************************************************************************
// Function: main
// Description: Starts the board and runs the application loop.
// Parameters: None
// Returns: Does not return.
// Design:
//   - Initialize HAL and the system clock.
//   - Enable the UART clocks and initialize the USART1 pins, driver, and board LED.
//   - Print the firmware build date and time over USART1.
//   - Keep the application running in a loop.
// ****************************************************************************
int main(void)
{

  uint8_t buffer;

  /* Initialize HAL and its default time base. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  // Initialize the UART clocks, pins, and driver, then initialize LED2.
  rcc_init();
  gpio_init();
  uart_handle_init();
  BSP_LED_Init(LED2);

  // Print the firmware build date and time.
  printf("build generated at this time: %s %s\r\n", __DATE__, __TIME__);

  while (1)
  {

    uart_handle_rx(&buffer, 1);

    //recv
    rx_complete = get_rx_complete_status();

    if(rx_complete)
    {
      //rx finished, tx data out the UART
      // rearm rx_complete ready to recieve again
      set_rx_complete_status(false);

      //TODO: Murilloc - use this if necessary
      tx_complete = tx_complete;
      uart_handle_tx(&buffer,1);
    }

    BSP_LED_Toggle(LED2);
  }
}



// ****************************************************************************
// Function: PUTCHAR_PROTOTYPE
// Description: Writes one character to the USART1 driver.
// Parameters: ch - Character to write.
//             f - Stream argument supplied by Arm C library builds.
// Returns: The transmitted byte on success, or EOF on failure.
// Design:
//   - Use the compiler-specific function name selected by PUTCHAR_PROTOTYPE.
//   - Convert ch to one byte and send it with a 100 ms timeout.
// ****************************************************************************
PUTCHAR_PROTOTYPE
{
  uint8_t byte = (uint8_t)ch;
  if (uart_handle_tx(&byte, 1) != HAL_OK)
  {
    return EOF;
  }

  return byte;
}






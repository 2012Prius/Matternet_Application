// File: rcc.c
// Configures the system clock and enables the clocks used by USART1.

/* Includes ------------------------------------------------------------------*/
#include "rcc.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void rcc_err_handler( void );

/* Functions -----------------------------------------------------------------*/

// ****************************************************************************
// Function: rcc_init
// Description: Enables the GPIOC and USART1 peripheral clocks.
// Parameters: None
// Returns: None
// Design:
//   - Enable GPIOC on AHB2 so its USART1 pins can be configured.
//   - Enable USART1 on APB2 before initializing the peripheral.
// ****************************************************************************
void rcc_init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  // Enable GPIO clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Enable UART1 Clock
}

// ****************************************************************************
// Function: SystemClock_Config
// Description: Sets the system and bus clocks to 170 MHz.
// Parameters: None
// Returns: None
// Design:
//   - Select voltage scale 1 boost and use the internal HSI oscillator as the PLL input.
//   - Switch SYSCLK to the PLL output and set the AHB and both APB prescalers to divide by one.
//   - Set flash latency to four wait states and call rcc_err_handler if the oscillator or clock setup fails.
// ****************************************************************************
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    rcc_err_handler();  
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    rcc_err_handler();
  }
}

// ****************************************************************************
// Function: rcc_err_handler
// Description: Stops startup after a system clock configuration failure.
// Parameters: None
// Returns: Does not return.
// Design:
//   - Toggle LED2 and wait 500 ms on each iteration.
// ****************************************************************************
void rcc_err_handler(void)
{

  while (1)
  {
    /* Toggle LED2 for error */
    BSP_LED_Toggle(LED2);
    HAL_Delay(500);
  }

}
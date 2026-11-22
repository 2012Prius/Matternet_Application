//  File: rcc.c
//  This file contains the RCC setup for the UART1 driver.
//  Functions include:
//
//  init (TODO: Murilloc)

//Includes
#include "rcc.h"

// Macros
// Static Variables
// Functions

// ****************************************************************************
// Function: rcc_init
// Description: Configures the GPIOC and USART1 clocks for UART1.
// Parameters: None
// Returns: None
// Design:
//   - TODO: Murilloc
// ****************************************************************************
void rcc_init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  // Enable GPIO clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Enable UART1 Clock
}

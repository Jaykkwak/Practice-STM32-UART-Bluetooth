/*
 * stm32f407xx_rcc_driver.h
 *
 *  Created on: Apr 6, 2024
 *      Author: me
 */

#ifndef STM32F407XX_RCC_DRIVER_H_
#define STM32F407XX_RCC_DRIVER_H_

//This returns the APB1 clock value
uint32_t RCC_GetPCLK1Value(void);

//This returns the APB2 clock value
uint32_t RCC_GetPCLK2Value(void);


uint32_t  RCC_GetPLLOutputClock(void);

#endif /* STM32F407XX_RCC_DRIVER_H_ */

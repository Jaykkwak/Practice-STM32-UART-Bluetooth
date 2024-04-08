/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f407xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

USART_Handle_t usart2_handle;
uint8_t rx_buff[1024];

void GPIO_LEDInit(void)
{
	GPIO_Handle_t GpioLed;

	//this is led gpio configuration
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0 | GPIO_PIN_NO_1 | GPIO_PIN_NO_2 | GPIO_PIN_NO_3;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&GpioLed);

}

void USART2_GPIOInit(void)
{
	GPIO_Handle_t usart_gpios;

	usart_gpios.pGPIOx = GPIOA;
	usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode =7;

	usart_gpios.GPIO_PinConfig.GPIO_PinNumber  = GPIO_PIN_NO_2;
	GPIO_Init(&usart_gpios);

	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&usart_gpios);

}


void USART2_Init(void)
{
	usart2_handle.pUSARTx = USART2;
	usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_9600;
	usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_RX;
	usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(&usart2_handle);
}


void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

int main(void)
{
	GPIO_LEDInit();

	USART2_GPIOInit();

	USART2_Init();

	USART_IRQInterruptConfig(IRQ_NO_USART2, ENABLE);

//	USART_IRQPriorityConfig(IRQ_NO_USART2, 0);

	USART_PeripheralControl(USART2,ENABLE);

	while(1){
		//First lets enable the reception in interrupt mode
		//this code enables the receive interrupt
		while ( USART_ReceiveDataIT(&usart2_handle,rx_buff,1) != USART_READY );

	}

}


void USART2_IRQHandler(void)
{
	USART_IRQHandling(&usart2_handle);

	if(rx_buff =='A'){
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_0, GPIO_PIN_SET);
		delay();
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_0, GPIO_PIN_RESET);
	}
	else if(rx_buff == 'B'){
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_1, GPIO_PIN_SET);
		delay();
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_1, GPIO_PIN_RESET);
	}else if(rx_buff == 'C'){
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_2, GPIO_PIN_SET);
		delay();
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_2, GPIO_PIN_RESET);
	}
	else{
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_3, GPIO_PIN_SET);
		delay();
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_3, GPIO_PIN_RESET);
	}
}

void USART_ApplicationEventCallback( USART_Handle_t *pUSARTHandle,uint8_t ApEv)
{
   if(ApEv == USART_EVENT_RX_CMPLT)
   {
			rxCmplt = SET;

   }else if (ApEv == USART_EVENT_TX_CMPLT)
   {
	   ;
   }
}

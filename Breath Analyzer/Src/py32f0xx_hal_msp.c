/**
  ******************************************************************************
  * @file    py32f0xx_hal_msp.c
  * @author  MCU Application Team
  * @brief   This file provides code for the MSP Initialization
  *          and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief 初始化全局MSP
  */
void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
		if(hadc->Instance == ADC1)
			__HAL_RCC_ADC_CLK_ENABLE();
		
		GPIO_InitTypeDef pin;
		pin.Mode = GPIO_MODE_ANALOG;
		pin.Pin = 6;
		pin.Pull = GPIO_NOPULL;
		
		HAL_GPIO_Init(GPIOA, &pin);
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance ==  I2C1)
		__HAL_RCC_I2C_CLK_ENABLE();
	
	GPIO_InitTypeDef pin;
	pin.Mode = GPIO_MODE_AF_OD;
	pin.Pin = GPIO_PIN_0;
	pin.Pull = GPIO_NOPULL;
	pin.Speed = GPIO_SPEED_FREQ_HIGH;
	pin.Alternate = GPIO_AF12_I2C;
	
	HAL_GPIO_Init(GPIOF, &pin);
	
	pin.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOF, &pin);
}
/************************ (C) COPYRIGHT Puya *****END OF FILE******************/

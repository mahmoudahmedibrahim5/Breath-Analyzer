/* 
 * Author: Mahmoud Ahmed 
 * Date: 16 Sep, 2024
 *
 * Target: PY32F002Ax5
 * Project name: Breath Analyzer
 * Description:
 * 
*/

#ifndef __MAIN_H
#define __MAIN_H

#include "py32f0xx_hal.h"
#include "ssd1306.h"

void SYSTICK_voidInit(void);
void GPIO_voidInit(void);
void ADC_voidInit(void);
void I2C_voidInit(void);



#endif /* __MAIN_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/

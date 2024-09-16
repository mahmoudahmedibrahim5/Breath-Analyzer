/* 
 * Author: Mahmoud Ahmed 
 * Date: 16 Sep, 2024
 *
 * Target: PY32F002Ax5
 * Project name: Breath Analyzer
 * Description:
 * 
*/

#include "main.h"

void delay(uint32_t nTime)
{
		while(nTime--);
}

int main(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	
	GPIO_InitTypeDef led;
	led.Mode = GPIO_MODE_OUTPUT_PP;
	led.Pin = GPIO_PIN_1;
	led.Pull = GPIO_NOPULL;
	led.Speed = GPIO_SPEED_FREQ_LOW;
	led.Alternate = 0;
	
	HAL_GPIO_Init(GPIOA, &led);
	
	I2C_HandleTypeDef test;
	test.Instance = I2C1;
	test.Init.ClockSpeed = 400000;
	test.Init.DutyCycle = I2C_DUTYCYCLE_2;
	test.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	test.Init.OwnAddress1 = 0x00;
	test.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	
	HAL_I2C_Init(&test);
	
	uint8_t data[6] = "Hello\n";
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		HAL_I2C_Master_Transmit(&test, 0x78, data, 6, 5000);
		delay(0x3FFFF);
  }
}

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
#include "ssd1306.h"

void delay(uint32_t nTime)
{
		while(nTime--);
}
I2C_HandleTypeDef test;
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
	
	
	test.Instance = I2C1;
	test.Init.ClockSpeed = 400000;
	test.Init.DutyCycle = I2C_DUTYCYCLE_2;
	test.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	test.Init.OwnAddress1 = 0x00;
	test.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	
	HAL_I2C_Init(&test);
	delay(0x3FFFF);
		SSD1306_Init();
		SSD1306_Clear();
		SSD1306_GotoXY(24, 25);
		SSD1306_Puts("Saba7o", &Font_11x18, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		delay(0x3FFFF);
  }
}

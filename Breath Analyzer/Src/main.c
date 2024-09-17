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

/* GLobal Variables */
I2C_HandleTypeDef screen;
ADC_HandleTypeDef sensor;

int main(void)
{
	/* Peripheral Initialization */
	SYSTICK_voidInit();
	GPIO_voidInit();
	I2C_voidInit();
	
	/* OLED Initialize */
	SSD1306_Init();
	SSD1306_Clear();
	
	/* Example Print */
	SSD1306_GotoXY(24, 25);
	SSD1306_Puts("Saba7o", &Font_11x18, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
	
	while(1)
	{
		/* Blink PA1 LED */
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		HAL_Delay(500);
  }
}

void SYSTICK_voidInit(void)
{
	/* Use systick as time base source and configure 1ms tick (default clock after Reset is HSI) */
  HAL_InitTick(TICK_INT_PRIORITY);
}

void GPIO_voidInit(void)
{
	/* RCC Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	
	/* LED (PA1) Initialize */
	GPIO_InitTypeDef led;
	led.Mode = GPIO_MODE_OUTPUT_PP;
	led.Pin = GPIO_PIN_1;
	led.Pull = GPIO_NOPULL;
	led.Speed = GPIO_SPEED_FREQ_LOW;
	led.Alternate = 0;
	
	HAL_GPIO_Init(GPIOA, &led);
}

void ADC_voidInit(void)
{
	/* ADC channel? (Sensor) Initialize */
	sensor.Instance = ADC1;
	
	HAL_ADC_Init(&sensor);
}

void I2C_voidInit(void)
{
	/* I2C For OLED Initialize */
	screen.Instance = I2C1;
	screen.Init.ClockSpeed = 400000;
	screen.Init.DutyCycle = I2C_DUTYCYCLE_2;
	screen.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	screen.Init.OwnAddress1 = 0x00;
	screen.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	
	HAL_I2C_Init(&screen);
}

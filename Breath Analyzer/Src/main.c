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
	ADC_voidInit();
	I2C_voidInit();
	
	/* OLED Initialize */
	SSD1306_Init();
	SSD1306_Clear();
	
	uint32_t sensorVal = 10;
	while(1)
	{
		HAL_ADC_Start(&sensor);
		sensorVal = HAL_ADC_GetValue(&sensor);
		Screen_showPotValue(sensorVal);
		HAL_Delay(100);
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
	/* ADC1 Initialize */
	sensor.Instance = ADC1;
	sensor.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
	sensor.Init.Resolution = ADC_RESOLUTION_12B;
	sensor.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	sensor.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
	sensor.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	sensor.Init.LowPowerAutoWait = DISABLE;
	sensor.Init.ContinuousConvMode = DISABLE;
	sensor.Init.DiscontinuousConvMode = DISABLE;
	sensor.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	sensor.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	sensor.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	sensor.Init.SamplingTimeCommon = ADC_SAMPLETIME_3CYCLES_5;
	
	HAL_ADC_Init(&sensor);
	
	/* Channel 6 (Sensor) Configuration */
	ADC_ChannelConfTypeDef channel;
	channel.Channel = ADC_CHANNEL_6;
	channel.Rank = 1;
	channel.SamplingTime = ADC_SAMPLETIME_3CYCLES_5;
	
	HAL_ADC_ConfigChannel(&sensor, &channel);
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

void Screen_showPotValue(uint32_t val)
{
	/* Map the analog value to milli volt */
	val = (val * 3300) / 4096;
	
	/* Write the value in string */
	uint8_t data[5] = "0000";
	data[4] = '\0';
	data[3] = '0' + ((val % 10) / 1);
	data[2] = '0' + ((val % 100) / 10);
	data[1] = '0' + ((val % 1000) / 100);
	data[0] = '0' + ((val % 10000) / 1000);
	
	/* Delete the left zeros */
	if(val < 1000)
		data[0] = ' ';
	if(val < 100)
		data[1] = ' ';
	if(val < 10)
		data[2] = ' ';
	
	/* Display the Data */
	SSD1306_GotoXY(0, 25);
	SSD1306_Puts("Volt = ", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_Puts((char *)data, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_Puts(" mV", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
}
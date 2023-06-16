#include <stdio.h>
#include "stm32f3xx_hal.h"

HAL_StatusTypeDef status;
uint32_t adc_values[10];

void CLKEnable(GPIO_TypeDef* GPIOx)
{
	if(GPIOx == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	if(GPIOx == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	if(GPIOx == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	if(GPIOx == GPIOD)
		__HAL_RCC_GPIOD_CLK_ENABLE();
	if(GPIOx == GPIOF)
		__HAL_RCC_GPIOF_CLK_ENABLE();
}

void buttonInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Port Clock Enable */
	CLKEnable(GPIOx);

	/*Configure GPIO pin : PC13 */
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void buttonDeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
	HAL_GPIO_DeInit(GPIOx,GPIO_Pin);
}

void ADC_Init(ADC_HandleTypeDef hadc, uint32_t ADC_CHANNEL)
{
	ADC_MultiModeTypeDef multimode = {0};
	ADC_ChannelConfTypeDef sConfig = {0};

	/** Common config
	 */
	hadc.Instance = ADC1;
	hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc.Init.ContinuousConvMode = DISABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.NbrOfConversion = 1;
	hadc.Init.DMAContinuousRequests = DISABLE;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc.Init.LowPowerAutoWait = DISABLE;
	hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	if (HAL_ADC_Init(&hadc) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure the ADC multi-mode
	  */
	multimode.Mode = ADC_MODE_INDEPENDENT;
	if (HAL_ADCEx_MultiModeConfigChannel(&hadc, &multimode) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Regular Channel
	  */
	sConfig.Channel = ADC_CHANNEL;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
	    Error_Handler();
	}
}

void ADC_DeInit(ADC_HandleTypeDef* hadc)
{
	HAL_ADC_DeInit(hadc);
}

void ADC_Calibration(ADC_HandleTypeDef* hadc, uint32_t SingleDiff)
{
	HAL_ADCEx_Calibration_Start(hadc, SingleDiff);
}

HAL_StatusTypeDef ADC_Start(ADC_HandleTypeDef* hadc)
{
	return HAL_ADC_Start(hadc);
}

HAL_StatusTypeDef ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout)
{
	return HAL_ADC_PollForConversion(hadc, Timeout);
}

uint32_t ADC_GetValue(ADC_HandleTypeDef* hadc)
{
	return HAL_ADC_GetValue(hadc);
}

void teste_ADC(ADC_HandleTypeDef* hadc)
{
	ADC_Calibration(hadc, ADC_SINGLE_ENDED);
	status = ADC_Start(hadc);
	uint32_t avrg_value=0;
	if (status != HAL_OK)
	{
		Error_Handler();
	}

	status = ADC_PollForConversion(hadc, 100);
	if (status != HAL_OK)
	{
		Error_Handler();
	}
	for(int i=0; i<10;i++){
		adc_values[i] = ADC_GetValue(hadc);
		avrg_value+=adc_values[i];
	}
	avrg_value = avrg_value/10;
	//tensao_media = avrg_value*Vref/4095

}

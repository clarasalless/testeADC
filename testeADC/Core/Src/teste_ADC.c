/**
  ******************************************************************************
  * @file    teste_ADC.c
  * @author  Clara Luz Salles Cavalcante
  * 		 Danilo Mota Alencar Filho
  * @brief   O objetivo deste arquivo é testar a funcionalidade
  * 		 do conversor analógico digital do dispositivo.
  *
  ******************************************************************************/



/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f3xx_hal.h"


HAL_StatusTypeDef status;
ADC_HandleTypeDef hadc;

/**
  * @brief  Inicializa o clock do GPIOx especificado.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @retval None
  */
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

/**
  * @brief  Inicializa GPIOx especificado para ser utilizado como botão no teste.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @param  GPIO_Pin especifica o pino a ser inicializado.
  * @retval None
  */
void buttonInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Port Clock Enable */
	CLKEnable(GPIOx);

	/*Configure GPIO pin : */
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
  * @brief  Deinicializa o pino do GPIO especificado.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @param  GPIO_Pin especifica o pino a ser deinicializado.
  * @retval None
  */
void buttonDeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
	HAL_GPIO_DeInit(GPIOx,GPIO_Pin);
}

/**
  * @brief  Lê o valor de entrada do pino da porta especificada.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @param  GPIO_Pin especifica o pino a ser lido.
  * @retval O valor do pino da porta especificada.
  */
GPIO_PinState GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

/**
  * @brief  Retorna um valor de tick em milisegundos.
  * @retval tick value
  */
uint32_t GetTick(void)
{
	return HAL_GetTick();
}

/**
  * @brief  Inicializa canal do ADC especificado para a realização do teste.
  * @param  hadc ADC handle
  * @param  ADC_CHANNEL Canal a ser inicializado
  * @retval HAL status
  */
void ADC_Init(ADC_HandleTypeDef *hadc, ADC_TypeDef* ADC, uint32_t ADC_CHANNEL)
{
	 /* USER CODE BEGIN ADC1_Init 0 */
	//ADC_HandleTypeDef hadc;
	  /* USER CODE END ADC1_Init 0 */

	  ADC_MultiModeTypeDef multimode = {0};
	  ADC_ChannelConfTypeDef sConfig = {0};

	  /* USER CODE BEGIN ADC1_Init 1 */

	  /* USER CODE END ADC1_Init 1 */

	  /** Common config
	  */
	  hadc-> Instance = ADC;
	  hadc -> Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	  hadc -> Init.Resolution = ADC_RESOLUTION_12B;
	  hadc -> Init.ScanConvMode = ADC_SCAN_DISABLE;
	  hadc -> Init.ContinuousConvMode = DISABLE;
	  hadc -> Init.DiscontinuousConvMode = DISABLE;
	  hadc -> Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  hadc -> Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  hadc -> Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc -> Init.NbrOfConversion = 1;
	  hadc -> Init.DMAContinuousRequests = DISABLE;
	  hadc -> Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	  hadc -> Init.LowPowerAutoWait = DISABLE;
	  hadc -> Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	  if (HAL_ADC_Init(hadc) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  /** Configure the ADC multi-mode
	  */
	  multimode.Mode = ADC_MODE_INDEPENDENT;
	  if (HAL_ADCEx_MultiModeConfigChannel(hadc, &multimode) != HAL_OK)
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
	  if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /* USER CODE BEGIN ADC1_Init 2 */

	  /* USER CODE END ADC1_Init 2 */

}

ADC_HandleTypeDef ADC_HandleConfiguration(ADC_HandleTypeDef hadc_origin)
{
	hadc_origin.Instance = ADC1;
	hadc_origin.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc_origin.Init.Resolution = ADC_RESOLUTION_12B;
	hadc_origin.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc_origin.Init.ContinuousConvMode = DISABLE;
	hadc_origin.Init.DiscontinuousConvMode = DISABLE;
	hadc_origin.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc_origin.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc_origin.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc_origin.Init.NbrOfConversion = 1;
	hadc_origin.Init.DMAContinuousRequests = DISABLE;
	hadc_origin.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc_origin.Init.LowPowerAutoWait = DISABLE;
	hadc_origin.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;

	return hadc_origin;

}

/**
  * @brief  Deinicializa o ADC especificado.
  * @param  hadc ADC handle.
  * @retval None
  */
void ADC_DeInit(ADC_HandleTypeDef* hadc)
{
	HAL_ADC_DeInit(hadc);
}

/**
  * @brief  Realiza auto-calibração do ADC
  *         Pre-requisito: ADC precisa estar desativado (executar esta função antes de
  *         ADC_Start() ou depois de ADC_Stop()).
  * @param  hadc ADC handle
  * @param  SingleDiff Seleção de modo de entrada single-ended ou differential input
  *          Este parâmetro pode assumir um dos seguintes valores:
  *            @arg ADC_SINGLE_ENDED: Canal em modo de single ended
  *            @arg ADC_DIFFERENTIAL_ENDED: Canal em modo differential ended
  * @retval HAL status
  */
void ADC_Calibration(ADC_HandleTypeDef* hadc, uint32_t SingleDiff)
{
	HAL_ADCEx_Calibration_Start(hadc, SingleDiff);
}

/**
  * @brief  Inicia o ADC e começa a conversão.
  * @param  hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef ADC_Start(ADC_HandleTypeDef* hadc)
{
	return HAL_ADC_Start(hadc);
}

/**
  * @brief  Espera as conversões serem concluidas.
  * @param  hadc ADC handle
  * @param  Timeout Valor do tempo de espera em milisegundos
  * @retval HAL status
  */
HAL_StatusTypeDef ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout)
{
	return HAL_ADC_PollForConversion(hadc, Timeout);
}

/**
  * @brief  Recebe o valor do ADC após conversão.
  * @param  hadc ADC handle
  * @retval Valor convertido
  */
uint32_t ADC_GetValue(ADC_HandleTypeDef* hadc)
{
	return HAL_ADC_GetValue(hadc);
}

uint32_t teste_ADC(ADC_HandleTypeDef* hadc, uint32_t* adc_values, int size)
{
	status = ADC_Start(hadc);
	uint32_t avrg_value = 0;

	if (status != HAL_OK)
	{
		Error_Handler();
	}

	status = ADC_PollForConversion(hadc, 100);
	if (status != HAL_OK)
	{
		Error_Handler();
	}
	for(int i=0; i<size; i++){
		adc_values[i] = ADC_GetValue(hadc);
		avrg_value = avrg_value + adc_values[i];
	}
	avrg_value = avrg_value*3300/40950;
	return avrg_value;

}

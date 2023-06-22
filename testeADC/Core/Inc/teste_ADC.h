/**
  ******************************************************************************
  * @file    teste_ADC.h
  * @author  Clara Luz Salles Cavalcante
  * 		 Danilo Mota Alencar Filho
  * @brief   Cabeçalho para arquivo de teste de conversor analógico digital.
  ******************************************************************************
  */

/* Protótipos das funções ------------------------------------------------------------------*/
void CLKEnable(GPIO_TypeDef* GPIOx);
void buttonInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void buttonDeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
GPIO_PinState GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void ADC_Init(ADC_HandleTypeDef hadc, uint32_t ADC_CHANNEL);
void ADC_DeInit(ADC_HandleTypeDef* hadc);
void ADC_Calibration(ADC_HandleTypeDef* hadc, uint32_t SingleDiff);
HAL_StatusTypeDef ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);
uint32_t ADC_GetValue(ADC_HandleTypeDef* hadc);
uint32_t teste_ADC(ADC_HandleTypeDef* hadc);

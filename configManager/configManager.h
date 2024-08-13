#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_
#include "main.h"

extern ADC_HandleTypeDef   hadc1;
extern DMA_HandleTypeDef   hdma_adc1;
extern TIM_HandleTypeDef   htim1;
extern UART_HandleTypeDef  huart1;

extern uint32_t adc_value;

extern uint8_t  RxData[4];
extern uint32_t pwm_factor;
extern uint32_t  adc_dma_result[1];

void config_functions(void);


void SystemClock_Config(void);
void MPU_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_TIM1_Init(void);
void MX_ADC1_Init(void);
void MX_USART1_UART_Init(void);

#endif


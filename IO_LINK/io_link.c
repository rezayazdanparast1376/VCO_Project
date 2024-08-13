#include "main.h"
#include "io_link.h"
#include "stm32h7b0xx.h"
#include "stm32h7xx_hal.h"
#include "../configManager/configManager.h"

#include "stdbool.h"

void receive_all(void) {
    receive_analog();
    receive_usart();
}


void receive_analog(void) {
    adc_value = HAL_ADC_GetValue(&hadc1);
}




bool uart1_recev_cmp = false;

void receive_usart(void) {
    if (uart1_recev_cmp == true) {
        uint32_t receive_number =  (RxData[3] << 0) | (RxData[2] << 8) | (RxData[1] << 16) | (RxData[0] << 24);
        if (receive_number <= 100) {
            pwm_factor = receive_number;
        }
        uart1_recev_cmp = false;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        uart1_recev_cmp = true;
    }
    //TODO: Implementation for other usart interface ...
}

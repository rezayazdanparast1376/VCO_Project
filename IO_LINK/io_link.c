#include "main.h"
#include "io_link.h"
#include "stm32h7b0xx.h"
#include "stm32h7xx_hal.h"
#include "../OtherLibs/RawBuffer.h"
#include "../configManager/configManager.h"

void receive_all(void) {
    receive_analog();
    receive_usart();
}




#define RECEIVE_BUFFER_LENGTH 300  //about double of the max mavlink packet size
uint8_t buf[RECEIVE_BUFFER_LENGTH];

void receive_usart(void) {
    
    int32_t  len = 0;
	int      max_len = RECEIVE_BUFFER_LENGTH;
    // HAL_UART_Receive(&huart1, msg)
    do {
        raw_buff_uart_addr->ERR = 0;
        len = rbPull(raw_buff_uart_addr, 1, buf, max_len, 0);
        
        
    } while (len > 0);

    if (len > 0) {
        uint8_t elem_0 = buf[0];
        uint8_t elem_1 = buf[1];
    }
        
}


void receive_analog(void) {
    adc_value = HAL_ADC_GetValue(&hadc1);
}


uint8_t recev_buf[1] = {0};
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        HAL_UART_Receive_IT(&huart1, recev_buf, 1);
        rbPush(raw_buff_uart_addr, 1, recev_buf, 1);
    }

    if (huart->Instance == USART2) {
        //TODO: Implementation ...
    }
    if (huart->Instance == USART3) {
        //TODO: Implementation ...
    }
    if (huart->Instance == USART6) {
        //TODO: Implementation ...
    }
    if (huart->Instance == USART10) {
        //TODO: Implementation ...
    }
    
    
}

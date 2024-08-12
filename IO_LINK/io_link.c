#include "io_link.h"
#include "main.h"
#include "../configManager/configManager.h"
void receive_all(void) {
    receive_analog();
}



void receive_analog(void) {
    adc_value = HAL_ADC_GetValue(&hadc1);
}

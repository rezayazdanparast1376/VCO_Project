#include "configManager.h"

void generate_pulse(void) {
    double   arr_factor = rescale(adc_value, 0, 65535, 1, 10);
    uint32_t arr_final  = (1000) / arr_factor;
    
    TIM1->ARR = arr_final;
    uint32_t pre_arr = __HAL_TIM_GET_AUTORELOAD(&htim1);
    if (pre_arr > 2) {
        TIM1->CCR1 = (pre_arr / 2);
    }
}

#include <stdint.h>
#include "../../configManager/configManager.h"
#include "../../OtherLibs/other_lib.h"
#include "vco.h"
#include "vco_config.h"


/**
 * @brief 
 * 
 *  F(pwm) = (F(cpu)) / (1 + ARR) (1 + Pre_Scaler)
 * 
 *  F(pwm) = 64MHz / (1 + ARR) (1 + 63)     ==>   F(pwm) = 1MHz / (1 + ARR) 
 * 
 */

void initialize_pwm_signal(void) {
    __HAL_TIM_SET_PRESCALER(&htim1, DEFAULT_PRE_SCALER);      //TIM1->PSC   = DEFAULT_PRE_SCALER;
    __HAL_TIM_SET_AUTORELOAD(&htim1, DEFAULT_ARR);            //TIM1->CCR1  = DEFAULT_CRR;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, DEFAULT_CRR);//TIM1->ARR   = DEFAULT_ARR;
}


void generate_pulse(void) {
    double   arr_factor = rescale(adc_value, 0, 65535, 1, 10);
    uint32_t arr_final  = (1000) / arr_factor;
    
    TIM1->ARR = arr_final;
    uint32_t pre_arr = __HAL_TIM_GET_AUTORELOAD(&htim1);

    if (pre_arr > 2) {//Set Duty cycle to 50%
        TIM1->CCR1 = (pre_arr / 2);
    }
}

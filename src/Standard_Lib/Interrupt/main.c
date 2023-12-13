#include "stm32f10x.h"
#include "lib.h"


void EXTI2_IRQHandler() {
    if(EXTI_GetITStatus(EXTI_Line2) != RESET) {
        // 按键按下，执行相应的操作
        uint32_t temp = TIM_GetCounter(TIM2);
        if ((BitAction)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET) {        // 按键按下
            delay(20);                                                               // 消抖
            if ((BitAction)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET) {     // 确认按下
                GPIO_WriteBit(LED_PORT, LED_PIN_6, (BitAction)!GPIO_ReadInputDataBit(LED_PORT, LED_PIN_6));     // 翻转LED
                while ((BitAction)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET);                // 等待按键释放
            }
        }
        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line2);
        TIM_SetCounter(TIM2, temp);
    }
}

void TIM2_IRQHandler() {
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        // 这里进行中断处理
        GPIO_WriteBit(LED_PORT, LED_PIN_5, (BitAction)!GPIO_ReadInputDataBit(LED_PORT, LED_PIN_5));
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}


int main() {
    TIM2_Init();
    TIM3_Init();

    KEY_PIN_Init();
    LED_PIN_Init();
    Interrupt_Init();
    
    GPIO_WriteBit(LED_PORT, LED_PIN_6, Bit_RESET);
    GPIO_WriteBit(KEY_PORT, KEY_PIN, Bit_SET);

    while(1)
    {
        
    }

    return 0;
}
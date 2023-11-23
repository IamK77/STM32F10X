/*
 * ************************************************
 * 
 *              STM32 blink gcc demo
 * 
 *  CPU: STM32F103C8
 *  PIN: PA2 -> KEY
 *      PA1 -> LED
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

#define LED_PERIPH RCC_APB2Periph_GPIOA
#define LED_PORT GPIOA
#define LED_PIN GPIO_Pin_1

#define KEY_PERIPH RCC_APB2Periph_GPIOA
#define KEY_PORT GPIOA
#define KEY_PIN GPIO_Pin_2


void TIM2_Init(void)
{
    /* 
     * 这里进行初始化
     * 用psc分到1MHz
     * arr设65535让它一直计数
     */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1;  // 72000000 / 1000000 = 72
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM2, ENABLE);
}

void GPIO_Pin_Init(void)
{
    GPIO_InitTypeDef gpioDef_PP;
    GPIO_InitTypeDef gpioDef_IPU;

    RCC_APB2PeriphClockCmd(LED_PERIPH, ENABLE);
    RCC_APB2PeriphClockCmd(KEY_PERIPH, ENABLE);

    gpioDef_PP.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioDef_PP.GPIO_Pin = LED_PIN;
    gpioDef_PP.GPIO_Speed = GPIO_Speed_10MHz;

    gpioDef_IPU.GPIO_Mode = GPIO_Mode_IPU;  
    gpioDef_IPU.GPIO_Pin = KEY_PIN;
    gpioDef_IPU.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(LED_PORT, &gpioDef_PP);
    GPIO_Init(KEY_PORT, &gpioDef_IPU);
}

void delay_us(uint32_t us)
{
    /* 
     * 这里进行延时
     * 用us参数来计数
     * 每次计数就设cnt为0
     * 循环等待cnt达到us
     */
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < us);
}


void delay_ms(uint32_t ms)
{
    for(uint32_t i=0; i<ms; i++)
        delay_us(1000);
}

int main()
{
    TIM2_Init();
    GPIO_Pin_Init();

    while (1)
    { 
        if ((BitAction)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET) {        // 按键按下
            delay_ms(30);                                                               // 消抖
            if ((BitAction)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET) {     // 确认按下
                GPIO_WriteBit(LED_PORT, LED_PIN, (BitAction)!GPIO_ReadInputDataBit(LED_PORT, LED_PIN));     // 翻转LED
                while ((BitAction)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET);                // 等待按键释放
            }
        }
    }
}

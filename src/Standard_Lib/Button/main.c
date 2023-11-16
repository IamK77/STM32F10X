/*
 * ************************************************
 * 
 *              STM32 blink gcc demo
 * 
 *  CPU: STM32F103C8
 *  PIN: PA2 | PA12
 * 
 * ************************************************
*/

#include "stm32f10x.h"

#define LED_PERIPH RCC_APB2Periph_GPIOB
#define LED_PORT GPIOB
#define LED_PIN GPIO_Pin_12

#define KEY_PERIPH RCC_APB2Periph_GPIOA
#define KEY_PORT GPIOA
#define KEY_PIN GPIO_Pin_2                                                                                                                                                                                                                                       


void delay(int x)
{
    for (int i = 0; i < x; i++){
        for (int j = 0; j < 1000; j++)
            __NOP();
    }
}


int main()
{
    TIM2_Init();

    GPIO_InitTypeDef gpioDef_led;
    GPIO_InitTypeDef gpioDef_key;
    RCC_APB2PeriphClockCmd(LED_PERIPH, ENABLE);
    RCC_APB2PeriphClockCmd(KEY_PERIPH, ENABLE);

    gpioDef_led.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioDef_led.GPIO_Pin = LED_PIN;
    gpioDef_led.GPIO_Speed = GPIO_Speed_50MHz;

    gpioDef_key.GPIO_Mode = GPIO_Mode_IPU;
    gpioDef_key.GPIO_Pin = KEY_PIN;
    gpioDef_key.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LED_PORT, &gpioDef_led);
    GPIO_Init(KEY_PORT, &gpioDef_key);

    GPIO_WriteBit(LED_PORT, LED_PIN, Bit_RESET);
    GPIO_WriteBit(KEY_PORT, KEY_PIN, Bit_SET);

    while (1)
    { 
        if ((BitAction)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET) {        // 按键按下
            delay(30);                                                               // 消抖
            if ((BitAction)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET) {     // 确认按下
                GPIO_WriteBit(LED_PORT, LED_PIN, (BitAction)!GPIO_ReadInputDataBit(LED_PORT, LED_PIN));     // 翻转LED
                while ((BitAction)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET);                // 等待按键释放
            }
        }
    }
}

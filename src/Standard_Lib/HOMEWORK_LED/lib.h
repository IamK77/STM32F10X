#pragma once

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

#define LED_PORT GPIOA

int ledPin[4] = {GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7, GPIO_Pin_8};

/*------------------ GPIO PIN INIT ------------------*/ 
void LED_Init()
{
    GPIO_InitTypeDef gpioDef;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    gpioDef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioDef.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
    gpioDef.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(LED_PORT, &gpioDef);

    for (int i = 0; i < 4; i++)
    {
        GPIO_WriteBit(LED_PORT, ledPin[i], Bit_RESET);
    }
}

/* ------------------- Timer ----------------------*/
void TIM2_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_Cmd(TIM2, ENABLE);
}

void delay_us(uint32_t us)
{
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < us);
}

void delay(uint32_t ms)
{
    for(uint32_t i=0; i<ms; i++)
        delay_us(1000);
}

/* ------------------- Funtion ----------------------*/
void LED_ON(int wait) { for (int i = 0; i < 4; i++) { GPIO_WriteBit(LED_PORT, ledPin[i], Bit_SET); delay(wait); } }

void LED_OFF(int wait) { for (int i = 0; i < 4; i++) { GPIO_WriteBit(LED_PORT, ledPin[i], Bit_RESET); delay(wait); } }

void LED_Gradually()
{
    LED_ON(1000);
    delay(5000);
    LED_OFF(1000);
}

void LED_TEN_TIMES()
{
    for (int i = 0; i < 5; i++)
    {
        LED_ON(0);
        delay(1000);
        LED_OFF(0);
        delay(1000);
    }
}

void LED_ONLE_ZERO_AND_ONE_ON()
{
    GPIO_WriteBit(LED_PORT, ledPin[0], Bit_SET);
    GPIO_WriteBit(LED_PORT, ledPin[1], Bit_SET);
    delay(5000);
}

void LED_END()
{
    LED_OFF(0);
    delay(3000); // keep silence 3s
}
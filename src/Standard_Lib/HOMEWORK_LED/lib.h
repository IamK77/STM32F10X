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
void TIM2_Init()
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
void LED_ON(int i) {
    GPIO_WriteBit(LED_PORT, ledPin[i], Bit_SET);
}

void LED_OFF(int i) {
    GPIO_WriteBit(LED_PORT, ledPin[i], Bit_RESET);
}

void LED_Gradually()
{
    for (int i = 0; i < 4; i++)
    {
        LED_ON(i);
        delay(1000);
    }

    delay(5000);

    for (int i = 0; i < 4; i++)
    {
        LED_OFF(i);
        delay(1000);
    }
}

void LED_TEN_TIMES()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            LED_ON(j);
        }
        delay(1000);
        for (int j = 0; j < 4; j++)
        {
            LED_OFF(j);
        }
        delay(1000);
    }

    delay(4000);
}

void LED_ONLE_ZERO_AND_ONE_ON()
{
    LED_ON(0);
    LED_ON(1);
    delay(5000);
}

void LED_END()
{
    for (int i = 0; i < 4; i++)
    {
        LED_OFF(i);
    }
    delay(3000); // keep silence 3s
}
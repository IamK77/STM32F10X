#pragma once

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

#define KEY_PERIPH RCC_APB2Periph_GPIOA
#define KEY_PORT GPIOA
#define KEY_PIN GPIO_Pin_2

#define LED_PERIPH RCC_APB2Periph_GPIOA
#define LED_PORT GPIOA
#define LED_PIN_5 GPIO_Pin_5
#define LED_PIN_6 GPIO_Pin_6

/* ------------------- Timer ----------------------*/
void TIM2_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_Cmd(TIM2, ENABLE);
}

void TIM3_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_Cmd(TIM3, ENABLE);
}

void delay_us(uint32_t us)
{
    TIM_SetCounter(TIM3, 0);
    while (TIM_GetCounter(TIM3) < us);
}

void delay(uint32_t ms)
{
    for(uint32_t i=0; i<ms; i++)
        delay_us(1000);
}

/*----------------------KEY & LED-----------------------*/
void KEY_PIN_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 启用GPIOA的时钟
    RCC_APB2PeriphClockCmd(KEY_PERIPH, ENABLE);

    // 配置GPIOA2为输入模式，并启用内部上拉电阻
    GPIO_InitStructure.GPIO_Pin = KEY_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);
}

void LED_PIN_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 启用GPIOA的时钟
    RCC_APB2PeriphClockCmd(LED_PERIPH, ENABLE);

    // 配置GPIOA13和GPIOA14为输出模式
    GPIO_InitStructure.GPIO_Pin = LED_PIN_5 | LED_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

/*----------------------Interrupt-----------------------*/
void Interrupt_Init(void)
{

    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure_Tim;

    // 配置GPIOA2的中断触发方式为下降沿触发
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 启用GPIOA2的中断，并设置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure_Tim.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure_Tim.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure_Tim.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure_Tim.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure_Tim);
}
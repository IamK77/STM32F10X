# PWM

该例程将使用PWM实现对一个LED的控制，达成呼吸灯的效果

例程: [PWM](./../../src/Standard_Lib/PWM/)

## 代码

该例程通过两个定时器

- TIM2: 用于延时
- TIM3: 用于输出PWM波

来实现一个LED灯的呼吸灯效果

## lib.h

```c
#pragma once

#include "stm32f10x.h"
#include "stm32f10x_tim.h"


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

/* ------------------- PWM ----------------------*/
void PWM_Configuration()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  // 使能定时器3和GPIOA的时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  // 配置GPIOA的引脚5为复用推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // 配置定时器2
  TIM_TimeBaseStructure.TIM_Period = 999; // PWM周期    每1ms循环一次
  TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1; // 预分频器 每1us计数一次
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  // 配置定时器2通道2为PWM输出模式
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // 设置比较模式为PWM1模式，在此模式下，当计数器的值小于TIM_Pulse时，PWM信号为高
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 900; // PWM占空比，可根据需要调整
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  // 使能定时器2
  TIM_Cmd(TIM3, ENABLE);
}

void LED_Control(int wait)
{
    for (int i = 1; i < 999; i++)
    {
        TIM_SetCompare1(TIM3, i);
        delay(wait);
      }
    for (int i = 999; i > 1; i--)
    {
        TIM_SetCompare1(TIM3, i);
        delay(wait);
    }
}
```

## main.c

```c
/*
 * 通过PWM实现LED呼吸灯效果
 * 引脚: PA6
 * 定时器: TIM3
 * 通道: 1
 * delay定时器: TIM2
*/

#include "stm32f10x.h"
#include "lib.h"

int main()
{
  PWM_Configuration();
  TIM2_Init();

  while (1)
  {
    LED_Control(1);
  }
}
```

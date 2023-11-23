# Timer

该例程将初步使用定时器进行精准定时

例程: [Timer](./../../src/Standard_Lib/Timer/)

## 代码

```c
#include "stm32f10x.h"
#include "stm32f10x_tim.h"

#define LED_PERIPH RCC_APB2Periph_GPIOA
#define LED_PORT GPIOA
#define LED_PIN GPIO_Pin_1


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
    
    GPIO_InitTypeDef gpioDef;
    RCC_APB2PeriphClockCmd(LED_PERIPH, ENABLE);
    gpioDef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioDef.GPIO_Pin = LED_PIN;
    gpioDef.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(LED_PORT, &gpioDef);

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
```

## 代码分析

本次代码除了delay部分, 其余部分均与上次例程相同, 这里不再重复

这里我们先来理清什么叫定时器

### 定时器

stm32有以下几个定时器

| 定时器 | 类别 |
| ------- | ------- |
| TIM2 | 通用定时器 |
| TIM3 | 通用定时器 |
| TIM4 | 通用定时器 |
| TIM5 | 通用定时器 |
| TIM6 | 基本定时器 |
| TIM7 | 基本定时器 |
| TIM1 | 高级定时器 |
| TIM8 | 高级定时器 |

其中高级定时器 > 通用定时器 > 基本定时器, 上级定时器拥有下级定时器的所有功能, 我们这里以通用定时器为例子

### 时钟源

定时器的时钟源有数种, 我们只以白话讲解, 不做细究

stm32拥有内部时钟源就犹如我们人体拥有心脏, 但不同的是, stm32的心脏跳动频率为72MHz, 也就是说, 每秒钟会跳动72000000次

### 时基单元

通用定时器的本质就是计数器

时基单元中有三个寄存器, 分别是

- TIMx_ARR: 自动重装载寄存器, 用于设置计数器的上限, 当计数器达到上限时, 会自动清零

- TIMx_PSC: 预分频器, 用于设置时钟源的分频系数, 也就是说, 时钟源的频率除以分频系数, 就是计数器的频率

- TIMx_CNT: 计数器, 用于计数, 当计数器达到上限时, 会自动清零

这里我们简称他们为`arr`, `psc`, `cnt`

### 计数

`cnt`会计算“心脏”一共跳了多少下, 但是, 由于`cnt`是一个16位的寄存器, 因此, `cnt`的最大值为2的16次方, 也就是65535, 当`cnt`达到65535时, 会到达极限, 无法再计数, 但是, “心脏” 每秒就跳动72000000次, 65535这个数字对于“心脏”来说, 只是一个瞬间, 因此, `psc`就应运而生

### 分频

`psc`的作用就是将“心脏”跳动的频率降低, 降低到`cnt`可以计数的范围内, 也就是说, `psc`的值越大, “心脏”跳动的频率就越低, `cnt`就可以计数的越久

举一个具体的例子, 假设`psc`的值为`3`, 而我们给`psc`12次信号, 那么`psc`会每当到达`3`时, 再给`psc`一次信号, 那么`psc`会清零, 并向外传输一次信号

    12次信号 -> psc(2) -> 4次信号 -> cnt

`psc`从0开始计数, 具体的输出与输入如下

| 输入的信号 | psc的值 | 输出的信号 |
| ------- | ------- | ------- |
| 1 | 0 | 0 |
| 2 | 1 | 0 |
| 3 | 2 | 0 |
| 4 | 0 | 1 |
| 5 | 1 | 1 |
| 6 | 2 | 1 |
| 7 | 0 | 2 |
| 8 | 1 | 2 |
| 9 | 2 | 2 |
| 10 | 0 | 3 |
| 11 | 1 | 3 |
| 12 | 2 | 3 |

在机械中, 减速器的原理与此类似, 两个齿轮之间的齿数比例就相当于`psc`的值, 而`cnt`就相当于减速后齿轮的转数

我们将`psc`的值设为`71`, 那么`psc`会每当到达`71`时, 再给`psc`一次信号, 那么`psc`会清零, 并向外传输一次信号

    72000000次信号 -> psc(71) -> 1000000次信号 -> cnt

因此, 我们可以通过`psc`的值来将“心跳”的频率降低到1MHz, 再交由cnt计数

### 溢出计时

我们将`arr`的值设为`100`, 那么`cnt`会每当到达`100`时, 再给`cnt`一次信号, 那么`cnt`会清零, 并产生一个更新中断

    100次信号 -> cnt -> 0次信号 -> arr -> 一个更新中断

如果我们不设置`arr`的值, 那么`cnt`会一直计数, 直到达到极限, 然后归零, 重新计数, 无事发生

### 流程

综上, 整个流程如下

    心脏 -> 72000000次信号 -> psc(71) -> 1000000

/*
 * ************************************************
 * 
 *              STM32 blink gcc demo
 * 
 *  CPU: STM32F103C8
 *  PIN: PA1
 * 
 * 该dome由Vscode EIDE 内置模板 STM32F1 GCC QuickStart 生成并修改而来
 * 用于点亮PA1引脚的LED灯, 并每隔一定时间翻转一次
 * ************************************************
*/

#include "stm32f10x.h"

#define LED_PERIPH RCC_APB2Periph_GPIOA
#define LED_PORT GPIOA
#define LED_PIN GPIO_Pin_1

// 延时函数, x为延时时间, 单位为ms, 该函数仅演示使用, 实际使用中应使用定时器，后续会在其他例程中介绍
void delay(int x)
{
    for (int i = 0; i < x; i++){
        for (int j = 0; j < 1000; j++)  // 1000次循环大约为1ms
            __NOP();    // 空操作, 仅占用一个CPU周期
    }
}


int main()
{
    GPIO_InitTypeDef gpioDef;   // GPIO 初始化结构体
    RCC_APB2PeriphClockCmd(LED_PERIPH, ENABLE); // 使能GPIOA时钟
    gpioDef.GPIO_Mode = GPIO_Mode_Out_PP;   // 推挽输出
    gpioDef.GPIO_Pin = LED_PIN;        // LED引脚
    gpioDef.GPIO_Speed = GPIO_Speed_10MHz;  // GPIO速度
    GPIO_Init(LED_PORT, &gpioDef);   // 初始化GPIO

    while (1)
    {   
        /*
         * 这里使用GPIO_ReadInputDataBit读取引脚状态, 并取反
         * BitAction是一个枚举类型, 有Bit_RESET和Bit_SET两个值
         * Bit_RESET = 0, Bit_SET = 1
         * 即读取当前灯的亮灭状态后, 取反, 再将其写入引脚
        */
        GPIO_WriteBit(LED_PORT, LED_PIN, (BitAction)!GPIO_ReadInputDataBit(LED_PORT, LED_PIN));  
        delay(5000);
    }
}

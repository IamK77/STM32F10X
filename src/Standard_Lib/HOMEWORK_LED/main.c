/*
 * ************************************************
 * 
 *              STM32 blink gcc
 * 
 *  CPU: STM32F103C8
 *  PIN: PA5 | PA6 | PA7 | PA8
 *  Author: chen yinfeng & GitHub Copilot
 *  Date: 2023-11-25
 *  Compiler: arm-none-eabi-gcc.exe
 *  IDE: VSCode & EIDE
 *        
 * ************************************************
*/

#include "stm32f10x.h"

#include "lib.h"

int main()
{
    LED_Init();
    TIM2_Init();

    while (1)
    {    
        LED_Gradually();                // 4个LED 灯LEDO~LED3间隔1s 依次点亮 5s后依次熄灭
        LED_TEN_TIMES();                // 2s后 LEDO~LED3间隔 1s 亮、灭交替十次
        LED_ONLE_ZERO_AND_ONE_ON();     // 5s后 LED0、LED1亮5s，其余灭
        LED_END();                      // LED0~LED3全灭
    }
}

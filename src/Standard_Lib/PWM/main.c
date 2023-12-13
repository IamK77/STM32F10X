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

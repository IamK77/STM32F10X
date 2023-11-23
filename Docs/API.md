# Standard Peripheral Library API

## All

一些通用的类型

### Enum BitAction

-------

`BitAction`是一个枚举类型，包含以下几个可选参数：

| 结构体成员  | 类型              | 描述    |
| -------    | -------           | ------- |
| `Bit_RESET` | `uint8_t`  | 0 |
| `Bit_SET`   | `uint8_t`  | 1 |

## RCC AND APB2

在 STM32 微控制器中，RCC（Reset and Clock Control）模块负责管理和控制微控制器的时钟系统。微控制器的各种外设（例如 GPIO、USART、SPI 等）都需要时钟才能工作，这些时钟由 RCC 模块提供。

APB2（Advanced Peripheral Bus 2）是微控制器的一个总线，一些外设（例如 GPIOA、GPIOB、ADC1 等）连接在这个总线上。这些外设的时钟由 RCC 模块通过 APB2 总线提供。

### Function RCC_APB2PeriphClockCmd

-------

`void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)`

#### Description

使能或禁用APB2外设时钟。

#### Parameters

| 参数类型             | 描述 |
| ------              | ---- |
| `RCC_APB2Periph`    | APB2外设时钟 |
| `FunctionalState`   | 使能或禁用APB2外设时钟，可选参数为`ENABLE`和`DISABLE` |

其中，`RCC_APB2Periph`可选参数如下：

| 可选参数           | 描述    |
| -------           | ------- |
| `RCC_APB2Periph_ADC1` | ADC1外设时钟 |
| `RCC_APB2Periph_ADC2` | ADC2外设时钟 |
| `RCC_APB2Periph_ADC3` | ADC3外设时钟 |
| `RCC_APB2Periph_AFIO` | 复用功能IO时钟 |
| `RCC_APB2Periph_GPIOA` | GPIOA时钟 |
| `RCC_APB2Periph_GPIOB` | GPIOB时钟 |
| `RCC_APB2Periph_GPIOC` | GPIOC时钟 |
| `RCC_APB2Periph_GPIOD` | GPIOD时钟 |
| `RCC_APB2Periph_GPIOE` | GPIOE时钟 |
| `RCC_APB2Periph_GPIOF` | GPIOF时钟 |
| `RCC_APB2Periph_GPIOG` | GPIOG时钟 |
| `RCC_APB2Periph_SPI1` | SPI1时钟 |
| `RCC_APB2Periph_SPI2` | SPI2时钟 |
| `RCC_APB2Periph_TIM1` | TIM1时钟 |
| `RCC_APB2Periph_TIM8` | TIM8时钟 |
| `RCC_APB2Periph_USART1` | USART1时钟 |
| `RCC_APB2Periph_USART6` | USART6时钟 |
| `RCC_APB2Periph_UART9` | UART9时钟 |
| `RCC_APB2Periph_UART10` | UART10时钟 |
| `RCC_APB2Periph_SYSCFG` | 系统配置时钟 |

## GPIO

GPIO（General Purpose Input/Output，通用输入/输出）是微控制器的一个外设，用于与外部电路进行通信。STM32 微控制器的 GPIO 模块包含多个 GPIO 端口，每个 GPIO 端口包含多个 GPIO 引脚

### Macro GPIOX

-------

`GPIOX`是一个宏，用于指定GPIO端口，X为A~G

### Macro GPIO_Pin_x

-------

`GPIO_Pin_x`是一个宏，用于指定GPIO引脚，x为引脚编号，取值范围为0~15

### Struct GPIO_InitTypeDef

-------
`GPIO_InitTypeDef`是一个结构体类型，通常在 STM32 微控制器的 GPIO(General Purpose Input/Output，通用输入/输出) 配置中使用，用于初始化 GPIO 引脚

| 结构体成员  | 类型              | 描述    |
| -------    | -------           | ------- |
| `GPIO_Mode`  | `GPIOMode_TypeDef`  | 设置 GPIO 引脚的工作模式 |
| `GPIO_Pin`   | `GPIO_Pin_x`        | 选定的针脚 |
| `GPIO_Speed` | `GPIOSpeed_TypeDef` | 用于设置GPIO引脚的输出速度 |

#### GPIO_Mode

`GPIOMode_TypeDef`是一个枚举类型，包含以下几个可选参数：

| 可选参数           | 描述    |
| -------           | ------- |
| `GPIO_Mode_AIN`     | 模拟输入模式 |
| `GPIO_Mode_IN_FLOATING` | 浮空输入模式 |
| `GPIO_Mode_IPD`     | 下拉输入模式 |
| `GPIO_Mode_IPU`     | 上拉输入模式 |
| `GPIO_Mode_Out_OD`  | 开漏输出模式 |
| `GPIO_Mode_Out_PP`  | 推挽输出模式 |
| `GPIO_Mode_AF_OD`   | 复用开漏输出模式 |
| `GPIO_Mode_AF_PP`   | 复用推挽输出模式 |

#### GPIO_Pin

`GPIO_Pin_x`是一个宏，用于指定GPIO引脚，x为引脚编号，取值范围为0~15。

#### GPIO_Speed

`GPIOSpeed_TypeDef`是一个枚举类型，包含以下几个可选参数：

| 可选参数           | 描述    |
| -------           | ------- |
| `GPIO_Speed_10MHz`  | 10MHz输出速度 |
| `GPIO_Speed_2MHz`   | 2MHz输出速度 |
| `GPIO_Speed_50MHz`  | 50MHz输出速度 |

#### Example

```c
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
```

### Function GPIO_Init

-------

`void GPIO_Init(GPIOX, GPIO_InitTypeDef* GPIO_InitStruct)`

#### Description

初始化GPIO引脚。

#### Parameters

| 参数类型             | 描述 |
| ------              | ---- |
| `GPIOX`             | GPIO端口，X为A~G |
| `GPIO_InitTypeDef*` | 指向`GPIO_InitTypeDef`结构体的指针，包含GPIO引脚的初始化信息 |

#### Return Value

| 返回值 | 描述 |
| ------ | ---- |
| `void` | 无   |

#### Example

```c
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure);
```

### Function GPIO_WriteBit

-------

`void GPIO_WriteBit(GPIOX, GPIO_Pin_x, BitAction BitVal)`

#### Description

设置GPIO引脚的输出状态。

#### Parameters

| 参数类型      | 描述 |
| ------     | ---- |
| `GPIOX`    | GPIO端口，X为A~G |
| `GPIO_Pin_x` | 选定的针脚 |
| `BitAction`   | GPIO引脚的输出状态，可选参数为`Bit_RESET`和`Bit_SET` |

#### Return Value

| 返回值 | 描述 |
| ------ | ---- |
| `void` | 无   |

#### Example

```c
GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
```

### Function GPIO_ReadInputDataBit

-------

`BitAction GPIO_ReadInputDataBit(GPIOX, GPIO_Pin_x)`

#### Description

读取GPIO引脚的输入状态。

#### Parameters

| 参数类型      | 描述 |
| ------     | ---- |
| `GPIOX`    | GPIO端口，X为A~G |
| `GPIO_Pin_x` | 选定的针脚 |

#### Return Value

| 返回值 | 描述 |
| ------ | ---- |
| `BitAction` | GPIO引脚的输入状态，可选参数为`Bit_RESET`和`Bit_SET` |

#### Example

```c
BitAction bit = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
```

## TIM

TIM（Timer，定时器）是微控制器的一个外设，用于产生定时中断。STM32 微控制器的 TIM 模块包含多个 TIM 定时器，每个 TIM 定时器包含多个 TIM 通道。

### Macro TIMx

-------

`TIMx`是一个宏，用于指定TIM定时器，x为定时器编号，取值范围为1~14

### Macro TIM_Channel_x

-------

`TIM_Channel_x`是一个宏，用于指定TIM通道，x为通道编号，取值范围为1~4

### Struct TIM_TimeBaseInitTypeDef

-------

`TIM_TimeBaseInitTypeDef`是一个结构体类型，通常在 STM32 微控制器的 TIM(Timer，定时器) 配置中使用，用于初始化 TIM 定时器

| 结构体成员  | 类型              | 描述    |
| -------    | -------           | ------- |
| `TIM_Prescaler`  | `uint16_t`  | 设置 TIM 定时器的预分频值 |
| `TIM_CounterMode`   | `uint16_t`        | 设置 TIM 定时器的计数模式 |
| `TIM_Period` | `uint16_t` | 设置 TIM 定时器的计数周期 |
| `TIM_ClockDivision` | `uint16_t` | 设置 TIM 定时器的时钟分频值 |
| `TIM_RepetitionCounter` | `uint8_t` | 设置 TIM 定时器的重复计数值 |

#### TIM_Prescaler

`uint16_t`是一个无符号短整型，用于设置 TIM 定时器的预分频值，取值范围为0~65535。

#### TIM_CounterMode

`uint16_t`是一个无符号短整型，用于设置 TIM 定时器的计数模式，取值范围为0~3。

| 可选参数           | 描述    |
| -------           | ------- |
| `TIM_CounterMode_Up`     | 向上计数模式 |
| `TIM_CounterMode_Down` | 向下计数模式 |
| `TIM_CounterMode_CenterAligned1`     | 中央对齐模式1 |
| `TIM_CounterMode_CenterAligned2`     | 中央对齐模式2 |
| `TIM_CounterMode_CenterAligned3`     | 中央对齐模式3 |

#### TIM_Period

`uint16_t`是一个无符号短整型，用于设置 TIM 定时器的计数周期，取值范围为0~65535。

#### TIM_ClockDivision

`uint16_t`是一个无符号短整型，用于设置 TIM 定时器的时钟分频值，取值范围为0~7。

| 可选参数           | 描述    |
| -------           | ------- |
| `TIM_CKD_DIV1`     | 不分频 |
| `TIM_CKD_DIV2` | 2分频 |
| `TIM_CKD_DIV4`     | 4分频 |


#### TIM_RepetitionCounter

`uint8_t`是一个无符号字符型，用于设置 TIM 定时器的重复计数值，取值范围为0~255。

#### Example

```c
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_TimeBaseStructure.TIM_Prescaler = 0;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseStructure.TIM_Period = 0;
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
```

### Function TIM_TimeBaseInit

-------

`void TIM_TimeBaseInit(TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)`

#### Description

初始化TIM定时器。

#### Parameters

| 参数类型             | 描述 |
| ------              | ---- |
| `TIMx`             | TIM定时器，x为定时器编号，取值范围为1~14 |
| `TIM_TimeBaseInitTypeDef*` | 指向`TIM_TimeBaseInitTypeDef`结构体的指针，包含TIM定时器的初始化信息 |

#### Return Value

| 返回值 | 描述 |
| ------ | ---- |
| `void` | 无   |

#### Example

```c
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_TimeBaseStructure.TIM_Prescaler = 0;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseStructure.TIM_Period = 0;
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
```

### Function TIM_Cmd

-------

`void TIM_Cmd(TIMx, FunctionalState NewState)`

#### Description

使能或禁用TIM定时器。

#### Parameters

| 参数类型             | 描述 |
| ------              | ---- |
| `TIMx`             | TIM定时器，x为定时器编号，取值范围为1~14 |
| `FunctionalState` | 使能或禁用TIM定时器，可选参数为`ENABLE`和`DISABLE` |

#### Return Value

| 返回值 | 描述 |
| ------ | ---- |
| `void` | 无   |

#### Example

```c
TIM_Cmd(TIM1, ENABLE);
```

### Function TIM_ITConfig

-------

`void TIM_ITConfig(TIMx, uint16_t TIM_IT, FunctionalState NewState)`

#### Description

使能或禁用TIM定时器的中断。

#### Parameters

| 参数类型             | 描述 |
| ------              | ---- |
| `TIMx`             | TIM定时器，x为定时器编号，取值范围为1~14 |
| `uint16_t` | TIM定时器的中断源，可选参数为`TIM_IT_Update`、`TIM_IT_CC1`、`TIM_IT_CC2`、`TIM_IT_CC3`和`TIM_IT_CC4` |

其中，`TIM_IT`可选参数如下：

| 可选参数           | 描述    |
| -------           | ------- |
| `TIM_IT_Update`     | 更新中断 |
| `TIM_IT_CC1` | 捕获/比较1中断 |
| `TIM_IT_CC2`     | 捕获/比较2中断 |
| `TIM_IT_CC3`     | 捕获/比较3中断 |
| `TIM_IT_CC4`     | 捕获/比较4中断 |

| `FunctionalState` | 使能或禁用TIM定时器的中断，可选参数为`ENABLE`和`DISABLE` |

#### Return Value

| 返回值 | 描述 |
| ------ | ---- |
| `void` | 无   |

#### Example

```c
TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
```

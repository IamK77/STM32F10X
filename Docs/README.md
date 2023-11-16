# Documentaion

本项目所有例程均基于 `STM32F103C8T6` 杭州电子科技大学开发板

本项目环境基于Vscode EIDE

本文旨在快速上手, 用词不会太严谨

## 开发须知

stm32的开发分为`标准库`和`HAL`两种，请根据自己的情况选择

注意: 官方已不再维护前者, 而改为主推后者

### 何为项目

一般来说`项目/工程/解决方案/工作空间`是指一个大文件夹，包含了多个文件夹和文件

通常项目的结构如下

```bash
项目文件夹
├── 源代码文件夹
│   ├── main.c
│   ├── ...
│   └── ...
├── 资源文件夹
│   ├── ...
│   └── ...
├── 项目说明文件
└── ...
```

项目文件夹被称为根目录

本项目提供了一个简单的Project框架

### 环境配置

环境搭建可以参照此[视频](https://www.bilibili.com/video/BV1nr4y1R7Jb)

这里有三点基于视频的补充

- 安装Vscode插件时可以搜索`sim`来安装`Chinese(Simplified) Language Pack for Visual Studio Code`，这样可以将Vscode的界面变为中文
- EIDE在`安装实用工具`一步时可以多选择`JLink`，这样可以在Vscode中使用JLink下载程序
- 就目前来看, 不设置ac5/6似乎也没什么问题

如果不想看视频, 可以按照下列步骤

- 下载Vscode, 其下载地址为[https://code.visualstudio.com/](https://code.visualstudio.com/)
- 安装Vscode时记得勾选以下选项
  - `添加到PATH`
  - `将通过 Code 打开“操作添加到 Windows 资源管理器文件上下文菜单`
  - `将Code 注册为受支持的文件类型的编辑器`
- 安装插件, 插件的安装方法为
  - 打开Vscode
  - 按下`Ctrl+Shift+X`
  - 在搜索框中输入`C/C++`
  - 找到`C/C++`, `C/C++ Extension`, `C/C++ Themes`
  - 搜索`sim`
  - 找到`Chinese(Simplified) Language Pack for Visual Studio Code`
  - 搜索`eide`
  - 找到`Embedded IDE`
  - 搜索`cortex`
  - 找到`Cortex-Debug`
  - 安装以上插件, 会要求重启Vscode
- 在Vscode的侧边栏找到EIDE，在操作一栏中点击安装实用工具
  - 在弹出的窗口中选择`JLink`
  - `Cppcheck (Code Inspection)`
  - `GNU Arm Embedded Toolchain`
  - `OpenOCD Programmer`
  - `RISC-V GNU Toolchain`
  - 安装完毕后会要求重启Vscode
- 在Vscode的左侧边栏找到EIDE，在操作一栏中点击`新建项目`-`内置项目模板`-`STM32F1 GCC Quickstart`
  - 在弹出的窗口中输入项目名`LED`
  - 选择项目路径
  - 右下角会问你是否切换工作区, 选择`是`
- 打开项目后进入`src/main.c`, 点击构建, 出现绿色的`done`即为编译成功

此时根据侧边栏的资源管理器或EIDE的项目资源, 我们可以清楚的看到项目的结构

```bash
LED
├─LED.code-workspace
├─.eide
│  ├─deps
│  └─log
├─.vscode
├─hal
│  └─STM32F10x_StdPeriph_Driver
│      ├─inc
│      └─src
├─lib
│  └─cmsis
└─src
```

这里的`LED`即为项目文件夹, 其中的`.eide`和`.vscode`为Vscode的配置文件夹, `hal`和`lib`为库文件夹, `src`为源代码文件夹

打开`src`文件夹, 我们可以看到`main.c`文件, 这就是我们的源代码文件

如果下次我们需要用Vscode打开这个项目, 我们只需要点击`LED.code-workspace`或在文件夹空白处右键, 选择用code打开即可

### Standard Peripheral Library

`Standard Peripheral Library`即标准库，是ST官方提供的库，但官方已经不再维护

其优点有

- 体积小
- 运行速度快
- 适合对代码大小和速度有要求的项目
- 适合对代码有一定了解的人员

其缺点有

- 相较于HAL库, 开发速度慢
- 官方不再维护

### Hardware Abstraction Layer

`HAL`即硬件抽象层，是ST官方提供的库，目前官方主流推荐

其优点有

- 开发速度快
- 适合对代码不熟悉的人员

其缺点有

- 体积大
- 运行速度慢

什么是抽象? 抽象是指将事物的共性质提取出来, 从而形成新的事物

以下方伪代码为例

```c
int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int div(int a, int b) {
    return a / b;
}
```

此处我声明了四个函数, 但这四个函数都有一个共性, 即都是对两个数进行运算, 从而得到一个数

于是我将这四个函数抽象/封装为一个函数

```c
int calc(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0;
    }
}
```

现在, 这个函数有了四个功能, 使用起来也更加方便，但是如果我们原本只需要使用/调用一个函数的话, 只需要写/编译一行代码, 现在我们却需要为不必要的功能多编译好几行,这使得我们的程序变得更大, 运行速度也变慢了, 但反过来一想, 如果我们需要非常频繁的使用多个功能, 那么这样做就是值得的

### 选择

建议使用`HAL`，因为官方已不再维护`Standard Peripheral Library`

但本文目前将主要强调`Standard Peripheral Library`，因为其难度更高

通过下文的`Directory`可以找到对应的文档

## QuickStart

- [`Standard Peripheral Library`](./SPL/README.md)

  - [Frist_LED](./SPL/First_LED.md)
  - [Button](./SPL/Button.md)

- [`HAL`](./HAL/README.md)(待补充)


## TODO

- Timer
- Interrupt
- PWM


## Update

- 2023.11.16
  - 新增`Button`例程
  - 新增`Update`
  - 新增`TODO`
- 2023-11-14
  - 初始化仓库
  
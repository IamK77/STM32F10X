# STM32F10X

本文档旨在速成，用词不会太严谨

虽然stm32涉及到C语言，但是本文档不会涉及C语言的基础知识，如果不了解C语言，请自行学习

## 开发环境

- Windows 10
- Vscode
- STM32CubeMX(可选)

## 阅读建议

- 建议使用Vscode打开Markdowm预览阅读(右上角点击侧边预览)
- 或使用Typora, Obsidian等Markdown编辑器阅读
- 由于Github的特殊原因, 不使用魔法上网可能不会加载图片, 建议下载本地阅读
- 边读边写试试
- 如果访问Github比较慢, 可以使用[Watt Toolkit](https://steampp.net/)(原Steam++)加速
- 提供[C语言基础语法文档](https://github.com/IamK77/note/blob/master/C/cnote.md)以供查阅, 如果这都看不懂, 那我还是那句话

    ✋🤚菜就多练，✋🤚，学不会就别玩，✋🤚，以前是以前✋🤚，现在是现在✋🤚，你要是一直拿以前当作现在✋🤚，哥们，你怎么不拿你出生的时候对比啊✋🤚

    <img src="./Docs/Resource/菜就多练.jpg" width=150>


## Download

在Github页面中点击绿色的Code按钮, 然后点击Download ZIP下载本项目, 或点击[此处](https://github.com/IamK77/STM32F10X/archive/refs/heads/main.zip)

或者使用git clone命令(建议)

```bash
git clone https://github.com/IamK77/STM32F10X.git
```

拉取更新

```bash
git pull https://github.com/IamK77/STM32F10X.git
```

## 项目结构

```bash
├─.vscode
├─Docs
├─.gitignore
├─README.md
├─STM32F10X.code-workspace
└─src
    ├─HAL_Lib
    │  ├─Project
    │  │  ├─...
    │  │  └─src
    │  └─Example_Project
    └─Standard_Lib
        ├─Example_Project
        ├─Project
        │  ├─...
        │  └─src
        └─...
```

## 代码详解

详细文档请参照[Documentation](./Docs/README.md)

快速阅读请参照[QuickStart](./Docs/README.md#quickstart)

## 鸣谢

- [EIDE](https://github.com/github0null/eide) 提供了一个非常好用的IDE
- [keysking](https://space.bilibili.com/6100925)的教学视频
- [threekb](https://space.bilibili.com/3493142393260061)的环境搭建视频
- [小k撸电机](https://www.bilibili.com/video/BV15S4y1g7WT)的人话教学视频

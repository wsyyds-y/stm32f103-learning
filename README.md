# STM32F103 学习工程

基于 **STM32F103C8T6** 与 **STM32 标准外设库（SPL）** 的嵌入式学习工程，使用 **Keil MDK 5 + ARM Compiler 5** 开发。

当前版本实现：**按键每按一次，舵机角度 +10°（0~180° 循环），OLED 实时显示当前角度。**

## 功能

| 模块 | 实现方式 |
|---|---|
| 舵机 | TIM2 通道 1 输出 50 Hz PWM，CCR 对应 0.5~2.5 ms 脉宽，线性映射到 0~180° |
| 按键 | PB1 上拉输入 + 20 ms 软件消抖，松手时触发一次，角度 +10° |
| 显示 | 0.96" OLED（SSD1306），软件 I²C 驱动，显示当前角度 |

角度换算：`CCR = angle / 180 * 2000 + 500`，即 20 ms 周期内 0.5~2.5 ms 高电平。

## 硬件接线

| 功能 | STM32 引脚 | 外设 |
|---|---|---|
| 舵机信号（橙） | **PA0**（TIM2_CH1） | SG90 等 9 g 舵机 |
| 按键 | **PB1** | 按键另一端接 GND |
| OLED SCL | **PB8** | SSD1306 |
| OLED SDA | **PB9** | SSD1306 |
| 电源 | 5V / GND | 舵机用 5 V 供电，必须与开发板共地 |

## 目录结构

```
├─ Start/        启动文件（startup_stm32f10x_md.s）与 CMSIS 内核文件
├─ Library/      STM32F10x 标准外设库
├─ User/         main.c、中断服务函数、库配置
├─ System/       Delay（SysTick 延时）、PWM、定时器等系统级模块
├─ Hardware/     OLED、按键、舵机、LED、编码器、对射红外、光敏等外设模块
└─ one.uvprojx   Keil MDK 工程文件
```

除当前 `main.c` 启用的 OLED / 按键 / 舵机外，工程内还包含 LED、旋转编码器、对射式红外计次、光敏传感器、定时器中断等模块代码，可按需接入。

## 编译与下载

1. 安装 Keil MDK 5.x（需 ARM Compiler 5 / AC5）
2. 打开 `one.uvprojx`
3. `F7` 编译，`F8` 下载（ST-Link）

构建产物（`Objects/`、`Listings/`、`DebugConfig/`）已通过 `.gitignore` 排除，克隆后重新编译即可。

## 开发环境

- MCU：STM32F103C8T6（Cortex-M3，64 KB Flash / 20 KB RAM）
- 外设库：STM32F10x Standard Peripheral Library
- IDE：Keil MDK 5.40 + ARMCC 5.06 update 5
- 编辑器：VS Code + Keil Assistant 扩展

## 说明

本项目为学习实践，部分外设驱动参考江协科技（江科大）STM32 入门教程，仅用于学习与交流。
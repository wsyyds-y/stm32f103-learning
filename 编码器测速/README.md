# 编码器测速（TIM3 硬件编码器接口）

基于 **STM32F103C8T6 + STM32F10x 标准外设库（SPL）** 的旋转编码器练习工程：用定时器的硬件编码器接口读取正交编码器，按固定周期统计增量并显示。

## 功能

- TIM3 工作在**编码器模式 TI12**（CH1 = PA6，CH2 = PA7），由硬件根据 A/B 两相相位差自动加/减计数；
- 计数器周期 65535（16 位满量程），预分频 0，输入滤波 `0x0F`，两脚配置为上拉输入；
- `Encoder_GetCount()` 读出本次增量并把计数器清零，返回**带符号**结果：正转为正、反转为负；
- 主循环每 1 s 刷新一次 OLED，显示这一秒内的计数值。

## 硬件连接

| 信号 | 引脚 | 说明 |
|---|---|---|
| 编码器 A 相 | PA6 | TIM3_CH1 |
| 编码器 B 相 | PA7 | TIM3_CH2 |
| OLED SCL | PB8 | SSD1306，软件 I²C |
| OLED SDA | PB9 | SSD1306，软件 I²C |

## 代码说明

| 文件 | 内容 |
|---|---|
| `Hardware/Encoder.c` / `Encoder.h` | `Encoder_Init()` 初始化 TIM3 编码器接口；`Encoder_GetCount()` 读取并清零计数 |
| `User/main.c` | 主循环：读取增量 → OLED 显示 → 延时 1 s |

`Hardware/Encoder.c` 下半部分保留了**早期用 EXTI 外部中断 + 软件判方向**的完整注释代码（`//` 开头，不参与编译），方便对照两种做法的区别；当前生效的是文件开头的 TIM3 硬件编码器版本。

`Library/`、`Start/`、`System/` 及 `Hardware/` 下其余驱动都是模板自带文件，本工程未调用。

## 编译与下载

1. 用 **Keil MDK 5** 打开 `one.uvprojx`（器件 STM32F103C8，编译器 ARM Compiler 5）；
2. 编译（F7）→ 下载（F8）；
3. 也可以在 VS Code + Keil Assistant 扩展里编译/下载。

> 编译产物（`Objects/`、`Listings/`、`*.hex` 等）已在 `.gitignore` 中忽略，不会入库。
# AD 单通道采样（ADC1 + OLED）

基于 **STM32F103C8T6 + STM32F10x 标准外设库（SPL）** 的 ADC 练习工程：对一路模拟电压做 12 位采样，把原始码值和换算出的电压显示在 OLED 上。

## 功能

- ADC1 通道 0，独立模式、单通道、不扫描、数据右对齐，采样时间 55.5 个周期；
- ADC 时钟 = PCLK2 / 6（72 MHz / 6 = 12 MHz，未超过 14 MHz 上限）；
- 上电先做 ADC 校准（复位校准 + 启动校准），再进入主循环；
- 主循环每 100 ms 采样一次，按 `V = value / 4095 × 3.3` 换算，OLED 显示码值与电压。

## 硬件连接

| 信号 | 引脚 | 说明 |
|---|---|---|
| 模拟输入 | PA0 | ADC1_IN0，输入范围 0 ~ 3.3 V |
| OLED SCL | PB8 | SSD1306，软件 I²C |
| OLED SDA | PB9 | SSD1306，软件 I²C |

## 本工程实际用到的代码

| 文件 | 内容 |
|---|---|
| `Hardware/AD.c` / `AD.h` | `ad_init()` 配置 ADC1；`ad_start()` 软件启动一次转换并返回结果 |
| `User/main.c` | 主循环：采样 → 换算电压 → OLED 显示 |

`Library/`、`Start/`、`System/` 及 `Hardware/` 下其余驱动都是模板自带文件，本工程未调用。

## 编译与下载

1. 用 **Keil MDK 5** 打开 `one.uvprojx`（器件 STM32F103C8，编译器 ARM Compiler 5）；
2. 编译（F7）→ 下载（F8）；
3. 也可以在 VS Code + Keil Assistant 扩展里编译/下载。

> 编译产物（`Objects/`、`Listings/`、`*.hex` 等）已在 `.gitignore` 中忽略，不会入库。
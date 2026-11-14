# STM32F103 学习工程集

基于 **STM32F103C8T6** 与 **STM32 标准外设库（SPL）** 的嵌入式学习工程，使用 **Keil MDK 5（ARM Compiler 5）** + **VS Code** 开发。

每个子目录都是一个独立的 Keil 工程，按学习进度逐个添加：

| 目录 | 内容 | 涉及外设/知识点 |
|---|---|---|
| `9.20` | GPIO 输出练习 | GPIO 初始化、推挽输出（PB12） |
| `11.7` | 工程骨架练习 | 工程目录结构、Timer 模块 |
| `到内部时钟` | 时钟配置（内部） | RCC、HSI |
| `外部时钟` | 时钟配置（外部） | RCC、HSE、PLL |
| `TIM1` | 定时器练习 | TIM 定时中断、PWM |
| `PWM驱动直流电机` | 直流电机 PWM 调速 | TIM PWM、电机驱动（进行中） |
| `AD单通道` | ADC 单通道采样 | ADC1 软件触发、OLED 显示码值与电压 |
| `编码器测速` | 旋转编码器测速 | TIM3 编码器接口（TI12）、OLED 显示增量 |
| `DMA数据转运` | DMA 存储器到存储器数据转运 | DMA1 通道1、软件触发（M2M）、地址自增 |
| `DMA+AD多通道` | ADC 多通道扫描 + DMA 自动搬运 | ADC1 扫描模式、ADC→DMA 请求、软件触发单次转换 |
| `STM32工程模板` | **可复制的模板工程** | 标准库骨架 + 常用驱动 |

## 如何新建一个工程

1. 复制 `STM32工程模板` 文件夹，重命名为你的工程名（例如 `PWM驱动直流电机`），放在本目录下；
2. 用 Keil 打开工程里的 `one.uvprojx`；
3. 在 `User/main.c` 里写代码（模板里是空骨架）；
4. 编译、下载；
5. 提交上传：

   ```bash
   git add <工程目录>
   git commit -m "feat: 工程说明"
   git push
   ```

## 开发环境

- Keil MDK 5.40 / ARM Compiler 5（AC5）
- STM32F103C8T6（中容量）
- STM32F10x 标准外设库（SPL）
- VS Code + Keil Assistant 扩展（编译 F7 / 下载 F8）
- 源文件编码 UTF-8
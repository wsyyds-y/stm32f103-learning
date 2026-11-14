# STM32 工程模板（可直接复制）

基于 **STM32F103C8T6 + STM32F10x 标准外设库（SPL）+ Keil MDK 5（AC5）** 的空白工程骨架，复制一份即可开始新工程。

## 用法

1. **复制** 整个 `STM32工程模板` 文件夹，重命名为你的工程名（例如 `PWM驱动直流电机`），放在本仓库根目录下；
2. 用 **Keil** 打开 `one.uvprojx`；
3. 在 `User/main.c` 里写代码（当前是空骨架：一个空的 `main()`）；
4. 编译、下载到 STM32F103C8T6；
5. 上传到 GitHub：

   ```bash
   git add 你的工程目录
   git commit -m "feat: 工程说明"
   git push
   ```

## 目录结构

| 目录 | 内容 |
|---|---|
| `User/` | `main.c`（入口）、`stm32f10x_conf.h`、中断服务函数 `stm32f10x_it.c/h` |
| `System/` | 基础驱动：`Delay`（延时）、`PWM`、`tim`、`Timer` |
| `Hardware/` | 外设驱动：`OLED`（SSD1306 软件 I²C）、`Key`、`LED`、`LightSensor`、`Guangmin`、`Count`、`Encoder`、`Servo` |
| `Start/` | 启动文件（`startup_stm32f10x_md.s`）、内核文件、`system_stm32f10x.c` |
| `Library/` | STM32F10x 标准外设库（SPL） |

## 说明

- 模板**不含 `.git`**，复制后的新工程不会继承任何仓库历史；
- 复制到本仓库根目录下，`git add` 即可纳入版本管理；
- 工程文件名是 `one.uvprojx`（Keil 默认）。想改成工程名：重命名 `.uvprojx` 文件，再在 Keil 的 `Options for Target → Target` 标签里改 Target 名称即可；
- 源文件编码为 **UTF-8**；编译器为 **ARMCC 5**，宏 `USE_STDPERIPH_DRIVER` 已配置好；
- 编译产物（`Objects/`、`Listings/` 等）已在 `.gitignore` 中忽略，不会上传。
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

## OLED 中文显示

`Hardware/OLED` 除了原来的英文字符/数字，还支持 **16×16 汉字**（字库在 `Hardware/OLED_ChineseFont.h`，共 67 个常用字，约 2.1 KB Flash）：

```c
OLED_Init();
OLED_ShowString(1, 1, "OLED Test");            // 英文 8x16，一行 16 列
OLED_ShowChinese(2, 1, 1);                     // 按字库序号显示第 1 个字
OLED_ShowChineseString(3, 1, "温度:25C");      // 中英混排，汉字占 2 列 x 2 行
OLED_ShowChineseString(4, 1, "电压:3.3V");
```

要点：

- 汉字 **宽 16 像素、高 16 像素**，占 2 列 × 2 行屏幕空间，所以 `Column` 最大 15；
- `OLED_ShowChineseString` 的源文件必须存成 **UTF-8**（本工程已统一 UTF-8，Keil 编译不会转换编码）；
- 字库没有的汉字会显示成 `?`，先确认字库收录了，没有就重新生成：

  ```bash
  py312 E:\DeepSeek\tools\oled-font-gen.py --text "你要显示的字" --out Hardware\OLED_ChineseFont.h
  # 也可以 --file 你的UTF-8文本.txt 一次把整段话里的字都收进去，--preview out.png 可肉眼检查字形
  ```

## 说明

- 模板**不含 `.git`**，复制后的新工程不会继承任何仓库历史；
- 复制到本仓库根目录下，`git add` 即可纳入版本管理；
- 工程文件名是 `one.uvprojx`（Keil 默认）。想改成工程名：重命名 `.uvprojx` 文件，再在 Keil 的 `Options for Target → Target` 标签里改 Target 名称即可；
- 源文件编码为 **UTF-8**；编译器为 **ARMCC 5**，宏 `USE_STDPERIPH_DRIVER` 已配置好；
- 编译产物（`Objects/`、`Listings/` 等）已在 `.gitignore` 中忽略，不会上传。
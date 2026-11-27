# NTC 温度模块实时显示（AO + DO + OLED + 串口）

基于 **STM32F103C8T6 + STM32F10x 标准外设库（SPL）** 的温度采集工程：读取 NTC 热敏 + LM393 温度模块的模拟量 AO 算出温度，同时读开关量 DO 做超温判断，OLED 显示、串口打印。

## 功能

- AO → PA0（ADC1_IN0）单次采样，8 次平均压噪声，上电做 ADC 校准；
- 按“10k 上拉 + 10k NTC(B=3950)”分压模型反推阻值，再用 **B 值公式**换算温度，精度约 ±1℃（模块本身精度，非传感器标称精度）；
- DO → PB13 上拉输入，读 LM393 比较器输出的超温标志，阈值由模块上的**蓝色电位器**调；
- OLED 四行：`TEMP:25.3°C` / `DO:NORMAL/ALARM` / `AO:1650mV` / `ADC:2048`；
- 串口 **115200-8-N-1** 同步输出 `T=25.3C AO=1650mV ADC=2048 DO=NORMAL`。

## 硬件连接

| 模块引脚 | STM32F103C8T6 | 说明 |
|---|---|---|
| VCC | 3.3V | 供电，与 ADC 参考同一电压，读数才准 |
| GND | GND | 必须共地 |
| AO | **PA0** | 模拟电压 0~3.3V，随温度连续变化 |
| DO | **PB13** | 比较器开关量，超阈值翻转（LM393 通常低有效） |

OLED（SSD1306 软件 I²C）：SCL→PB8、SDA→PB9、VCC/GND→3.3V/GND。
串口可选：PA9→USB 转串口 RX、PA10→TX。

> 换引脚：AO 改 `Hardware/NTC.c` 顶部的 `NTC_GPIO_PIN / NTC_ADC_CHANNEL`，DO 改 `NTC_DO_PORT / NTC_DO_PIN`。

## 工作原理

**AO 这一路是“测电压再算电阻”**。模块内部就是一只 NTC 与固定电阻分压：

```
3.3V ── R1(10k) ──┬── AO ──> PA0
                  └── NTC ──> GND
```

- 温度升高 → NTC 阻值变小 → AO 电压变低（本工程按这个方向建模，即 `NTC_LOW_SIDE = 1`）；
- 由分压反推：`Rt = R1 × V / (3.3 − V)`；
- 再用 B 值公式：`1/T = 1/T0 + ln(Rt/R0)/B`，减 273.15 得摄氏度；
- 25℃ 时 Rt=R0=10k，AO 约 1.65V，ADC 约 2048，可用这组数快速判断接线对不对。

**DO 这一路是比较器**，与温度换算完全独立：电位器给一个阈值电压，AO 越过它 LM393 就翻转 DO，所以它只知道“有没有超过你拧的那个点”，不知道具体温度。DO 通常开漏输出，模块板载上拉，代码里配成上拉输入即可，极性由 `NTC_DO_ACTIVE_LOW` 控制。

## 标定（读数不对时改这几个宏）

都在 `Hardware/NTC.c` 顶部：

| 宏 | 默认 | 什么时候改 |
|---|---|---|
| `NTC_R_SERIES` | 10000 | 板上串联电阻不是 10k（看丝印/万用表量） |
| `NTC_R0` | 10000 | NTC 标称 25℃ 阻值不是 10k（常见 5k/10k/100k） |
| `NTC_B` | 3950 | 丝印写的是 3435 等其他 B 值 |
| `NTC_LOW_SIDE` | 1 | 加热时 AO 电压**升高**说明 NTC 在上臂，改成 0 |
| `NTC_DO_ACTIVE_LOW` | 1 | 超温时 DO 是高电平（或 LED 逻辑相反），改成 0 |

判断方向最简单的办法：手指捏住 NTC 看 OLED 的 `AO:` 毫伏值——变小就是默认的接法，变大就把 `NTC_LOW_SIDE` 改 0。

## 本工程实际用到的代码

| 文件 | 内容 |
|---|---|
| `Hardware/NTC.c` / `.h` | `NTC_Init()` ADC + DO 初始化；`NTC_ReadAdc()` 单次采样；`NTC_AdcToTempX10()` 码值→温度；`NTC_IsAlarm()` 读 DO |
| `Hardware/Serial.c` / `.h` | USART1 初始化 + `printf` 重定向 |
| `User/main.c` | 主循环：8 次平均 → 算温度 → 读 DO → OLED/串口刷新，500ms 一次 |

`Library/`、`Start/`、`System/` 及 `Hardware/` 下其余驱动都是模板自带文件，本工程未调用。

## 编译与下载

1. 用 **Keil MDK 5** 打开 `one.uvprojx`（器件 STM32F103C8，编译器 ARM Compiler 5）；
2. 编译（F7）→ 下载（F8）；
3. 也可以在 VS Code + Keil Assistant 扩展里编译/下载。

> 编译产物（`Objects/`、`Listings/`、`*.hex` 等）已在 `.gitignore` 中忽略，不会入库。

## 常见问题

| 现象 | 可能原因 |
|---|---|
| 温度固定在 125℃ 或 -55℃ | AO 没接 / 接错脚 / 分压模型方向反了（改 `NTC_LOW_SIDE`） |
| 温度整体偏高或偏低几度 | B 值、R0 与实物不符；或 VCC 不是 3.3V（用 5V 供电时 ADC 参考仍是 3.3V，公式里的 VREF 要同步改） |
| 读数跳 ±1~2℃ | 模块本身分辨率有限，已做 8 次平均；电源纹波大时可在 AO 对地加 0.1µF |
| DO 状态乱跳 | 温度正好在阈值附近，LM393 无迟滞；把电位器拧离当前温度，或软件加连续 3 次判定 |
| 改了阈值 DO 不翻转 | 模块 LED 亮/灭与 DO 极性相反，先看 LED 再改 `NTC_DO_ACTIVE_LOW` |
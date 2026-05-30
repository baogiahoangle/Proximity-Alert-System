# Proximity Alert System

![subject-image](/Docs/SubjectImage/subject-image.jpg)

A bare-metal embedded project on the STM32F103C8T6 (ARM Cortex-M3) that monitors object distance in real time and triggers alerts when something enters a danger zone.

All peripheral configuration is done directly at the register level (RCC, GPIO, AFIO, SPI, Timer, and EXTI).

---

## How It Works

![hardware-block](Docs/BlockDiagram/diagram_block.drawio.png)

---

## Architecture
Layer Architecture:
![layered-architecture](Docs/LayeredArchitecture/layered_architecture.drawio.png)

---

## Stack

| | |
|---|---|
| MCU | STM32F103C8T6 (Cortex-M3) |
| Sensor | SRF05 Ultrasonic |
| Display | ST7735 TFT via SPI |
| Build | arm-none-eabi-gcc + custom Makefile, linker script & startup code |
| Output | `.hex` flashed via ST-Link |

---

## Build & Flash

Requirements: `arm-none-eabi-gcc` toolchain installed at `C:/Toolchain/Arm_Toolchain` (or update the path in the Makefile).

```bash
cd Code
make        
make clean  
```

The build uses a custom linker script (`stm_ls.ld`) and startup file (`stm32_startup.c`) - no CMSIS startup.

Flash `Output/makefile.hex` to the board using ST-Link.

---

## Flowchart

![flowchart](Docs/Flowchart/flow_chart_app.drawio.png)

---

## Demo

[Proximity Alert System](https://youtu.be/pPYZduCxOzM)

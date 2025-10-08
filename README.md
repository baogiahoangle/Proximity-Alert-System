# Smart Proximity Alert System
## Table of Contents

- [Overview](#overview)
- [Key Features](#key-features)
- [Technologies](#technologies)
- [Functional Requirements](#functional-requirements)
- [Hardware Block Diagram](#hardware-block-diagram)
- [Layered Architecture](#layered-architecture)
- [Flowchart of project](#flowchart-of-project)
- [Repository Layout](#repository-layout)

## Overview
- The primary objective of Smart Proximity Alert System (SPAS) is to provide immediate and actionable alerts by continuously monitoring the distance of objects in its field of view. 
- It dynamically categorizes these distances into predefined "SAFE" and "DANGEROUS" zones, triggering both visual (on-screen messages, graphical host position) and discrete (LED indicator) notifications when an object enters a critical "DANGEROUS" threshold.
---

## Key Features
 - **Real-time Proximity Sensing**: Continuously measures distance using an SRF05 ultrasonic sensor, providing instant feedback on object proximity.
- **Dynamic Zone-Based Alerting**: Classifies object distance into distinct "SAFE" and "DANGEROUS" zones and triggers immediate alerts based on zone transitions.
- **Multi-Modal User Feedback**:
    - **Visual Display**: Utilizes an ST7735 TFT screen to graphically represent the "host" object's position and display clear textual messages ("DANGEROUS" in red, "SAFE" in green).
    - **LED Indication**: Provides a clear, dedicated LED alert that illuminates when the object enters the "DANGEROUS" zone and turns off when in "SAFE" zone.
- **Efficient Display Management**: Implements logic for drawing and clearing dynamic objects on the display to ensure smooth visual updates and prevent ghosting.
---

## Technologies
- **IDE**: Keil MDK-ARM (Keil C51 uVision)
- **MCU**: STM32F103C8T6 (ARM Cortex-M3)
- **Peripherals**: SRF05 Ultrasonic Sensor, ST7735 TFT Display, LED

## Functional Requirements
|ID|Feature Name|Description|Source/ Hardware Module|
|-|-|-|-|
|FR1|System Initialization|Initialize the system, including system clock configuration and peripherals for the display (ST7735), distance sensor (SRF05), and LED.|System Clock, ST7735, SRF05, LED
|FR2|Distance Measurement & Scaling|Continuously measure distance from the SRF05 sensor and scale the distance value to a host position (0-127) for display.|SRF05|
|FR3|Dynamic Host Position Display|Display the host's position as a 4x4 pixel object on the ST7735 screen, with varying colors depending on its current zone (dangerous/safe).|ST7735|
|FR4|Danger Zone Detection|Detect when the host's position falls within a predefined "dangerous zone" (x < 64).|ST7735|
|FR5|Visual Danger Alert|Display a "DANGEROUS" message in red on the screen when the host is in the dangerous zone, and a "SAFE" message in green when in the safe zone. Clear previous messages upon state change.|ST7735|
|FR6|LED Danger Indication|Turn on an LED when the host is in the dangerous zone and turn off the LED when the host is in the safe zone.|LED|
---
## Hardware Block Diagram
![hardware-block](Docs/BlockDiagram/diagram_block.drawio.png)

---

## Layered Architecture
![layered-architecture](Docs/LayeredArchitecture/layered_architecture.drawio.png)

---

## Flowchart of project
![flowchart](Docs/Flowchart/flow_chart_app.drawio.png)
---

## Repository Layout
```
Code/
├── App/            
│   ├── Inc/         
│   └── Src/         
├── BSP/             
│   ├── Inc/
│   └── Src/
├── Core/
│   ├── Inc/
│   └── Src/
├── Drivers/
│   ├── CMSIS/
│   ├── DeviceDrivers/
│       ├── Inc/
│       └── Src/
│   └── STM32F1xx_HAL_Driver/
├── MDK-ARM/
├── Middlewares&Libraries/
│   ├── Inc/
│   └── Src/
├── SystemService/
│   ├── Inc/
│   └── Src/

Docs/            
├── BlockDiagram/
├── Flowchart/
└── LayeredArchitecture/

README.md        
```
---



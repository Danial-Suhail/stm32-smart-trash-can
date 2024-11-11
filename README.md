# Smart Waste Management System - ECE198 Analysis & Design
This is our ECE 198 group repository source code! :smile:

This project implements a Smart Waste Management System using STM32 microcontrollers, coded and configured in STM32CubeIDE. The system is designed to streamline waste sorting through voice recognition, servo motor control, ultrasonic sensors for fill-level monitoring, and LCD display integration.

## Project Overview
The system includes:
* __Microcontrollers:__ STM32 Nucleo F401RE boards (2)
* __Components:__ Servo Motors, Ultrasonic Sensors, I2C LCD Displays, Voice Recognition Module
* __Libraries:__ STM32 HAL for hardware abstraction, Speech Recognition Library for voice processing

This system uses voice commands to control a multi-compartment bin with dedicated sections for recycling, compost, and trash. Voice input is processed to identify the type of waste, triggering the appropriate bin section to open. Additionally, ultrasonic sensors monitor the fill levels in each compartment, displaying this data on the corresponding LCD screens.

## Features
* __Voice Recognition:__ The system recognizes predefined commands to categorize waste disposal (e.g., “trash,” “recycle,” “compost”).
* __Automatic Compartment Control:__ Based on voice input, the system opens the correct compartment using servo motors.
* __Fill-Level Detection:__ Each bin compartment includes an ultrasonic sensor to measure and monitor fill levels in real-time.
* __User Feedback:__ Fill levels are displayed on three LCD screens, allowing easy identification of which bins require emptying.

## Technical Components
* __STM32CubeIDE Configuration:__ Used to set up GPIO, I2C, UART, ADC, and PWM for servo motor control.
* __UART Communication:__ Transfers voice recognition data from the microphone module to the STM32 microcontroller for processing.
* __I2C Interface:__ Controls the LCD displays for fill-level feedback.
* __Ultrasonic Sensor Integration:__ HC-SR04 ultrasonic sensors are configured to detect proximity and measure bin fill levels, with data processed to determine bin status.

## Setup and Installation
### 1. Hardware Connections:
* Connect each ultrasonic sensor to the STM32 with GPIO pins for trigger and echo.
* Attach servo motors to PWM-configured pins on the STM32.
* Wire each LCD display to the STM32’s I2C pins with unique addresses.
* Connect the voice recognition module via UART.
### 2. STM32CubeIDE Setup:
* Import the codebase in STM32CubeIDE.
* Configure project peripherals: GPIO for motor control, I2C for LCDs, UART for voice recognition, and ADC for sensor readings.
* Load and build the project in STM32CubeIDE.
### 3. How to Use:
1. Power on the system and connect to STM32CubeIDE.
2. Speak into the microphone to specify the type of waste (e.g., "recycle").
3. The designated compartment will open for disposal.
4. Monitor fill levels displayed on the LCD screens.

## References
* <a href="https://www.st.com/resource/en/user_manual/um1725-description-of-stm32f4-hal-and-lowlayer-drivers-stmicroelectronics.pdf">STM32 HAL Library Documentation</a>
* <a href="https://www.st.com/resource/en/user_manual/um2609-stm32cubeide-user-guide-stmicroelectronics.pdf">STM32CubeIDE</a>




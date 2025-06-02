# Smart Irrigation System using ESP32 and Blynk IoT

An intelligent and fully automated irrigation system built with the **ESP32**, **DHT22**, and **Soil Moisture Sensor** to monitor real-time environmental data and control a water pump accordingly. This project combines **IoT**, **embedded systems**, and **cloud monitoring** to create an efficient solution for sustainable agriculture and home gardening.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Bill of Materials](#bill-of-materials)
- [Circuit Diagram](#circuit-diagram)
- [Pin Configuration](#pin-configuration)
- [Working Principle](#working-principle)
- [Software Requirements](#software-requirements)
- [Installation & Setup](#installation--setup)
- [Blynk App Setup](#blynk-app-setup)
- [Code Explanation](#code-explanation)
- [Future Scope](#future-scope)
- [Screenshots](#screenshots)
- [License](#license)
- [Contact](#contact)

---

## Overview

The **Smart Irrigation System** helps automate the watering process by:

- Monitoring **soil moisture**
- Measuring **temperature and humidity**
- Automatically switching the **water pump**
- Providing **remote control and real-time data visualization** through **Blynk IoT**

It aims to reduce water wastage and human effort in agriculture or gardening.

---

## Features

- Automatic pump control based on soil moisture level
- Manual pump control via Blynk IoT app
- Temperature and humidity measurement using DHT22
- Real-time data logging and visualization
- LCD display for on-device monitoring
- Fail-safe logic to prevent false pump triggers

---

## System Architecture

```text
       +------------+       WiFi       +---------+
       |   ESP32    | <----------------|  Blynk  |
       +------------+                  +---------+
            | GPIO                            |
     +------+--------+                       |
     |               |                       |
[DHT22 Sensor] [Soil Moisture]               |
     |               |                       |
  LCD (I2C)       Relay Module ------------- Pump
```

---

## Bill of Materials

| Component                | Quantity | Notes                          |
|--------------------------|----------|--------------------------------|
| ESP32 DevKit V1          | 1        | Main controller                |
| DHT22 Temperature Sensor | 1        | For temperature/humidity       |
| Soil Moisture Sensor     | 1        | Analog output type             |
| Relay Module (1-Channel) | 1        | Active LOW                     |
| 16x2 LCD (I2C Interface) | 1        | For visual feedback            |
| Submersible Water Pump   | 1        | 5V or 12V pump                 |
| Jumper Wires             | —        | Male-to-male recommended       |
| Breadboard               | 1        | Optional                       |
| Power Supply             | 1        | 5V or USB (for ESP + relay)    |

---

## Circuit Diagram

> *(Insert Fritzing image or schematic diagram here)*

---

## 🔌 Pin Configuration

| Module         | ESP32 Pin |
|----------------|-----------|
| DHT22          | GPIO4     |
| Soil Sensor    | GPIO34 (ADC1) |
| Relay (Pump)   | GPIO26    |
| LCD SDA        | GPIO21    |
| LCD SCL        | GPIO22    |

---

## Working Principle

- The soil sensor reads moisture levels.
- If moisture < threshold (e.g., 40%), pump is automatically activated.
- DHT22 reads temperature and humidity every 5 seconds.
- All data is shown on the LCD and sent to Blynk via Wi-Fi.
- Pump can also be triggered manually from the Blynk app using a switch widget.

---

## Software Requirements

- Arduino IDE 1.8.19 or newer
- ESP32 Board Package
- Blynk Library
- DHT Library by Adafruit
- LiquidCrystal_I2C Library

---

## Installation & Setup

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/smart-irrigation-system.git
   cd smart-irrigation-system
   ```

2. **Open `Smart_Irrigation.ino` in Arduino IDE**

3. **Install Required Libraries**
   - `Blynk` by Volodymyr Shymanskyy
   - `DHT sensor library`
   - `Adafruit Unified Sensor`
   - `LiquidCrystal_I2C`

4. **Replace the Wi-Fi and Auth Credentials in Code**
   ```cpp
   char ssid[] = "YourWiFiName";
   char pass[] = "YourWiFiPassword";
   #define BLYNK_AUTH_TOKEN "YourAuthToken"
   ```

5. **Upload Code to ESP32**  
   Select board: **ESP32 Dev Module**, and upload via USB.

6. **Open Serial Monitor @ 115200 baud** to verify data.

---

## Blynk App Setup

1. Install Blynk from the [Play Store](https://play.google.com/store/apps/details?id=cc.blynk) or [App Store](https://apps.apple.com/).
2. Create a new template:
   - **Template ID**: TMPL3S4kSHAXj
   - **Template Name**: SMART IRRIGATION
   - **Auth Token**: Use from your app/email
3. Add Widgets:
   - `Gauge` for Soil Moisture → V0
   - `Gauge` for Temperature → V1
   - `Gauge` for Humidity → V2
   - `Switch` for Manual Pump → V3

---

##  Code Explanation Highlights

- **Relay Logic**: Active LOW
- **Sensor Mapping**:
  ```cpp
  int soilPercent = map(analogRead(SOIL_PIN), 4095, 0, 0, 100);
  ```
- **Control Logic**:
  ```cpp
  if (!manualPumpOn && soilPercent < pumpThreshold)
      autoPumpOn = true;
  ```

---

## Future Scope

- Add water level monitoring
- Introduce MQTT for scalable IoT integration
- Implement solar-powered irrigation
- Add mobile notifications via Blynk or IFTTT
- Use capacitive soil moisture sensors for better accuracy

---



## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.

---

##  Contact

- **Developer**: Suyog Maindarkar
- **Email**: suyogmaindarkar@gmail.com
- **GitHub**:https://github.com/suyogmaindarkar

---

> “Let your garden grow smarter, not harder.” 🌾

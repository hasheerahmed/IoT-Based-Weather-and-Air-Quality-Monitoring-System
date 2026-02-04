# 🌦️ IoT Weather & Air Quality Monitoring System (ESP32 + Blynk)

An IoT-based weather and air quality monitoring system using the ESP32 microcontroller, DHT22 temperature and humidity sensors, and MQ135 gas sensors. The microcontroller reads the sensors and calculates the derived parameters. It also displays the live results on a 16×2 I2C LCD and sends the live results to the Blynk IoT Cloud.

## 🚀 Features

- Temperature and humidity sensors using DHT22
- Calculation of heat index or “feels like temperature”
- Calculation of dew point
- Monitoring of air quality using the MQ135 sensor
- Calculation of AQI using baseline calibration
- Status of the AQI - GOOD, MODERATE, POLLUTED
- Local display on 16×2 LCD
- Real-time results on Blynk IoT Cloud
- Support for mobile and web applications using Blynk

## 🧠 System Overview

ESP32 reads the sensor data and calculates the results. It then displays the results on the LCD and sends the results to the Blynk IoT Cloud using Virtual Pins.

The MQ135 sensors are calibrated using the baseline calibration method for clean air quality and then send the results.

## 🧰 Hardware Components

| Component | Description |
|---------|------------|
| ESP32 Dev Module | Main microcontroller |
| DHT22 | Temperature and humidity sensors |
| MQ135 | Gas sensors |
| 16×2 LCD (I2C) | Local display |
| Jumper wires | Connectors |
| Breadboard | Prototyping |

---

## 🔌 Pin Connections

### DHT22
- DATA → GPIO 4  
- VCC → 3.3V  
- GND → GND  

### MQ135
- AO → GPIO 34 (ADC pin)  
- VCC → 5V  
- GND → GND  

### 16×2 I2C LCD
- SDA → GPIO 21  
- SCL → GPIO 22  
- VCC → 5V  
- GND → GND  

---

## 📟 LCD Display Format (16×2)

Line 1:
T:25.6C AQI:120


Line 2:
H:62% GOOD

---

## ☁️ Blynk IoT Configuration

### Datastreams (Virtual Pins)

| Parameter | Virtual Pin | Type |
|---------|------------|------|
| Temperature | V0 | Double |
| Humidity | V1 | Double |
| AQI Status | V2 | String |
| Heat Index | V3 | Double |
| Dew Point | V4 | Double |
| AQI Value | V5 | Integer |

### Dashboards

- 📱 Mobile dashboard with gauges, labels, and charts  
- 💻 Web dashboard for real-time monitoring and demos  


---

## 🧪 AQI Calculation Logic

1. MQ135 is first run in **clean air** to determine a baseline value.  
2. Live readings are mapped relative to this baseline.  
3. AQI is calculated using linear mapping and constrained to a 0–500 range.  
4. AQI Status is classified as:  
   - **GOOD**  
   - **MODERATE**  
   - **POLLUTED**  

This approach improves reliability over fixed thresholds.
🛠️software_and_libraries:
  - Arduino IDE
  - ESP32 Board Package
  - Blynk IoT Library
  - DHT Sensor Library
  - LiquidCrystal_I2C Library

## 📈Applications:
  - Smart home air quality monitoring
  - Indoor environment tracking
  - IoT learning and academic projects
  - Weather-based automation systems

## 🧾Future improvements:
  - Automatic calibration for MQ135 sensors
  - AQI trend analysis
  - SMS and Email notifications
  - Power optimization for battery usage
  - Additional sensors for PM2.5 and CO2

## 👤Author:
  Hasheer Ahmed

## 📄 License
  This project is open-source and is licensed under the MIT License.

# Iot-Based Hazard Detection System

## Overview

The Haztec IoT Sensor System is an Arduino-based project that integrates multiple sensors to monitor environmental conditions, detect hazards, and send real-time data to Firebase Realtime Database.

## Features

- **Temperature & Humidity Monitoring** using a DHT11 sensor
- **Motion Detection** using a PIR sensor
- **Flame Detection** using an analog flame sensor
- **Water Level Detection** using a digital water sensor
- **Buzzer Alarm System** for hazard alerts
- **Cloud Data Storage & Retrieval** via Firebase Realtime Database
- **WiFi Connectivity** for remote monitoring

## Hardware Components

- **Arduino Board** (ESP8266 or ESP32 recommended)
- **DHT11 Temperature & Humidity Sensor**
- **PIR Motion Sensor**
- **Flame Sensor**
- **Water Level Sensor**
- **Buzzer**
- **WiFi Module (built-in for ESP8266/ESP32)**
- **LCD Display (optional for debugging)**

## Software Requirements

- **Arduino IDE** (latest version)
- **ESP8266WiFi or ESP32WiFi Library**
- **DHT Sensor Library**
- **Firebase ESP8266/ESP32 Library**
- **Wire Library** (for I2C communication)

## Firebase Configuration

1. **Create a Firebase Project** at [Firebase Console](https://console.firebase.google.com/)
2. **Enable Realtime Database** and set rules to allow read/write access
3. **Obtain API Key & Database URL** from Firebase settings
4. **Register a user with email & password authentication**
5. **Update ********************`API_KEY`********************, ********************`DATABASE_URL`********************, ********************`USER_EMAIL`********************, and ********************`USER_PASSWORD`******************** in the Arduino sketch**

## Circuit Diagram

Ensure proper connections:

- **DHT11 Sensor** → Digital Pin 2
- **PIR Sensor** → Digital Pin 5
- **Flame Sensor** → Analog Pin A0
- **Water Sensor** → Digital Pin 16
- **Buzzer** → Digital Pin 4
- **LCD (Optional)** → I2C Pins

## Code Explanation

### 1. **WiFi & Firebase Setup**

- Connect to WiFi using **SSID** and **Password**
- Authenticate with Firebase using **email & password**

### 2. **Sensor Readings & Data Logging**

- Reads temperature, humidity, motion, flame, and water level data
- Sends data to Firebase every 3 seconds

### 3. **Alert System**

- If flame sensor detects fire (value < 400), buzzer is activated

### 4. **Cloud Storage & Retrieval**

- Uploads sensor values to Firebase
- Retrieves and verifies data from Firebase

## How to Use

1. **Upload the code** to your ESP8266/ESP32 using Arduino IDE
2. **Monitor Serial Output** to check WiFi connection & sensor readings
3. **View data on Firebase Realtime Database** in the `/Haztec1/` node
4. **Test hazard detection** by exposing the flame sensor to a flame source

## Future Improvements

- Add a web dashboard for live monitoring
- Integrate SMS/email alerts for hazards
- Implement battery backup for power failures

## Author

**Qasim Adebisi**

---

This project is designed for safety monitoring in homes, offices, and industries. 🚀


# ⚡ ESP32 Smart Energy Meter Dashboard

## 📌 Overview
This project creates a **Smart Energy Meter** using ESP32 and an ACS712 current sensor.  
It serves a **local web dashboard** showing **current, voltage, and power** in real-time.

---

## 🛠️ Hardware Required
- ESP32 Dev Board  
- ACS712 Current Sensor (5A / 20A / 30A model)  
- Voltage Divider (to measure mains voltage safely)  
- Jumper wires, breadboard  
- Optional: LCD display for local readings

---

## 🔌 Wiring
- ACS712 → ESP32:  
  - VCC → 5V  
  - GND → GND  
  - OUT → GPIO34 (Analog input)

- Voltage Divider → ESP32:  
  - Output → GPIO35 (Analog input)  
  - Resistors as per divider design to scale 230V AC to ESP32-safe voltage

> ⚠️ Be careful when connecting mains voltage! Use proper isolation.

---

## ▶️ Usage
1. Upload the sketch to ESP32.  
2. Connect to the Wi-Fi access point `ESP32-AccessPoint` (password: `12345678`).  
3. Open a browser → go to `192.168.4.1` to view the dashboard.  
4. Current, Voltage, and Power readings update every second.

---

## 📂 Repo Structure

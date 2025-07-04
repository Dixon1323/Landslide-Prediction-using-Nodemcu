# Landslide-Prediction-using-Nodemcu

[![Language](https://img.shields.io/badge/Language-C%2B%2B-yellow.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/Programming_language)

This project implements a basic landslide prediction system using NodeMCU (ESP8266/ESP32) microcontrollers. It involves multiple **transmitter units** that gather environmental sensor data and a **receiver unit** that processes this data for early warnings. The modular and distributed nature suggests a scalable sensor network approach.

## 📑 Table of Contents

- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## 🚀 Features

- **Data Acquisition**: Collect environmental parameters (e.g., soil moisture, tilt, vibration) using NodeMCU-based transmitters  
- **Wireless Communication**: Use Wi-Fi or supported protocols to transmit data to the receiver  
- **Data Processing**: Receiver aggregates sensor readings and may perform basic threshold analysis  
- **Modular Design**: Codebase is organized by function (`transmitter_X`, `receiver_X`) for easy expansion  
- **Visual System Architecture**: Includes `block_diagram.png` for high-level understanding of the system  

## 🧰 Technologies Used

- **C++**  
- **NodeMCU / ESP8266 / ESP32**  
- **Arduino IDE or PlatformIO**  
- **Wi-Fi Communication Libraries** (`ESP8266WiFi`, `WiFiClient`, etc.)

## 🔧 Installation

> This project requires a microcontroller development environment and multiple NodeMCU/ESP8266 boards.

1. **Clone the repository:**
   ```bash
   git clone https://github.com/your-username/landslide-prediction-using-nodemcu.git
   cd landslide-prediction-using-nodemcu
   ```

2. **Install Arduino IDE or PlatformIO** and configure ESP8266/ESP32 board support via the Boards Manager or platform configuration.

3. **Explore the Project Structure:**
   - `new_transmitter/`
   - `receiver/`
   - `receiver_new/`
   - `transmitter_1/`, `transmitter_2/`, `transmitter_3/`

4. **Open each folder** individually in your IDE to work on or upload that specific unit.

5. **Install required libraries** based on includes in each `.ino` file (e.g., `EEPROM.h`, `ESP8266WiFi.h`, sensor-specific libraries).

6. **Connect your NodeMCU board** and select the correct port and board under:
   - Arduino IDE: `Tools > Board`, `Tools > Port`
   - PlatformIO: Via `platformio.ini`

7. **Upload the code** to the appropriate microcontroller unit.

## ▶️ Usage

1. **Deploy the transmitter units** in different monitoring zones. Each one collects sensor data related to landslide-prone conditions.

2. **Power up the receiver unit**, which collects and processes incoming data from transmitters.

3. **Wi-Fi Configuration**:  
   Ensure the correct SSID/password and static IPs or soft-AP configurations are set inside the transmitter and receiver code for successful communication.

4. **Monitor the output** from the receiver — either via:
   - Serial Monitor (Arduino IDE)
   - OLED/LCD displays (if connected)
   - Remote notification setup (optional)

5. **Interpret the data** to evaluate environmental conditions and determine landslide risk levels based on thresholds coded into the receiver.

## 🖼️ System Diagram

A high-level overview of the project architecture is provided in:

- `block_diagram.png`

Refer to this image for understanding the data flow between transmitters and receiver.

## 🤝 Contributing

Contributions are welcome!

1. Fork the repository  
2. Create a new feature branch:  
   ```bash
   git checkout -b feature/YourFeature
   ```
3. Commit your changes:  
   ```bash
   git commit -m "Add YourFeature"
   ```
4. Push to your fork:  
   ```bash
   git push origin feature/YourFeature
   ```
5. Open a Pull Request for review

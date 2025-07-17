Gas Sensor Data Logger (ESP32 + Firebase)

This project logs gas concentration data in real-time using an MQ2 sensor and ESP32.  
Data is uploaded to Firebase and can be viewed through a live dashboard.

Features
- Real-time gas concentration monitoring
- Cloud logging using Firebase Realtime Database
- Wi-Fi-based communication using ESP32
- Threshold alert system (can be extended)

Tools & Components
- ESP32  
- MQ2 Gas Sensor  
- Firebase Realtime Database  
- Arduino IDE (C)

Setup Instructions

1. Connect the MQ2 sensor to ESP32:
   - `VCC` to `3.3V`
   - `GND` to `GND`
   - `AO` to any analog pin (e.g. `GPIO34`)

2. Use the Arduino IDE:
   - Install `Firebase_ESP_Client` library
   - Set up your Wi-Fi SSID and password
   - Add Firebase API key and Database URL

3. Upload the code and observe the Firebase data flow.

Future Improvements
- Add LCD or OLED display for local viewing
- Include buzzer/LED alerts
- Plot data on web dashboard using JavaScript or Node.js

Author
Ghulam Ali – Electrical Engineer @ IST  

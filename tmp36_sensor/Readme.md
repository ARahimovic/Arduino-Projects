# TMP36 Temperature Sensor: Summary

## 1. How the TMP36 Works
The TMP36 is a **precision analog temperature sensor** based on semiconductor technology. It works by leveraging the **temperature-dependent behavior of transistors**:
- The **voltage across a transistor junction** changes predictably with temperature.
- The TMP36 generates a voltage that is linearly proportional to temperature.
- The sensor is factory-calibrated to output **500 mV at 0°C** and **10 mV for every 1°C increase** in temperature.

### Key Points:
- **Output Voltage Range**: 500 mV at 0°C, 750 mV at 25°C.
- **Linearity**: For every degree Celsius increase, the output voltage increases by 10 mV.
- **Operating Voltage**: 2.7V to 5.5V, making it compatible with Arduino.

## 2. What the TMP36 Outputs
- The TMP36 outputs an **analog voltage** that is proportional to temperature:
  - **500 mV at 0°C**.
  - **750 mV at 25°C**.
- This analog voltage is then read by the **Arduino's ADC (Analog-to-Digital Converter)** as a value between **0 and 1023**.

## 3. Interfacing TMP36 with Arduino

### Wiring:
- **TMP36 Pin 1 (Vs)** → Arduino **5V** (or 3.3V).
- **TMP36 Pin 2 (Vout)** → Arduino **A0** (analog input pin).
- **TMP36 Pin 3 (GND)** → Arduino **GND**.

### Code to Read Temperature:

```cpp
const int sensorPin = A0;  // Pin where TMP36 is connected
const float voltageReference = 5.0;  // Use 5V for 5V Arduinos, or 3.3V for 3.3V boards

void setup() {
  Serial.begin(9600);  // Start serial communication
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Read the analog value from the sensor
  float voltage = sensorValue * (voltageReference / 1024.0);  // Convert to voltage
  float temperatureC = (voltage - 0.5) * 100.0;  // Convert voltage to Celsius
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  delay(1000);  // Wait 1 second before next reading
}

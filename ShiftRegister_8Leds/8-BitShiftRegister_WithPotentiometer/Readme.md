# Potentiometer Summary

## What is a Potentiometer?
A **potentiometer** (or "pot") is a three-terminal variable resistor used to adjust resistance or divide voltage in a circuit. It is commonly used for adjusting levels such as volume, brightness, or motor speed.

## Structure
A potentiometer consists of:
- **Two fixed terminals** (A and B) connected to either end of a resistive element.
- **One wiper terminal (W)** that moves along the resistive element and varies the resistance between terminals as it rotates or slides.

## How It Works
The potentiometer can function in two ways:
1. **As a Variable Resistor (Rheostat)**:
   - Only two terminals (A and W or B and W) are used.
   - The wiper adjusts the resistance between the fixed terminal and the wiper.
   - The total resistance can vary from 0 ohms to the maximum rated value of the potentiometer.

2. **As a Voltage Divider**:
   - All three terminals (A, B, and W) are used.
   - Terminal A is connected to the input voltage (e.g., 5V).
   - Terminal B is connected to ground (0V).
   - The wiper (W) outputs a voltage between 0V and the input voltage depending on its position.
   
   ### Voltage Divider Formula:
   The output voltage at the wiper (\( V_{out} \)) is calculated by the formula:
   
   \[
   V_{out} = V_{in} \times \frac{R_2}{R_1 + R_2}
   \]
   
   Where:
   - \( R_1 \) is the resistance between **Vcc** and the wiper (A to W).
   - \( R_2 \) is the resistance between the wiper and **GND** (W to B).
   - \( V_{in} \) is the input voltage applied across terminals A and B.

## How to Connect a Potentiometer

1. **As a Variable Resistor**:
   - Connect **A** to one point in the circuit.
   - Connect **W** to another point in the circuit (leave **B** disconnected).

2. **As a Voltage Divider**:
   - Connect **A** to the power supply (e.g., +5V).
   - Connect **B** to ground (0V).
   - Connect **W** to an analog input or wherever the divided voltage is required.

## Example: Using Potentiometer with Arduino
Here’s an example of how to read a potentiometer value using Arduino:

### Circuit:
- **A** to +5V.
- **B** to GND.
- **W** to an analog input pin (e.g., A0).

### Arduino Code:
```cpp
int potPin = A0;  // Pin where the wiper is connected
int potValue = 0; // Variable to store the potentiometer value

void setup() {
  Serial.begin(9600);  // Start the serial communication
}

void loop() {
  potValue = analogRead(potPin);  // Read the potentiometer value (0-1023)
  Serial.print("Potentiometer value: ");
  Serial.println(potValue);       // Print the value to the Serial Monitor
  delay(500);                     // Wait for 500 ms
}

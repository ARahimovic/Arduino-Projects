#include <Wire.h>

#define SLAVE_ADDRESS 0x27  // LCD adress is 0x27

void setup() {
    Wire.begin(); // Initialize I2C as master
    Serial.begin(9600); // Initialize Serial for debugging
}

void loop() {
    // Step 1: Begin transmission to the I2C slave device
    Wire.beginTransmission(SLAVE_ADDRESS);

    // Step 2: Send data (example: sending command 0x01)
    Wire.write(0x01);

    // Step 3: End transmission and check for acknowledgment
    byte status = Wire.endTransmission();

    // Step 4: Check the status of the transmission
    if (status == 0) {
        Serial.println("ACK received: Data sent successfully.");
    } else if (status == 1) {
        Serial.println("Error: Data too long to send.");
    } else if (status == 2) {
        Serial.println("Error: NACK received on address (incorrect address or no device).");
    } else if (status == 3) {
        Serial.println("Error: NACK received on data.");
    } else {
        Serial.println("Error: Other error occurred.");
    }

    delay(1000); // Wait for a second before the next loop iteration
}
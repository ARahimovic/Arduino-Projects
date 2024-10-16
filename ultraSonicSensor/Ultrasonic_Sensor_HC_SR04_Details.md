
# How an Ultrasonic Sensor Works

An ultrasonic sensor, such as the **HC-SR04**, works by using sound waves to measure the distance to an object. Here's a step-by-step breakdown of the basic principle and operation:

## 1. Principle of Operation

- **Sound Waves**: The sensor sends out sound waves at a high frequency (typically 40 kHz), which is beyond the range of human hearing (ultrasonic).
- **Echo Detection**: When these sound waves hit an object, they bounce back to the sensor. The sensor then measures the time it takes for the sound to travel to the object and return.
- **Distance Calculation**: Since the speed of sound in air is known (approximately 343 meters per second), the sensor uses the time it takes for the echo to return to calculate the distance to the object.

## 2. Basic Formula

The formula used to calculate the distance based on the time for the echo to return is:

\[	ext{Distance} = rac{	ext{Speed of Sound} 	imes 	ext{Time}}{2}\]

Why divide by 2? The sound wave travels to the object and back, so the total time measured is for a round trip. Dividing by 2 gives the one-way distance.

For example, the speed of sound is approximately **343 m/s** (or **34,300 cm/s**). If the sensor detects an echo after 1 millisecond (1000 microseconds), the distance would be calculated as:

\[	ext{Distance (cm)} = rac{34300 	imes 1000\, \mu s}{2 	imes 1000000} = 17.15\, cm\]

## HC-SR04 Ultrasonic Sensor

The **HC-SR04** is a popular ultrasonic sensor used in many electronics and Arduino projects. It has four pins:

- **VCC**: Power supply (+5V).
- **GND**: Ground.
- **TRIG**: Trigger pin. You send a signal to this pin to initiate the measurement.
- **ECHO**: Echo pin. This pin outputs the time it takes for the sound wave to return after hitting an object.

## How HC-SR04 Works

### Triggering the Sensor:

1. You send a **10-microsecond HIGH pulse** to the **TRIG** pin to start the measurement.
2. This signals the sensor to emit an ultrasonic burst of 8 pulses at 40 kHz (ultrasound).

### Listening for Echo:

1. After sending the pulse, the sensor switches to listen mode and waits for the reflected echo to return.
2. The **ECHO** pin goes HIGH as soon as the sensor emits the sound pulse, and it stays HIGH until the echo returns.

### Measuring the Echo Duration:

- The duration for which the **ECHO** pin remains HIGH is the time it took for the sound to travel to the object and back.
- This duration can be measured using the **`pulseIn()`** function in Arduino.

### Distance Calculation:

Once the duration is measured, you can calculate the distance using the speed of sound as described earlier.

## Example Timing

- **Trigger Signal**: A 10-microsecond pulse is sent on the **TRIG** pin.
- **Echo Return Time**: If the echo is received after, say, 1 millisecond (1000 microseconds), the distance is calculated as:

\[	ext{Distance (cm)} = rac{34300 	imes 1000\, \mu s}{2 	imes 1000000} = 17.15\, cm\]

## `pulseIn()` Function

The `pulseIn()` function in Arduino is used to measure the time a pin remains in a HIGH or LOW state. Here’s how it works:

### Syntax:

```cpp
pulseIn(pin, value);
```

- **pin**: The pin number on which to read the pulse (in this case, the **ECHO** pin).
- **value**: The state to listen for, either HIGH or LOW. In the case of the ultrasonic sensor, we are measuring how long the **ECHO** pin stays HIGH.

### Example:

```cpp
long duration = pulseIn(echoPin, HIGH);
```

This command measures the time (in microseconds) for which the **ECHO** pin remains HIGH.

### How `pulseIn()` Works with HC-SR04

- **Wait for Echo Pin to Go HIGH**: After sending the trigger signal, the sensor sends out a pulse and the **ECHO** pin goes HIGH. The `pulseIn()` function starts counting as soon as it detects the **ECHO** pin going HIGH.
- **Wait for Echo Pin to Go LOW**: The **ECHO** pin stays HIGH until the sensor receives the reflected sound wave (echo) from the object. As soon as the echo is detected, the **ECHO** pin goes LOW, and `pulseIn()` stops counting.
- **Return Duration**: `pulseIn()` returns the duration (in microseconds) for which the **ECHO** pin was HIGH, representing the total time the sound took to travel to the object and back.

## Summary of the Process:

1. Send a 10-microsecond pulse to the **TRIG** pin.
2. The sensor emits an ultrasonic pulse and listens for an echo.
3. The **ECHO** pin stays HIGH while waiting for the echo.
4. Use `pulseIn()` to measure the time the **ECHO** pin remains HIGH.
5. Calculate the distance using the formula:

\[	ext{Distance (cm)} = rac{	ext{Duration} 	imes 34.3}{2}\]

## Example Code:

```cpp
#define TRIG_PIN 5  // Trigger pin
#define ECHO_PIN 3  // Echo pin

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop() {
    // Send a 10µs pulse to trigger the sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure the duration for the echo to return
    long duration = pulseIn(ECHO_PIN, HIGH);

    // Calculate the distance (in cm)
    float distance = (duration * 0.0343) / 2;

    // Output the distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(500);  // Delay between measurements
}
```

This code sets up an HC-SR04 sensor and uses `pulseIn()` to measure the echo duration, then calculates the distance to an object in centimeters.

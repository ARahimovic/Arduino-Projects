# Summary of Piezo Buzzers

## 1. How a Piezo Buzzer Works
- A **piezo buzzer** converts electrical energy into sound using the **piezoelectric effect**.
- When voltage is applied to the piezoelectric material inside the buzzer, it vibrates and produces sound waves.
- The frequency of the sound produced depends on the frequency of the applied electrical signal.

## 2. Types of Buzzers
- **Active Buzzer**:
  - Contains an internal oscillator.
  - Requires only DC voltage to produce a fixed frequency sound.
  - Operates at its natural resonant frequency, producing clear and loud sound.
  
- **Passive Buzzer**:
  - Lacks an internal oscillator and needs an external AC signal or square wave.
  - Can produce sounds at varying frequencies based on the input signal.
  - The quality of sound varies with how close the applied frequency is to its natural frequency.

## 3. Tone Function
- The `tone(pin, frequency, duration)` function in programming (e.g., Arduino) generates sound on a buzzer:
  - **`pin`**: The digital pin connected to the buzzer.
  - **`frequency`**: The frequency of the tone in Hertz (Hz).
  - **`duration`** (optional): Length of time to produce the tone.
- The function generates a square wave signal, toggling the pin HIGH and LOW to create sound at the specified frequency.

## 4. Frequency Calibration in Passive Buzzers
- Passive buzzers can vibrate at various frequencies, but they produce sound most efficiently at their resonant frequency.
- The buzzer responds to the frequency of the input signal, allowing it to generate different sounds.
- While the buzzer can produce sound at non-resonant frequencies, the output may be quieter or of lower quality.

## 5. Active Buzzer Functionality
- An active buzzer operates at its natural frequency due to its internal oscillator.
- When powered, it generates a constant tone without needing an external signal.

## Conclusion
- Both active and passive buzzers have unique characteristics and applications.
- Understanding how each type works helps in selecting the right buzzer for specific projects.

# Button Debouncing and Action Handler

This project demonstrates a button debouncing mechanism in Arduino, with the ability to assign custom actions to different buttons. It handles both momentary button presses (trigger mode) and continuous button presses, with debouncing logic to filter out signal noise.

## Features

- **Debouncing Logic**: Ensures that any noise or transient changes during button presses are ignored by implementing a debounce delay.
- **Trigger and Continuous Mode**: Supports two modes of button operation:
  - **Trigger Mode**: Detects state transitions and triggers actions when a button is pressed or released.
  - **Continuous Mode**: Executes an action continuously as long as the button remains pressed.
- **Customizable Actions**: You can assign different functions to be executed for each button press by using function pointers. This makes the code reusable for different buttons with distinct behaviors.

## Components

- **Button Struct**: Stores each button's state, debounce timer, and action to perform.
- **Debouncing Logic**: Implements button debouncing and prevents erratic behavior caused by noisy signals.
- **Function Pointers**: Allows dynamic assignment of functions to be triggered by button events.

## Wiring

- Connect the first button to pin **2**.
- Connect the second button to pin **3**.
- Use **INPUT_PULLUP** for both buttons to detect state changes when pressed.

## Example Code

```cpp
const int input1 = 2;
const int input2 = 3;
const int bouncingDelay = 50;

struct Button
{
  int pin;
  int lastButtonReading;
  int lastButtonState;
  unsigned long bouncingTimer;
  bool isTrigger;
  void(*action)();
};

Button button1 = {input1, HIGH, 0, HIGH, true, Print};
Button button2 = {input2, HIGH, 0, HIGH, false, Print};

void setup()
{
  pinMode(input1, INPUT_PULLUP);
  pinMode(input2, INPUT_PULLUP);

  Serial.begin(9600);
  while (!Serial);
}

void loop()
{
  checkButton(&button1);
  checkButton(&button2);

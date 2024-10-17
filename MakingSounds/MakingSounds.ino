/***
 * This program controls an active buzzer (or a LED for dimming) using three buttons.
 * - One button toggles the power (on/off) for the buzzer/LED.
 * - The other two buttons adjust the volume or brightness in increments or decrements.
 *
 * Key Features:
 * - Debouncing: Each button press is debounced to avoid false triggers.
 * - Power Control: The buzzer/LED can be powered on or off using the power button.
 * - Volume/Brightness Control: The volume of the buzzer (or brightness of an LED) can be
 *   increased or decreased incrementally using two buttons.
 *
 * The code is written in a generic way to handle different actions for different buttons using
 * function pointers, making it flexible and reusable.
 *
 * The `analogWrite` function is used to control the buzzer volume or LED brightness by setting
 * a PWM value between 0 (off) and 255 (maximum).
 *
 * How it works with LEDs:
 * - When connected to an LED instead of a buzzer, the same logic will allow you to dim or
 *   brighten the LED by increasing or decreasing the PWM signal sent to the LED.
 *
 * The buttons support two modes:
 * - Trigger mode: The action is executed once when the button is pressed and released.
 * - Continuous press mode: The action is continuously executed while the button remains pressed.
 ***/

const int bouncingDelay = 50; // 50 ms for debouncing
const int decreasePin = 2;
const int increasePin = 3;
const int powerPin = 4;
const int buzzerPin = 5; // active buzzer pin
bool isPowered = false;  // by default the buzzer is off

const int defaultVolume = 255 / 2; // default at 50%
const int maxVolume = 255;         // default at 50%
const int minVolume = 0;           // default at 50%
const int increaseAmount = 10;     // Volume increase step
int currentVolume = defaultVolume; // Initialize current volume with default value

void increaseVolume();
void decreaseVolume();
void togglePower();

struct Button
{
  int pin;
  int lastButtonReading;
  int lastButtonState;
  unsigned long bouncingTimer;
  // is trigger button or as long is pressed
  bool isTrigger;
  // function pointer
  void (*action)();
};

Button increaseButton = {increasePin, HIGH, HIGH, 0, true, increaseVolume};
Button decreaseButton = {decreasePin, HIGH, HIGH, 0, true, decreaseVolume};
Button powerButton = {powerPin, HIGH, HIGH, 0, true, togglePower};

void setup()
{
  pinMode(increasePin, INPUT_PULLUP);
  pinMode(decreasePin, INPUT_PULLUP);
  pinMode(powerPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  while (!Serial)
    ;
}

void loop()
{
  // increase /decrease volume only when power is on
  if (isPowered)
  {
    checkButton(&increaseButton);
    checkButton(&decreaseButton);
  }
  checkButton(&powerButton);
}

void increaseVolume()
{
  currentVolume += increaseAmount;
  if (currentVolume > maxVolume)
    currentVolume = maxVolume;

  analogWrite(buzzerPin, currentVolume);
  Serial.print("current Volume : ");
  Serial.println(currentVolume);
}

void decreaseVolume()
{
  currentVolume -= increaseAmount;
  if (currentVolume < minVolume)
    currentVolume = minVolume;

  analogWrite(buzzerPin, currentVolume);
  Serial.print("current Volume : ");
  Serial.println(currentVolume);
}

void togglePower()
{
  isPowered = !isPowered;
  if (isPowered)
  {
    // when we power it , we power it at default volume
    analogWrite(buzzerPin, defaultVolume);
    // reset current volume
    currentVolume = defaultVolume;
  }
  else
  {
    analogWrite(buzzerPin, 0);
    Serial.println("power is OFF");
  }
}

void checkButton(Button *btn)
{
  int reading = digitalRead(btn->pin);
  if (reading != btn->lastButtonReading)
  {
    btn->bouncingTimer = millis();
    btn->lastButtonReading = reading;
  }

  if ((millis() - btn->bouncingTimer) > bouncingDelay)
  {
    if (btn->isTrigger)
    {
      if (reading != btn->lastButtonState)
      {
        btn->lastButtonState = reading;
        if (reading == LOW)
        {
          btn->action();
        }
        else
        {
          Serial.println("button released");
        }
      }
    }
    // if not trigger , check for continue pressing
    else
    {
      if (reading == LOW)
      {
        btn->action();
      }
    }
  }
}
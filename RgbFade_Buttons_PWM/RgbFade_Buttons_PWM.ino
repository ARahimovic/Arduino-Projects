/***
 * This code controls the brightness of an RGB LED (common anode) using three buttons.
 * Each button controls one color: red, green, or blue. Pressing a button will cycle
 * the brightness of the corresponding color from fully on (255) to fully off (0),
 * by decrementing its brightness value.
 *
 * The following elements are defined:
 *
 * - Buttons: Three buttons are assigned to control red, green, and blue brightness individually.
 *   The buttons have a debounce mechanism to avoid unintended triggers due to signal noise.
 *
 * - RGB Pins: The RGB LED is connected to three PWM-capable pins, which are used to control
 *   the brightness of each color. The LED operates with a common anode, meaning the brightness
 *   decreases as the PWM value approaches 0 (full on).
 *
 * - Button Logic: When a button is pressed, the corresponding color value is decremented.
 *   Once the value reaches 0, it resets to 255 to continue the cycle.
 *
 * - Main Loop: The loop checks for button presses and adjusts the brightness accordingly using
 *   the `analogWrite()` function, which sets the PWM value for each color pin.
 */

const int bouncingDelay = 50; // 50 ms for debouncing

const int redButtonPin = 2;
const int greenButtonPin = 3;
const int blueButtonPin = 4;

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int redVal = 0; // or can start with redVal = 255 and decrement directly
int greenVal = 0;
int blueVal = 0;

bool isPowerd = false;

void incrementRed();
void incrementGreen();
void incrementBlue();

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

Button redButton = {redButtonPin, HIGH, HIGH, 0, false, incrementRed};
Button greenButton = {greenButtonPin, HIGH, HIGH, 0, false, incrementGreen};
Button blueButton = {blueButtonPin, HIGH, HIGH, 0, false, incrementBlue};

void setup()
{
  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  analogWrite(redPin, 255 - redVal);
  analogWrite(greenPin, 255 - greenVal);
  analogWrite(bluePin, 255 - blueVal);

  Serial.begin(9600);
  while (!Serial)
    ;
}

void loop()
{
  // increase /decrease volume only when power is on
  checkButton(&redButton);
  checkButton(&greenButton);
  checkButton(&blueButton);
}

void incrementRed()
{
  redVal++;
  if (redVal > 255)
    redVal = 0;

  analogWrite(redPin, 255 - redVal);
  Serial.print("red Val = ");
  Serial.println(redVal);
}

void incrementGreen()
{
  greenVal++;
  if (greenVal > 255)
    greenVal = 0;

  analogWrite(greenPin, 255 - greenVal);
  Serial.print("greenVal  = ");
  Serial.println(greenVal);
}

void incrementBlue()
{
  blueVal++;
  if (blueVal > 255)
    blueVal = 0;

  analogWrite(bluePin, 255 - blueVal);
  Serial.print("blueVal  = ");
  Serial.println(blueVal);
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
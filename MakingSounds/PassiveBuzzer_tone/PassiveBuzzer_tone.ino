/***
 * Buzzer Controller with Tone Selection
 * 
 * This program controls a passive buzzer using three buttons: 
 * - One button to toggle power on/off
 * - One button to increase the frequency (note) of the sound
 * - One button to decrease the frequency (note) of the sound
 *
 * The buzzer will play tones based on the C Major scale frequencies. 
 * The program uses debouncing techniques to ensure accurate button presses.
 * 
 * Key Features:
 * - Power toggle to turn the buzzer on/off
 * - Frequency cycling through a predefined array of musical notes (C4, D4, E4, F4, G4, A4, B4, C5)
 * 
 * Note: The tone is generated using the tone() function, and the program checks for button states continuously 
 * in the loop to react to user input promptly.
 * 
 * This sketch uses an Arduino compatible microcontroller.
 ***/


const int bouncingDelay = 50; // 50 ms for debouncing
const int decreasePin = 2;
const int increasePin = 3;
const int powerPin = 4;
const int buzzerPin = 5; // active buzzer pin
bool isPowered = false;  // by default the buzzer is off

const int Cfrequencies[] = {
  // C Major scale frequencies (Do, Re, Mi, Fa, Sol, La, Si, Do)
  261,  // C4 (Do)
  293,  // D4 (Re)
  329,  // E4 (Mi)
  349,  // F4 (Fa)
  392,  // G4 (Sol)
  440,  // A4 (La)
  493,  // B4 (Si)
  523   // C5 (Do)
};

int index = 0;
int size = sizeof(Cfrequencies) / sizeof(Cfrequencies[0]);

void increaseIndex();
void decreaseIndex();
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

Button increaseButton = {increasePin, HIGH, HIGH, 0, true, increaseIndex};
Button decreaseButton = {decreasePin, HIGH, HIGH, 0, true, decreaseIndex};
Button powerButton = {powerPin, HIGH, HIGH, 0, true, togglePower};

void setup()
{
  pinMode(increasePin, INPUT_PULLUP);
  pinMode(decreasePin, INPUT_PULLUP);
  pinMode(powerPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  while (!Serial);
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

void increaseIndex()
{
  index++;
  if (index >= size)
    index = 0;

  tone(buzzerPin, Cfrequencies[index]);
  Serial.print("current frequency : ");
  Serial.println(Cfrequencies[index]);
}

void decreaseIndex()
{
  index--; 
  if (index < 0)
    index = size - 1;

  tone(buzzerPin, Cfrequencies[index]);
  Serial.print("current frequency : ");
  Serial.println(Cfrequencies[index]);
}

void togglePower()
{
  isPowered = !isPowered;
  if (isPowered)
  {
    // when we power it , we power it at default volume
     tone(buzzerPin, Cfrequencies[index]);
     Serial.println("power is On");
  }
  else
  {
    noTone(buzzerPin);
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
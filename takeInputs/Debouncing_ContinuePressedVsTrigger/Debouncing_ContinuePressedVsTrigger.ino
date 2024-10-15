const int input1 = 2;
const int input2 = 3;
const int bouncingDelay = 50;

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
void Print()
{
  Serial.println("button Pressed");
}

Button button1 = {input1, HIGH, HIGH, 0, true, Print};
Button button2 = {input2, HIGH, HIGH, 0, false, Print};

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
    // Check for continue pressing
    else
    {
      if (reading == LOW)
      {
        btn->action();
      }
    }
  }
}
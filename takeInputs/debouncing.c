#define DEBOUNCING_ON

const int led = 5;
const int pushButton = 3;
const unsigned int debounceDelay = 50 ; // 50 ms is a good debounce delay

int ledState = LOW; 
int lastRawButtonState = HIGH; //by default not pressed
int lastStableButtonState = HIGH;
unsigned long bounceTimer = 0;

void setup()
{
    pinMode(led, OUTPUT);
  //INPUT_PULLUP : meaning when not connected, default state is HIGH
  //PushButton is connected to the ground in order to be LOW when pressed
    pinMode(pushButton, INPUT_PULLUP);
}

void loop()
{
    int currentButtonReading = digitalRead(pushButton);
    
#ifdef DEBOUNCING_ON    
    if(currentButtonReading != lastRawButtonState)
    {
        bounceTimer = millis();
        lastRawButtonState = currentButtonReading;
    }

    if((millis() - bounceTimer) > debounceDelay)
    {
        if(lastStableButtonState != currentButtonReading)
        {
            lastStableButtonState = currentButtonReading;
            if(lastStableButtonState == LOW)
            {
                ledState = !ledState;
                digitalWrite(led, ledState);
            }
        }
    } 

    

#else

if(currentButtonReading == LOW)
    {
        ledState = !ledState;
        digitalWrite(led, ledState);

    }
#endif

}

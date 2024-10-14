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
    //each time an input change, reset timer
    if(currentButtonReading != lastRawButtonState)
    {
        bounceTimer = millis();
        lastRawButtonState = currentButtonReading;
    }

    // if the timer is greated than the bounce delay, it means the system stabilised
    if((millis() - bounceTimer) > debounceDelay)
    {
        // Only change the button state if it has actually changed
        if(lastStableButtonState != currentButtonReading)
        {
            lastStableButtonState = currentButtonReading;
            if(lastStableButtonState == LOW)                          // if we wanted the led to be on as long the button is pressed we change this part of the logic 
            {                                                            
                ledState = !ledState;                                       
                digitalWrite(led, ledState);                              /*
                                                                          if(lastStableButtonState == LOW)                         
                                                                          {   
                                                                            digitalWrite(led,HIGH);
                                                                          else
                                                                            digitalWrite(led,HIGH);
                                                                          */                            
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

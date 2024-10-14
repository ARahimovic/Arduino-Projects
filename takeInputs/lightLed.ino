//#define lightLedWhilePressed
#define toggleLedWithEachPress

const int led = 5;
const int pushButton = 3;

int ledState = LOW;

void setup()
{
    pinMode(led, OUTPUT);
  //INPUT_PULLUP : meaning when not connected, default state is HIGH
  // need to connect the button to ground in order to be low when pressed
    pinMode(pushButton, INPUT_PULLUP);
}

void loop()
{

#ifdef lightLedWhilePressed
    
    if(digitalRead(pushButton) == LOW )
        digitalWrite(led, HIGH);
    else
        digitalWrite(led, LOW);

#elif toggleLedWithEachPress

    if(digitalRead(pushButton) == LOW)
            //toggle the state using XOR with 1
            ledState ^= 1; 
    
    digitalWrite(led, ledState);
    
#endif



}
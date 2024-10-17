const int columns = 16;
const int rows = 2;
const int enablePin = 3;
const int rsPin = 2;
const int LCD_brightnessPin = 9; // PWM pin for backlight brightness control
const int brightnessControlPin = A5; // Analog pin for brightness control

//4 bit mode
const int dataPins[4] = {4,5,6,7};

void InitialisePin()
{
    for(int i =0; i <4; i++)
    {
        pinMode(dataPins[i], OUTPUT);
    }
    pinMode(enablePin, OUTPUT);
    pinMode(rsPin, OUTPUT);
    pinMode(LCD_brightnessPin, OUTPUT);
}

void sendCommand(uint8_t command)
{
    //we set the rsPin to low
    digitalWrite(rsPin, LOW);
    lcdSend(command);
    digitalWrite(rsPin, HIGH);
}
void sendData(uint8_t data)
{

}
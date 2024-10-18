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


void sendNibble(uint8_t nibble)
{
    nibble = nibble & 0x0F;
    digitalWrite(dataPins[0], nibble & 0x01);
    digitalWrite(dataPins[1], (nibble >> 1) & 0x01);
    digitalWrite(dataPins[2], (nibble >> 2) & 0x01);
    digitalWrite(dataPins[3], (nibble >> 3) & 0x01);
    digitalWrite(enablePin, HIGH);
    delayMicroseconds(1);
    digitalWrite(enablePin, LOW);
}

void sendByte(uint8_t byte)
{
    //send upper nibble
    sendNibble(byte >> 4);
    delay(1);
    //send LowerNibble
    sendNibble(byte & 0x0F);
}

void sendCommand(uint8_t command)
{
    //we set the rsPin to low
    digitalWrite(rsPin, LOW);
    delay(1);
    sendByte(command);
}
void sendData(uint8_t data)
{
    //we set the rsPin to HIGH : data
    digitalWrite(rsPin, HIGH);
    delay(1);
    sendByte(data);
}

void InitialiseLCD()
{
    InitialisePin();
    //we do initialisation sequence
    delay(15);
    sendNibble(0x3);
    delay(5);
    sendNibble(0x3);
    delay(1);
    sendNibble(0x3);
    delay(1);
    sendNibble(0x2);
  //function set in 4 bit mode : 4 bit mode, 2 lines, font 0 : 5*8
    sendCommand(0x28);
    //clear display
    sendCommand(0x01);
    delay(3);
  	//entry mode set : increment , no display shift
    sendCommand(0x6);
    //Display on , cursor on , cursor blinking
    sendCommand(0xF);

    analogWrite(LCD_brightnessPin, 255);
}


void ControlBrightness(float pourcentage)
{
    int val = pourcentage * 255 / 100;
    analogWrite(LCD_brightnessPin, val);
}

void lcdPrint(const char* str)
{
    while(*str)
    {
        sendData(*str);
        str++;
    }
}


void setup()
{
    InitialiseLCD();
    sendData('C');
    lcdPrint("Hello/n");
}

void loop()
{
}
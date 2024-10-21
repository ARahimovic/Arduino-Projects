#define CLEAR_COMMAND 0x01
#define RETURN_HOME_COMMAND 0x02
// display instruction status 0b00001DCB / D : display, C: cursor, B:blink
uint8_t displayControl = 0x08;
#define DISPLAY_MASK 0x04
#define CURSOR_MASK 0x02
#define BLINK_MASK 0x01

const int columns = 16;
const int rows = 2;
const int enablePin = 3;
const int rsPin = 2;
const int LCD_brightnessPin = 9;     // PWM pin for backlight brightness control
const int brightnessControlPin = A5; // Analog pin for brightness control

// 4 bit mode
const int dataPins[4] = {4, 5, 6, 7};

void InitialisePin()
{
    for (int i = 0; i < 4; i++)
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
    // send upper nibble
    sendNibble(byte >> 4);
    delay(1);
    // send LowerNibble
    sendNibble(byte & 0x0F);
}

void sendCommand(uint8_t command)
{
    // we set the rsPin to low
    digitalWrite(rsPin, LOW);
    delay(1);
    sendByte(command);
}
void sendData(uint8_t data)
{
    // we set the rsPin to HIGH : data
    digitalWrite(rsPin, HIGH);
    delay(1);
    sendByte(data);
}

void InitialiseLCD()
{
    InitialisePin();
    displayControl = 0x08;
    // we do initialisation sequence
    delay(15);
    sendNibble(0x3);
    delay(5);
    sendNibble(0x3);
    delay(1);
    sendNibble(0x3);
    delay(1);
    sendNibble(0x2);
    // function set in 4 bit mode : 4 bit mode, 2 lines, font 0 : 5*8
    sendCommand(0x28);
    // clear display
    sendCommand(0x01);
    delay(3);
    // entry mode set : increment , no display shift
    sendCommand(0x6);
    display();
    cursor();
    blink();
    // Display on , cursor on , cursor blinking
    sendCommand(0xF);

    analogWrite(LCD_brightnessPin, 255);
}

void ControlBrightness(float pourcentage)
{
    int val = pourcentage * 255 / 100;
    analogWrite(LCD_brightnessPin, val);
}

// Print function for Arduino String type
void lcdPrint(const String &str)
{
    lcdPrint(str.c_str()); // Call the char* version
}

// Print function for C-string (char array)
void lcdPrint(const char *str)
{
    while (*str)
    {
        sendData(*str);
        str++;
    }
}

size_t lcdPrint(uint8_t val)
{

    lcdPrint(String(val));
    return 1;
}

// Print function for C-string (char array)
void lcdPrint(int val)
{
    lcdPrint(String(val));
}

void Clear()
{
    sendCommand(CLEAR_COMMAND);
}

void ReturnHome()
{
    sendCommand(RETURN_HOME_COMMAND);
}

int setCursor(int col, int row)
{
    if (col >= columns || col < 0 || row < 0 || row > rows)
    {
        Serial.println("Error in column or row argument");
        return -1;
    }

    uint8_t DDRAMAdress = 0;
    switch (row)
    {
    case 0:
        DDRAMAdress = 0x0;
        break;

    case 1:
        DDRAMAdress = 0x40;
        break;

        // case 2:
        //     break;

        // case 3 :
        //     break;
    }
    DDRAMAdress += col;
    sendCommand((1 << 7) | DDRAMAdress);
}

// enable the display
void display()
{
    displayControl |= DISPLAY_MASK;
    sendCommand(0x0F & displayControl);
}

// disable the display
void noDisplay()
{
    displayControl &= ~DISPLAY_MASK;
    sendCommand(0x0F & displayControl);
}

// enable Cursor
void cursor()
{
    displayControl |= CURSOR_MASK;
    sendCommand(0x0F & displayControl);
}
// disable cursor
void noCursor()
{
    displayControl &= ~CURSOR_MASK;
    sendCommand(0x0F & displayControl);
}
// blink cursor
void blink()
{
    displayControl |= BLINK_MASK;
    sendCommand(0x0F & displayControl);
}
// dont blink cursor

void noBlink()
{
    displayControl &= ~BLINK_MASK;
    sendCommand(0x0F & displayControl);
}

void backLight()
{
    digitalWrite(LCD_brightnessPin, HIGH);
}

void noBackLight()
{
    digitalWrite(LCD_brightnessPin, LOW);
}

void setup()
{
    String str = "my Name is ";
    InitialiseLCD();
    // sendData('C');
    // lcdPrint("Hello");
    lcdPrint(str);
    setCursor(0, 1);
    lcdPrint(50);
    setCursor(8, 1);
    lcdPrint(2050);
}

void loop()
{
}
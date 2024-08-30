#pragma once
#define INV 0
#define USB 1
#define MAP 2
#define RAD 3

bool gamecontrolleropen = false;
bool clockwise = false;
bool anticlockwise = false;
long oldPosition = -999;
uint8_t gamestate = 0;
uint8_t currentframe = 0;
uint8_t firstframe = 0;
uint8_t framecount = 7; //1 less than actual number of frames, first frame = 0
uint8_t startcounter = 0;
uint8_t mainMenu = INV;
uint8_t USBselect = 0;
uint8_t INVselect = 0;
uint8_t RADselect = 0;
uint8_t INVcursorx;
uint8_t INVcursory;
uint8_t currentawaveframe = 0;
uint8_t currentbwaveframe = 13;
int oldPos = -999;
int lastSample;
struct Wave {
  int x;
  int y;
};
Wave wave = {64,0};
bool toggleflashlight = false;

//int pin[6] = {A0, A1, A2, A3, 7, 8};
// Last state of the buttons
//int lastButtonState[6] = {0,0,0,0,0,0};
/*///////////////////////////////JOYSTICK////////////////////////////////////////////////////*/
unsigned long holdSpecialButton = 0, startHeldDown = 0, selectHeldDown = 0;
bool startButton = false, selectButton = false;
//const int m = 0xFFFF;
const int buttonHeldTime = 300, buttonReleaseTime = 1000;
int x =0;
int y=0;
int prevx =0;
int prevy =0;
bool dirty = true;
/*/////////////////////////////////////////////////////////////////////////////////////////////////*/




void keybufferPrint(uint24_t address){
   
    size_t length = 0;

    // Determine the length of the string by reading byte-by-byte
    while (true) {
      char currentChar;
      FX::readDataBytes(address + length, &currentChar, 1);
      if (currentChar == '\0') break;
      length++;
    }

    // Now you know the length, create a buffer
    char* buffer = new char[length + 1];  // Allocate buffer with detected size

    // Read the entire string into the buffer
    FX::readDataBytes(address, buffer, length);
    buffer[length] = '\0';  // Null-terminate the string

    // Print the string using the Keyboard library
    Keyboard.println(buffer);

    // Clean up
    delete[] buffer;
}
extern void CommandAtRunBarMSWIN(char *SomeCommand); //Opens the run bar and executes the command.
extern void CommandAtRunBarGnome(char *SomeCommand);

/********************************************************************
 * Opens the run bar and executes the command. 
 ********************************************************************/
void CommandAtRunBarMSWIN(char *SomeCommand){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  delay(1500);
  keybufferPrint(SomeCommand);
  delay(100);
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
}
void CommandAtRunBarGnome(char *SomeCommand){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F2);
  delay(100);
  Keyboard.releaseAll();
  delay(1500);
  Keyboard.print(SomeCommand);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}

uint16_t ENIPinRead(uint8_t npin)
{
  power_adc_enable();
  uint16_t v = analogRead(npin);
  power_adc_disable();
  return v;
}



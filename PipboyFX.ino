#include <Keyboard.h>
#include <Arduboy2.h>  // required to build for Arduboy
#include <Joystick.h> // Use library https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-1.0
#include "src/ArduboyPlaytuneFX.h"
#include <ArduboyFX.h>      // required to access the FX external flash
#include "fxdata/fxdata.h"  // this file contains all references to FX data

Arduboy2 pipboy;
uint8_t radbuffer[32];
ArduboyPlaytuneFX radio(pipboy.audio.enabled, radbuffer);
BeepPin2 beep;
#include "func.h"

void setup() {
  pipboy.begin();
  
  FX::disableOLED();
  FX::begin(FX_DATA_PAGE);
  FX::setCursorRange(0, 128);
  pinMode(micpin, INPUT);
  pinMode(ADC_PIN, INPUT);
  FX::display(CLEAR_BUFFER);
  FX::drawBitmap(0, 0, voidlogo, 0, dbmMasked);
  FX::display();
  delay(1000);
  //power_adc_enable();
  //pinMode(ADC_PIN, INPUT);
  //analogReference(DEFAULT); 
  Serial.begin(9600);
  Joystick.begin();
 // Joystick.setXAxisRange(-1, 1);
  //Joystick.setYAxisRange(-1, 1);
  Keyboard.begin();
  pipboy.audio.begin();
  inputString.reserve(200);
  radio.initChannel(PIN_SPEAKER_1);
  radio.initChannel(PIN_SPEAKER_2);
  power_adc_enable();
}
void loop() {
  // put your main code here, to run repeatedly:
  if (!pipboy.nextFrame()) {
    return;
  }
  pipboy.pollButtons();
  
  bigloop();
  FX::display(CLEAR_BUFFER);
}

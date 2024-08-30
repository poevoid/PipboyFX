#include <Keyboard.h>
#include <Arduboy2.h>  // required to build for Arduboy
#include <Joystick.h>
#include "src/ArduboyTonesFX.h"
#include <ArduboyFX.h>      // required to access the FX external flash
#include "fxdata/fxdata.h"  // this file contains all references to FX data


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  4, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
  

Arduboy2 pipboy;
uint16_t radbuffer[8];
ArduboyTonesFX radio(pipboy.audio.enabled, radbuffer);

#include "func.h"

void setup() {
  pipboy.begin();
  
  FX::disableOLED();
  FX::begin(FX_DATA_PAGE);
  FX::setCursorRange(0, 128);
  pinMode(A4, INPUT);
  Serial.begin(9600);
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
  Keyboard.begin();
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

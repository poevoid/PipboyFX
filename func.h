#include "Arduino.h"
#include "ArduboyFX.h"
#pragma once

#include "vars.h"
void gamecontroller(){
  if (holdSpecialButton < millis()) {
    if (startButton || selectButton)
    {
      Joystick.setButton(2, false);
      Joystick.setButton(3, false);
      selectButton = false;
      startButton = false;
    }
    if (pipboy.pressed(UP_BUTTON) && pipboy.notPressed(DOWN_BUTTON)) {
      y = -1;
    }
    if (pipboy.notPressed(UP_BUTTON) && pipboy.notPressed(DOWN_BUTTON)) {
      y = 0;
    }
    if (pipboy.pressed(DOWN_BUTTON) && pipboy.notPressed(UP_BUTTON)) {
      y = 1;
    }
    if (pipboy.pressed(DOWN_BUTTON) && pipboy.pressed(UP_BUTTON)) {
      if (startHeldDown == 0)
        startHeldDown = millis();
      else if (millis() - startHeldDown > buttonHeldTime) {
        holdSpecialButton = millis() + buttonReleaseTime;
        Joystick.setButton(3, true);
        startButton = true;
      }
    } else {
      startHeldDown = 0;
    }
    if (pipboy.pressed(LEFT_BUTTON) && pipboy.notPressed(RIGHT_BUTTON)) {
      x = -1;
    }
    if (pipboy.notPressed(LEFT_BUTTON) && pipboy.notPressed(RIGHT_BUTTON)) {
      x = 0;
    }
    if (pipboy.pressed(RIGHT_BUTTON) && pipboy.notPressed(LEFT_BUTTON)) {
      x = 1;
    }
    if (pipboy.pressed(RIGHT_BUTTON) && pipboy.pressed(LEFT_BUTTON)){
       if (selectHeldDown == 0)
        selectHeldDown = millis();
      else if (millis() - selectHeldDown > buttonHeldTime)
      {
        holdSpecialButton = millis() + buttonReleaseTime;
        Joystick.setButton(2, true);
        selectButton = true;
      }
    }
    else{
      selectHeldDown = 0;
      }
    
    if (pipboy.pressed(A_BUTTON)) {
      Joystick.setButton(0, 1);
    } else {
      Joystick.setButton(0, 0);
    }
    if (pipboy.pressed(B_BUTTON)) {
      Joystick.setButton(1, 1);
    } else {
      Joystick.setButton(1, 0);
    }

    if (y != prevy) {
      Joystick.setYAxis(y);
      prevy = y;
    }
    if (x != prevx) {
      Joystick.setXAxis(x);
      prevx = x;
    }
  }
  if (selectButton && startButton) {
      gamecontrolleropen = false;
      gamestate = 1;
    }
  dirty = !pipboy.nextFrame();
  if (dirty) {
    pipboy.clear();
    switch (x) 
    {
    case 0: pipboy.drawTriangle(18, 13, 30, 25, 18, 37, WHITE); pipboy.drawRect(7, 13, 12, 25);
        pipboy.drawTriangle(46, 13, 46, 37, 34, 25, WHITE); pipboy.drawRect(46, 13, 12, 25);
        pipboy.drawLine(18, 14, 18, 36, BLACK); pipboy.drawLine(46, 14, 46, 36, BLACK);
        break;
      case -1: pipboy.fillTriangle(18, 13, 30, 25, 18, 37, WHITE); pipboy.fillRect(7, 13, 12, 25);
        pipboy.drawTriangle(46, 13, 46, 37, 34, 25, WHITE); pipboy.drawRect(46, 13, 12, 25);
        /*pipboy.drawLine(18, 14, 18, 36, BLACK);*/ pipboy.drawLine(46, 14, 46, 36, BLACK);
        break;
      case 1: pipboy.drawTriangle(18, 13, 30, 25, 18, 37, WHITE); pipboy.drawRect(7, 13, 12, 25);
        pipboy.fillTriangle(46, 13, 46, 37, 34, 25, WHITE); pipboy.fillRect(46, 13, 12, 25);
        pipboy.drawLine(18, 14, 18, 36, BLACK); /*pipboy.drawLine(46, 14, 46, 36, BLACK);*/
        break;
    }

    switch (y) 
    {
      case 0: pipboy.drawTriangle(32, 23, 44, 11, 20, 11, WHITE); pipboy.drawRect(20, 0, 25, 12);
        pipboy.drawTriangle(32, 27, 44, 39, 20, 39, WHITE); pipboy.drawRect(20, 39, 25, 12);
        pipboy.drawLine(43, 11, 21, 11, BLACK); pipboy.drawLine(21, 39, 43, 39, BLACK);
        break;
      case -1: pipboy.fillTriangle(32, 23, 44, 11, 20, 11, WHITE); pipboy.fillRect(20, 0, 25, 12);
        pipboy.drawTriangle(32, 27, 44, 39, 20, 39, WHITE); pipboy.drawRect(20, 39, 25, 12);
        /*pipboy.drawLine(43, 11, 21, 11, BLACK);*/ pipboy.drawLine(21, 39, 43, 39, BLACK);
        break;
      case 1: pipboy.drawTriangle(32, 23, 44, 11, 20, 11, WHITE); pipboy.drawRect(20, 0, 25, 12);
        pipboy.fillTriangle(32, 27, 44, 39, 20, 39, WHITE); pipboy.fillRect(20, 39, 25, 12);
        pipboy.drawLine(43, 11, 21, 11, BLACK); /*pipboy.drawLine(21, 39, 43, 39, BLACK);*/
        break;
    }
    if (pipboy.pressed(A_BUTTON))
      pipboy.fillCircle(88, 30, 12);
    else
      pipboy.drawCircle(88, 30, 12);

    if (pipboy.pressed(B_BUTTON))
      pipboy.fillCircle(115, 24, 12);
    else
      pipboy.drawCircle(115, 24, 12);

    if (selectButton)
      pipboy.fillRoundRect(40, 56, 20, 8, 1);
    else
      pipboy.drawRoundRect(40, 56, 20, 8, 1);

    if (startButton)
      pipboy.fillRoundRect(68, 56, 20, 8, 1);
    else
      pipboy.drawRoundRect(68, 56, 20, 8, 1);

    // Rounding
    pipboy.drawPixel(20, 0, BLACK);
    pipboy.drawPixel(44, 0, BLACK);
    pipboy.drawPixel(20, 50, BLACK);
    pipboy.drawPixel(44, 50, BLACK);
    pipboy.drawPixel(7, 13, BLACK);
    pipboy.drawPixel(7, 37, BLACK);
    pipboy.drawPixel(57, 13, BLACK);
    pipboy.drawPixel(57, 37, BLACK);

    pipboy.display();
    dirty = false;
  }
  delay(10);
}

void bleep() {
  for (int i = 0; i < 15; i++) {
    radio.tone(i);
  }
  delay(10);
  radio.noTone();
}
void animate() {
  if (pipboy.everyXFrames(12)) {
    if (currentframe < framecount) {
      ++currentframe;
      ++startcounter;
    } else {
      currentframe = firstframe;
    }
  }
}
void USBattackL() {
  delay(5000);
  CommandAtRunBarGnome(bul1);
  delay(3000);
  keybufferPrint(bul2);
  delay(2000);
  keybufferPrint(bul3);
  delay(2000);
  keybufferPrint(bul4);
  delay(2000);
  keybufferPrint(bul5);
  delay(2000);
  keybufferPrint(bul6);
  //delay(2000);
  //Keyboard.println(F("<center><a href=\"http://www.usbrubberducky.com/\"><img src=\"http://cdn.shopify.com/s/files/1/0068/2142/products/usbducky2.jpg\" /></a><center>"));
  delay(2000);
  
  keybufferPrint(bul8);
  
  delay(2000);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('x');
  delay(100);
  Keyboard.releaseAll();
  delay(2000);
  keybufferPrint(bul9);
  delay(3000);
  keybufferPrint(exitstring);
}
void USBattackW() {
  delay(5000);
  CommandAtRunBarMSWIN(buw1);
  delay(4000);
  keybufferPrint(buw2);
  delay(2000);
  keybufferPrint(buw3);
  delay(2000);Keyboard.print(F("$speak.Speak(\""));
  keybufferPrint(buw4);Keyboard.println(F("\")"));
  delay(2000);
  keybufferPrint(exitstring);
}
void lockwindows() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.println(F("l"));
  Keyboard.releaseAll();
}
void displaywindows() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.println(F("d")); 
  Keyboard.releaseAll();
} 
void openterminal() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.println(F("t"));
  Keyboard.releaseAll();
}
void plotData(){
  for (wave.x=94; wave.x < 126; wave.x++){
      int sample = ENIPinRead(A4);
      int newY = map(sample, 0, 200, 15, 42);

      //if (newY<10){newY=10;}
     // if (newY>42){newY=42;}
      wave.y = newY;
      pipboy.drawLine(wave.x, lastSample, wave.x, wave.y, WHITE);
      lastSample = newY;
    }
}

void splashscreen(){  
  FX::drawBitmap(45, 0, vaultboy, currentframe, dbmNormal);
  animate();
  FX::setCursor(0, 28);
  FX::setFont(arduboyFont, dbmNormal);
  FX::drawString(test);
  FX::setCursor(85, 28);
 // FX::setFont(tinyFont, dbmNormal);
  FX::drawString(splashnum);
  if (pipboy.justPressed(A_BUTTON)) {
    pipboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
    gamestate = 1;
  }
  if (startcounter == framecount * 3) {
    gamestate = 1;
  }
}

void handleMainMenu(){
 if (mainMenu == INV) { //highlight INV
    pipboy.drawLine(0, 51, 35, 51);
    pipboy.drawLine(35, 51, 35, 64);
    
  }
  if (mainMenu == USB) { //highlight UDB
    pipboy.drawLine(33, 51, 65, 51);
    pipboy.drawLine(33, 51, 33, 65);
    pipboy.drawLine(65, 51, 65, 64);
  }
  if (mainMenu == MAP) { //highlight MAP
    pipboy.drawLine(63, 51, 63, 64);
    pipboy.drawLine(63, 51, 95, 51);
    pipboy.drawLine(95, 51, 95, 64);
  }
  if (mainMenu == RAD) { //highlight RAD
    pipboy.drawLine(93, 51, 93, 64);
    pipboy.drawLine(93, 51, 128, 51);
    
  }
  
  if (pipboy.justPressed(RIGHT_BUTTON) && mainMenu < 3) {
    ++mainMenu;
  }
  if (pipboy.justPressed(LEFT_BUTTON) && mainMenu > 0) {
    --mainMenu;
  }
}
void subMenus(){
  if (mainMenu == INV) {
    
    FX::setCursorRange(6, 128);
    FX::setFont(tinyFont, dbmNormal);
    FX::setCursor(6, 0);
    FX::drawString(inventorylist);
    INVcursorx = 0;
    FX::setCursor(64, 5);
    
    FX::setCursorRange(64, 128);
    switch (INVselect) {
      case 0:
        INVcursory =10;
        FX::drawString(Lock);
      break;

      case 1:
        INVcursory =20;
        FX::drawString(Key);
      break;

      case 2:
        INVcursory =30;
        FX::drawString(Cache);
      break;
    }
    
    if (pipboy.justPressed(DOWN_BUTTON) && INVselect < 2) INVselect += 1;
    if (pipboy.justPressed(UP_BUTTON) && INVselect > 0) INVselect -= 1;

    pipboy.fillRect(INVcursorx, INVcursory-4, 4, 4);
  }
  if (mainMenu == MAP) {
    FX::drawBitmap(0, -12, houston, 0, dbmNormal);
  }
  if (mainMenu == USB) {
    FX::setCursor(0, 0);
    FX::setFont(arduboyFont, dbmNormal);
    //FX::drawString(USBoptions);
      switch (USBselect) {

      case 0:
        FX::setCursor(5, 0);pipboy.setCursor(-2, 0);
        FX::drawString(WinUSB);
        break;

      case 1:
        FX::setCursor(5, 8);pipboy.setCursor(-2, 8);
        FX::drawString(LinUSB);
        break;

      case 2:
        FX::setCursor(5, 16);pipboy.setCursor(-2, 16);
        FX::drawString(GC);
        break;

      case 3:
        FX::setCursor(5, 24);pipboy.setCursor(-2, 24);
        FX::drawString(lockout);
        break;

      case 4:
        FX::setCursor(5, 32);pipboy.setCursor(-2, 32);
        FX::drawString(toggleWin);
        break;

      case 5:
        FX::setCursor(5, 40);pipboy.setCursor(-2, 40);
        FX::drawString(openTerm);
        break;

    }pipboy.print(F(">"));
    
    if (pipboy.justPressed(DOWN_BUTTON) && USBselect < 5) USBselect += 1;
    if (pipboy.justPressed(UP_BUTTON) && USBselect > 0) USBselect -= 1;
    if (pipboy.justPressed(A_BUTTON) ) {
     if (USBselect == 0){
      bleep();
      USBattackW();
     }
     if (USBselect == 1){
      
      USBattackL();
     }
     if (USBselect == 2){
      bleep();
      gamecontrolleropen = true;
      gamestate = 2;
     }
     if (USBselect == 3){
      bleep();
      lockwindows();
     }
     if (USBselect == 4){
      bleep();
      displaywindows();
     }
     if (USBselect == 5){
      bleep();
      openterminal();
     }
    }
    /*if (pipboy.justPressed(A_BUTTON) && USBselect == 2) {  //hold all four directions to exit
      gamecontrolleropen = true;
      bleep();
      gamestate = 2;
    }
    if (pipboy.justPressed(A_BUTTON) && USBselect == 1) {
      bleep();
      USBattackL();
    }
    if (pipboy.justPressed(A_BUTTON) && USBselect == 3) {
      bleep();
      lockwindows();
    }
    if (pipboy.justPressed(A_BUTTON) && USBselect == 4) {
      bleep();
      displaywindows();
    }
    if (pipboy.justPressed(A_BUTTON) && USBselect == 5) {
      bleep();
      openterminal();
    }
*/
  }
  if (mainMenu == RAD) {
    radio.fillBufferFromFX();
    FX::setCursor(5, 0);
    FX::setFont(arduboyFont, dbmNormal);
    FX::drawString(life);
    FX::setCursor(5, 12);
    FX::drawString(crawl);
    switch (RADselect) {
      case 0:
        pipboy.setCursor(-2, 0);
        break;

      case 1:
        pipboy.setCursor(-2, 10);
        break;
    }
    pipboy.print(F(">"));
    FX::drawBitmap(94, 10, radiograph, 0, dbmNormal);
    plotData();
    
    if (pipboy.justPressed(DOWN_BUTTON) && RADselect < 1) RADselect += 1;
    if (pipboy.justPressed(UP_BUTTON) && RADselect > 0) RADselect -= 1;
    if (pipboy.justPressed(A_BUTTON) && RADselect == 0) {
    if (radio.playing()) {
      radio.noTone();
    } else {
      radio.tonesFromFX(eachlife);
    }
  }if (pipboy.justPressed(A_BUTTON) && RADselect == 1) {
    if (radio.playing()) {
      radio.noTone();
    } else {
      radio.tonesFromFX(crawlout);
    }
  }
  }
}
void UI(){
  subMenus();
  pipboy.setCursor(0, 56);
  pipboy.print(F("  INV  USB  MAP  RAD"));
  pipboy.drawLine(0, 52, 128, 52);//bottom H-line
  pipboy.drawLine(34, 52, 34, 64);//INV | USB
  pipboy.drawLine(64, 52, 64, 64);// USB | MAP
  pipboy.drawLine(94, 52, 94, 64);// MAP | RAD
  if (pipboy.pressed(B_BUTTON)) {
    startcounter = 0;
    //pipboy.digitalWriteRGB(RGB_ON, RGB_ON, RGB_ON);
    gamestate = 0;
  }
  handleMainMenu();
}
void bigloop() {
  switch (gamestate) {
    case 0:
    splashscreen();

    break;

    case 1:
    UI();
    break;

    case 2:
    gamecontroller();
    break;
  }
 if (pipboy.justPressed(B_BUTTON) && gamestate != 2) {

    pipboy.digitalWriteRGB(RGB_ON, RGB_ON, RGB_ON);
  }
}
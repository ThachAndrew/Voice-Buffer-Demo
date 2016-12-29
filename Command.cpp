#include "Command.h"

Command::Command() {
  capacity = 10;
  input = new String[capacity];
  rxBuffer = "";
  argc = 0; 
  foundFlag = 0; 
  blinkDelay = 500;
}
Command::~Command() {
  delete [] input;
  input = 0;
}
//read input from serial(and default TX RX)
void Command::updateInput() {
    //tokenize input into PFA by spaces
    char c = Serial.read();
    if (c == ' ' || c == '\n') {
      input[argc] = rxBuffer; rxBuffer = "";
      argc++;      //command is ready to be parsed after ENTER key
      if(c == '\n') parseInput();
    }
    else if (c > 0)
      rxBuffer += c;
    
    checkFlags();
}
void Command::parseInput() { foundFlag = false; //reset flag
  //parse if input isn't empty
  if(argc && input[0] != ""){
    if (foundCommand("on") || foundCommand("off"))
      controlLights();
    if (foundCommand("color") || foundCommand("colored") || foundCommand("light"))
      controlColor();
    if (foundCommand("blink") || foundCommand("blinking")){
      blinkFlag = true;
      controlBlink(); 
    }
    else if (foundCommand("play"))
      SoundDemo.playScale();
    else if(foundFlag == false){
      Serial.print("\n-uno: "); printInput();
      Serial.println(": no keywords detected!\n Example keywords: light, color, on, off, play");
    }
  }
  argc = 0; //prepare for next input
  Serial.print("\nThachArduino $ ");
}
void Command::printInput() {
  for (int i = 0; i < argc; i++)
    Serial.print(input[i] + " ");
}
//Private helper function for parser
bool Command::foundCommand(String target) {
  for (int i = 0; i < argc; i++)
    if (target.equalsIgnoreCase(input[i])){
      foundFlag = true;
      return true;
    }
  //foundFlag = false;
  return false;
}
//Contro
void Command::controlLights(){
  const int led[4+1] = {0, 2, 4, 7, 8};
  if (foundCommand("on")){     
     if(foundCommand("first") || foundCommand("1st"))  digitalWrite(led[1], HIGH);
     if(foundCommand("second")|| foundCommand("2nd")) digitalWrite(led[2], HIGH);
     if(foundCommand("third") || foundCommand("3rd"))  digitalWrite(led[3], HIGH);
     if(foundCommand("fourth")|| foundCommand("4th")) digitalWrite(led[4], HIGH);
     if(foundCommand("all")) for(auto pin : led) digitalWrite(pin, HIGH);
  }else 
  if(foundCommand("off")){
     if(foundCommand("first") || foundCommand("1st"))  digitalWrite(2, LOW);
     if(foundCommand("second")|| foundCommand("2nd")) digitalWrite(4, LOW);
     if(foundCommand("third") || foundCommand("3rd"))  digitalWrite(7, LOW);
     if(foundCommand("fourth")|| foundCommand("4th")) digitalWrite(8, LOW);
     if(foundCommand("all")) for(auto pin : led) digitalWrite(pin, LOW);
  }
}

//Controls Color class, has hardcoded colors as a demo.
Color Command::presetColors[6] = {Color(255,0,0),Color(0,255,0),Color(0,0,255),Color(255,255,0),Color(0,255,255), Color(255, 0, 255)};
void Command::controlColor(){
  if(foundCommand("red"))
    ColorDemo.displayColor(presetColors[0]);
  if(foundCommand("green"))
    ColorDemo.displayColor(presetColors[1]);
  if(foundCommand("blue"))
    ColorDemo.displayColor(presetColors[2]);
  if(foundCommand("yellow"))
    ColorDemo.displayColor(presetColors[3]);
  if(foundCommand("light blue"))
    ColorDemo.displayColor(presetColors[4]);
  if(foundCommand("purple"))
    ColorDemo.displayColor(presetColors[5]);
}

//Temporary patch for blink
  const int ledPin = 2;
  int ledState = LOW;
  unsigned long previousMillis = 0;
  const long interval = 1000;
//Comment: not using delay because artificial pause messes with future input
void Command::controlBlink(){
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}

void Command::checkFlags(){
  if(blinkFlag == true)
    controlBlink();
}






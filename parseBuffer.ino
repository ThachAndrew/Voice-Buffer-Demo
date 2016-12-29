/*
 * Purpose: 
 *    -Emulate a bash-like interface that connects multiple classes.
 *    -Process command line with a "regex" implementation.      
 *    -Can communicate over Bluetooth Serial and Serial Monitor at the same time. (if BT module is connected to default TX and RX)
 * 
 * Implementation: 
 *   The parser searches a line for keywords and decides what to do with it.
 *   (Similar to vims "verb-noun-adjective" modifier commands)
 * 
 *   Main Keywords (case-insensitive): 
 *   -ON  (FIRST, SECOND, THIRD, or FOURTH led)
 *   -OFF (FIRST, SECOND, THIRD, or FOURTH led)
 *   -COLOR (RED, GREEN, BLUE, YELLOW, PURPLE, LIGHT BLUE)
 *   -PLAY (SCALE, C-SCALE, D-SCALE)
 *
 *    Fully modifiable; add functions similar to "controlLights", "controlColors"
 *  
 *  Future Implementations: 
 *    - "-help" for a list of keywords and its nouns/adjectives/modifiers 
 *    - organize precedence for keywords and modifiers 
 */


#include "Command.h"
//Most of the good stuff is in the Command library

Command SerialCMD;
void setup() {
  Serial.begin(9600);

  const int led[4] = {2, 4, 7, 8};
  for(int i = 0; i < 4; i++)  //prepare digital leds
    pinMode(led[i], OUTPUT);
  
  Serial.print("ThachArduino $ ");
}

void loop() {
  //if(Serial.available())
    SerialCMD.updateInput();
}


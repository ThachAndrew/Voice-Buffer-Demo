#ifndef COMMAND__H
#define COMMAND__H

#include <Arduino.h>
#include "Speaker.h"
#include "Color.h"

/* 
 * Purpose: 
 *    Handles interface of all classes.
 *    Uses a form of "regex" to find commands
 *    
 *   Main Keywords (case-insensitive): 
 *   -ON  (FIRST, SECOND, THIRD, or FOURTH led)
 *   -OFF (FIRST, SECOND, THIRD, or FOURTH led)
 *   -COLOR (RED, GREEN, BLUE, YELLOW, PURPLE, LIGHT BLUE)
 *   -PLAY 
 *
 *  Fully modifiable, just add more functions similar to "controlLights" or "controlColors"
 */

class Command{
  public:
    Command(); 
    ~Command();
    void updateInput();
    void parseInput();
    void printInput();
  private:
    //Objects that Command.h controls
    Speaker SoundDemo; 
    Color ColorDemo;  static Color presetColors[6];  //hardcoded preset colors: red, blue, green, purple, etc,
    
    //searches array for command
    bool foundCommand(String); 
    bool foundFlag; //decides error message
    void checkFlags(); //controls currently running programs
    
    // Purpose: Control the 4 LEDS
    // Keywords: CALLED when "on" or "off" is detected. 
    //    all, first, second, third, fourth.
    void controlLights(); 

    // Purpose: Control color class
    // Keywords: CALLED when "color" is detected.
    //    red, blue, green, yellow, light blue, purple.
    void controlColor();

    // Purpose: Control speed of blink
    // Keywords: 
    //    blink, fast, faster, slow, slower
    void controlBlink(); int blinkDelay;
    bool blinkFlag = 0; //controls execution of fx
    
    String *input; //partially filled array of input arguments
    String rxBuffer; //single tokens of input
    int argc, capacity;
};
#endif



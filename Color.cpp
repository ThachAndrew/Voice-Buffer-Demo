#include <Arduino.h>
#include "Color.h"
using namespace std;

Color::Color(){
  red = green = blue = 0;
}
Color::Color(const Color &other){
  red = other.red;
  blue = other.blue;
  green = other.green;
}
Color::Color(int value){
  red = green = blue = value;
}
Color::Color(int r, int g, int b){
  red = r;
  green = g;
  blue = b;
}
void Color::displayColor(){
  analogWrite(redLED, 255 - red);
  analogWrite(greenLED, 255 - green);
  analogWrite(blueLED, 255 - blue);
}
void Color::displayColor(Color &other){
  analogWrite(redLED, 255-other.red);
  analogWrite(greenLED, 255-other.green);
  analogWrite(blueLED, 255-other.blue);
}
void Color::saturate(){
  int minColor = red;
  if(green < minColor)
    minColor = green;
  if(blue < minColor)
    minColor = blue;

  red -= minColor;
  green -= minColor;
  blue -= minColor;
}
String Color::getDominantColor(){
   if(red >= green && red >= blue)
     return "red";
   else if(green >= red && green >= blue)
     return "green";
   else if(blue >= green && blue >= red)
     return "blue";     
}
/* Doesn't work without <ArduinoSTL.h>
void Color::printColorVal(){
  cout << "The color was: " << "r: " << red << " g: " << green << " b: " << blue << endl;
  cout << "The dominant color is: " << getDominantColor() << endl;
}
*/
Color Color::getReflectedColor(){
  Color Instance, Red(255, 0, 0), Green(0, 255, 0), Blue(0, 0, 255);
  Color off(0);

  //get black-noise val
  off.displayColor(); delay(800);
  int photocellReading = (analogRead(A0)/4);
  Color blkVal(255-photocellReading); 

  //get RGB vals
  Red.displayColor(); delay(800);
  photocellReading = (255-analogRead(A0)/4);
  red = photocellReading - blkVal.red;  //use OO 
  
  Green.displayColor(); delay(800);
  photocellReading = (255-analogRead(A0)/4);
  green = photocellReading - blkVal.green;
  
  Blue.displayColor(); delay(800);
  photocellReading = (255-analogRead(A0)/4);
  blue = photocellReading - blkVal.blue;
  
  return *this;
}


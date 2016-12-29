/*
 * Purpose: 
 *    -Handle color processing and display
 *    -Displays to RGB LED
 *          
 */
#ifndef COLOR__H
#define COLOR__H

class Color{
  public:
    Color();
    Color(const Color &);
    //monochrome constructor
    Color(int);
    //rgb constructor
    Color(int, int, int);
    void displayColor();

    //overloaded function to display specified color 
    void displayColor(Color &);
    
    Color getReflectedColor();
    void saturate();
    String getDominantColor();
    int getRed(){return red;}
    int getGreen(){return green;}
    int getBlue(){return blue;}

    //debugging statement
    void printColorVal();
     
  private:
    int red, green, blue;
    const int redLED = 11, greenLED = 10, blueLED = 9;
};

#endif


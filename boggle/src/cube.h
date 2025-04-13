#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <string>

using namespace std;
class Cube {
public:
    //Default constructor
    Cube();
    //Constructor
    Cube(char insertLetter, int x, int y);
    //Returns x-position of the cube
    int xPos();
    //Returns y-position of the cube
    int yPos();
    // Checks the status of the cube, if we're been here before
    bool checkStatus();
    //Sets the status of a cube
    void setStatus(const bool insertStatus);
    //Returns the letter of the cube
    char getLetter();

private:
    char letter;
    int xpos;
    int ypos;
    bool status;

};

#endif // CUBE_H

#include "cube.h"
#include <iostream>
#include <string>
using namespace std;
Cube::Cube(){
};

Cube::Cube(char insertLetter, int x, int y){
    letter = insertLetter;
    xpos = x;
    ypos = y;
    status = false;
}

int Cube::xPos(){
    return xpos;
}

int Cube::yPos(){
    return ypos;
}

bool Cube::checkStatus(){
    return status;
}

void Cube::setStatus(const bool insertStatus){

    status = insertStatus;

}

char Cube::getLetter(){
    return letter;
}

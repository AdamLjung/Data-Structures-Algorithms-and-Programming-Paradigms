// This is the CPP file you will edit and turn in.
// Game of life
// by Adam Ljung, liu-id: Adalj586
// by Isak Skott, liu-id: Isask052
// mail: anders.marak.leffler@liu.se

#include <iostream>
// For grid<>
#include "grid.h"
// For pause(ms) & clearConsole()
#include "lifeutil.h"
#include <string>
#include <fstream>
Grid<char> loadGrid(const std::string &inFileName);
void showGrid(const Grid<char> &inGrid);
void tick(Grid<char> &inGrid);
void animate(Grid<char> &inGrid);

int main() {


    std::cout << "Have a nice Life! "  << std::endl;
    std::cout << "Grid input filename?" << std::endl;
    std::string inType;
    std::cin >> inType;

    //Loads the grid from the textfile given by user
    Grid<char> userGrid = loadGrid(inType);
    showGrid(userGrid);

    // Menu with choices for user
    std::cout << "a)nimate, t)ick, q)uit" << std::endl;
    while(std::cin >> inType){

        if(inType == "a"){
            animate(userGrid);
        }
        if(inType == "t"){
            tick(userGrid);

        }
        if(inType == "q"){
            break;
        }
        showGrid(userGrid);
        std::cout << "a)nimate, t)ick, q)uit"<< std::endl;

    }

    std::cout << "\n";
    showGrid(userGrid);


    return 0;
}

Grid<char> loadGrid(const std::string &inFileName){

    char inputChar;
    int nRows;
    int nCols;

    //stream to load chars for the grid
    std::ifstream loadStream(inFileName);
    // Reads first two rows in the textfile, contains the number of cols/rows
    loadStream >> nRows;
    loadStream >> nCols;

    //Creates the grid with the number of cols/rows read
    Grid<char> returnGrid(nRows, nCols);
    // counter to create the correct amount of spaces in the grid
    int counter = 0;

    //While the amount of spaces(rows*cols) is bigger than counter keep reading chars
    while(loadStream && counter < nRows*nCols){
        //sets the read character of the textfile on the grid
        for(int i = 0; i < nRows; i++){
            for(int j = 0; j < nCols; j++){
                loadStream >> inputChar;
                returnGrid.set(i,j,inputChar);

                counter ++;
            }
        }
    }
    //closes the stream
    //returns the created grid
    loadStream.close();
    return returnGrid;
}

void showGrid(const Grid<char> &inGrid){

    //Prints the grid
    for(int i = 0; i < inGrid.numRows(); i++){
        for(int j = 0; j < inGrid.numCols(); j++){
            std::cout << inGrid.get(i,j);
        }
        std::cout << "\n";
    }
}
// ticks one generation
void tick(Grid<char> &inGrid){

    int neighbourCounter;
    //copies the original grid to be able to change to next generation inside the loop
    Grid<char> temp = inGrid;

    for(int i = 0; i<inGrid.numRows(); i++){
        for(int j = 0; j<inGrid.numCols(); j++){
            //sets neighbourcounter to 0 before counter neighbours
            neighbourCounter = 0;

            //Checks the neigbours (left and right) of current position
            //Will check if the neighbour exists, will ignore if they dont
            if(inGrid.inBounds(i,j-1) && inGrid.get(i, j-1) == 'X' ){
                neighbourCounter++;
            }
            if(inGrid.inBounds(i,j+1) && inGrid.get(i, j+1) == 'X'){
                neighbourCounter++;
            }

            //Checks neigbours in the row above and below currents position
            //Will check if the neighbour exists, will ignore if they dont
            for(int x = -1; x < 2; x++){
                if(inGrid.inBounds((i-1),j+x) && inGrid.get((i-1),j+x) == 'X'){
                    neighbourCounter++;
                }
                if(inGrid.inBounds((i+1),j+x) && inGrid.get(i+1,j+x) == 'X' ){
                    neighbourCounter++;
                }
            }

            //if there is less than 2 or more than 3 neighbours cell dies, ie cell will get char '-'
            // else if there is more than 2 and less than 4 neigbours a cell spawns, ie cell will get char 'X'
            if(neighbourCounter < 2 || neighbourCounter > 3){
                temp.set(i,j,'-');

            }else if(neighbourCounter > 2 && neighbourCounter<4){
                temp.set(i,j,'X');

            }
        }
    }
    //sets the grid to next generation
    inGrid = temp;

}

void animate(Grid<char> &inGrid){
    const int maxTick = 30;
    Grid<char> temp;
    // Will tick the amount of times that maxTick is set to
    // with a pause of n amount of ms (pause(ms))
    for(int i = 0; i < maxTick; i++){
        tick(inGrid);
        showGrid(inGrid);
        pause(150);
        clearConsole();
    }
}

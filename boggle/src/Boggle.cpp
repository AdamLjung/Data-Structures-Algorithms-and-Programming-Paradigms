// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "lexicon.h"
#include "grid.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
                                          "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
                                          "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
                                          "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
                                          "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
                                 };

Boggle::Boggle(){
};
void Boggle::shuffleBoard(){
    shuffle(theBoard);
};

Boggle::~Boggle(){
    for(Cube* cube:theBoard){
        delete cube;
    }
};

void Boggle::showBoard(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << theBoard[i][j]->getLetter();

        }
        cout << "\n";
    }
};

void Boggle::operator()(string letter){

    theBoard.resize(4,4);
    int counter = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            Cube* cube = new Cube(letter[counter],i,j);

            theBoard.set(i, j, cube);
            counter ++;
        }
    }
};

void Boggle::createBoard(){
    int randNum;
    char letter;
    int counter = 0;
    theBoard.resize(4,4);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            randNum = rand()% CUBE_SIDES;
            letter = CUBES[counter][randNum];
            Cube* cube = new Cube(letter, i ,j);
            theBoard.set(i, j, cube);
            counter++;
        }
    }

};

void Boggle::loadLexicon(){
    theLexicon.addWordsFromFile(DICTIONARY_FILE);
};

Cube* Boggle::findStartCube(const string &word){
    for(int i = 0; i<theBoard.nRows; i++){
        for(int j = 0; j<theBoard.nCols; j++){
            if(theBoard.get(i,j)->getLetter() == word[0]){
                return theBoard.get(i,j);
            }
        }
    }
};

bool Boggle::searchForWords(string word){

    for(int y = 0; y < theBoard.nRows; y++){
        for(int x = 0; x < theBoard.nCols; x++){

            if(word[0] == theBoard.get(x, y)->getLetter()){
            Cube* cube = theBoard.get(x, y);
            word = cube->getLetter();
            cube->setStatus(true);

            if(searchForWord(word.substr(1), x, y)){
                return true;
            }
            cube->setStatus(false);
            }
        }
    }
    return false;

};
bool Boggle::searchForWord(string word, int xPos, int yPos){
    int startPosY = yPos-1;
    int startPosX = xPos-1;
    int endPosY = yPos+2;
    int endPosX = xPos+2;

    if(word == ""){
        return true;
    }

    for(startPosY = yPos-1; yPos-1 < endPosY; yPos++){
        for(startPosX = xPos-1; xPos-1 < endPosX; xPos++){

            if(theBoard.inBounds(xPos-1, yPos-1) && theBoard.get(xPos, yPos)->getLetter() == word[0] && theBoard.get(xPos, yPos)->checkStatus() == false){
               theBoard.get(xPos-1, yPos-1)->setStatus(true);

               if(searchForWord(word.substr(1), xPos-1, yPos-1)){
                   return true;
               }
               theBoard.get(xPos-1, yPos-1)->setStatus(false);
            }
        }

    }
    return false;
};

void Boggle::resetBoard(){
    for(int i = 0; i<theBoard.nRows; i++){
        for(int j = 0; j < theBoard.nCols; j++){

            theBoard.get(i,j)->setStatus(false);
        }
    }
};

void Boggle::showFoundWords(){
    cout << endl;
    cout << "Your words " << "(" << foundWords.size() << "):" << " {";
    for(auto i: foundWords){
        cout << '"' << i << '"' << " ";
    }
    cout << "} " << endl;;
};


void Boggle::computerSearchForWords(){
    string word;

    for(int y = 0; y < theBoard.nRows; y++){

        for(int x = 0; x <theBoard.nCols; x++){

            Cube* cube = theBoard.get(x,y);
            word = cube->getLetter();
            cube->setStatus(true);
            computerSearchForWord(cube, word);
            cube->setStatus(false);

        }
    }
};

void Boggle::computerSearchForWord(Cube *cube, string word){
    int startPosY = cube->yPos()-1;
    int startPosX = cube->xPos()-1;
    int endPosY = cube->yPos()+2;
    int endPosX = cube->xPos()+2;

    if(theLexicon.contains(word) && word.length() > 3 && foundWords.find(word) == foundWords.end()){
        computerFoundWords.insert(word);
    }



    for(startPosY = cube->yPos()-1; startPosY < endPosY; startPosY++){

        for(startPosX = cube->xPos()-1; startPosX < endPosX; startPosX++){


            if(theBoard.inBounds(startPosX, startPosY) && theLexicon.containsPrefix(word+theBoard.get(startPosX,startPosY)->getLetter()) && theBoard.get(startPosX,startPosY)->checkStatus() == false)
            {
               theBoard.get(startPosX, startPosY)->setStatus(true);
               computerSearchForWord(theBoard.get(startPosX,startPosY),(word+theBoard.get(startPosX,startPosY)->getLetter()));
               theBoard.get(startPosX, startPosY)->setStatus(false);
            }

        }

    }


};

void Boggle::showComputerWords(){
    cout << "My words (" << computerFoundWords.size() << "):" << " {";
    for(auto i: computerFoundWords){

       cout << '"' << i << '"' << " ";
    }
    cout << "} " << endl;

};

int Boggle::returnPoints(set<string> words){
    int points = 0;
    set<string>::iterator itr;
    for(itr = words.begin(); itr != words.end(); itr ++){
        points += (itr->length() -3);
    }
    return points;
};














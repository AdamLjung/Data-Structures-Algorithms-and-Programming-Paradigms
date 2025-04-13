// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "shuffle.h"
#include "lexicon.h"
#include <grid.h>
#include "cube.h"
#include "set"
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    //default constructor
    Boggle();
    //Operator()
    void operator()(string letter);
    //destructor
    ~Boggle();
    //creates the boggle board
    void createBoard();
    //Shuffles the board
    void shuffleBoard();
    //prints the board
    void showBoard();
    //loads up the lexicon
    void loadLexicon();
    //Finds the position of the starting letter(cube)
    Cube* findStartCube(const string &word);
    //searches for a single word on the boggle board
    bool searchForWord(string word, int xPos, int yPos);
    //Searches the entire board for the word guessed by the user
    bool searchForWords(string word);
    //Resets the state of visited cubes
    void resetBoard();
    //Prints the words found of the user
    void showFoundWords();
    //Searches the remaining words of the board
    void computerSearchForWords();
    //Searches the board for a single word
    void computerSearchForWord(Cube *cube, string word);
    //Prints the words found by the computer
    void showComputerWords();
    //Counts and return the points for the words
    int returnPoints(set<string> words);
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;


    Grid<Cube*> theBoard;
    set<string> foundWords;
    set<string> computerFoundWords;
    Lexicon theLexicon;
private:


};

#endif

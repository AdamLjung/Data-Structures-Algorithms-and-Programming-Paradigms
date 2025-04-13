// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include <set>

void userGuesses(Boggle &boggle);
/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle boggle) {
    if(userChoice() == true){
          string letters;
          do{
               cout << "Write 16 letters: ";
               cin >> letters;
          }while(letters.length() != 16 || letters.find("1234567890") != string::npos);
   boggle(letters);
   cin.ignore();
   }else{
       boggle.createBoard();
   }
   boggle.loadLexicon();
   boggle.showBoard();
   userGuesses(boggle);
   cout << "It's my turn!!" << endl;
   boggle.computerSearchForWords();
   boggle.showComputerWords();
   cout << "My score " << boggle.returnPoints(boggle.computerFoundWords) << endl;

}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}

bool userChoice(){
    cout << "Would you like to enter your own Boggle board? " << endl;
    cout << "Yes/No?: ";
    string answer;
    getline(cin, answer);
    if(answer == "yes"){
        return true;
    }else{
        return false;
    }
}

void userGuesses(Boggle &boggle){
    string userGuess;
    // Grid<Cube*> gameBoard = boggle.theBoard;
    while(userGuess.length() < 4 || !boggle.theLexicon.contains(userGuess) || true){
        boggle.resetBoard();
        cout << "Type a an existing word with atleast 4 letters (or press Enter to end your turn)" << endl;

        getline(cin, userGuess);
        if(boggle.foundWords.find(userGuess) != boggle.foundWords.end()){
            cout << "Word already guessed, try again!" << endl;
        }else{

        if(boggle.theLexicon.contains(userGuess) && boggle.searchForWords(userGuess) && userGuess.length() > 3){
          cout << "Congratz you found a new word: " << userGuess << endl;
          boggle.showBoard();
          boggle.foundWords.insert(userGuess);
          boggle.showFoundWords();
          cout << "Your score " << boggle.returnPoints(boggle.foundWords) << endl;

        }
        }
        if(userGuess.empty()){
            return;
        }

    }
}

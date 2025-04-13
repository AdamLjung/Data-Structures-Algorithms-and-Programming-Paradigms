/* bensu844@student.liu.se
 * This program will let the user play the game hangman, against
 * an opponent that consisteley cheats. The program will continue to
 * change the word throughout the guesses to wordfamilies that holds the
 * most possible letterguesses left.
 * Adam Ljung. LIU-ID: Adalj586
 * Isak Skott. LIU-ID: Isask052
*/


#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <vector>


using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
//Loads the dictionary from the textfile
void load(string inFile, set<string> &dictionary);
//Finds the correct length of words, from user input
set<string> findWordLength(size_t userInput, const set<string> &dictionary);
//Plays the game, out of the words with the correct word length
void playTheGame(const set<string> &correctWordLengths);
//Creates a map. out of the wordfamilies. Wordfamilies is paired with a key which contains the the different
// possible guesses out of the guessed letter(searchLetter).
void nextGuess(const char searchLetter, const set<string> &words, map<string, vector<string>> &currentMap);
//Loops through the sizes of vectors finding the largest one. Will set the map with a key to that vector.
void findBiggestFamily(map<string, vector<string>> &allCurrentFamilies);
//Will show the user the remaining words
void showWordsLeft(const set<string> &dictionary);
//Removes guessed words from the dictionary
void removeGuessedWords(const map<string, vector<string>> &currentMap, set<string> &dictionary);
//Asks for a guess and checks if the guess is valid i.e it hasnt been guessed before and the letter
//is in the alphabet
void guess(string &lettersInPlay, char &guess);
//When there is families with the same sizes, will count the amount of '-'
//in both keys. Whichever has the most '-' will return.
string countRemainingSpots(const map<string,vector<string>> &map);
//Asks if user wants to see the remaining words
bool seeRemainingWords();

int main() {

    cout << "Welcome to Hangman!" << endl;
    set<string> dictionary;
    set<string> correctWordLengthSet;
    load("dictionary.txt", dictionary);
    string tryAgain;

    // Main loop
    while(tryAgain != "no"){
    cout << "Write a desired length of a word: ";
    size_t input;
    cin >> input;

    // Set of the words that has desired length of user.
    correctWordLengthSet = findWordLength(input, dictionary);
    playTheGame(correctWordLengthSet);
    cout << "Would you like to try again?: ";
    cin >> tryAgain;
    cout << endl;
    }


    return 0;
}

void load(string inFile, set<string> &dictionary){
   ifstream loadStream(inFile);
   string inputLine;

   while(getline(loadStream, inputLine)){
    loadStream >> inputLine;
    dictionary.insert(inputLine);
   }
    loadStream.close();
}

// Finds the word with the length of the userinput
set<string> findWordLength(size_t userInput, const set<string> &dictionary){
      // Loop through dictionary and find words with the length of userinput
     set<string> resultSet;
     for(const string &word:dictionary){
        if(word.length() == userInput){
            resultSet.insert(word);
        }
     }
     return resultSet;
}

void playTheGame(const set<string> &correctWordLengths){
    int amountOfGuesses = -1;
    //String that holds the guessed letters
    string lettersInPlay;
    map<string, vector<string>> playMap;
    set<string> dictionary = correctWordLengths;
    bool seeWords;
    int win_or_lose = 0;
    // Asks for how many guesses the user would like
    while(amountOfGuesses <0){
        cout << "How many guesses would you like? ";
        cin >> amountOfGuesses;
    }
    char guessingLetter;
    seeWords = seeRemainingWords();

    while(amountOfGuesses >0){

    if(seeWords == true){
    //If user wants to see, show the remaining words.
     showWordsLeft(dictionary);
    }
    //Asks user to guess a letter
    guess(lettersInPlay, guessingLetter);
    // Creates families of words with keys out of the guessed letter
    nextGuess(guessingLetter, dictionary, playMap);
    //Finds the key that holds the biggest family of words
    findBiggestFamily(playMap);

    amountOfGuesses--;
    cout << "You have " << amountOfGuesses << " guesses left" << endl;
    //Removes words in the dictionary except for the ones in current map
    removeGuessedWords(playMap, dictionary);
    cout << playMap.begin()->first << endl;
    // Asks user if they wanna see the remaining words.

    // If the key corresponds to the first spot in the vector, user has won
    if(playMap.begin()->second[0] == playMap.begin()->first){
        win_or_lose = 1;
        amountOfGuesses = 0;
    }
    }



    if(win_or_lose == 1){
        cout<< "Congrats, you have won the game!! The word was: " << playMap.begin()->first <<endl;
    }else{
        cout << "You have lost!! The word was: " << playMap.begin()->second.front() <<endl;
        win_or_lose = 0;
    }
    lettersInPlay.clear();

}


void nextGuess(const char searchLetter, const set<string> &words, map<string, vector<string>> &currentMap){

    map<string, vector<string>> storeMap;
    vector<string> tempVector;
    string key = "";
    //If the map is not empty key will be set to the first key
    //Will only contain one key at this stage since its been cleared before
    if(!(currentMap.empty())){
        key = currentMap.begin()->first;
    }else{
        //When map is empty, creates a key to be able to start making keys

        for(size_t j = 0; j<words.begin()->size(); j++){
            key[j] = '-';
        }
    }
    //Loops through the remaining words in the dictionary
    for(const string &word:words){
        string tempString = "";

        // For each word, loops through every letter and checks if the searchletter is in that position
        for(size_t i = 0; i<word.length(); i++){

            //To not overwrite existing key, needs to check that the position of the found searchletter is "-"
            if(word[i] == searchLetter && key[i] == '-'){
                tempString.push_back(searchLetter);

            //If the key doesnt have "-", the letter has been guessed and found, pushes that letter to tempstring
            }else if(key[i] != '-'){
                tempString.push_back(key[i]);
            //If noone of the above, pushes "-", since letter hasnt been found or guessed already
            }else{
                tempString.push_back('-');
            }
        }
        //Counts the numbers of values with a key, if not creates a key and adds the vector
        if(storeMap.count(tempString) == 0){
          storeMap[tempString] = tempVector;
          storeMap[tempString].push_back(word);

         // pushes a value to the key found
        }else{
            storeMap[tempString].push_back(word);
        }

    }
    //sets currentmap to storemap
    currentMap = storeMap;

}

void findBiggestFamily(map<string, vector<string>> &allCurrentFamilies){

    map<string, vector<string>> returnMap;
    vector<string> tempVector;
    unsigned maxSize=0;
    string key;

    //Loops through the current map, checks the sizes of the vectors holding words. The largest one will return
    for(auto i:allCurrentFamilies){

        if(i.second.size()>maxSize){
            maxSize = i.second.size();
            tempVector = i.second;
            key = i.first;
        }
    }
    //If the families in the map is the same size, will count the occurances of "-" to see which word has the most guesses left
    if(tempVector.size() == 0){
        key = countRemainingSpots((allCurrentFamilies));
        //Sets the vector to the vector of key which contains words with the most guesses left
        tempVector = allCurrentFamilies[key];
    }
    //Adds the vector containing words to returnmap
    returnMap[key] = tempVector;
    //Clears all existing families in the "playmap"
    allCurrentFamilies.clear();
    //Adds the newly made map to the playmap
    allCurrentFamilies = returnMap;

}
void showWordsLeft( const set<string> &dictionary){

    cout << "-- Words left--" << endl;
    cout << dictionary.size() << endl;
}

void removeGuessedWords(const map<string, vector<string>> &currentMap, set<string> &dictionary){
    //If there is more than 1 word left in dictionary, removes all the words and adds the words of
    //the current map. Will only hold one family, the largest one.
    if(dictionary.size() > 1){
    dictionary.clear();
    for(auto i: currentMap){
        for(size_t j = 0; j<i.second.size(); j++){
            dictionary.insert(i.second[j]);
        }
    }
    }
}

void guess(string &lettersInPlay, char &guess){

    cout << "Guess a letter: ";
    cin >> guess;
    cout << endl;
    // Searches the alphabet and the string lettersInPlay if the guessed letter is in them
    // If no matches were found, the function returns string::npos.
    while(ALPHABET.find(guess) != string::npos && lettersInPlay.find(guess) != string::npos){
        cout << "Letter not in play, guess again: ";
        cin >> guess;
        cout << endl;
    }

    //Adds the guessed letter to the string
    lettersInPlay += guess;


}

string countRemainingSpots(const map<string,vector<string>> &map){
    int countLetters;
    int maxAmount = 0;
    string winningKey;
    //Counts the occurances of "-", whichever word family has the most will return that key.
    for(auto i: map){
        countLetters = 0;
        for(size_t j = 0; j<i.first.size(); j++){
            if(i.first[j] == '-'){
                countLetters++;
            }
        }
        if(countLetters>maxAmount){
            winningKey = i.first;
            maxAmount = countLetters;
        }
    }
    return winningKey;
}

bool seeRemainingWords(){
    string answer;
    cout << "Would you like to see the remaining words?";
    cin >> answer;
    cout << endl;
    if(answer == "yes"){
        return true;
    }else{
        return false;
    }
}















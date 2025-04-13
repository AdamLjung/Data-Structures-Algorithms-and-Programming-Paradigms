/* Program that will make chain from one word to
 * the another one. Finding the word chain by changing
 * one letter at a time.
 * BY: Adam Ljung. LIU-ID: Adalj586@student.liu.se
 *     Isak Skott. LIU-ID: Isask052@student.liu.se
 *
*/



#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <deque>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
//Loads words from a textfile to a set
void load(const string &inFile, set<string> &inSet);
//Finds the wordchain from wordFrom to wordTo
stack<string> findWord(string wordFrom, const string wordTo, set<string> dictionary);
//Prints the result of the wordchain
void printStackResult(stack<string> printStack);

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
    set<string> dictionary;
    load("dictionary.txt", dictionary);
    cout << "Please type two words: " << endl;
    string wordFrom, wordTo;
    cin >> wordFrom >> wordTo;
    printStackResult(findWord(wordFrom, wordTo, dictionary));






    // TODO: Finish the program!

    return 0;
}


stack<string> findWord(string wordFrom, const string wordTo, set<string> dictionary){
    stack<string> resultStack;
    queue<stack<string>> my_que;
    stack<string> wordStack;
    //Adds the first word to the stack
    wordStack.push(wordFrom);
    //Adds the first stack to que
    my_que.push(wordStack);




    while(!my_que.empty()){
        //Adds the stack to a temporary stack
        stack<string> temp_chain = my_que.front();
        //Removes it from the top of the que
        my_que.pop();
        //If the top of the stack is the same as the word we're going to
        if(temp_chain.top() == wordTo){
            while(!temp_chain.empty()){
                //Adds the top of tempchain to the resultstack
                resultStack.push(temp_chain.top());
                // removes the top element of the temporary chain
                temp_chain.pop();


            }
            break;
        }else{

            for(size_t i = 0; i <temp_chain.top().length(); i++){

                for(size_t j = 0; j < ALPHABET.length(); j++){

                    string checkWord = temp_chain.top();
                    //Changes one letter and see if it is a word in the dictionary
                    checkWord[i] = ALPHABET[j];

                    //Check if the word is in the dictionary, if it is removes word from dictionary, and adds the chain to a temporary stack
                    //Adds the newly found word to the temporarystack and pushes the stack to the que
                    if(dictionary.count(checkWord) != 0){
                        dictionary.erase(checkWord);
                        stack<string> copyChain = temp_chain;
                        copyChain.push(checkWord);
                        my_que.push(copyChain);

                    }

                }
            }

        }

    }
    return resultStack;
}

void load(const string &inFileName, set<string> &inSet){
    ifstream loadStream(inFileName);
    string inputString;
    while(loadStream){
        loadStream >> inputString;
        inSet.insert(inputString);
    }
    loadStream.close();

}

void printStackResult(stack<string> printStack){
    while(!printStack.empty()){
        cout << printStack.top() << " ";
        printStack.pop();
    }
    cout << endl;
}

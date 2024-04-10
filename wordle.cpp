#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateWords(string currentWord, const string& in, const string& floating, set<string>& validWords, const set<string>& dict, size_t currentIndex, int dashCount);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> validWords;

    int dashCount = 0;
    for(size_t i = 0; i < in.size(); ++i){ //count blank spaces
        if(in[i] == '-'){
            dashCount++;
        }
    }

    generateWords("", in, floating, validWords, dict, 0, dashCount);
    return validWords;
}

// Define any helper functions here
void generateWords(string currentWord, const string& in, const string& floating, set<string>& validWords, const set<string>& dict, size_t currentIndex, int dashCount){
    if(currentIndex == in.length()){ //if word is complete and is in the dictionary
        if(dict.find(currentWord) != dict.end()){
            validWords.insert(currentWord);
        }
        return;
    }
    
    if(in[currentIndex] != '-'){ //not a dash
        generateWords(currentWord + in[currentIndex], in, floating, validWords, dict, currentIndex + 1, dashCount);
    }
    else{ //if blank
        string tempFloating = floating;
        for(size_t i = 0; i < tempFloating.size(); ++i){ //first try replacing with floating letter
            char letter = tempFloating[i];
            size_t pos = tempFloating.find(letter);
            if(pos != string::npos){
                tempFloating.erase(pos, 1); //erase the used floating letter
            }
            generateWords(currentWord + letter, in, tempFloating, validWords, dict, currentIndex + 1, dashCount-1);
            tempFloating = floating; //reset for next iteration
        }

        if(dashCount > static_cast<int>(tempFloating.length())){ //if more letters are needed
            for(char letter = 'a'; letter <= 'z'; ++letter){
                tempFloating = floating; //reset
                size_t i = tempFloating.find(letter);
                if(i != string::npos){
                    tempFloating.erase(i,1); //erase used floating letter
                }
                generateWords(currentWord + letter, in, tempFloating, validWords, dict, currentIndex + 1, dashCount - 1);
            }
        }
    }
}

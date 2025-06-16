#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// function prototypes
void getTokens();
void execute();
string checkType(int);

vector<string> tokens;


int main() {
    cout << "===================== \nRIZZING IN PROGRESS: \n===================== \n";
    getTokens();
    execute();

    return 0;
}


void getTokens() {
    // get the input file
    ifstream InputRizz("code.rizz");
 
    string currToken;
    char charac, prevCharac;
    bool stringStarted = false;

    while (InputRizz.get(charac)) {
        // add the token if the reader hits a whitespace AND not inside a string
        if ( (charac == ' ' || charac == '\n') && !stringStarted) {
            // if token is not empty, push into the vector of tokens
            if (!currToken.empty()) {
                tokens.push_back(currToken);
                currToken = "";
            }
        }
        // add characters into the current token
        else {
            // check if a string is started
            if (checkType(charac) == "quote") {
                stringStarted = !stringStarted;
                continue;
            }
            // if the next character are not the same type AND it's not inside a string thingy idk
            else if ( !(checkType(prevCharac) == checkType(charac)) && !stringStarted) {
                // append the current token, and create a new token entry
                if (!currToken.empty()) {
                    tokens.push_back(currToken);
                    currToken = "";
                }
            }

            // current letter into the current token
            currToken += charac;

            // save the previous token
            prevCharac = charac;
        }
    }

}


// check for the character types
string checkType(int ascii) {

    // if A-Z a-z
    if ( (ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122) ) {
        return "letters";
    }
    // if 0-9
    else if (ascii >= 48 && ascii <= 57) {
        return "numbers";
    }
    // if arithmatics symbols
    else if (string("+-*/").find(ascii) != string::npos) {
        return "math";
    }
    // if compare symbols
    else if (string("=<>").find(ascii) != string::npos) {
        return "compare";
    }
    // if boolean logic
    else if (string("&|!").find(ascii) != string::npos) {
        return "boolean logic";
    }
    // if quotes (": 34, ': 39)
    else if (ascii == 34 || ascii == 39 ) {
        return "quote";
    }
    // if semicolor 
    else if (ascii == 59) {
        return "semicolon";
    }

    return "misc";
}



void execute() {
    cout << "Tokens: [";
    for (string str : tokens) {
        cout << '(' << str << ")  ";
    }

    cout << "]" << endl;
 
    for (int i=0; i < tokens.size(); i++) {
        // if user want to yap
        if (tokens.at(i) == "yap") {
            cout << tokens.at(i + 1) << endl;
        }
    }
}

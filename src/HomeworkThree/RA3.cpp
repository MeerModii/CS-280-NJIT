#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool isStringEmptyorWhiteSpace(const string line){
    for(char ch : line){
        if(!isspace(ch)){
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    int numLines = 0;
    int numNonBlankLines = 0;
    int numWords = 0;
    int numIntegers = 0;
    int numSpecialNames = 0;
    int numWordsLessThanOrEqualTo5 = 0;
    int numWordsGreaterThan5 = 0;

    if (argc < 2) {
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "CANNOT OPEN THE FILE: " + filename << endl;
        return 1;
    }



    string line;
    while (getline(inputFile, line)) {
        numLines++;

        if (line.empty()) {
            numNonBlankLines++;
            continue;
        }

        istringstream iss(line);
        string word;
        while (iss >> word) {
            numWords++;

            // Counting words less than or equal to 5 characters
            if (word.length() <= 5) {
                numWordsLessThanOrEqualTo5++;
            }
                // Counting words greater than 5 characters
            else {
                numWordsGreaterThan5++;
            }

            // Checking for special names
            if (isalpha(word[0])) {
                bool isSpecialName = true;
                for (char ch : word) {
                    if (!isalpha(ch)) {
                        isSpecialName = false;
                        break;
                    }
                }
                if (isSpecialName) {
                    numSpecialNames++;
                }
            }

            // Checking for unsigned integers
            bool isUnsignedInteger = true;
            for (char ch : word) {
                if (!isdigit(ch)) {
                    isUnsignedInteger = false;
                    break;
                }
            }
            if (isUnsignedInteger) {
                numIntegers++;
            }
        }
    }

    inputFile.close();

    // Print out the requested statistics
    if(numLines == 0){
        cout << "File is empty." << endl;
    }
    else{
        cout << "Total Number of Lines: " << numLines << endl;
        cout << "Number of non-blank lines: " << numNonBlankLines+1 << endl;
        cout << "Number of Words: " << numWords << endl;
        cout << "Number of Integers: " << numIntegers << endl;
        cout << "Number of Names: " << numSpecialNames << endl;
        cout << "Number of Words Less Than or Equal to 5 Characters: " << numWordsLessThanOrEqualTo5 << endl;
        cout << "Number of Words Greater Than 5 Characters: " << numWordsGreaterThan5 << endl;
    }
    return 0;
}

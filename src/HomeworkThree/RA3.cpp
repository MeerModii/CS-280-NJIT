#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool isStringEmptyOrWhiteSpace(const std::string& line) {

    // Check if the string is empty
    if (line.empty()) {
        return true;
    }
    else{
        return false;
    }
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
        if (!isStringEmptyOrWhiteSpace(line)) {
            numNonBlankLines++;
        }

        istringstream iss(line);
        string word;
        while (iss >> word) {
            numWords++;

            if (word.length() <= 5) {
                numWordsLessThanOrEqualTo5++;
            }
            else {
                numWordsGreaterThan5++;
            }

            if (isalpha(word[0])) {
                bool isSpecialName = true;
                for (char ch : word) {
                    if (!isalnum(ch) && ch != '_' && ch != '@') {
                        isSpecialName = false;
                        break;
                    }
                }
                if (isSpecialName) {
                    //cout << word << endl;
                    numSpecialNames++;
                }
            }

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

    if(numLines == 0){
        cout << "File is empty." << endl;
    }
    else{
        cout << "Total Number of Lines: " << numLines << endl;
        cout << "Number of non-blank lines: " << numNonBlankLines << endl;
        cout << "Number of Words: " << numWords << endl;
        cout << "Number of Integers: " << numIntegers << endl;
        cout << "Number of Names: " << numSpecialNames << endl;
        cout << "Number of Words Less Than or Equal to 5 Characters: " << numWordsLessThanOrEqualTo5 << endl;
        cout << "Number of Words Greater Than 5 Characters: " << numWordsGreaterThan5 << endl;
    }
    return 0;
}

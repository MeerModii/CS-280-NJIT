#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    // Arrays for storing statistics
    string str[2];  // 0 = longest word, 1 = longest line
    int num[3];     // 0 = total lines read, 1 = total of non-commented lines, 2 = number of words

    // Variable declarations
    string line;
    string userIn;
    string word;

    // Taking input from the user and assigning it to a variable.
    cout << "Enter the name of a file to read from: \n" << endl;
    cin >> userIn;

    // C++ does not check if the file opening was successful or failed, hence does not throw an exception.
    ifstream fileToBeRead;
    fileToBeRead.open(string(userIn));

    // Reading lines if the file was successfully opened
    if (fileToBeRead.is_open()) {
        while (getline(fileToBeRead, line)) {
            // Check if the line starts with "//" or "#"
            if (line.substr(0, 2) == "//" || line.substr(0, 1) == "#") {
                num[0]++;
            } else {
                num[1]++;
                num[0]++;

                // Update statistics for the line of maximum length
                if (line.length() > str[1].length()) {
                    str[1] = line;
                }

                istringstream iss(line);


                while (iss >> word) {
                    // Update statistics for the word of maximum length
                    if (word.length() > str[0].length()) {
                        str[0] = word;
                    }

                    // Increment number of words
                    num[2]++;
                }
            }
        }

        // Print out the requested statistics using arrays
        cout << "Total Number of Lines: " << num[0] << endl;
        cout << "Number of non-commented lines: " << num[1] << endl;
        cout << "Line of Maximum Length: \"" << str[1] << "\"" << endl;
        cout << "Number of Words: " << num[2] << endl;
        cout << "Word of Maximum Length: \"" << str[0] << "\"" << endl;
    } else {
        cout << "File cannot be opened " + userIn << endl;
        exit(1);
    }

    fileToBeRead.close();
    return 0;
}

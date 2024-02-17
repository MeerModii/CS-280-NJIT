#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include <fstream>
#include <map>
#include <iterator>

using namespace std;

int main(int argc, char* argv[])
{

    ifstream inFile;
    map <int, int> numberOccur;
    map <char, int> charOccur;
    map <char, int> punctOccur;
    int highestCount = 0;
    char highestKey;
    int highestKeyNum = 0;
    bool occurNum = false;
    bool occurChar = false;
    bool occurPunct = false;
    string line;
    string word;


    if (argc < 2)
    {
        cout << "NO SPECIFIED INPUT FILE NAME.\n";
        exit(1);
    }
    inFile.open(argv[1]);
    if (!inFile)
    {
        cout << "CANNOT OPEN THE FILE: " << argv[1] << "\n";
        exit(1);
    }
    if (inFile.peek() == EOF)
    {
        cout << "File is empty.\n";
        exit(1);
    }
    if (argc > 2)
    {
        for (int i  = 2; i < argc && i <= 3; i++)
        {
            if (string(argv[i]) == "-all")
            {
                occurChar = true;
                occurPunct = true;
                occurNum = true;
                break;
            }
            else if (string(argv[i]) == "-D")
                occurNum = true;
            else if (string(argv[i]) == "-L")
                occurChar = true;
            else if (string(argv[i]) == "-P")
                occurPunct = true;
        }
    }
    while (getline(inFile, line))
    {
        stringstream ss(line);
        while (ss >> word)
        {
            for (char c: word)
            {
                if (isalpha(c))
                    charOccur[toupper(c)] +=1;
                else if (isdigit(c)) {
                    numberOccur[c - '0'] += 1;
                }
                else if (ispunct(c))
                    punctOccur[c] += 1;
            }
        }
    }

    map<char, int>::iterator ss1 = charOccur.begin();

    if (!charOccur.empty())
    {
        while (ss1 != charOccur.end())
        {
            if (ss1->second > highestCount)
            {
                highestKey = ss1->first;
                highestCount = ss1->second;
            }
            ss1++;
        }
        cout << "Letter of Largest number of occurrences: " <<
             highestKey << " occurred " << highestCount << " times\n";
    }
    highestCount = 0;
    map<int, int>::iterator ss2 = numberOccur.begin();

    if (!numberOccur.empty())
    {
        while (ss2 != numberOccur.end())
        {
            if (ss2->second > highestCount)
            {
                highestKeyNum = ss2->first;
                highestCount = ss2->second;
            }
            ss2++;
        }
        cout << "Digits of Largest number of occurrences: " <<
             highestKeyNum << " occurred " << highestCount << " times\n";
    }
    highestCount = 0;
    map<char, int>::iterator ss3 = punctOccur.begin();
    if (!punctOccur.empty())
    {
        while (ss3 != punctOccur.end())
        {
            if (ss3->second > highestCount)
            {
                highestKey = ss3->first;
                highestCount = ss3->second;
            }
            ss3++;
        }
        cout << "Punctuations of Largest number of occurrences: " <<
             highestKey << " occurred " << highestCount << " times\n";
    }
    if (occurChar && !charOccur.empty())
    {
        cout << "List of Letters seen in the file and their number of occurrences:\n";
        for (ss1 = charOccur.begin(); ss1 != charOccur.end(); ss1++)
            cout << ss1->first << ": " << ss1->second << "\n\n";
    }
    if (occurNum && !numberOccur.empty())
    {
        cout << "List of Digits seen in the file and their number of occurrences:\n";
        for (ss2 = numberOccur.begin(); ss2 != numberOccur.end(); ss2++)
            cout << ss2->first << ": " << ss2->second << "\n\n";
    }
    if (occurPunct && !punctOccur.empty())
    {
        cout << "List of Punctuations seen in the file and their number of occurrences:\n";
        for (ss3 = punctOccur.begin(); ss3 != punctOccur.end(); ss3++)
            cout << ss3->first << ": " << ss3->second << "\n\n";
    }
    return 0;

}




//#include <iostream>
//#include <fstream>
//#include <string>
//#include <map>
//using namespace std;
//
//int main(int argc, char *argv[]) {
//
//    map<int, int> numbers;
//    map<char, int> alphabets;
//    map<char, int> specialChars;
//
//
//    int nums[10] = {0};
//    int letters[26] = {0};
//    int nonAlphaNumeric[32] = {0};
//    int numLines = 0;
//    string line;
//    string word;
//
//    if (argc < 2) {
//        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
//        return 1;
//    }
//
//    string filename = argv[1];
//    ifstream inputFile(filename);
//
//    if (!inputFile.is_open()) {
//        cout << "CANNOT OPEN THE FILE: " + filename << endl;
//        return 1;
//    }
//
//    // Check if the file is empty
//    if (inputFile.peek() == ifstream::traits_type::eof()) {
//        cout << "File is empty." << endl;
//        return 0;
//    }
//
//    while (getline(inputFile, line)) {
//        numLines++;
//        // everychar of line
//        for (char ch : line) {
//            // char alphabet or numebric?
//            if (isalnum(ch)) {
//                // char digit?
//                if (isdigit(ch)) {
//                    nums[ch - '0']++;
//                }
//                else { // not alphabet?
//                    if (isupper(ch)) {
//                        ch = tolower(ch);
//                    }
//                    letters[ch - 'a']++;
//                }
//            } else {
//                // Check if character falls within non-alphanumeric range
//                if ((ch >= 33 && ch <= 47) || (ch >= 58 && ch <= 64) || (ch >= 91 && ch <= 96) || (ch >= 123 && ch <= 126)) {
//                    nonAlphaNumeric[ch - 33]++;  // Increment count for non-alphanumeric character
//                }
//            }
//        }
//    }
//
//    inputFile.close();
//
//    // Print counts of  numbers
//    for (int i = 0; i < 10; i++) {
//        numbers.insert({i,nums[i]});
//    }
//
//    // Print counts for letters
//    for (int i = 0; i < 26; i++) {
//        alphabets.insert({toupper(static_cast<char>('a' + i)), letters[i]});
//
//    }
//
//    // Print counts for non-alphanumeric characters
//    for (int i = 0; i < 32; i++) {
//        specialChars.insert({static_cast<char>(33 + i),nonAlphaNumeric[i]});
//    }
//// ... (your existing code)
//
//    cout << "Numbers:" << endl;
//    for (const auto& [num, count] : numbers) {
//        cout << num << ": " << count << endl;
//    }
//
//    cout << "Alphabets:" << endl;
//    for (const auto& [letter, count] : alphabets) {
//        cout << "\t" << letter << ": " << count << endl;
//    }
//
//    cout << "Special Characters:" << endl;
//    for (const auto& [charValue, count] : specialChars) {
//        // Convert numeric character to displayable character
//        char specialChar = static_cast<char>(charValue + 33);
//        cout << "\t" << specialChar << ": " << count << endl;
//    }
//
//    return 0;
//}
//

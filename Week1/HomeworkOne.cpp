#include <iostream>
using namespace std;

int main() {
    string first_name;
    string last_name;
    int section_number;
    cout << "Please enter your first name >>" << endl;
    cin >> first_name;
    cout << "Please enter your last name >>"<< endl;
    cin >> last_name;
    cout << "Please enter your CS 280 section number >>"<< endl;
    cin >> section_number;
    cout << "Hello " << first_name << ", welcome to CS 280 section " << section_number << endl;
} 


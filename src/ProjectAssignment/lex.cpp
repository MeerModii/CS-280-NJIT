
#include<iostream>
#include<map>
#include<cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include "lex.h"
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
using namespace std;

// while loop x


static map<Token, string> tokens = {
    {PROGRAM, "PROGRAM"},
    {END, "END"},
    {ELSE, "ELSE"},
    {IF, "IF"},
    {THEN, "THEN"},
    {INTEGER, "INTEGER"},
    {REAL, "REAL"},
    {CHARACTER, "CHARACTER"},
    {PRINT, "PRINT"},
    {LEN, "LEN"},
    {PLUS, "PLUS"},
    {MINUS, "MINUS"},
    {MULT, "MULT"},
    {DIV, "DIV"},
    {POW, "POW"},
    {ASSOP, "ASSOP"},
    {EQ, "EQ"},
    {LTHAN, "LTHAN"},
    {GTHAN, "GTHAN"},
    {CAT, "CAT"},
    {COMMA, "COMMA"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {DCOLON, "DCOLON"},
    {DOT, "DOT"},
    {DEF, "DEF"},
    {ICONST, "ICONST"},
    {RCONST, "RCONST"},
    {SCONST, "SCONST"},
    {IDENT, "IDENT"},
    {ERR, "ERR"},
    {DONE, "DONE"}
};
// upper lower
static map<string, Token> keywords = {
    {"PROGRAM", PROGRAM},
    {"program", PROGRAM},
    {"PRINT", PRINT},
    {"print", PRINT},
    {"IF", IF},
    {"if", IF},
    {"ELSE", ELSE},
    {"else", ELSE},
    {"END", END},
    {"end", END},
    {"INTEGER", INTEGER},
    {"integer", INTEGER},
    {"REAL", REAL},
    {"real", REAL},
    {"CHARACTER", CHARACTER},
    {"character", CHARACTER},
    {"THEN", THEN},
    {"then", THEN}
};

//implementing abstract methods from lex.h
LexItem id_or_kw(const string& lexeme, int linenum) {
    if (keywords.find(lexeme) != keywords.end()) {
        return LexItem(keywords[lexeme], lexeme, linenum);
    } else {
        return LexItem(IDENT, lexeme, linenum);
    }
}
ostream& operator << (ostream& out, const LexItem& tok) {
    Token tt = tok.GetToken();
    out << tokens[tt];

    if (tt == IDENT) {
        out << ": \'" << tok.GetLexeme() << "\'";
    } 
    else if (tt == ICONST || tt == RCONST) {
        out << ": (" << tok.GetLexeme() << ")";
    } 
    else if (tt == SCONST) {
        out << ": \"" << tok.GetLexeme() << "\"";
    }

    return out;
}

LexItem getNextToken(istream& in, int& linenumber) {
    enum TokState { START, INID, INSTRING, ININT, INCOMMENT, INREAL };
    string lexeme;
    LexItem lex;
    char ch;
    TokState state = START;
    bool isDoubleQuote = false;

    while (in.get(ch)) {
        switch (state) {
            case START:
                if (ch == '\n') {
                    linenumber++;
                }
                if (isspace(ch)) {
                    continue;
                }
                lexeme = ch;

                if (isalpha(ch)) {
                    lexeme = ch;;
                    state = INID;
                } 
                else if (isdigit(ch)) {
                    lexeme = ch;
                    state = ININT;
                } 
                else if (ch == '\"') {
                    state = INSTRING;
                    isDoubleQuote = true;
                } 
                else if (ch == '\'') {
                    state = INSTRING;
                } 
                else if (ch == '!') {
                    state = INCOMMENT;
                } 
                else if (ch == '+') {
                    lexeme += ch;
                    lex = LexItem(PLUS, "PLUS", linenumber);
                    return lex;
                } 
                else if (ch == '-') {
                    lexeme += ch;
                    lex = LexItem(MINUS, "MINUS", linenumber);
                    return lex;
                } 
                else if (ch == '*') {
                    lexeme += ch;
                    in.get(ch);
                    if (ch == ',') {
                        in.putback(ch);
                        lex = LexItem(DEF, "DEF", linenumber);
                        return lex;
                    }
                    if (ch == '*') {
                        lexeme += ch;
                        lex = LexItem(POW, "POW", linenumber);
                        return lex;
                    } else {
                        in.putback(ch);
                        lex = LexItem(MULT, "MULT", linenumber);
                        return lex;
                    }
                } 
                else if (ch == '/') {
                    lexeme += ch;
                    in.get(ch);
                    if (ch == '/') {
                        lexeme += ch;
                        lex = LexItem(CAT, "CAT", linenumber);
                        return lex;
                    } 
                    else {
                        in.putback(ch);
                        lex = LexItem(DIV, "DIV", linenumber);
                        return lex;
                    }
                } 
                else if (ch == '>') {
                    lexeme += ch;
                    return LexItem(GTHAN, "GTHAN", linenumber);
                } 
                else if (ch == '<') {
                    lexeme += ch;
                    return LexItem(LTHAN, "LTHAN", linenumber);
                } 
                else if (ch == '=') {
                    lexeme += ch;
                    in.get(ch);
                    if (ch == '=') {
                        lexeme += ch;
                        lex = LexItem(EQ, "EQ", linenumber);
                        return lex;
                    } 
                    else {
                        in.putback(ch);
                        lex = LexItem(ASSOP, "ASSOP", linenumber);
                        return lex;
                    }
                } 
                else if (ch == '(') {
                    lexeme += ch;
                    lex = LexItem(LPAREN, "LPAREN", linenumber);
                    return lex;
                } 
                else if (ch == ')') {
                    lexeme += ch;
                    lex = LexItem(RPAREN, "RPAREN", linenumber);
                    return lex;
                } 
                else if (ch == ',') {
                    lexeme += ch;
                    lex = LexItem(COMMA, "COMMA", linenumber);
                    return lex;
                } 
                else if (ch == ':') {
                    lexeme += ch;
                    in.get(ch);
                    if (ch == ':') {
                        lexeme += ch;
                        lex = LexItem(DCOLON, "DCOLON", linenumber);
                        return lex;
                    } 
                    else {
                        in.putback(ch);
                        lex = LexItem(ERR, lexeme, linenumber);
                        return lex;
                    }
                } 
                else if (ch == '.') {
                    if (isdigit(in.peek())) {
                        state = INREAL;
                    } 
                    else {
                        return LexItem(DOT, "DOT", linenumber);
                    }
                } 
                else {
                    lex = LexItem(ERR, lexeme, linenumber);
                    return lex;
                }
                break;
            case INID:
                if (isalpha(ch) || isdigit(ch) || ch == '_') {
                    lexeme += ch;
                    continue;
                } 
                else {
                    in.putback(ch);
                    lex = id_or_kw(lexeme, linenumber);
                    return lex;
                }
                break;
            case INSTRING:
                if (ch == '\n') {
                    return LexItem(ERR, lexeme, linenumber);
                }
                if ((isDoubleQuote && ch == '\"') || (!isDoubleQuote && ch == '\'')) {
                    return LexItem(SCONST, lexeme.substr(1, lexeme.size() - 1), linenumber);
                    lexeme = "";
                    state = START;
                } 
                else {
                    lexeme += ch;
                    continue;
                }
                break;
            case ININT:
                if (isdigit(ch)) {
                    lexeme += ch;
                } 
                else if (ch == '.') {
                    state = INREAL;
                    lexeme += ch;
                } 
                else {
                    in.putback(ch);
                    lex = LexItem(ICONST, lexeme, linenumber);
                    return lex;
                }
                break;
            case INREAL:
                if (isdigit(ch)) {
                    lexeme += ch;
                } 
                else if (ch == '.') {
                    lexeme += ch;
                    return LexItem(ERR, lexeme, linenumber);
                } 
                else {
                    in.putback(ch);
                    return LexItem(RCONST, lexeme, linenumber);
                }
                break;
            case INCOMMENT:
                if (ch == '\n') {
                    linenumber++;
                    state = START;
                    continue;
                }
                break;
        }
    }

    return LexItem(DONE, "", linenumber);
}

// running methods in main method

int main(int argc, char *argv[])
{
    bool everytoken = false;
    bool coutint = false;
    bool coutreal = false;
    bool coutstr = false;
    bool coutid = false;
    bool coutkw = false;
    bool inputFIle = false;
    string filename;
    int i = 1;


    while(i<argc){

        if (strcmp(argv[i], "-all") == 0){
            everytoken = true;
        }
        else if (strcmp(argv[i], "-int") == 0){
            coutint = true;
        }
        else if (strcmp(argv[i], "-real") == 0){
            coutreal = true;
        }
        else if (strcmp(argv[i], "-str") == 0){
            coutstr = true;
        }
        else if (strcmp(argv[i], "-id") == 0){
            coutid = true;
        }
        else if (strcmp(argv[i], "-kw") == 0){
            coutkw = true;
        }


        else if (argv[i][0] == '-'){
            cout<<"UNRECOGNIZED FLAG {"<<argv[i]<<"}"<<endl;
            return 0;
        }
        else if(inputFIle){
            cout<<"ONLY ONE FILE NAME IS ALLOWED."<<endl;
            return 0;
        }
        else{
            inputFIle = true;
            filename = argv[i];
        }
        i++;
    }
    if(!inputFIle){
        cout<<"NO SPECIFIED INPUT FILE."<<endl;
		return 0;
    }
    ifstream fin(filename); 
    if(fin.fail()){ 
		cout<<"CANNOT OPEN THE FILE " <<filename<<endl;
		return 0;
	}

    LexItem lex;

    int lnnum = 1;  //1 works
    int numtokens = -1;
    int numident = 0;
    int numint = 0;
    int numreal = 0;
    int numstr = 0;

    map<string, int> identifiers;
    map<string, int> keywords;
    map<string, int> integers;
    map<string, int> reals;
    map<string, int> strings;


    // dosn't work
    while(true){
        lex = getNextToken(fin, lnnum);
        numtokens++;

        if(lex.GetToken() == DONE){
            break;
        }
        else if (lex.GetToken() == ICONST) {
            auto it = integers.find(lex.GetLexeme());

            if (it == integers.end()) {
                integers[lex.GetLexeme()] = 1;
                numint++;
            }
        }
        else if (lex.GetToken() == IDENT) {
            auto it = identifiers.find(lex.GetLexeme());
            if (it == identifiers.end()) {
                identifiers[lex.GetLexeme()] = 1;
                numident++;
            } else {
                identifiers[lex.GetLexeme()]++;
            }
        }
        else if(lex.GetToken()==RCONST){
            auto it = reals.find(lex.GetLexeme());

            if (it == reals.end()) {
                reals[lex.GetLexeme()] = 1;
                numreal++;
            }
        }
        else if(lex.GetToken()==SCONST){
            numstr++;
            if(strings.find(lex.GetLexeme()) == strings.end()){
                strings[lex.GetLexeme()] = 1;
            }
            else{
                strings[lex.GetLexeme()]++;
            }
        }
        else if(lex.GetToken() == IF || lex.GetToken() == ELSE || lex.GetToken() == PRINT || 
                lex.GetToken() == END || lex.GetToken() == PROGRAM || lex.GetToken() == THEN ||
                lex.GetToken() == INTEGER || lex.GetToken() == REAL || lex.GetToken() == CHARACTER || 
                lex.GetToken() == LEN)
        {
            if(keywords.find(lex.GetLexeme()) == keywords.end()){
                keywords[lex.GetLexeme()] = 1;
            }
            else{
                keywords[lex.GetLexeme()]++;
            }
        }

        if(lex.GetToken() == ERR){
            cout<<"Error in line "<<lex.GetLinenum()<<": Unrecognized Lexeme {" << lex.GetLexeme()<<"}"<<endl;
            return 0;
        }

        if(everytoken){
            cout<<lex<<endl;
        }
    }

    if(numtokens == 0){ 
        cout<<"Empty File."<<endl;
        return 0;
    }
    cout << "\nLines: " << lnnum-1 << endl;
    cout << "Total Tokens: " << numtokens << endl;
    cout << "Identifiers: " << numident << endl;
    cout << "Integers: " << numint << endl;
    cout << "Reals: " << numreal << endl;
    cout << "Strings: " << numstr << endl;

    
    if(coutid){
        cout<<"IDENTIFIERS:" <<endl;
        for(auto it = identifiers.begin(); it != identifiers.end(); it++){
            cout<<it->first<<" ("<<it->second<<")";
            if(next(it) != identifiers.end()){
                cout<<", ";
            }
        }
        cout<<endl;
    }

    if(coutkw){
        cout<<"KEYWORDS:" <<endl;
        for(auto it = keywords.begin(); it != keywords.end(); it++){
            cout<<it->first<<" ("<<it->second<<")";
            if(next(it) != keywords.end()){
                cout<<", ";
            }
        }
        cout<<endl;
    }
    if (coutint) {
        cout << "INTEGERS:\n";
        vector<string> integerKeys;
        for (const auto& entry : integers) {
            integerKeys.push_back(entry.first);
        }

        sort(integerKeys.begin(), integerKeys.end(), [](const string& a, const string& b) {
            return stoi(a) < stoi(b);
        });

        for (const auto& key : integerKeys) {
            cout << key;
            if (next(find(integerKeys.begin(), integerKeys.end(), key)) != integerKeys.end()) {
                cout << ", ";
            }
        }
        cout << '\n';
    }

    if (coutreal) {
    cout << "REALS:" << endl;
    for (auto it = reals.begin(); it != reals.end(); it++) {
        if (it->first[0] == '.' && it->first.size() > 1) {
            cout << "0";
        }
        cout << it->first;
        if (next(it) != reals.end()) {
            cout << ", ";
        }
    }
    cout << endl;
}


    if (coutstr) {
    cout << "STRINGS:" << endl;
    bool firstString = true;  

    for (const auto& pair : strings) {
        if (!firstString) {
            cout << ", ";
        } else {
            firstString = false;
        }

        cout << "\"" << pair.first << "\"";
    }

    cout << endl;
}
    return 0;       
}

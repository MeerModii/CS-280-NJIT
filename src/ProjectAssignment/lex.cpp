#include "lex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string> 

ostream& operator << (ostream& out, const LexItem& tok) {
    out << "Token: " << tok.GetToken() << ", Lexeme: " << tok.GetLexeme() << ", Line: " << tok.GetLinenum();
    return out;
}
extern LexItem id_or_kw(const string& lexeme, int linenum){
    
}
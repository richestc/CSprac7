#include <iostream>
#include <list>

#include "CompilerParser.h"
#include "Token.h"

using namespace std;

int main(int argc, char *argv[]) {
    /* Tokens for:
     *     class MyClass {
     *
     *     }
     */
    list<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "MyClass"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));

    try {
        CompilerParser parser(tokens);
        ParseTree* result = parser.compileProgram();
        if (result != NULL){
            cout << result->tostring() << endl;
        }
    } catch (ParseException e) {
        cout << "Error Parsing!" << endl;
    }

    //CMPClass test
    //list<Token*> CMPClass;
    //CMPClass.push_back(new Token("keyword", "class"));
    //CMPClass.push_back(new Token("identifier", "MyClass"));
    //CMPClass.push_back(new Token("symbol", "{"));
    //CMPClass.push_back(new Token("symbol", "}"));

    //CMPVarDec test
    //list<Token*> CMPVarDec;
    //CMPVarDec.push_back(new Token("keyword", "var"));
    //CMPVarDec.push_back(new Token("keyword", "int"));
    //CMPVarDec.push_back(new Token("identifier", "a"));
    //CMPVarDec.push_back(new Token("symbol", ";"));

}
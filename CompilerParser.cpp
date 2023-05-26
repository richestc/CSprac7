#include "CompilerParser.h"


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    return compileClass();
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    // 'class' className '{' classVarDec* subroutokenListeDec* '}'

    ParseTree* compileClass = new ParseTree("compileClass","");

    //adding class
    if(tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "class"){
            ParseTree* temp1 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileClass->addChild(temp1);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //adding className
    if(tokenList.front()->getType() == "identifier"){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileClass->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException();
    }

    //adding {
    if(tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "{"){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileClass->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException();
    }

    //adding classVarDec* or subRoutineDec* --> while loop due to '*'
    while(tokenList.front()->getValue() != "}" && (tokenList.size() > 0)){

        //classVarDec*
        if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "static" ||
            tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "field"){
            compileClass->addChild(compileClassVarDec());
        }
        //subRoutineDec*
        else if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "constructor") ||
                (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "function") ||
                (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "method")){
                    compileClass->addChild(compileSubroutine());
                }
        else if(tokenList.front()->getType() != "symbol" && tokenList.front()->getValue() != "}"){
            throw ParseException();
        }
    }

    //adding }
    if(tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "}"){
        ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
        compileClass->addChild(temp3);
        tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException();
    }
    return compileClass;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    // ('static'|'field') type varName(',' varName)*';'

    ParseTree* compileClassVarDec = new ParseTree("compileClassVarDec","");

    //add static or field
    if(tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "static")
        ||(tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "field"){
            ParseTree* temp1 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileClassVarDec->addChild(temp1);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }
    
    //add type
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean" 
    || tokenList.front()->getType() == "identifier"){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileClassVarDec->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //add varName
    if(tokenList.front()->getType() == "identifier"){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileClassVarDec->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //add (','varName)*
    while(tokenList.front()->getValue() != ";" && (tokenList.size() > 0)){

        //(','varName)*
        if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ","
            && tokenList.front()->getType() == "identifier"){
            compileClassVarDec->addChild(compileClassVarDec());
        }
        else if(tokenList.front()->getType() != "symbol" && tokenList.front()->getValue() != ";"){
            throw ParseException();
        }
    }

    //add ';'
    if(tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ";"){
            ParseTree* temp4 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileClassVarDec->addChild(temp4);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }
    return compileClassVarDec;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* compileSubroutine = new ParseTree("compileSubroutine","");
        //add 'constructor' | 'function' | 'method'
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "constructor" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "function" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "method" ){
            ParseTree* temp1 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileSubroutine->addChild(temp1);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //add void | type
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "void" 

    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean" 
    || tokenList.front()->getType() == "identifier"){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileSubroutine->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //add subRoutineName
    if(tokenList.front()->getType() == "identifier"){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileSubroutine->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //add '('
    if(tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "("){
            ParseTree* temp4 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileSubroutine->addChild(temp4);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //add parameterList

    //add type varName
    if((tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean" 
    || tokenList.front()->getType() == "identifier")
    
    && tokenList.front()->getType() == "identifier"){
            ParseTree* temp5 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileSubroutine->addChild(temp5);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //add ()',' type varName)*
    while(tokenList.front()->getValue() != (tokenList.front()->getType() == "stringConstant") && (tokenList.size() > 0)){

        //(','varName)*
        if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ","
            && (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int" 
            || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char" 
            || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean" 
            || tokenList.front()->getType() == "identifier")
            && (tokenList.front()->getType() == "identifier")) {
            compileClass->addChild(compileSubroutine());
        }
        else if(tokenList.front()->getType() != "symbol" && tokenList.front()->getValue() != ","){
            throw ParseException();
        }
    }

    //add ?

    if(tokenList.front()->getType() == "stringConstant"){
        ParseTree* temp6 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
        compileSubroutine->addChild(temp6);
        tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    return compileSubroutine;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* compileVarDec = new ParseTree("compileVarName","");

    //var
    if(tokenList.front()->getType() == "keyword" && token.front()->getValue() = "var"){
            ParseTree* temp1 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileVarDec->addChild(temp1);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //type
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char" 
    || tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean" 
    || tokenList.front()->getType() == "identifier"){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileVarDec->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //varName
    if( tokenList.front()->getType() == "identifier"){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileVarDec->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //(','varName)*

    while( tokenList.front()->getType() != "symbol" && tokenList.front()->getValue() != ";" ){

        if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ","
            || tokenList.front()->getType() == "identifier"){
                ParseTree* temp4 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
                compileVarDec->addChild(temp4);
                tokenList.erase(tokenList.begin());
        }
        else{
            throw ParseException(); //parseError
        }
    }

    //;
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ";"){
            ParseTree* temp5 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            compileVarDec->addChild(temp5);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }
 

}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    return NULL;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    return NULL;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
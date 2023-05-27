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
    return NULL;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree* CMPClass = new ParseTree("CMPClass","");

    //class
    if(tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "class"){
            ParseTree* temp1 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPClass->addChild(temp1);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //className
    if( tokenList.front()->getType() == "identifier"){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPClass->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }
    
    //{
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "{"){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPClass->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    // (classVarDec)* (subroutineDec)*
    while( tokenList.front()->getType() != "symbol" && tokenList.front()->getValue() != "}" ){

        if(tokenList.size() <= 1){
            break;
        }

        if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "static") 
            || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "field") ){

            CMPClass->addChild( compileClassVarDec() );

        }
        else if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "constructor") 
            || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "function")
            || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "method") ){

            CMPClass->addChild( compileSubroutine() );
        }

        else if(tokenList.front()->getType() != "symbol" && tokenList.front()->getValue() != "}"){
            //throw std::invalid_argument( "Error in parsing: 04" + tIn.front()->getType() + "  " + tIn.front()->getValue());
            throw ParseException();
        }     
        else{
            throw ParseException(); //parseError
        }
    }

    //}
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "}"){
            ParseTree* temp4 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPClass->addChild(temp4);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    return CMPClass;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {

    //ParseTree* CMPClassVarDec = new ParseTree("CMPClassVarDec","");

    //static or field 
    //CMPClassVarDec->addChild(tokenList.front()->getType(), tokenList.front()->getValue() );
    //tokenList.next();

    //type

    return NULL;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    return NULL;
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
    ParseTree* CMPVarDec = new ParseTree("CMPVarDec","");

    //var
    if(tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "var"){
            ParseTree* temp1 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPVarDec->addChild(temp1);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //type
    if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int") 
    || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char") 
    || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean") 
    || (tokenList.front()->getType() == "identifier")){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPVarDec->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //varName
    if( tokenList.front()->getType() == "identifier"){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPVarDec->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //(','varName)*

    while( tokenList.front()->getType() != "symbol" && tokenList.front()->getValue() != ";" ){

        if(tokenList.size() <= 1){
            break;
        }

        if( (tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ",")
            || (tokenList.front()->getType() == "identifier") ){
                ParseTree* temp4 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
                CMPVarDec->addChild(temp4);
                tokenList.erase(tokenList.begin());
        }
        else{
            throw ParseException(); //parseError
        }
    }

    //;
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ";"){
            ParseTree* temp5 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPVarDec->addChild(temp5);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    return CMPVarDec;
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

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

    ParseTree* CMPClassVarDec = new ParseTree("CMPClassVarDec","");

    //static or field 
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPClassVarDec->addChild(temp1);
    tokenList.erase(tokenList.begin());
    //tokenList.next(); ???

    //type
    if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int") 
    || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char") 
    || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean") 
    || (tokenList.front()->getType() == "identifier")){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPClassVarDec->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //varName
    if( tokenList.front()->getType() == "identifier"){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPClassVarDec->addChild(temp3);
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
                CMPClassVarDec->addChild(temp4);
                tokenList.erase(tokenList.begin());
        }
        else{
            throw ParseException(); //parseError
        }
    }

    //;
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ";"){
            ParseTree* temp5 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPClassVarDec->addChild(temp5);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    return CMPClassVarDec;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* CMPSubroutine = new ParseTree("CMPSubroutine","");

    //constructor/function/method
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPSubroutine->addChild(temp1);
    tokenList.erase(tokenList.begin());

    //void/type
    if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "void") ||
     ((tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int") 
    || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char") 
    || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean") 
    || (tokenList.front()->getType() == "identifier")) ){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPSubroutine->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //subroutineName
    if( (tokenList.front()->getType() == "identifier") ){
            ParseTree* temp4 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPSubroutine->addChild(temp4);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //(
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "(" ){
            ParseTree* temp5 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPSubroutine->addChild(temp5);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //parameterList
    if( ((tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int") 
    || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char") 
    || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean") 
    || (tokenList.front()->getType() == "identifier"))  ||
    ((tokenList.front()->getType() == "identifier")) ){
            CMPSubroutine->addChild( compileParameterList() );
    }
    else{
        throw ParseException(); //parseError
    }
    
    //)
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ")" ){
            ParseTree* temp6 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPSubroutine->addChild(temp6);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //subroutineBody
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "{" ){
            CMPSubroutine->addChild( compileSubroutineBody() );
    }
    else{
        throw ParseException(); //parseError
    }
    
    return CMPSubroutine;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* CMPParameterList = new ParseTree("CMPParameterList","");

    //(type varName)
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPParameterList->addChild(temp1);
    tokenList.erase(tokenList.begin());

    //(',' type varName)*?
    while( !tokenList.empty() ){

        if(tokenList.size() <= 1){
            break;
        }

        if( (tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ",") ||
        ((tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "int") 
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "char") 
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "boolean") 
        || (tokenList.front()->getType() == "identifier")) ||
        ((tokenList.front()->getType() == "identifier")) ){
                ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
                CMPParameterList->addChild(temp2);
                tokenList.erase(tokenList.begin());
        }
        else{
            throw ParseException(); //parseError
        }

    //?
    if( tokenList.front()->getType() == "stringConstant" && tokenList.front()->getValue() == "?" ){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPParameterList->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }
    
    }

    return CMPParameterList;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* CMPSubroutineBody = new ParseTree("CMPSubroutineBody","");

    //{
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPSubroutineBody->addChild(temp1);
    tokenList.erase(tokenList.begin());

    //varDec*
    while( tokenList.front()->getType() != "symbol" && tokenList.front()->getValue() != "}" ){

        if(tokenList.size() <= 1){
            break;
        }

        if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "var" ){
                CMPSubroutineBody->addChild( compileVarDec() );
        }
        else{
            throw ParseException(); //parseError
        }
    }

    //statements
    if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "let")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "if")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "while")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "do")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "return") ){
            CMPSubroutineBody->addChild( compileStatements() );
    }
    else{
        throw ParseException(); //parseError
    }

    //}
    if(tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "}"){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPSubroutineBody->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    return CMPSubroutineBody;
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
    ParseTree* CMPStatements = new ParseTree("CMPStatements","");

    //
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPStatements->addChild(temp1);
    tokenList.erase(tokenList.begin());

    //letStatement
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "let"){
            CMPStatements->addChild( compileLet() );
    }
    else{
        throw ParseException(); //parseError
    }

    //ifStatement
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "if"){
            CMPStatements->addChild( compileIf() );
    }
    else{
        throw ParseException(); //parseError
    }

    //whileStatement
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "while"){
            CMPStatements->addChild( compileWhile() );
    }
    else{
        throw ParseException(); //parseError
    }

    //doStatement
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "do"){
            CMPStatements->addChild( compileDo() );
    }
    else{
        throw ParseException(); //parseError
    }

    //returnStatement
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "return"){
            CMPStatements->addChild( compileReturn() );
    }
    else{
        throw ParseException(); //parseError
    }

    return CMPStatements;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* CMPLet = new ParseTree("CMPLet","");

    //let
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPLet->addChild(temp1);
    tokenList.erase(tokenList.begin());

    //varName
    if( tokenList.front()->getType() == "identifier"){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPLet->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //[
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "[" ){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPLet->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //expression
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "skip" ){
            CMPLet->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    //]
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "]" ){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPLet->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //=
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "=" ){
            ParseTree* temp4 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPLet->addChild(temp4);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //expression
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "skip" ){
            CMPLet->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    //;
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ";" ){
            ParseTree* temp5 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPLet->addChild(temp5);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }


    return CMPLet;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* CMPIf = new ParseTree("CMPIf","");

    //if
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPIf->addChild(temp1);
    tokenList.erase(tokenList.begin());

    //(
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "(" ){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPIf->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //expression
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "skip" ){
            CMPIf->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    //)
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ")" ){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPIf->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //{
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "{" ){
            ParseTree* temp4 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPIf->addChild(temp4);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //statements
    if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "let")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "if")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "while")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "do")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "return") ){
            CMPIf->addChild( compileStatements() );
    }
    else{
        throw ParseException(); //parseError
    }


    //}
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "}" ){
            ParseTree* temp5 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPIf->addChild(temp5);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //(
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "(" ){
            ParseTree* temp6 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPIf->addChild(temp6);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //else
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "else" ){
            ParseTree* temp7 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPIf->addChild(temp7);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //{
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "{" ){
            ParseTree* temp8 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPIf->addChild(temp8);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //statements
    if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "let")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "if")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "while")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "do")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "return") ){
            CMPIf->addChild( compileStatements() );
    }
    else{
        throw ParseException(); //parseError
    }

    //}
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "}" ){
            ParseTree* temp9 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPIf->addChild(temp9);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    return CMPIf;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* CMPWhile = new ParseTree("CMPWhile","");

    //while
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPWhile->addChild(temp1);
    tokenList.erase(tokenList.begin());

    //(
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "(" ){
            ParseTree* temp2 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPWhile->addChild(temp2);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //expression
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "skip" ){
            CMPWhile->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    //)
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ")" ){
            ParseTree* temp3 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPWhile->addChild(temp3);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //{
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "{" ){
            ParseTree* temp4 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPWhile->addChild(temp4);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    //statement
    if( (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "let")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "if")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "while")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "do")
        || (tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "return") ){
            CMPWhile->addChild( compileStatements() );
    }
    else{
        throw ParseException(); //parseError
    }

    //}
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "}" ){
            ParseTree* temp5 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPWhile->addChild(temp5);
            tokenList.erase(tokenList.begin());
    }
    else{
        throw ParseException(); //parseError
    }

    return CMPWhile;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* CMPDo = new ParseTree("CMPDo","");

    //do
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPDo->addChild(temp1);
    tokenList.erase(tokenList.begin());

    //expression
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "skip" ){
            CMPDo->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    //;
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ";" ){
            CMPDo->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    return CMPDo;
}


/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* CMPReturn = new ParseTree("CMPReturn","");

    //return
    ParseTree* temp1 = new ParseTree(tokenList.front()->getType(), tokenList.front()->getValue());
    CMPReturn->addChild(temp1);
    tokenList.erase(tokenList.begin());

    //expression
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "skip" ){
            CMPReturn->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    //;
    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == ";" ){
            CMPReturn->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    return CMPReturn;
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
    ParseTree* CMPExpressionList = new ParseTree("CMPExpressionList","");

    //expression
    if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "skip" ){
            CMPExpressionList->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    //(',')expression
    while( tokenList.front()->getType() != "symbol" && tokenList.front()->getValue() != ";" ){

    if(tokenList.size() <= 1){
            break;
    }

    if( tokenList.front()->getType() == "symbol" && tokenList.front()->getValue() == "," ){
            ParseTree* temp1 = new ParseTree(tokenList.front()->getType(),tokenList.front()->getValue());
            CMPExpressionList->addChild(temp1);
            tokenList.erase(tokenList.begin());
    }
    else if( tokenList.front()->getType() == "keyword" && tokenList.front()->getValue() == "skip" ){
            CMPExpressionList->addChild( compileExpression() );
    }
    else{
        throw ParseException(); //parseError
    }

    }


    return CMPExpressionList;
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

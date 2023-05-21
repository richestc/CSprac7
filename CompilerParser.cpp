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
    // Example implementation for parsing a class
    ParseTree* classNode = new ParseTree("Class", "");

    mustBe("Keyword", "class"); // Check if the current token is "class"
    Token* className = mustBe("Identifier", ""); // Get the class name
    mustBe("Symbol", "{"); // Check if the current token is "{"

    // Parse classVarDec if present
    while (have("Keyword", "static") || have("Keyword", "field")) {
        ParseTree* classVarDecNode = compileClassVarDec();
        classNode->addChild(classVarDecNode);
    }

    // Parse subroutineDec if present
    while (have("Keyword", "constructor") || have("Keyword", "function") || have("Keyword", "method")) {
        ParseTree* subroutineDecNode = compileSubroutine();
        classNode->addChild(subroutineDecNode);
    }

    mustBe("Symbol", "}"); // Check if the current token is "}"

    return classNode;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    // Example implementation for parsing a class variable declaration
    ParseTree* classVarDecNode = new ParseTree("ClassVarDec", "");

    // Parse static or field
    if (have("Keyword", "static")) {
        mustBe("Keyword", "static");
    } else if (have("Keyword", "field")) {
        mustBe("Keyword", "field");
    }

    // Parse type
    Token* type = mustBe("Identifier", ""); // Assuming type is an identifier

    // Parse variable names
    Token* varName = mustBe("Identifier", "");
    classVarDecNode->addChild(new ParseTree("Type", type->getValue()));
    classVarDecNode->addChild(new ParseTree("VarName", varName->getValue()));

    // Parse additional variable names if present
    while (have("Symbol", ",")) {
        mustBe("Symbol", ",");
        varName = mustBe("Identifier", "");
        classVarDecNode->addChild(new ParseTree("VarName", varName->getValue()));
    }

    mustBe("Symbol", ";"); // Check if the current token is ";"

    return classVarDecNode;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    // Example implementation for parsing a subroutine
    ParseTree* subroutineNode = new ParseTree("Subroutine", "");

    // Parse constructor, function, or method
    if (have("Keyword", "constructor")) {
        mustBe("Keyword", "constructor");
    } else if (have("Keyword", "function")) {
        mustBe("Keyword", "function");
    } else if (have("Keyword", "method")) {
        mustBe("Keyword", "method");
    }

    // Parse return type
    Token* returnType = mustBe("Identifier", ""); // Assuming return type is an identifier

    // Parse subroutine name
    Token* subroutineName = mustBe("Identifier", "");

    mustBe("Symbol", "("); // Check if the current token is "("

    // Parse parameter list
    ParseTree* parameterListNode = compileParameterList();
    subroutineNode->addChild(parameterListNode);

    mustBe("Symbol", ")"); // Check if the current token is ")"

    // Parse subroutine body
    ParseTree* subroutineBodyNode = compileSubroutineBody();
    subroutineNode->addChild(subroutineBodyNode);

    return subroutineNode;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    // Example implementation for parsing a parameter list
    ParseTree* parameterListNode = new ParseTree("ParameterList", "");

    // Check if the parameter list is empty
    if (have("Symbol", ")")) {
        // Empty parameter list, return the empty node
        return parameterListNode;
    }

    // Parse first parameter
    Token* type = mustBe("Identifier", ""); // Assuming type is an identifier
    Token* varName = mustBe("Identifier", "");
    parameterListNode->addChild(new ParseTree("Type", type->getValue()));
    parameterListNode->addChild(new ParseTree("VarName", varName->getValue()));

    // Parse additional parameters if present
    while (have("Symbol", ",")) {
        mustBe("Symbol", ",");
        type = mustBe("Identifier", ""); // Assuming type is an identifier
        varName = mustBe("Identifier", "");
        parameterListNode->addChild(new ParseTree("Type", type->getValue()));
        parameterListNode->addChild(new ParseTree("VarName", varName->getValue()));
    }

    return parameterListNode;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    // Example implementation for parsing a subroutine body
    ParseTree* subroutineBodyNode = new ParseTree("SubroutineBody", "");

    mustBe("Symbol", "{"); // Check if the current token is "{"

    // Parse variable declarations
    ParseTree* varDecNode = compileVarDec();
    if (varDecNode != nullptr) {
        subroutineBodyNode->addChild(varDecNode);
    }

    // Parse statements
    ParseTree* statementsNode = compileStatements();
    subroutineBodyNode->addChild(statementsNode);

    mustBe("Symbol", "}"); // Check if the current token is "}"

    return subroutineBodyNode;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    // Example implementation for parsing a variable declaration
    ParseTree* varDecNode = nullptr;

    // Check if the current token is a variable declaration
    if (have("Keyword", "var")) {
        varDecNode = new ParseTree("VarDec", "");

        mustBe("Keyword", "var"); // Check if the current token is "var"

        // Parse variable type
        Token* type = mustBe("Identifier", ""); // Assuming type is an identifier
        varDecNode->addChild(new ParseTree("Type", type->getValue()));

        // Parse variable names
        Token* varName = mustBe("Identifier", "");
        varDecNode->addChild(new ParseTree("VarName", varName->getValue()));

        // Parse additional variable names if present
        while (have("Symbol", ",")) {
            mustBe("Symbol", ",");
            varName = mustBe("Identifier", "");
            varDecNode->addChild(new ParseTree("VarName", varName->getValue()));
        }

        mustBe("Symbol", ";"); // Check if the current token is ";"
    }

    return varDecNode;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    // Example implementation for parsing a series of statements
    ParseTree* statementsNode = new ParseTree("Statements", "");

    // Parse statements until a non-statement token is encountered
    while (true) {
        if (have("Keyword", "let")) {
            ParseTree* letStatementNode = compileLet();
            statementsNode->addChild(letStatementNode);
        } else if (have("Keyword", "if")) {
            ParseTree* ifStatementNode = compileIf();
            statementsNode->addChild(ifStatementNode);
        } else if (have("Keyword", "while")) {
            ParseTree* whileStatementNode = compileWhile();
            statementsNode->addChild(whileStatementNode);
        } else if (have("Keyword", "do")) {
            ParseTree* doStatementNode = compileDo();
            statementsNode->addChild(doStatementNode);
        } else if (have("Keyword", "return")) {
            ParseTree* returnStatementNode = compileReturn();
            statementsNode->addChild(returnStatementNode);
        } else {
            break;  // Not a statement, exit the loop
        }
    }

    return statementsNode;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    // Example implementation for parsing a let statement
    ParseTree* letStatementNode = new ParseTree("LetStatement", "");

    mustBe("Keyword", "let"); // Check if the current token is "let"

    // Parse variable name
    Token* varName = mustBe("Identifier", "");
    letStatementNode->addChild(new ParseTree("VarName", varName->getValue()));

    // Check if there is an array index
    if (have("Symbol", "[")) {
        mustBe("Symbol", "["); // Check if the current token is "["
        ParseTree* arrayIndexNode = compileExpression();
        letStatementNode->addChild(arrayIndexNode);
        mustBe("Symbol", "]"); // Check if the current token is "]"
    }

    mustBe("Symbol", "="); // Check if the current token is "="

    // Parse expression
    ParseTree* expressionNode = compileExpression();
    letStatementNode->addChild(expressionNode);

    mustBe("Symbol", ";"); // Check if the current token is ";"

    return letStatementNode;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    // Example implementation for parsing an if statement
    ParseTree* ifStatementNode = new ParseTree("IfStatement", "");

    mustBe("Keyword", "if"); // Check if the current token is "if"
    mustBe("Symbol", "("); // Check if the current token is "("

    // Parse condition expression
    ParseTree* conditionNode = compileExpression();
    ifStatementNode->addChild(conditionNode);

    mustBe("Symbol", ")"); // Check if the current token is ")"
    mustBe("Symbol", "{"); // Check if the current token is "{"

    // Parse if body statements
    ParseTree* ifBodyNode = compileStatements();
    ifStatementNode->addChild(ifBodyNode);

    mustBe("Symbol", "}"); // Check if the current token is "}"

    // Check if there is an else clause
    if (have("Keyword", "else")) {
        mustBe("Keyword", "else"); // Check if the current token is "else"
        mustBe("Symbol", "{"); // Check if the current token is "{"

        // Parse else body statements
        ParseTree* elseBodyNode = compileStatements();
        ifStatementNode->addChild(elseBodyNode);

        mustBe("Symbol", "}"); // Check if the current token is "}"
    }

    return ifStatementNode;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    // Example implementation for parsing a while statement
    ParseTree* whileStatementNode = new ParseTree("WhileStatement", "");

    mustBe("Keyword", "while"); // Check if the current token is "while"
    mustBe("Symbol", "("); // Check if the current token is "("

    // Parse condition expression
    ParseTree* conditionNode = compileExpression();
    whileStatementNode->addChild(conditionNode);

    mustBe("Symbol", ")"); // Check if the current token is ")"
    mustBe("Symbol", "{"); // Check if the current token is "{"

    // Parse while body statements
    ParseTree* whileBodyNode = compileStatements();
    whileStatementNode->addChild(whileBodyNode);

    mustBe("Symbol", "}"); // Check if the current token is "}"

    return whileStatementNode;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    // Example implementation for parsing a do statement
    ParseTree* doStatementNode = new ParseTree("DoStatement", "");

    mustBe("Keyword", "do"); // Check if the current token is "do"

    // Parse subroutine call
    ParseTree* subroutineCallNode = compileSubroutineCall();
    doStatementNode->addChild(subroutineCallNode);

    mustBe("Symbol", ";"); // Check if the current token is ";"

    return doStatementNode;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    // Example implementation for parsing a return statement
    ParseTree* returnStatementNode = new ParseTree("ReturnStatement", "");

    mustBe("Keyword", "return"); // Check if the current token is "return"

    // Check if there is an expression to return
    if (!have("Symbol", ";")) {
        // Parse expression
        ParseTree* expressionNode = compileExpression();
        returnStatementNode->addChild(expressionNode);
    }

    mustBe("Symbol", ";"); // Check if the current token is ";"

    return returnStatementNode;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    // Example implementation for parsing an expression
    ParseTree* expressionNode = new ParseTree("Expression", "");

    // Parse the first term
    ParseTree* termNode = compileTerm();
    expressionNode->addChild(termNode);

    // Parse any additional terms and operators
    while (have("Symbol", "+") || have("Symbol", "-") || have("Symbol", "*") || have("Symbol", "/") || have("Symbol", "&") || have("Symbol", "|") || have("Symbol", "<") || have("Symbol", ">") || have("Symbol", "=")) {
        // Parse the operator
        ParseTree* operatorNode = new ParseTree("Operator", current()->getValue());
        expressionNode->addChild(operatorNode);
        next();

        // Parse the next term
        ParseTree* nextTermNode = compileTerm();
        expressionNode->addChild(nextTermNode);
    }

    return expressionNode;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    ParseTree* termNode = new ParseTree("Term", "");

    if (have("IntegerConstant", "") || have("StringConstant", "") || have("Keyword", "true") || have("Keyword", "false") || have("Keyword", "null") || have("Keyword", "this")) {
        // Parse a constant value
        termNode->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();
    } else if (have("Identifier", "")) {
        if (have("Symbol", "[")) {
            // Parse an array index expression
            termNode->addChild(new ParseTree("ArrayIndexExpression", ""));
            termNode->addChild(new ParseTree(current()->getType(), current()->getValue()));
            next();
            mustBe("Symbol", "[");
            termNode->addChild(compileExpression());
            mustBe("Symbol", "]");
        } else if (have("Symbol", "(") || have("Symbol", ".")) {
            // Parse a subroutine call
            termNode->addChild(compileSubroutineCall());
        } else {
            // Parse a variable reference
            termNode->addChild(new ParseTree("VariableReference", ""));
            termNode->addChild(new ParseTree(current()->getType(), current()->getValue()));
            next();
        }
    } else if (have("Symbol", "(")) {
        // Parse an expression within parentheses
        mustBe("Symbol", "(");
        termNode->addChild(compileExpression());
        mustBe("Symbol", ")");
    } else if (have("Symbol", "-") || have("Symbol", "~")) {
        // Parse a unary operation
        termNode->addChild(new ParseTree("UnaryOperation", current()->getValue()));
        next();
        termNode->addChild(compileTerm());
    } else {
        // Invalid term
        throw ParseException();
    }

    return termNode;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    // Example implementation for parsing an expression list
    ParseTree* expressionListNode = new ParseTree("ExpressionList", "");

    // Check if the expression list is not empty
    if (!have("Symbol", ")")) {
        // Parse the first expression
        ParseTree* expressionNode = compileExpression();
        expressionListNode->addChild(expressionNode);

        // Parse any additional expressions
        while (have("Symbol", ",")) {
            mustBe("Symbol", ","); // Check if the current token is ","
            ParseTree* nextExpressionNode = compileExpression();
            expressionListNode->addChild(nextExpressionNode);
        }
    }

    return expressionListNode;
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
    return *tokenIterator;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    if (tokenIterator != tokenList.end()) {
        Token* currentToken = *tokenIterator;
        std::string currentType = currentToken->getType();
        std::string currentValue = currentToken->getValue();

        // Compare the current token with the expected type and value
        if (currentType == expectedType && currentValue == expectedValue) {
            return true;
        }
    }

    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if (tokenIterator != tokenList.end()) {
        Token* currentToken = *tokenIterator;
        std::string currentType = currentToken->getType();
        std::string currentValue = currentToken->getValue();

        // Compare the current token with the expected type and value
        if (currentType == expectedType && currentValue == expectedValue) {
            // Advance to the next token
            next();
            // Return the current token
            return currentToken;
        }
    }

    // Throw a ParseException if the expected token is not found
    throw ParseException();
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}

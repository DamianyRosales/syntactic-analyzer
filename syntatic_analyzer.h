#include "filereader.h"
#include <stack>
#include <iostream>
#include <vector>
#include <cstring>
#include "semantic_analyzer.h"
using namespace std;

int searchIndexArray(string word, vector<string> array)
{
    for (int i = 0; i <= array.size(); i++)
    {
        if (word == array[i])
        {
            return i;
        }
    }
    return -1;
}

bool isTerminal(string word)
{
    int wordLength = word.length() - 1;
    if (word[0] == '<' && word[wordLength] == '>')
    {
        return false;
    }
    return true;
}

int oracle(int row, int column, int matrix[30][35])
{
    return matrix[row][column];
}

vector<string> split(string text, string delimiter)
{
    size_t pos = 0;
    string token;
    vector<string> myVector;
    while ((pos = text.find(delimiter)) != std::string::npos)
    {
        token = text.substr(0, pos);
        myVector.push_back(token);
        text.erase(0, pos + delimiter.length());
    }
    return myVector;
}

vector<string> getIndexesFromVector(int begin, int finish, vector<string> v)
{
    vector<string> res;
    for (int i = begin; i <= finish; i++)
    {
        res.push_back(v.at(i));
    }
    return res;
}

stack<string> putProductionInStack(string production, stack<string> stack)

{
    vector<string> productionSplit = split(production, " ");
    // Remove last production and push the new one
    stack.pop();
    if (productionSplit[0] != "€")
    {
        for (int i = 0; i < productionSplit.size(); i++)
        {
            stack.push(productionSplit[i]);
        }
    }
    return stack;
}

void exec_syntatic(SymbolTable tb)
{
    stack<string> stack;
    vector<string> arrayTokens = readFile("tokens.txt");

    // cout << "Tokens: " << endl;
    // for (int i = 0; i < arrayTokens.size(); i++)
    // {
    //     cout << arrayTokens[i] << endl;
    // }
    vector<string>
        nonTerms = {"<PROGRAM>", "<STATEMENT", "<S>", "<ST>", "<RO>", "<AO>", "<ASO>", "<DT>", "<VALUE>", "<ID>", "<VARIABLES>",
                    "<VARIABLES1>", "<SWITCH>", "<SWITCHBODY>", "<CASE>", "<IF>", "<COND>", "<ELSE>", "<WHILE>", "<FOR>", "<FORCOND>", "<FUNCTION>",
                    "<FUNCTIONPARAMS>", "<PARAMS>", "<DO>", "<EXPRESSION>", "<EXPRESSION1>", "<EXPRESSION2>", "<EXPRESSION3>", "<MASMASOMENOSMENOS>"};
    vector<string> terms = {";", "=", "id", ">", ">=", "<", "<=", "==", "!=", "+", "-", "/", "*", "%", "int", "float", "str", "int_v",
                            "float_v", "str_v", "switch", "case", "if", "else", "while", "do", "for", "function", "(", ")", "[", "]", "--", "++", "dif"};
    int matrix[30][35] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 3, 0, 2, 0, 5, 7, 4, 8, 0, 0, 0, 10, 0, 0, 10},
        {0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11, 11, 0, 0, 0, 11, 0, 11, 0, 11, 11, 11, 11, 0, 0, 0, 12, 0, 0, 12},
        {0, 0, 0, 13, 14, 15, 16, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 20, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 34, 34, 64, 64, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {37, 36, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 0, 0, 41},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 0, 51, 0, 0, 0, 51},
        {0, 0, 52, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 53, 0, 0, 0, 0, 53},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 56, 0, 0, 0, 0, 0, 0, 55, 55, 55, 55, 0, 0, 0, 0, 56, 56, 56, 0, 0, 0, 0, 0, 0, 0, 0, 57, 0, 0, 0, 0, 0, 0},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 60, 60, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 61, 0, 0, 0, 0, 61},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 58, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 58, 0, 0, 0, 9, 35, 0},
    };

    vector<string> productions = {
        "<ST> ",
        "<IF> ",
        "<SWITCH> ",
        "<FOR> ",
        "<WHILE> ",
        "<VARIABLES> ",
        "<DO> ",
        "<FUNCTION> ",
        "-- ",
        "€ ",
        "<ST> <S> ",
        "€ ",
        "> ",
        ">= ",
        "< ",
        "<= ",
        "== ",
        "!= ",
        "+ ",
        "- ",
        "/ ",
        "* ",
        "% ",
        "= ",
        "int ",
        "float ",
        "str ",
        "int_v ",
        "float_v ",
        "str_v ",
        "id ",
        "<EXPRESSION> ",
        "id ",
        "; <VARIABLES1> <ID> <DT> ",
        "++ ",
        "<VALUE> = ",
        "€ ",
        "<SWITCHBODY> ) <id> ( switch ",
        "} <CASE> { ",
        "} <ST> { <VALUE> case ",
        "€ ",
        "<ELSE> } <ST> { <COND> if ",
        ") <VALUE> <RO> <VALUE> ( ",
        "} <ST> { else ",
        "€ ",
        "} <ST> { <COND> while ",
        "} <ST> { <FORCOND> for ",
        ") <MASMASOMENOSMENOS> <ID> ; <VALUE> <RO> <ID> ; <VALUE> <ASO> <ID> ( ",
        "} <ST> { <FUNCTIONPARAMS> <ID> function ",
        ") <PARAMS> ( ",
        "€ ",
        "<PARAMS> <ID> ",
        "€ ",
        "; ) <COND> ( while } <ST> { do ",
        "; <EXPRESSION3> <AO> ",
        "<EXPRESSION1> <VALUE> ",
        ") <EXPRESSION> ( ",
        ") <EXPRESSION> ( ",
        "<EXPRESSION1> <VALUE> ",
        "<EXPRESSION> <AO> ",
        "€ ",
        "<EXPRESSION> ",
        "; <VARIABLES1> <ID> ",
        "; <VARIABLES1> <VALUE> ",

    };
    vector<string> arithmetic_symbols = {"-", "+", "*", "/"};

    stack.push("$");
    stack.push("<ST>");
    stack.push("<S>");

    int i = 0;
    int pointer = 0;
    bool isVariableDeclaration = 0, isArithmeticOp = 0;
    string dataTypeCheck = "";
    bool isSemanticError = 0;
    string previousValue = "", arithmeticOperator = "";
    while (pointer != arrayTokens.size())
    {
        // cout << "top-->" << stack.top() << ", pointer-->" << split(arrayTokens[pointer], ", ")[0] << endl;
        if (isTerminal(stack.top()))
        {
            // Is the next st an arithmetic operation
            if (stack.top() == ";" && searchIndexArray(split(arrayTokens[pointer], ", ")[0], arithmetic_symbols) != -1)
            {
                // cout << "ahh" << endl;
                stack = putProductionInStack(productions[54], stack);
                continue;
            }

            if (stack.top() == split(arrayTokens[pointer], ", ")[0])
            {

                // Check if a data type is specified in order to declare a variable
                if (searchIndexArray(stack.top(), getIndexesFromVector(14, 16, terms)) != -1)
                {
                    isVariableDeclaration = 1;
                    dataTypeCheck = stack.top();
                }

                if (searchIndexArray(stack.top(), getIndexesFromVector(9, 12, terms)) != -1)
                {
                    // cout << "Arithmetic operation " << endl;
                    isArithmeticOp = 1;
                    arithmeticOperator = stack.top();
                    if (isVariableDeclaration)
                    {
                        previousValue = arrayTokens[pointer - 3];
                    }
                    else
                        previousValue = arrayTokens[pointer - 1];
                    {
                    }
                }
                if (
                    searchIndexArray(stack.top(), getIndexesFromVector(2, 2, terms)) != -1 ||
                    searchIndexArray(stack.top(), getIndexesFromVector(17, 19, terms)) != -1) // Is it either id or value?
                {
                    if (searchIndexArray(stack.top(), getIndexesFromVector(2, 2, terms)) != -1)
                    {
                        if (!isVariableDeclared(split(arrayTokens[pointer] + ", ", ", ")[1], tb) && !isVariableDeclaration)
                        {
                            cout << "Variable " << split(arrayTokens[pointer] + ", ", ", ")[1] << " is not declared" << endl;
                            isSemanticError = 1;
                            break;
                        }
                    }
                    if (isArithmeticOp)
                    {
                        // Analyze left and right part of an arithmetic operation
                        isVariableDeclaration = 0;
                        vector<string> opParts = {previousValue, arrayTokens[pointer]};
                        vector<string> opPartsDtv;
                        for (int i = 0; i < opParts.size(); i++)
                        {
                            opParts[i] += ", ";
                            // Is it id?
                            if (searchIndexArray(split(opParts[i], ", ")[0], getIndexesFromVector(2, 2, terms)) != -1)
                            {
                                opPartsDtv.push_back(getPairTypeMatch(split(tb.find(split(opParts[i], ", ")[1]) + ", ", ", ")[1]));
                            }
                            else
                            {
                                opPartsDtv.push_back(split(opParts[i], ", ")[0]);
                            }
                        }
                        // cout << opPartsDtv[0] << " <-- and --> " << opPartsDtv[1] << endl;
                        if (!canBeArithmeticallyOperated(opPartsDtv[0], opPartsDtv[1], arithmeticOperator)) // Compare data type values of the operation parts
                        {
                            cout << "Type mismatch: Operation couldn't be done since one of the operands is incompatible." << endl;
                            cout << opPartsDtv[0] << " <-- error --> " << opPartsDtv[1] << endl;
                            isSemanticError = 1;
                            break;
                        }
                    }
                }
                // Verify mismatch in var declaration
                if (searchIndexArray(stack.top(), getIndexesFromVector(17, 19, terms)) != -1 && isVariableDeclaration)
                {
                    if (getPairTypeMatch(dataTypeCheck) != split(arrayTokens[pointer], ", ")[0])
                    {
                        cout << "Type mismatch: " << getPairTypeMatch(dataTypeCheck) << " was expected, but " << split(arrayTokens[pointer], ", ")[0] << " was given" << endl;
                        isSemanticError = 1;
                        break;
                    }
                    isVariableDeclaration = 0;
                }

                pointer++;
                stack.pop();
            }
            else
            {
                cout << "Se esperaba: " << stack.top() << endl;
                break;
            }
        }
        else // Non terminal elements block of code
        {
            // Remove last empty chars when there are any token
            if (arrayTokens[pointer] == "$, eof")
            {
                stack.pop();
                if (stack.top() == "$")
                    pointer++;
                continue;
            }
            // Search production in matrix by Oracle
            int productionNumber =
                oracle(
                    searchIndexArray(stack.top(), nonTerms),
                    searchIndexArray(split(arrayTokens[pointer], ", ")[0], terms),
                    matrix);
            // Was the production found?
            if (productionNumber != 0)
            {
                stack = putProductionInStack(productions[productionNumber - 1], stack);
            }
            else
            {
                cout << "Se esperaba: " << stack.top() << endl;
                break;
            }
        }
    } // end of while
    // Final validation
    if (!isSemanticError)
    {
        if (stack.top() == "$" && arrayTokens.size() == pointer)
        {
            cout << "Syntax is valid!" << endl;
        }
        else
        {
            cout << "Syntax is not valid" << endl;
        }
    }
    else
    {
        cout << "Error semantico" << endl;
    }
}

#include "filereader.h"
#include <stack>
#include <iostream>
#include <vector>
#include <cstring>
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

int oracle(int row, int column, int matrix[29][33])
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

int main()
{
    stack<string> stack;
    vector<string> arrayTokens = readFile("tokens.txt");
    arrayTokens.pop_back();
    // cout << "Tokens: " << endl;
    // for (int i = 0; i < arrayTokens.size(); i++)
    // {
    //     cout << arrayTokens[i] << endl;
    // }
    vector<string>
        nonTerms = {"<PROGRAM>", "<STATEMENT", "<S>", "<ST>", "<RO>", "<AO>", "<ASO>", "<DT>", "<VALUE>", "<ID>", "<VARIABLES>",
                    "<VARIABLES1>", "<SWITCH>", "<SWITCHBODY>", "<CASE>", "<IF>", "<COND>", "<ELSE>", "<WHILE>", "<FOR>", "<FORCOND>", "<FUNCTION>",
                    "<FUNCTIONPARAMS>", "<PARAMS>", "<DO>", "<EXPRESSION>", "<EXPRESSION1>", "<EXPRESSION2>", "<EXPRESSION3>"};
    vector<string> terms = {";", "=", "id", ">", ">=", "<", "<=", "==", "!=", "+", "-", "/", "*", "%", "int", "float", "str", "int_v",
                            "float_v", "str_v", "switch", "case", "if", "else", "while", "do", "for", "function", "(", ")", "[", "]", "dif"};
    int matrix[29][33] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 3, 0, 2, 0, 5, 7, 4, 8, 0, 0, 0, 10, 10},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11, 11, 0, 0, 0, 11, 0, 11, 0, 11, 11, 11, 11, 0, 0, 0, 12, 12},
        {0, 0, 0, 13, 14, 15, 16, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 20, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 41},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 0, 0, 0, 0, 0, 0, 0, 0, 45},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 0, 51, 0, 51},
        {0, 0, 52, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 53, 0, 0, 53},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 55, 55, 55, 55, 0, 0, 0, 0, 56, 56, 56, 0, 0, 0, 0, 0, 0, 0, 0, 57, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 61},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 58, 0, 0, 0, 0},
    };

    vector<string> productions = {"<ST> ", "<IF> ", "<SWITCH> ", "<FOR> ", "<WHILE> ", "<VARIABLES> ", "<DO> ", "<FUNCTION> ",
                                  "<EXPRESSION> ", "€ ", "<ST> <S> ", "<€> ", "> ", ">= ", "< ", "<= ", "== ", "!= ", "+ ", "- ", "/ ", "* ", "% ", "= ", "int ", "float ",
                                  "str ", "int_v ", "float_v ", "str_v ", "id ", "<EXPRESSION> ", "id ", "; <VARIABLES1> <ID> <DT> ", "<VALUE> = <ID> ",
                                  "<VALUE> = ", "€ ", "<SWITCHBODY> ) <id> ( switch ", "} <CASE> { ", "} <ST> { <VALUE> case ", "€ ", "<ELSE> } <ST> { <COND> if ",
                                  ") <VALUE> <RO> <VALUE> ( ", "} <ST> { else "};
    // cout<<nonTerms;

    stack.push("$");
    stack.push("<ST>");
    stack.push("<S>");

    // cout<<split(arrayTokens[0], ", ")[0];

    int i = 0;
    int pointer = 0;
    cout << arrayTokens.size() << endl;
    while (!stack.empty() && pointer != arrayTokens.size() + 1)
    {
        cout<<"-c---"<<arrayTokens[pointer]<<endl;

        if (isTerminal(stack.top()))
        {
            if (stack.top() == split(arrayTokens[pointer], ", ")[0])
            {
                cout << "HUBO MATCH PAPI " << stack.top() << endl;
                pointer++;
                stack.pop();
            }
            else
            {
                cout << "1 Se esperaba: " << stack.top() << endl;
                break;
            }
        }
        else
        {
            if (arrayTokens[pointer] == " " || arrayTokens[pointer] == "}"){
                stack.pop();
                pointer++;
            }
            int productionNumber =
                oracle(
                    searchIndexArray(stack.top(), nonTerms),
                    searchIndexArray(split(arrayTokens[pointer], ", ")[0], terms),
                    matrix);
            if (productionNumber != 0)
            {
                vector<string> productionSplit = split(productions[productionNumber - 1], " ");
                // Remove last production and push the new one
                stack.pop();
                for (int i = 0; i < productionSplit.size(); i++)
                {
                    stack.push(productionSplit[i]);
                }
            }
            else
            {
                cout << "2 Se esperaba: " << stack.top() << endl;
                break;
            }
        }
    } // end of while
    cout << "top" << stack.top() << endl;
    cout << "-------------------" << arrayTokens[pointer] << endl;
    if (stack.top() == "$" && (arrayTokens.size() - 1) == pointer)
    {
        cout << "Syntax is valid!" << endl;
    }
    else
    {
        cout << "Syntax is not valid" << endl;
    }
}

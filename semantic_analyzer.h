#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include "symbol_table.h"
using namespace std;

map<string, string> pairTypeMatch{{"int", "int_v"}, {"float", "float_v"}, {"str", "str_v"}};

string getPairTypeMatch(string first)
{
    map<string, string>::iterator it = pairTypeMatch.find(first);
    if (it != pairTypeMatch.end())
    {
        return pairTypeMatch.find(first)->second;
    }
    return "";
}
void exec_semantic(SymbolTable tb)
{
    // while ()
    // {
    // }
    string semanticResult = getPairTypeMatch("str");
    string dataType = "str_v";
    if (semanticResult == dataType)
    {
        cout << "Hubo match" << endl;
    }
    else
    {
        cout << "data type " << dataType << " was found, but " << semanticResult << " was expected" << endl;
    }
}
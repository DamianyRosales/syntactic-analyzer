#include <iostream>
#include <string.h>
#include <vector>
#include <map>

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

bool isNumberDt(string dt)
{
    if (dt == "int_v" || dt == "float_v")
    {
        return true;
    }
    return false;
}

bool canBeArithmeticallyOperated(string opPartOne, string opPartTwo, string operatorSymbol)
{
    if (isNumberDt(opPartOne) && isNumberDt(opPartTwo))
        return true;
    if ((opPartOne == "str_v" && operatorSymbol == "+") ||
        opPartOne == "str_v" && opPartTwo == "str_v" && operatorSymbol == "+")
        return true;
    return false;
}

bool isVariableDeclared(string id, SymbolTable tb)
{
    if (tb.find(id) != "-1")
    {
        return true;
    }
    return false;
}
// void exec_semantic(SymbolTable tb)
// {
//     // while ()
//     // {
//     // }
//     string semanticResult = getPairTypeMatch("str");
//     string dataType = "str_v";
//     if (semanticResult == dataType)
//     {
//         cout << "Hubo match" << endl;
//     }
//     else
//     {
//         cout << "data type " << dataType << " was found, but " << semanticResult << " was expected" << endl;
//     }
// }
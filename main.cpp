#include <iostream>
#include "symbol_table.h"
#include "syntatic_analyzer.h"

using namespace std;
int main()
{
    SymbolTable stb = SymbolTable();
    stb.insert("num", "var", "int");
    exec_syntatic(stb);
}
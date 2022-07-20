#include <iostream>
#include "symbol_table.h"
#include "syntatic_analyzer.h"
#include "code_generator.h"

using namespace std;
int main()
{
    SymbolTable stb = SymbolTable();
    stb.insert("print", "func", "void");
    stb.insert("println", "func", "void");
    stb.insert("sayHello", "func", "void");
    stb.insert("id", "var", "int");
    stb.insert("newNum", "var", "int");
    stb.insert("name", "var", "str");
    bool isAnError = exec_syntatic(stb);
    if (!isAnError)
    {
        string newFileName = generateCode(stb);
        compileCodeGenerated(newFileName);
    }
    exit(1);
}
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"

using namespace std;
string getPreBuiltFuncBody(string funcName, vector<string> funcParams)
{
    if (funcName == "print")
    {
        return "cout << " + funcParams[0] + "";
    }
    if (funcName == "println")
    {
        return "cout << " + funcParams[0] + " << endl";
    }
    return "";
}

void insertToken(ofstream &file, string word)
{
    ofstream *newCppFile = &file;
    if (word == "{" || word == "}" || word == ";")
    {
        file << " " << word << " " << endl;
    }
    else
    {
        file << " " << word << " ";
    }
}

int insertPreBuiltFunction(ofstream &file, string funcName, vector<string> tokens, int pointer)
{
    ofstream *newCppFile = &file;
    vector<string> funcParams;
    pointer += 1;
    while (split(tokens[pointer] + ", ", ", ")[1] != ")")
    {
        funcParams.push_back(split(tokens[pointer + 1] + ", ", ", ")[1]);
        pointer++;
    }
    file << getPreBuiltFuncBody(funcName, funcParams);
    return pointer;
}

void compileCodeGenerated(string file)
{
    cout << "compiling..." << endl;
    string command = "g++ ./" + file + " -o ./compiled.exe";
    char cmd[200];
    strcpy(cmd, command.c_str());
    system(cmd);
}

string generateCode(SymbolTable tb)
{
    vector<string> ro_basic_symbols = {">", "<", "=", "!"};
    string fileName = "compiled.cpp";
    vector<string> preBuiltFuncsNames = {"print", "println"};
    int pointer = 0;
    vector<string> tokens = getTokensFromFile("tokens.txt");
    ofstream newCppFile{fileName, ios::out};
    bool isFuncDeclaration = 0;
    string word;

    if (!newCppFile)
    {
        cout << "Error al abrir "
             << fileName << endl;
        exit(EXIT_FAILURE);
    }
    newCppFile << " #include <iostream> " << endl;
    newCppFile << " using namespace std; " << endl;
    // Look for funcs declarations
    isFuncDeclaration = split(tokens[pointer], ", ")[0] == "function" ? 1 : 0;
    while (isFuncDeclaration)
    {
        // Insert void reserved word when the token function is found
        if (split(tokens[pointer], ", ")[0] == "function")
        {
            newCppFile << "void ";
            pointer++;
        }
        // Break loop if func declaration is not found
        if (split(tokens[pointer], ", ")[0] == "}")
        {
            insertToken(newCppFile, "}");
            pointer++;
            if (split(tokens[pointer + 1], ", ")[0] != "function")
            {
                isFuncDeclaration = 0;
                break;
            }
        }
        word = split(tokens[pointer] + ", ", ", ")[1];
        // Is it prebuilt func
        if (searchIndexArray(word, preBuiltFuncsNames) != -1 &&
            split(tokens[pointer + 1] + ", ", ", ")[1] == "(")
        {
            pointer = insertPreBuiltFunction(newCppFile, word, tokens, pointer);
            word = "";
        }
        else
        {

            insertToken(newCppFile, word);
        }
        pointer++;
    }
    // Write new code
    newCppFile << " int main() { " << endl;
    while (split(tokens[pointer], ", ")[0] != "$")
    {
        word = split(tokens[pointer] + ", ", ", ")[1];
        // Is it prebuilt func
        if (searchIndexArray(word, preBuiltFuncsNames) != -1 &&
            split(tokens[pointer + 1] + ", ", ", ")[1] == "(")
        {
            pointer = insertPreBuiltFunction(newCppFile, word, tokens, pointer);
            word = "";
        }
        if (searchIndexArray(split(tokens[pointer], ", ")[0], ro_basic_symbols) != -1 && split(tokens[pointer + 1], ", ")[0] == "=")
        {
            insertToken(newCppFile, split(tokens[pointer], ", ")[0] + split(tokens[pointer + 1], ", ")[0]);
            pointer += 2;
            continue;
        }
        insertToken(newCppFile, word);
        pointer++;
    }

    newCppFile << "}" << endl;
    return fileName;
}

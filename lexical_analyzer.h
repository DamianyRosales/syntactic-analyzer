/*
 Compiladores - Analizador Lexico para el lenguaje C#

 Este programa lee un archivo fuente (escrito en C#) y calcula las parejas
 ordenadas <token, lexema> por medio de un automata finito determinista.
 Los tokens son guardados en un archivo de texto. (tokens.txt)

 Este programa esta diseñado para compilarse en Turbo C de Borland.

 Licencia:
 Este programa es software libre, por lo tanto se puede distribuir o
 modificar bajo los terminos de la licencia GNU (General Public License)
 asi como lo ha publicado la fundacion de software libre.

*/
#pragma once
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "utils.h"
#include "symbol_table.h"
using namespace std;

int MT[57][24];
void llenar_matriz();
void corrige_arreglo(char arre[100]);
void fix_last_char(const char *file_location);
bool is_reserved_word(char arre[100], vector<string> reserved_words);
vector<string> reserved_words = {
    "int",
    "float",
    "str",
    "function",
    "switch",
    "case",
    "if",
    "else",
    "for",
    "while",
    "do",
    "break"};
string fileName = "test.hz";
string tokensFileName = "tokens.txt";
SymbolTable exec_lexical(SymbolTable st)
{

    FILE *apt, *apt2;
    char arch[15];
    char c;
    char arre[100];
    int ind = 0;
    int ban = 0, ban2 = 0;
    bool isStringDeclaration = false, isVar = false, isFunc = false;
    string dt = "";
    int edo = 1;
    int ptr;
    int yesp;

    strncpy(arre, "", 100);

    fix_last_char(tokensFileName.c_str());
    apt = fopen(fileName.c_str(), "r");
    apt2 = fopen(tokensFileName.c_str(), "w");

    llenar_matriz();

    while (!feof(apt))
    {
        // if (ban == 0)
        c = getc(apt);
        if (c == '\n')
            continue;
        if (c == ' ' && !isStringDeclaration)
        {
            // Evaluate lexeme when a black space is detected
            if (ban != 1)
            {
                string word = arre;
                if (edo == 28)
                {

                    fprintf(apt2, "int_v, %s\n", arre);
                    strncpy(arre, "", 100);
                }
                else if (edo == 29)
                {
                    fprintf(apt2, "float_v, %s\n", arre, arre);
                    strncpy(arre, "", 100);
                }
                else if (is_reserved_word(arre, reserved_words))
                {
                    // Check if the lexeme is a data type
                    if (searchIndexArray(word, getIndexesFromVector(0, 2, reserved_words)) != -1)
                    {
                        isVar = true;

                        dt = word;
                        // Change the data type name str to string
                        if (word == "str")
                        {
                            word = "string";
                        }
                    }
                    fprintf(apt2, "%s, %s\n", arre, word.c_str());
                    strncpy(arre, "", 100);
                }
                else
                {
                    fprintf(apt2, "id, %s\n", arre);
                    strncpy(arre, "", 100);
                    // Insert symbol into the symbol table
                    st.insert(word, (isVar) ? "var" : "func", (dt != "") ? dt : "void");
                    dt = "";
                    isVar = false;
                }
                edo = 1;
                ind = -1;
                ban = 0;
            }
            else
            {
                ind = -1;
            }
        }
        else
        {
            arre[ind] = c;
        }
        // Is it digit or letter
        if (isdigit(c))
        {
            if (edo != 29)
            {

                edo = MT[edo][4];
            }
            ban = 0;
        }
        // Is it float?
        else if (edo == 28 && c == '.')
        {
            edo = 29;
        }
        if (isalpha(c))
        {
            edo = MT[edo][3];
            ban = 0;
        }

        // Comparission of first character
        switch (c)
        {
        case '<':
            edo = MT[edo][6];
            break;
        case '>':
            edo = MT[edo][7];
            break;
        case '*':
            edo = MT[edo][8];
            break;
        case '/':
            edo = MT[edo][9];
            break;
        case '-':
            edo = MT[edo][10];
            break;
        case '+':
            edo = MT[edo][11];
            break;
        case '=':
            edo = MT[edo][12];
            break;
        case '!':
            edo = MT[edo][13];
            break;
        case '|':
            edo = MT[edo][14];
            break;
        case '&':
            edo = MT[edo][15];
            break;
        case '"':
            isStringDeclaration = !isStringDeclaration;
            edo = MT[edo][16];
            break;
        case '{':
            edo = MT[edo][17];
            break;
        case '}':
            edo = MT[edo][18];
            break;
        case ';':
            edo = MT[edo][19];
            break;
        case '(':
            edo = MT[edo][20];
            break;
        case ')':
            edo = MT[edo][21];
            break;
        case ':':
            edo = MT[edo][22];
            break;
        } // fin switch

        // Automata final states
        switch (edo)
        {
        case 3: // Asterisk
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "*, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 4: // Sum
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "+, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 5: // Sustract
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "-, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;
        case 6: // Divide
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "/, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;
        case 7: // Less than
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "<, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 11: // Less or equal than
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "<=, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;
        case 12: // Greater than
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, ">, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 13: // Greater or equal than
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, ">=, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 15: // Greater or equal than
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "=, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 18: // not equal
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "!=, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 20: // Logical or
            edo = 1;
            fprintf(apt2, "||, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 22: // Logical and
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "&&, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 24: // String
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "str_v, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 25: // open bracket
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "{, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 26: // closing bracket
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "}, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 27: // eos (;)
            edo = 1;
            fprintf(apt2, ";, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;
        case 30: // negative integer value
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "zzzz,	%s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 31: // negative float value
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "zzzz,		%s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 32: // open parentesis
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "(, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;

        case 33: // closing paraentesis
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, "), %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;
        case 34: // closing paraentesis
            edo = 1;
            // corrige_arreglo(arre);
            fprintf(apt2, ":, %s\n", arre);
            strncpy(arre, "", 100);
            ind = -1;
            ban = 1;
            break;
        }

        ind++;
    } // fin while

    fclose(apt2);
    fclose(apt);
    return st;
}

void corrige_arreglo(char arre[100])
{
    for (int r = 1; r <= 100; r++)
        arre[r - 1] = arre[r];
}

void llenar_matriz()
{
    // Fill row[0] column [e] with 0's
    for (int e = 0; e <= 23; e++)
        MT[0][e] = 0;
    // Fill row[m] column[0] with 0's
    // The first 33 are the non terminal states
    // 34 = 101
    for (int m = 0; m == 57; m++)
        MT[m][0] = 0;
    // Transiciones del automata!!
    // Non terminal states
    MT[2][1] = 1;
    MT[1][4] = 28;
    MT[28][4] = 28;
    MT[1][2] = 1;
    MT[2][2] = 1;
    MT[7][2] = 8;
    MT[8][2] = 9;
    MT[2][5] = 1;
    MT[28][5] = 29;
    MT[30][5] = 31;
    MT[1][6] = 7;
    MT[2][6] = 1;
    MT[1][7] = 12;
    MT[2][7] = 1;
    MT[9][7] = 10;
    MT[1][8] = 3;
    MT[2][8] = 1;
    MT[1][9] = 6;
    MT[2][9] = 1;
    MT[1][10] = 5;
    MT[2][10] = 1;
    MT[1][11] = 4;
    MT[2][11] = 1;
    MT[1][12] = 15;
    MT[2][12] = 1;
    MT[7][12] = 11;
    MT[12][12] = 13;
    MT[15][12] = 16;
    MT[17][12] = 18;
    MT[1][13] = 17;
    MT[2][13] = 1;
    MT[1][14] = 19;
    MT[2][14] = 1;
    MT[1][15] = 21;
    MT[2][15] = 1;
    MT[1][16] = 23;
    MT[2][16] = 1;
    MT[23][16] = 24;
    MT[23][3] = 23;
    MT[1][17] = 25;
    MT[2][17] = 1;
    MT[1][18] = 26;
    MT[2][18] = 1;
    MT[1][19] = 27;
    MT[2][19] = 1;
    MT[1][20] = 32;
    MT[2][20] = 1;
    MT[1][21] = 33;
    MT[2][21] = 1;
    MT[1][22] = 34;
    MT[2][22] = 1;

} // fin de la funcion llenar_matriz()

void fix_last_char(const char *file_location)
{
    FILE *file;
    file = fopen(file_location, "r");
    if (file == 0)
    {
        printf("No se encontro el archivo\n");
        getch();
        exit(0);
    }
    // Check if the last character is a line break
    if (fseek(file, -1, SEEK_END) == 0)
    {
        char last;
        last = fgetc(file);
        fclose(file);
        if (last != '\n')
        {
            // Append the line break
            file = fopen(file_location, "a");
            putc('\n', file);
            fclose(file);
        }
    }
}

bool is_reserved_word(char arre[100], vector<string> reserved_words)
{

    int ptr;
    for (int b = 0; b < reserved_words.size(); b++)
    {
        ptr = strcmp(arre, reserved_words[b].c_str());
        if (ptr == 0)
        {
            return true;
        }
    }
    return false;
}
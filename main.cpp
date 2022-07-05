#include "filereader.h"
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    stack<string> stack;
    vector <string> arrayTokens = readFile("tokens.txt");
    cout << "Tokens: " << endl;
    for (int i = 0; i < arrayTokens.size(); i++) {
        cout << arrayTokens[i] << endl;
    }
    
}
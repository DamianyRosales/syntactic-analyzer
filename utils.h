#pragma once
#include <string>
#include <vector>
#include <stack>
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

int searchIndexArray(int num, vector<int> array)
{
    for (int i = 0; i <= array.size(); i++)
    {
        if (num == array[i])
        {
            return i;
        }
    }
    return -1;
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

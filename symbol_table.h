#pragma once
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100;

class Node
{

    string identifier, type, value;
    int lineNo;
    Node *next;

public:
    Node()
    {
        next = NULL;
    }

    Node(string key, string value, string type)
    {
        this->identifier = key;
        this->type = type;
        this->value = value;
        next = NULL;
    }
    friend class SymbolTable;
};

class SymbolTable
{
    Node *head[MAX];

public:
    SymbolTable()
    {
        for (int i = 0; i < MAX; i++)
            head[i] = NULL;
    }

    int hashf(string id); // hash function
    bool insert(string id, string value, string Type);

    string find(string id);

    bool deleteRecord(string id);

    bool modify(string id, string scope,
                string Type, int lineno);

}; // end of class

// Function to delete an identifier
bool SymbolTable::deleteRecord(string id)
{
    int index = hashf(id);
    Node *tmp = head[index];
    Node *par = head[index];

    // no identifier is present at that index
    if (tmp == NULL)
    {
        return false;
    }
    // only one identifier is present
    if (tmp->identifier == id && tmp->next == NULL)
    {
        tmp->next = NULL;
        delete tmp;
        return true;
    }

    while (tmp->identifier != id && tmp->next != NULL)
    {
        par = tmp;
        tmp = tmp->next;
    }
    if (tmp->identifier == id && tmp->next != NULL)
    {
        par->next = tmp->next;
        tmp->next = NULL;
        delete tmp;
        return true;
    }

    // delete at the end
    else
    {
        par->next = NULL;
        tmp->next = NULL;
        delete tmp;
        return true;
    }
    return false;
}

// Function to find an identifier
string SymbolTable::find(string id)
{
    int index = hashf(id);
    Node *start = head[index];

    if (start == NULL)
        return "-1";

    while (start != NULL)
    {

        if (start->identifier == id)
        {
            return "" + start->value + ", " + start->type;
        }

        start = start->next;
    }

    return "-1"; // not found
}

// Function to insert an identifier
bool SymbolTable::insert(string id, string value, string Type)
{
    int index = hashf(id);
    Node *p = new Node(id, value, Type);

    if (head[index] == NULL)
    {
        head[index] = p;
        return true;
    }

    else
    {
        Node *start = head[index];
        while (start->next != NULL)
            start = start->next;
        start->next = p;
        return true;
    }

    return false;
}

int SymbolTable::hashf(string id)
{
    int asciiSum = 0;

    for (int i = 0; i < id.length(); i++)
    {
        asciiSum = asciiSum + id[i];
    }

    return (asciiSum % 100);
}

#include <iostream>
#include <string>
#include "List.h"
#include "ShennonFano.h"

using namespace std;

template <class arr> arr* ListArr(LinkedList* list)//creates an array of frequency or symbols
{
    arr* array = new arr[list->get_size()];
    Iterator* current = list->create_iterator();
    for (int i = 0; i < list->get_size(); i++)
    {
        if (is_same<arr, int>::value) array[i] = current->freq(); 
        if (is_same<arr, char>::value) array[i] = current->symbol(); 
        current->next();
    }
    return array;
}

void CodeSymbols(LinkedList* list, int* freqs, char* symbs, size_t size)//encodes the symbols in a list by shennon-fano algorithm
{
    int leftSum = 0, rightSum = 0;
    size_t leftSize = 0, rightSize = 0;
    LinkedList* LeftList = new LinkedList();
    LinkedList* RightList = new LinkedList();

    for (int i = 0; i < size; i++)
    {
        if (leftSum < rightSum)
        {
            leftSum += freqs[i];
            LeftList->push_back(symbs[i], freqs[i]);
            LeftList->at(LeftList->get_size() - 1);
            list->CodeNode(symbs[i], true);
            leftSize++;
        }
        else
        {
            rightSum += freqs[i];
            RightList->push_back(symbs[i], freqs[i]);
            list->CodeNode(symbs[i], false);
            rightSize++;
        }
    }
    if (LeftList->get_size() > 1)
    {
        int* leftarrf = ListArr<int>(LeftList); 
        char* leftarrs = ListArr<char>(LeftList); 
        CodeSymbols(list, leftarrf, leftarrs, leftSize);
    }
    if (RightList->get_size() > 1)
    {
        int* rightarrf = ListArr<int>(RightList); 
        char* rightarrs = ListArr<char>(RightList); 
        CodeSymbols(list, rightarrf, rightarrs, rightSize);
    }
}

LinkedList* ShennonFano(string str)//creates a list sorted by frequancy and arrays with frequancy and symbols
{
    LinkedList* list = new LinkedList();
    char current;
    for (size_t i = 0; i < str.length(); i++)
    {
        current = str[i];
        if (!list->find(current))
            list->push_back(current);
    }
    list->bubbleSort();
    int* freqs = ListArr<int>(list); 
    char* symbs = ListArr<char>(list); 
    CodeSymbols(list, freqs, symbs, list->get_size());
    return list;
}

string Code(string str)//encodes the original string
{
    LinkedList* list = ShennonFano(str);
    string code = "";
    for (size_t i = 0; i < str.length(); i++)
    {
        string codeSymbol = list->findCode(str[i]);
        for (int j = 0; j < codeSymbol.length(); j++)
            code.push_back(codeSymbol[j]);
    }
    return code;
}


string Decode(string str, string code)//decodes the string
{
    LinkedList* list = ShennonFano(str);
    string str_out = "";
    string codeSymbol = "";
    for (int i = 0; i < code.length(); i++)
    {
        codeSymbol.push_back(code[i]);
        if (list->find(codeSymbol))
        {
            str_out.push_back(list->findSymbol(codeSymbol));
            codeSymbol = "";
        }
    }
    return str_out;
}

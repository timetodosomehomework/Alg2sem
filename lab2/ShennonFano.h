#pragma once
#include "list.h"
#include <string>
using namespace std;

LinkedList* ShennonFano(string);
void CodeSymbols(LinkedList*, int*, char*, size_t);
template <class arr> arr* ListArr(LinkedList*);
string Code(string);
string Decode(string, string);
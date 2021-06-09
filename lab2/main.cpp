#include <iostream>
#include <string>
#include "ShennonFano.h"

using namespace std;

int main()
{
    string str, codestr;
    cout << "Enter string: ";
    getline(cin, str);
    LinkedList* list = ShennonFano(str);
    list->print_to_console();
    string code = Code(str);
    cout << "\nCode:" << code << endl;
    cout << "String size = " << str.length() * sizeof(char) * 8 << "bit" << endl; 
    cout << "Code size = " << code.length() << "bit" << endl;
    cout << "Compression ratio = " << (double)(str.length() / (double)(code.length() * 8)) << endl;
    cout << "Enter code: ";
    getline(cin, codestr);
    string str2 = Decode(str, codestr);
    cout << "String:" << str2 << endl;
}
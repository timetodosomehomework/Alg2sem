#include<iostream>
#include <Windows.h>
#include"flow.h"
#include <fstream>
using namespace std;
using namespace flow;
int main()
{
    ifstream file("F:\\in.txt");
    string line; int size;
    getline(file, line);
    size = atoi(line.c_str());
    int** Matrix = new int* [size];
    for (int i = 0; i < size; i++)
        Matrix[i] = new int[size];
    char* nodes = new char[size];
    read(file, Matrix, size, nodes);
    int** matrixflow = new int* [size];
    for (int i = 0; i < size; i++)
        matrixflow[i] = new int[size];
    pushing_flow(Matrix, matrixflow, size);
}
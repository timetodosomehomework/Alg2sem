#include<iostream>
#include <Windows.h>
#include"Floyd.h"
using namespace std;
using namespace Floyd;
int main()
{
    ifstream file("F:\\c.txt");
    string line; 
    getline(file, line);
    int n = atoi(line.c_str());
    string* cities = new string[n];
    int** Matrix = new int* [n];
    for (int i = 0; i < n; i++)
        Matrix[i] = new int[n];
    int** Ways = new int* [n];
    for (int i = 0; i < n; i++)
        Ways[i] = new int[n];
    read(file, Matrix, n, cities);
    FloydWarshall(Matrix, n, Ways);
    cout << "Cities:" << endl;
    for (int i = 0; i < n - 1; i++)
        cout << i + 1 << ". " << cities[i] << endl;
    int firsttown;
    cout << "Departure city: ";
    cin >> firsttown;
    int secondtown;
    cout << "Arrival city: ";
    cin >> secondtown;
    cout << "The cheapest flight - ";
    path_restore(Ways, firsttown, secondtown, Matrix, cities);
}
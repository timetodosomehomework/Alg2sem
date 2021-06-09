#pragma once
#include<iostream>
#include<iomanip>
#include <fstream>
#include<string>
const int inf = 999999;
using namespace std;
namespace Floyd
{
    void FloydWarshall(int** Matrix, int size, int** Ways) //Floyd-Warshall algorithm
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if ((Matrix[i][j] != inf) && (Matrix[i][j] != 0))
                    Ways[i][j] = j + 1;
                else
                    Ways[i][j] = 0;
            }
        }
        for (int k = 0; k < size; k++)
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if ((Matrix[i][k] + Matrix[k][j]) < Matrix[i][j])
                    {
                        Matrix[i][j] = Matrix[i][k] + Matrix[k][j];
                        Ways[i][j] = Ways[i][k];
                    }
                }
            }
        }
    }

    void path_restore(int** Ways, int firsttown, int secondtown, int** Matrix, string* cities)//restores the cheapest path
    {
        if (Matrix[firsttown - 1][secondtown - 1] == inf)
            cout << "No flight available" << endl;
        else
        {
            int index = firsttown;
            while (index != secondtown)
            {
                cout << cities[index - 1] << "->";
                index = Ways[index - 1][secondtown - 1];
            }
            cout << cities[secondtown - 1] << endl;
            cout << "Cost: " << Matrix[firsttown - 1][secondtown - 1] << endl;
        }
    }

    int get_index(string city, string* cities, int n)//gets index of the already existing city
    {
        for (int i = 0; i < n; i++)
        {
            if (city == cities[i])
                return i;
        }
        return -1;
    }

    void read(ifstream& file, int** Matrix, int size, string* cities)//reads the file and fills the matrix with its data
    {
        string line;
        int n = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (i == j)
                    Matrix[i][i] = 0;
                else
                    Matrix[i][j] = inf;
            }
        }
        while (!file.eof())
        {
            getline(file, line);
            int first = line.find(";");
            int second = line.find(";", first + 1);
            int third = line.find(";", second + 1);
            string firstcity = line.substr(0, first);
            string secondcity = line.substr(first + 1, second - first - 1);
            string firstcoststring = line.substr(second + 1, third - second - 1);
            string secondcoststring = line.substr(third + 1);
            int firstcost;
            int secondcost;
            if (firstcoststring != "N/A")
                firstcost = atoi(firstcoststring.c_str());
            else
                firstcost = inf;
            if (secondcoststring != "N/A")
                secondcost = atoi(secondcoststring.c_str());
            else
                secondcost = inf;
            if (get_index(firstcity, cities, n) == -1)
            {
                cities[n] = firstcity; 
                n++;
            }
            if (get_index(secondcity, cities, n) == -1)
            {
                cities[n] = secondcity; 
                n++;
            }
            Matrix[get_index(firstcity, cities, n)][get_index(secondcity, cities, n)] = firstcost;
            Matrix[get_index(secondcity, cities, n)][get_index(firstcity, cities, n)] = secondcost;
        }
    }
}

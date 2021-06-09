#pragma once
#include<iostream>
#include< iomanip >
#include <fstream>
#include<string>
const int inf = 999999;
using namespace std;
namespace flow
{
    void push(int u, int v, int** f, int* e, int** c, int n)
    {
        int d = min(e[u], c[u][v] - f[u][v]);
        f[u][v] += d;
        f[v][u] = -f[u][v];
        e[u] -= d;
        e[v] += d;
    }

    void lift(int u, int* h, int** f, int** c, int n)
    {
        int d = inf;
        for (int i = 0; i < n; i++)
            if (c[u][i] - f[u][i] > 0)
                d = min(d, h[i]);
        if (d == inf)
            return;
        h[u] = d + 1;
    }
    int overflow(int* e, int n) 
    {
        int i = 1;
        while ((e[i] <= 0) && (i < n - 1))
            i++;
        if (i == n - 1)
            return -1;
        else
            return i;
    }
    int pushing_flow(int** c, int** f, int n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                f[i][j] = 0;
        for (int i = 1; i < n; i++)
        {
            f[0][i] = c[0][i];
            f[i][0] = -c[0][i];
        }
        int* h = new int[n];
        h[0] = n;
        for (int i = 1; i < n; i++) h[i] = 0;
        int* e = new int[n];
        e[0] = 0;
        for (int i = 1; i < n; i++) e[i] = f[0][i];
        int i;
        while ((i = overflow(e, n)) != -1)
        {
            int j = 0;
            while (((c[i][j] - f[i][j] <= 0) || (h[i] != h[j] + 1)) && (j < n))
                j++;
            if (j < n)
                push(i, j, f, e, c, n);
            else
                lift(i, h, f, c, n);
        }
        int flow = e[n - 1];
        cout << "Maximum flow: " << flow << endl;
        return flow;
    }
    int get_index(char top, char* nodes, int n)
    {
        for (int i = 0; i < n; i++)
        {
            if (top == nodes[i])
                return i;
        }
        return -1;
    }
    void read(ifstream& file, int** Matrix, int size, char* nodes)
    {
        string line; 
        string selection;
        int sizetops = 0;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                Matrix[i][j] = 0;
        while (!file.eof())
        {
            getline(file, line);
            int firstspace = line.find(" ");
            int secondspace = line.find(" ", firstspace + 1);
            selection = line.substr(0, firstspace);
            char firstop = selection[0];
            selection = line.substr(firstspace + 1, secondspace - firstspace - 1);
            char secondtop = selection[0];
            selection = line.substr(secondspace + 1);
            int cost = atoi(selection.c_str());
            if (get_index(firstop, nodes, sizetops) == -1)
            {
                nodes[sizetops] = firstop; sizetops++;
            }
            if (get_index(secondtop, nodes, sizetops) == -1)
            {
                nodes[sizetops] = secondtop; sizetops++;
            }
            Matrix[get_index(firstop, nodes, sizetops)][get_index(secondtop, nodes, sizetops)] = cost;
        }
    }
}

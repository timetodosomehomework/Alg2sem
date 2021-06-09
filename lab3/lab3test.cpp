#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab3\Floyd.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Floyd;

namespace lab3test
{
	TEST_CLASS(lab3test)
	{
	public:
		
		TEST_METHOD(readtest)
		{
			ifstream file("F:\\test.txt");
			string line; int size;
			getline(file, line);
			size = atoi(line.c_str());
			string* cities = new string[size];
			int** Matrix = new int* [size];
			for (int i = 0; i < size; i++)
				Matrix[i] = new int[size];
			read(file, Matrix, size, cities);
			string citiestest[3] = { "SPB", "Vladivostok", "Moscow" };
			int Matrixtest[3][3] = { {0,7,inf},{12,0,9},{inf,15,0} };
			for (int i = 0; i < size; i++)
			{
				Assert::IsTrue(cities[i] == citiestest[i]);
				for (int j = 0; j < size; j++)
				{
					Assert::AreEqual(Matrix[i][j], Matrixtest[i][j]);
				}
			}
		}
		TEST_METHOD(FloydWarshalltest)
		{
			ifstream file("F:\\test.txt");
			string line; int size;
			getline(file, line);
			size = atoi(line.c_str());
			string* cities = new string[size];
			int** Matrix = new int* [size];
			for (int i = 0; i < size; i++)
				Matrix[i] = new int[size];
			int** Ways = new int* [size];
			for (int i = 0; i < size; i++)
				Ways[i] = new int[size];
			read(file, Matrix, size, cities);
			FloydWarshall(Matrix, size, Ways);
			int Matrixtest[3][3] = { {0,7,16},{12,0,9},{27,15,0} };
			int waystest[3][3] = { {0,2,2},{1,0,3},{2,2,0} };
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					Assert::AreEqual(Matrix[i][j], Matrixtest[i][j]);
					Assert::AreEqual(Ways[i][j], waystest[i][j]);
				}
		    }
		}
	};
}

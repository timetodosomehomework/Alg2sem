#include "pch.h"
#include "CppUnitTest.h"
#include "..\kurs\flow.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace flow;
namespace kurstest
{
	TEST_CLASS(kurstest)
	{
	public:
		
		TEST_METHOD(readtest)
		{
			ifstream file("F:\\test.txt");
			string line; int size;
			getline(file, line);
			size = atoi(line.c_str());
			char* nodes = new char[size];
			int** Matrix = new int* [size];
			for (int i = 0; i < size; i++)
				Matrix[i] = new int[size];
			read(file, Matrix, size, nodes);
			char nodestest[3] = { 'A', 'S', 'C' };
			int Matrixtest[3][3] = { {0,12,0},{0,0,4},{0,0,0} };
			for (int i = 0; i < size; i++)
			{
				Assert::IsTrue(nodes[i] == nodestest[i]);
				for (int j = 0; j < size; j++)
				{
					Assert::AreEqual(Matrix[i][j], Matrixtest[i][j]);
				}
			}
		}
	};
}

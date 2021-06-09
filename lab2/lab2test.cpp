#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab2\Iterator.h"
#include "..\lab2\List.h"
#include "..\lab2\ShennonFano.h"
#include "..\lab2\ListMethods.cpp"
#include "..\lab2\ShennonFano.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab2test
{
	TEST_CLASS(lab2test)
	{
	public:
		
		TEST_METHOD(CodeSymbolstest)
		{
			string str = "AAABCC";
			LinkedList* list = new LinkedList();
			char current;
			current = str[0];
			for (int i = 0; i < str.size(); i++)
			{
				current = str[i];
				if (!list->find(current))
					list->push_back(current);
			}
			int freqs[3] = { 3,1,2 };
			char symbs[3] = { 'A','B','C' };
			CodeSymbols(list, freqs, symbs, 3);
			Assert::AreEqual(list->findSymbol("0"), 'A');
		}

		TEST_METHOD(Codetest)
		{
			string str = Code("mama");
			Assert::AreEqual(str, (string)"0101");
		}

		TEST_METHOD(Decodetest)
		{
			string str = Decode("mama", "1010");
			Assert::AreEqual(str, (string)"amam");
		}
	};
}

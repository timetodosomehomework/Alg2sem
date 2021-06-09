#include "pch.h"
#include "CppUnitTest.h"
#include "..\RBtree\Map.h"
#include "..\RBtree\Methods.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RBtreeTest
{
	TEST_CLASS(RBtreeTest)
	{
	public:
		
		Map RBtree;

		TEST_METHOD(Insert_and_Find)
		{
			RBtree.insert(1, 2);
			Assert::AreEqual(RBtree.find(1)->data, 2);
		}
		TEST_METHOD(remove_and_return_size)
		{
			RBtree.insert(1, 2);
			RBtree.insert(2, 2);
			RBtree.insert(3, 2);
			RBtree.insert(4, 2);
			RBtree.insert(5, 2);
			Assert::AreEqual(RBtree.return_size(), 5);
			RBtree.remove(2);
			Assert::AreEqual(RBtree.return_size(), 4);
		}
		TEST_METHOD(clear)
		{
			RBtree.insert(1, 2);
			RBtree.insert(2, 2);
			RBtree.insert(3, 2);
			RBtree.insert(4, 2);
			RBtree.insert(5, 2);
			RBtree.clear();
			Assert::AreEqual(RBtree.return_size(), 0);
		}
	};
}

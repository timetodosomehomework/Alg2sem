#include <iostream>
#include "Map.h"
using namespace std;

int main()
{
	Map RBtree;
	RBtree.insert(11,65);
	RBtree.insert(2, 17);
	RBtree.insert(14, 58);
	RBtree.insert(1, 6);
	RBtree.insert(7, 6);
	RBtree.insert(15, 6);
	RBtree.insert(5, 6);
	RBtree.insert(8, 6);
	RBtree.print();
	RBtree.remove(2);
	RBtree.print();
}
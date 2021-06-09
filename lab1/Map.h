#pragma once
#include <stdlib.h>

class Map
{
private:
	class Node
	{
	public:
		Node(int key, char color, int data, Node* left, Node* right, Node* parent)
		{
			this->key = key;
			this->data = data;
			this->color = color;
			this->left = left;
			this->right = right;
			this->parent = parent;
		}
		char color;
		int data, key;
		Node* left, * right, * parent;
	};

	Node* root;
	Node* nil = new Node(0, 'b', 0, NULL, NULL, NULL);
	int size;
public:

	Map();

	int return_size();//return size of the tree
	void insert(int key, int data);//adds an element with key and value
	void remove(int key);//deletes element with the key
	Node* find(int key);//finds element with the key
	void clear();//clears tree
	int* get_keys();//gets array of keys
	int* get_values();//gets array of values
	void print();//prints in the console
	void InsertFixUp(Node* x);//fixes RB properties of the tree after insert
	void LeftRotate(Node* x);// left rotate
	void RightRotate(Node* x);//right rotate
	void Transplant(Node* x, Node* y);//for remove, swaps x and y 
	void DeleteFixUp(Node* x);//fixes RB properties of the tree after delete
};
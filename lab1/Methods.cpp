#include <iostream>
#include <stack>
#include "Map.h"
using namespace std;

Map::Map()
{
	root = nil;
	size = 0;
}

int Map::return_size()
{
	return size;
}

void Map::LeftRotate(Node* x)
{
	if (x->right == nil)
		return;
	Node* y = x->right;
	if (y->left != nil)
	{
		x->right = y->left;
		y->left->parent = x;
	}
	else
		x->right = nil;
	if (y != nil)
		y->parent = x->parent;
	if (x->parent != nil)
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else
	{
		y->parent = nil;
		root = y;
	}
	y->left = x;
	if (x != nil)
		x->parent = y;
}

void Map::RightRotate(Node* x)
{
	if (x->left == nil)
		return;
	Node* y = x->left;
	if (y->right != nil)
	{
		x->left = y->right;
		y->right->parent = x;
	}
	else
		x->left = nil;
	if (y != nil)
		y->parent = x->parent;
	if (x->parent != nil)
	{
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	else
	{
		y->parent = nil;
		root = y;
	}
	y->right = x;
	if (x != nil)
		x->parent = y;
}


void Map::InsertFixUp(Node* x)
{
	while (x->parent->color == 'r')
	{
		if (x->parent == x->parent->parent->left)
		{
			Node* y = x->parent->parent->right;
			if (y->color == 'r')
			{
				x->parent->parent->right->color = 'b';
				x->parent->parent->left->color = 'b';
				x->parent->parent->color = 'r';
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->right)
				{
					x = x->parent;
					LeftRotate(x);
				}
				x->parent->color = 'b';
				x->parent->parent->color = 'r';
				RightRotate(x->parent->parent);
			}
		}
		else
		{
			Node* y = x->parent->parent->left;
			if (y->color == 'r')
			{
				x->parent->parent->right->color = 'b';
				y->color = 'b';
				x->parent->parent->color = 'r';
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->left)
				{
					x = x->parent;
					RightRotate(x);
				}
				x->parent->color = 'b';
				x->parent->parent->color = 'r';
				LeftRotate(x->parent->parent);
			}
		}
	}
	root->color = 'b';
}

void Map::insert(int key, int data)
{
	Node* x = root, * y = nil;
	while (x != nil)
	{
		y = x;
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	Node* z = new Node(key, 'r', data, nil, nil, y);
	if (y == nil)
	{
		root = z;
		root->color = 'b';
	}
	else
		if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
	size++;
	InsertFixUp(z);
}

Map::Node* Map::find(int key)
{
	Node* x = root;
	while (x->key != key)
	{
		if (key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	return x;
}

void Map::Transplant(Node* x, Node* y)//for remove, swaps x and y
{
	if (x->parent == nil)
		root = y;
	else
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	y->parent = x->parent;
}

void Map::DeleteFixUp(Node* x)
{
	Node* pivot;
	while (x != root && x->color == 'b')
	{
		if (x == x->parent->left)
		{
			pivot = x->parent->right;
			if (pivot->color == 'r')
			{
				pivot->color = 'b';
				x->parent->color = 'r';
				LeftRotate(x->parent);
				pivot = x->parent->right;
			}
			if (pivot->left->color == 'b' && pivot->right->color == 'b')
			{
				pivot->color = 'r';
				x = x->parent;
			}
			else
			{
				if (pivot->right->color == 'b')
				{
					pivot->left->color = 'b';
					pivot->color = 'r';
					RightRotate(pivot);
					pivot = x->parent->right;
				}
				pivot->color = x->parent->color;
				x->parent->color = 'b';
				pivot->right->color = 'b';
				LeftRotate(x->parent);
				x = root;
			}
		}
		else
		{
			pivot = x->parent->left;
			if (pivot->color == 'r')
			{
				pivot->color = 'b';
				x->parent->color = 'r';
				RightRotate(x->parent);
				pivot = x->parent->left;
			}
			if (pivot->right->color == 'b' && pivot->left->color == 'b')
			{
				pivot->color = 'r';
				x = x->parent;
			}
			else
			{
				if (pivot->left->color == 'b')
				{
					pivot->right->color = 'b';
					pivot->color = 'r';
					LeftRotate(pivot);
					pivot = x->parent->left;
				}
				pivot->color = x->parent->color;
				x->parent->color = 'b';
				pivot->left->color = 'b';
				RightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = 'b';
}

void Map::remove(int key)
{
	Node* x = find(key), * t, * y;
	y = x;
	char originalColor = y->color;
	if (x->left == nil)
	{
		t = x->right;
		Transplant(x, t);
	}
	else
	{
		if (x->right == nil)
		{
			t = x->left;
			Transplant(x, t);
		}
		else
		{
			y = x->right;
			while (y->left != nil)
				y = y->left;
			originalColor = y->color;
			t = y->right;
			if (y->parent == x)
				t->parent = y;
			else
			{
				Transplant(y, y->right);
				y->right = x->right;
				y->right->parent = y;
			}
			Transplant(x, y);
			y->left = x->left;
			y->left->parent = y;
			y->color = x->color;
		}
	}
	if (originalColor == 'b')
		DeleteFixUp(t);
	size--;
}

void Map::clear()
{
	Node* x = root;
	int* keys = get_keys();
	for (int i = 0; i < size; i++)
	{
		remove(keys[i]);
	}
	size = 0;
}

int* Map::get_keys()
{
	int* keys = new int[size];
	Node* current = root;
	stack<Node*> stack;
	stack.push(root);
	for (int i = 0; i < size; i++)
	{
		current = stack.top();
		stack.pop();
		keys[i] = current->key;
		if (current->right != nil)
			stack.push(current->right);
		if (current->left != nil)
			stack.push(current->left);
	}
	return keys;
}

int* Map::get_values()
{
	int* values = new int[size];
	Node* current = root;
	stack<Node*> stack;
	stack.push(root);
	for (int i = 0; i < size; i++)
	{
		current = stack.top();
		stack.pop();
		values[i] = current->data;
		if (current->right != nil)
			stack.push(current->right);
		if (current->left != nil)
			stack.push(current->left);
	}
	return values;
}

void Map::print()
{
	int* keys = get_keys(), * values = get_values();
	cout << "Keys\tValues\n";
	for (int i = 0; i < size; i++)
	{
		cout << keys[i] << '\t' << values[i] << '\n';
	}
}
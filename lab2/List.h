#pragma once
#include <string>
#include "Iterator.h"

class LinkedList
{
private:

	class Node
	{
	public:
		Node(char data = ' ', Node* next = nullptr, Node* previous = nullptr, std::string code= "", int freq = 1)  //constructor
		{
			this->data = data;
			this->next = next;
			this->previous = previous;
			this->code = code;
			this->freq = freq;
		};
		~Node() {}; //destructor

		int freq;
		char data;
		std::string code;
		Node* next;
		Node* previous;
	};

	Node* head;
	Node* tail;
	size_t size;

public:

	LinkedList(); //for list initialisation

	bool find(char data);//increases frequancy if symbol exists and return bool value
	bool find(std::string string);//checks if the code exists
	char findSymbol(std::string);//returns value of symbol by code
	Node* findNode(char data);//returns the node with the set value
	std::string findCode(char data);//returns code by value of symbol
	void CodeNode(char data, bool bin);//creates a code in node searched by value
	void add_freq(Node* current);//increases frequancy
	void swap(Node* x, Node* y);//swaps frequancy and data between x and y
	void bubbleSort();// bubble sort
	void push_back(char newElem, int freq);//push back with set frequancy

	void push_back(int newElem); //adding to the end of the list
	void push_front(int newElem); //adding to the beginning of the list
	void pop_back(); //remove the last element
	void pop_front(); //remove the first element
	void insert(int newElem, size_t index); //adding an elment at index (insertion before an element that was previously accessible at that index)
	int at(size_t index); //getting an element by index
	void remove(size_t index); //remove an element by index
	size_t get_size(); //getting list size
	void print_to_console(); //print the list to the console 
	void clear(); //removing all list elements
	void set(size_t index, int newElem); //replacing the element by index with the new element
	bool isEmpty(); //checking if the list is empty
	size_t find_last(LinkedList List); //returning index of the beginning last sublist 

	Iterator* create_iterator();
	class iterator : public Iterator
	{
	public:
		iterator(Node* head)
		{
			cur = head;
		}
		~iterator()
		{
			delete cur;
		};
		bool has_current() override;
		char symbol() override;
		std::string code() override;
		int freq() override; 
		void next() override;
	private:
		Node* cur;
	};
};

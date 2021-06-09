#include "List.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() //for list initialisation
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

void LinkedList::push_back(int newElem) //adding to the end of the list
{
	if (size == 0) //if it's first element
	{
		head = new Node(newElem);
		tail = head;
	}
	else //if it isn't first element
	{
		tail->next = new Node(newElem, nullptr, tail);
		tail = tail->next;
	}
	size++;
}

void LinkedList::push_back(char newElem, int freq) //adding to the end of the list
{
	if (size == 0) //if it's first element
	{
		head = new Node(newElem);
		head->freq = freq;
		tail = head;
	}
	else //if it isn't first element
	{
		tail->next = new Node(newElem, nullptr, tail);
		tail = tail->next;
		tail->freq = freq;
	}
	size++;
}

void LinkedList::push_front(int newElem) //adding to the beginning of the list
{
	if (size == 0) //if it's first element
	{
		head = new Node(newElem);
		tail = head;
	}
	else //if it isn't first element
	{
		head = new Node(newElem, head);
	}
	size++;
}

void LinkedList::pop_back() //remove the last element
{
	if (size == 0) //if there are no elements in the list
		return;
	if (size == 1) //if there is only one element in the list
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		size--;
	}
	else //if there is more than one element in the list
	{
		Node* del = tail;
		tail = tail->previous;
		tail->next = nullptr;
		delete del;
	}
	size--;
}

void LinkedList::pop_front() //remove the first element
{
	if (size == 0) //if there are no elements in the list
		return;
	if (size == 1) //if there is only one element in the list
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else //if there is more than one element in the list
	{
		Node* del = head;
		head = head->next;
		head->previous = nullptr;
		delete del;
	}
	size--;
}

void LinkedList::insert(int newElem, size_t index) //adding an elment at index (insertion before an element that was previously accessible at that index)
{

	if (index == 0) //if adding the first element
		push_front(newElem);
	else
	{
		if (index == size - 1) //if adding the last element
			push_back(newElem);
		else
		{
			size_t counter = 1;
			Node* current = head;
			while (counter != index)
			{
				current = current->next;
				counter++;
			}
			current->next = new Node(newElem, current->next, current);
			current = current->next;
			Node* support = current;
			current = current->next;
			current->previous = support;
			size++;
		}
	}

}

int LinkedList::at(size_t index) //getting an element by index
{

	size_t counter = 0;
	Node* current = head;
	while (counter != index)
	{
		current = current->next;
		counter++;
	}
	return current->data;

}

void LinkedList::remove(size_t index) //remove an element by index
{

	if (index == 0) //if removing first element
		pop_front();
	else
	{
		if (index == size - 1) //if removing last element
			pop_back();
		else
		{
			size_t counter = 1;
			Node* current = head;
			while (counter != index)
			{
				current = current->next;
				counter++;
			}
			Node* prevcurrent = current;
			current = current->next;
			Node* nextcurrent = current->next;
			delete current;
			prevcurrent->next = nextcurrent;
			nextcurrent->previous = prevcurrent;
			size--;
		}
	}

}

size_t LinkedList::get_size() //getting list size
{
	return size;
}

void LinkedList::print_to_console() //print the list to the console 
{
	if (size == 0) //if there are no elements in the list
		throw "There are no elements in the list"; //if there are elements in the list
	else
	{
		Node* current = head;
		cout << "Symbol" << '\t' << "Frequency" << '\t' << "Code\n";
		cout << current->data << '\t' << current->freq << '\t' << current->code;
		while (current->next != nullptr)
		{
			current = current->next;
			cout << '\n' << current->data << '\t' << current->freq << '\t' << current->code;
		}
	}
}

void LinkedList::clear() //removing all list elements
{
	if (size == 1) //if there is only one element in the list
		pop_front();
	else //if there are more than one elements in the list
	{
		Node* current = head, * previous = current;
		do
		{
			current = current->next;
			delete previous;
			previous = current;
		} while (current->next != nullptr);
		delete previous;
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
}

void LinkedList::set(size_t index, int newElem) //replacing the element by index with the new element
{
	if (index >= size) //if index greater or equal than size of the list
		throw out_of_range("Index is greater than list size");
	else //if index lesser than size of the list
	{
		Node* current = head;
		size_t counter = 0;
		while (counter != index)
		{
			current = current->next;
			counter++;
		}
		current->data = newElem;
	}
}

bool LinkedList::isEmpty() //checking if the list is empty
{
	if (size == 0) //if there are no elements in the list
		return true;
	else //if there is at least one element in the list
		return false;
}

size_t LinkedList::find_last(LinkedList List) //returning index of the beginning last sublist 
{
	Node* current = tail;
	size_t counter = 0;
	while ((current->previous != nullptr) && (size - counter >= List.get_size() - 1))
	{
		while ((current->data != List.at(List.get_size() - 1)) && (current->previous != nullptr))
		{
			current = current->previous;
			counter++;
		}
		for (size_t i = 1; (current->data == List.at(List.get_size() - i) && (current->previous != nullptr) && (i < List.get_size())); i++)
		{
			current = current->previous;
			counter++;
		}
		if (current->data == List.at(0)) //if there is sublist
			return (size - 1 - counter);
	}
	if (current->previous == nullptr) //if there isn't sublist
		throw "There are no list in this list";
}

void LinkedList::add_freq(Node* current)
{
	current->freq++;
}

bool LinkedList::find(char data) 
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data == data)
		{
			add_freq(current);
			return true;
		}
		current = current->next;
	}
	return false;
}

bool LinkedList::find(string str)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->code == str)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

char LinkedList::findSymbol(string str)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->code == str)
		{
			return current->data;
		}
		current = current->next;
	}
}

LinkedList::Node* LinkedList::findNode(char data)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data == data)
		{
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

string LinkedList::findCode(char data)
{
	Node* current = findNode(data);
	if (current != nullptr)
		return current->code;
}

void LinkedList::CodeNode(char data, bool bin)
{
	Node* current = findNode(data);
	if (current != nullptr)
	{
		if (bin)
			current->code.push_back('1');
		else
			current->code.push_back('0');
	}
}

void LinkedList::swap(Node* x, Node* y)
{
	Node* temp = new Node;
	temp->freq = x->freq;
	temp->data = x->data;
	x->freq = y->freq;
	x->data = y->data;
	y->freq = temp->freq;
	y->data = temp->data;
	delete temp;
}

void LinkedList::bubbleSort()
{
	Node* current;
	if (head != tail)
	{
		for (size_t i = 0; i < size - 1; i++)
		{
			current = head;
			do
			{
				if (current->next->freq > current->freq)
					swap(current->next, current);
				current = current->next;
			} while (current != tail);
		}
	}
}

Iterator* LinkedList::create_iterator()
{
	return new iterator(head);
}

int LinkedList::iterator::freq()
{
	return cur->freq;
}

char LinkedList::iterator::symbol()
{
	return cur->data;
}

string LinkedList::iterator::code()
{
	return cur->code;
}

bool LinkedList::iterator::has_current()
{
	return (cur != nullptr);
}

void LinkedList::iterator::next()
{
	cur = cur->next;
}


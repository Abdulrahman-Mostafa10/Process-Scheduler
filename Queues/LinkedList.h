#pragma once

#include "Node.h"
#include<iostream>
using namespace std;
template <typename T>
class LinkedList
{
protected:
	Node<T>* Head;	//Pointer to the head of the list

	int count;
public:


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}

	~LinkedList()
	{
		DeleteAll();
	}
	void InsertBeg(const T& data)
	{
		count++;
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			count = 0;
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	void InsertEnd(const T& data)
	{
		count++;
		Node<T>* ptr = Head;
		if (!Head)
		{
			Head = new Node<T>(data);
		}
		else
		{
			while (ptr->getNext())
			{
				ptr = ptr->getNext();
			}
			Node<T>* ptr2 = new Node<T>(data);
			ptr->setNext(ptr2);
		}
	}

	bool DeleteFirst(T& x)
	{
		Node<T>* ptr = Head;
		if (ptr)
		{
			count--;
			Head = Head->getNext();
			x = ptr->getItem();
			//delete ptr;
			return 1;
		}
		return 0;
	}

	bool DeleteNode(int num, T& x) {
		if (!isEmpty())
		{
			Node<T>* ptr = Head;

			if (*(ptr->getItem()) == num)
			{
				x = ptr->getItem();
				Head = Head->getNext();
				ptr = nullptr;
				count--;
				return true;
			}
			else
			{
				Node<T>* prev = Head;
				ptr = Head->getNext();
				while (ptr)
				{
					if (*(ptr->getItem()) == num)
					{
						x = ptr->getItem();
						prev->setNext(ptr->getNext());
						ptr = nullptr;
						count--;
						return true;
					}
					prev = ptr;
					ptr = ptr->getNext();
				}
			}
			return false;
		}
		return false;
	};

	bool isEmpty()
	{
		if (Head == nullptr)
			return true;
		else return false;
	}
	void print()
	{
		Node<T>* ptr = Head;
		while (ptr)
		{
			cout << ptr->getItem() << "  ";
			ptr = ptr->getNext();
		}
		cout << endl;
	}
	int GetCount() {
		Node<T>* Trns = Head;
		int C = 0;
		while ((Trns))
		{
			C++;
			Trns = Trns->getNext();
		}
		return C;
	}

};


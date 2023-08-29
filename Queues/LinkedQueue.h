#pragma once
#include "Node.h"
#include "QueueADT.h"
#include<iostream>
using namespace std;


template <typename T>
class LinkedQueue :public QueueADT<T>
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	int getCount();
	bool enqueueshortest(T& newEntry);
		~LinkedQueue();
	void print();
	//copy constructor
	LinkedQueue(const LinkedQueue<T>& LQ);
};
template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template <typename T>
int LinkedQueue<T>::getCount() {
	int c = 0;
	Node<T>* temp = frontPtr;
	if (!frontPtr)
	{
		return 0;
	}
	while (temp)
	{
		c++;
		temp = temp->getNext();
	}
	return c;
}

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue


template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;

}

template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}
template<class T>
bool LinkedQueue<T>::enqueueshortest(T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	Node<T>* ptr = frontPtr;
	// Insert the new node

	if (isEmpty())	//special case if this is the first node to insert
		backPtr = frontPtr = newNodePtr; // The queue is empty
	else if (*(newEntry) < (frontPtr->getItem()))
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else if (*(newEntry) == (frontPtr->getItem()))
	{
		newNodePtr->setNext(frontPtr->getNext());
		frontPtr->setNext(newNodePtr);
		if (frontPtr == backPtr)
			backPtr = newNodePtr;
	}
	else if (*(newEntry) >= (backPtr->getItem()))
	{
		backPtr->setNext(newNodePtr);
		backPtr = newNodePtr;
	}
	else
	{
		Node<T>* prev = frontPtr;
		ptr = prev->getNext();
		while (ptr)
		{
			if (*(newEntry) >= (prev->getItem()) && *(newEntry) < (ptr->getItem()))
			{
				newNodePtr->setNext(ptr);
				prev->setNext(newNodePtr);
				break;
			}
			ptr = ptr->getNext();
			prev = prev->getNext();

		}
		if (newNodePtr->getNext() == nullptr)
		{
			backPtr = newNodePtr;
		}
	}
	// New node is the last node now
	return true;
}
template<class T>
void LinkedQueue<T>:: print()
{
	Node<T>* ptr = frontPtr;
	while (ptr)
	{
		cout <<  ptr->getItem() << "  ";
		ptr = ptr->getNext();
	}
	cout << endl;
}


#include"Node.h"
#include"LinkedQueue.h"
#include"process.h"
class EDFQ : public LinkedQueue<process*>
{
public:
	bool enqueueshortestDL(process* newEntry)
	{
		Node<process*>* newNodePtr = new Node<process*>(newEntry);
		Node<process*>* ptr = frontPtr;
		// Insert the new node

		if (isEmpty())	//special case if this is the first node to insert
			backPtr = frontPtr = newNodePtr; // The queue is empty
		else if ((newEntry->getdeadline()) < (frontPtr->getItem()->getdeadline()))
		{
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
		}
		else if ((newEntry->getdeadline()) == (frontPtr->getItem()->getdeadline()))
		{
			newNodePtr->setNext(frontPtr->getNext());
			frontPtr->setNext(newNodePtr);
			if (frontPtr == backPtr)
				backPtr = newNodePtr;
		}
		else if ((newEntry->getdeadline()) >= (backPtr->getItem()->getdeadline()))
		{
			backPtr->setNext(newNodePtr);
			backPtr = newNodePtr;
		}
		else
		{
			Node<process*>* prev = frontPtr;
			ptr = prev->getNext();
			while (ptr)
			{
				if ((newEntry->getdeadline()) >= (prev->getItem()->getdeadline()) && (newEntry->getdeadline()) < (ptr->getItem()->getdeadline()))
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

};

#pragma once
#include"LinkedList.h"
#include"Node.h"
#include"process.h"
class LinkedListprocess :public LinkedList<process*>
{
public:
	process* getnonchild()
	{
		if (!isEmpty())
		{
			Node<process*>* ptr = Head;
			Node<process*>* prev = Head;
			if (ptr->getItem()->getischild() == false)
			{
				Head = Head->getNext();
				return ptr->getItem();
			}
			ptr = ptr->getNext();
				while (ptr != nullptr)
				{
					if (ptr->getItem()->getischild() == false)
					{
						break;
					}
					prev = ptr;
					ptr = ptr->getNext();
				}
				if (ptr == nullptr)
				{
					return nullptr;
				}
				else
				{
					prev->setNext(ptr->getNext());
				}
			if (ptr)
			{
				return ptr->getItem();
			}
			
		}

	}




};
#pragma once
#include<iostream>
#include<stdlib.h>
#include<string>
#include<functional>
using namespace std;

//node difinition
template<typename type> class Node
{
public:
	type data;
	type originIndex;
	Node<type> *pNext;
};
//list definition
template<typename type> class SingleList
{
public:
	SingleList();
	~SingleList();
	Node<type> *GetTheEndNode();
	Node<type> *GetTheHeadNode();
	int GetListLength();
	void CreatList(int size);
	void InsertNode(int position, type data, type originIndex);
	void Add(type data);
	void Delete(int position);
	void Delete();
	void Sort(bool isPositiveOrder, Node<type> *pHead, Node<type> *pEnd, bool (*Compare)(type, type) = SingleList<type>::compare);
	void Display();
	type GetDataByPosition(int position);
	type GetOriginIndexByPosition(int position);
private:
	Node<type> *head;//the head node
	int listSize;
	static bool compare(type lNode, type rNode)//definition functor
	{
		return std::less_equal<type>()(lNode, rNode);//if the lNode is smaller than the rNode return TRUE
	}
};

template<typename type>
inline SingleList<type>::SingleList()
{
	head = new Node<type>;
	head->data = 0;
	head->originIndex = 0;
	head->pNext = NULL;
}

template<typename type>
inline SingleList<type>::~SingleList()
{
	std::cout << "Call the destructor function" << endl;
	//if you not delete the all node, may cause memory leak
	if (head)
	{
		Node<type> *work;
		while (head)
		{
			work = head->pNext;
			delete head;
			head = work;
		}
	}
}

template<typename type>
inline Node<type>* SingleList<type>::GetTheEndNode()
{
	Node<type> *pEnd = head;
	while (pEnd->pNext)
	{
		pEnd = pEnd->pNext;
	}

	return pEnd;
}

template<typename type>
inline Node<type>* SingleList<type>::GetTheHeadNode()
{
	return head;
}

template<typename type>
inline int SingleList<type>::GetListLength()
{
	return listSize;
}

template<typename type> 
inline void SingleList<type>::CreatList(int size)
{
	type temp1 = -999;
	type temp2 = 0;

	listSize = size;

	if (size < 1)
	{
		std::cout << "Illegal size !" << endl;
		return;
	}

	Node<type> *pNew, *pTemp;
	pTemp = head;
	int i = size;
	while (size-- > 0)
	{
		pNew = new Node<type>;
		std::cout << "Please input the " << i - size << "th data: ";
		std::cin >> temp2;
		while (temp2 <= temp1)
		{
			std::cout << "Please input a larger number !" << endl << "\t\tfor " << i - size << "th data: ";
			std::cin >> temp2;
		}
		temp1 = temp2;
		pNew->data = temp2;
		pNew->pNext = NULL;
		pTemp->pNext = pNew;
		pTemp = pNew;
	}	
}

template<typename type>
inline void SingleList<type>::InsertNode(int position, type data, type originIndex)
{
	if (position < 0 || position > listSize + 1)
	{
		std::cout << "Position is error or beyond size!" << endl;
		return;
	}
	Node<type> *pNew, *pTemp;
	pTemp = head;

	pNew = new Node<type>;
	pNew->data = data;
	pNew->originIndex = originIndex;
	pNew->pNext = NULL;

	while (position-- > 1)
		pTemp = pTemp->pNext;

	pNew->pNext = pTemp->pNext;
	pTemp->pNext = pNew;

	listSize++;
}
//add one node behind the last node
template<typename type>
inline void SingleList<type>::Add(type data)
{
	int length = listSize;

	Node<type> *pNew, *pTemp;
	pTemp = head;

	pNew = new Node<type>;
	pNew->data = data;
	pNew->pNext = NULL;

	do
	{
		pTemp = pTemp->pNext;
	} while (length-- >1);

	pNew->pNext = pTemp->pNext;
	pTemp->pNext = pNew;

	listSize++;
}

template<typename type>
inline void SingleList<type>::Delete(int position)
{
	if (position < 1 || position > listSize)
	{
		std::cout << "Position is error or beyond size!" << endl;
		return;
	}

	Node<type> *pTemp = head, *pDelete;

	while (position-- > 1)
		pTemp = pTemp->pNext;

	pDelete = pTemp->pNext;
	pTemp->pNext = pDelete->pNext;
	delete pDelete;

	pDelete = NULL;

	listSize--;
}

template<typename type>
inline void SingleList<type>::Delete()
{
	string isDelete;
	std::cout << "WARNING !!\n" << "Are you sure delete the whole list ??" << endl;
	std::cout << "If you want go on, please input \"YES\" !" << endl;

	std::cin >> isDelete;
	if (isDelete == "YES")
	{
		Node<type> *pDelete = head->pNext, *pTemp;
		while (pDelete != NULL)
		{
			pTemp = pDelete->pNext;
			head->pNext = pTemp;
			delete pDelete;
			pDelete = pTemp;

			listSize--;
		}
	}
	else
	{
		std::cout << "Function has exited" << endl;
		return;
	}
}

template<typename type>
inline void SingleList<type>::Sort(bool isPositiveOrder, Node<type> *pHead, Node<type> *pEnd, bool (*Compare)(type, type) = SingleList::compare)
{
	if (pHead == NULL || pEnd == NULL)
		return;
	if (pHead == pEnd)
		return;

	Node<type> *pSlow = pHead;
	Node<type> *pFast = pHead->pNext;
	Node<type> *pTemp = pHead;

	if (isPositiveOrder)
	{
		while (pFast && pFast != pEnd->pNext)
		{
			if (Compare(pFast->data, pHead->data))//i don't know why i use this method which is too complex to understand, 
			{									//and cause my brain a lot, and not as good as i thought
				pTemp = pSlow;
				pSlow = pSlow->pNext;
				swap(pSlow->data, pFast->data);
			}
			/*if (pFast->data <= pHead->data)
			{
				pTemp = pSlow;
				pSlow = pSlow->pNext;
				swap(pSlow->data, pFast->data);
			}*/

			pFast = pFast->pNext;
		}

		swap(pHead->data, pSlow->data);

		Sort(true, pHead, pTemp);
		Sort(true, pSlow->pNext, pEnd);
	}
	else
	{
		while (pFast && pFast != pEnd->pNext)
		{
			if (!Compare(pFast->data, pHead->data))
			{
				pTemp = pSlow;
				pSlow = pSlow->pNext;
				swap(pSlow->data, pFast->data);
			}
			/*if (pFast->data >= pHead->data)
			{
				pTemp = pSlow;
				pSlow = pSlow->pNext;
				swap(pSlow->data, pFast->data);
			}*/

			pFast = pFast->pNext;
		}

		swap(pHead->data, pSlow->data);

		Sort(false, pHead, pTemp);
		Sort(false, pSlow->pNext, pEnd);
	}
}

template<typename type>
inline void SingleList<type>::Display()
{
	if (listSize == 0)
	{
		std::cout << "List is not exist !" << endl;
		return;
	}

	Node<type> *p = head->pNext;
	while (p != NULL)
	{
		std::cout << "Pwd: " << p->data << "   " << "OriginIndex: " << p->originIndex << endl;
		p = p->pNext;
	}
	std::cout << endl << "All data has been displayed !" << endl;
}

template<typename type>
inline type SingleList<type>::GetDataByPosition(int position)
{
	if (position < 1 || position > listSize)
	{
		std::cout << "Position is error or beyond size!" << endl;
		return 0;
	}

	Node<type> *pTemp = head;

	while (position-- > 1)
		pTemp = pTemp->pNext;

	pTemp = pTemp->pNext;

	return pTemp->data;
}

template<typename type>
inline type SingleList<type>::GetOriginIndexByPosition(int position)
{
	if (position < 1 || position > listSize)
	{
		std::cout << "Position is error or beyond size!" << endl;
		return 0;
	}

	Node<type> *pTemp = head;

	while (position-- > 1)
		pTemp = pTemp->pNext;

	pTemp = pTemp->pNext;

	return pTemp->originIndex;
}

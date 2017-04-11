#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

//单链表 面向过程 c语言

typedef struct SListNode
{
	int _data;
	struct SListNode * _next;
	SListNode()
	{

	}

	SListNode(int  x)
		:_data(x)
		, _next(NULL)
	{

	}
}SListNode;

//void InitSList(SListNode ** head, int x) //必须是二级指针，否则一个指针传过去，是值传递，相当于拷贝了一个临时指针变量，不会该变原来的指针；
//{
//	*head = NULL;
//}
//
//SListNode * BuyNode(int x)
//{
//	SListNode * node = (SListNode *)malloc(sizeof(SListNode));
//	node->_data = x;
//	node->_next = NULL;
//
//	return node;
//}

//void PushBack(SListNode ** Head, int x)
//{
//
//	if (*Head == NULL) //没有数据
//	{
//		*Head = BuyNode(x);
//	}
//	else
//	{
//		SListNode * node = BuyNode(x);
//		SListNode * cur = *Head;
//
//		while (cur->_next != NULL)
//		{
//			cur = cur->_next;
//		}
//
//		cur->_next = node;
//	}
//}
//
//void Destory(SListNode ** head)
//{
//	assert(*head);
//	SListNode * cur = *head;
//
//	while (cur != NULL)
//	{
//		SListNode *del = cur;
//		cur = del->_next;
//		free(del);
//
//	}
//}
//void TestSList()
//{
//	SListNode *Head = NULL;
//	PushBack(&Head, 1);
//	PushBack(&Head, 2);
//	PushBack(&Head, 3);
//	PushBack(&Head, 4);
//
//}

//在c++中可以传引用来代替二级指针；
void InitSList(SListNode *& head)
{
	head = NULL;
}

void PushBack(SListNode *& head, int  x) //尾插
{
	if (head == NULL)
	{
		head = new SListNode(x); //c++可以使用new申请空间，释放也必须用delete；
	}
	else
	{
		SListNode *cur = head;

		while (cur->_next != NULL)
		{
			cur = cur->_next;
		}
		cur->_next = new SListNode(x);
	}
}

void PopBack(SListNode *& head) //尾删
{
	assert(head);
	SListNode *prev = NULL;
	SListNode * cur = head;
	if (head->_next == NULL)
	{
		delete head;
		head = NULL;
		return;
	}
	while (cur->_next != NULL) //找到尾节点；
	{
		prev = cur;
		cur = cur->_next;
	}

	delete cur;
	prev->_next = NULL;

}

void PrintReseveSList(SListNode *head)  //逆序打印链表
{
	if (head == NULL)
		return;
	PrintReseveSList(head->_next);
	cout << head->_data << " ";
}

void PrintSList(SListNode *head)  //打印链表
{
	while (head != NULL)
	{
		cout << head->_data << " ";
		head = head->_next;
	}

	cout << endl;
}

void RemoveNode(SListNode *&head, int value) //删除值为value的第一个节点
{
	assert(head);
	SListNode *cur = head;
	SListNode *prev = head;

	if (cur->_data == value)
	{
		head = cur->_next;
		delete cur;
		
	}
	else
	{
		while (cur != NULL)
		{
			if (cur->_data == value)
			{
				prev->_next = cur->_next;
				delete cur;
				break;
			}

			prev = cur;
			cur = cur->_next;
		}
	}
	
}

size_t Size(SListNode * head)  //链表长度即大小
{
	size_t count = 0;
	while (head != NULL)
	{
		count++;
		head = head->_next;
	}
	return count;
}
/*找到链表倒数第k个节点
法一：先算出链表的长度，倒数第k个就是从到向后遍历的第Size - k个，需要遍历两次链表;
法二：利用快慢指针，慢指针指向头，快指针先走K步，然后两个同时走，直到快指针走到NUll（即结尾），此时慢指针就在倒数第k个节点；
*/
//SListNode & FindRKNode(SListNode * head,int k) //法一
//{
//
//	int count = Size(head) - k;
//	for (int i = 0; i < count;i++)
//	{
//		head = head->_next;
//	}
//
//	return *head;
//}
SListNode & FindRKNode(SListNode * head, int k) //法二快慢指针
{
	SListNode *fast = head;  
	for (int i = 0; i < k; i++) //先走K步
		fast = fast->_next;
	
	SListNode *slow = head;

	while (fast != NULL)
	{
		fast = fast->_next;
		slow = slow->_next;
	}

	return *slow;
}
/*删除一个无头链表的非尾节点
无头：没有给出头节点，只给出了要删除的节点；
思想：将其和下一个节点的值互换，再删除下一个节点；
*/
void DeleteNonTailNode(SListNode * node)
{
	assert(node->_next); //判断是否是尾节点；

	SListNode *next = node->_next;
	swap(node->_data,next->_data); //将两个节点的内容进行交换;
	node->_next = next->_next;

	delete next;
}

/*链表的逆至
法一：建立一个新的头节点，从头到尾遍历旧链表，将每个节点头插到新链表上，就完成了逆至；O(N);
法二：可以尝试将指针翻转；
*/
void Reverse(SListNode *& head)
{
	if (head == NULL || head->_next == NULL) //若链表只有一个节点或者无节点，不用逆至
	{
		return;
	}
	else
	{
		SListNode *newHead = NULL;
		SListNode *cur = head;
		while (cur)  //将tmp的next指向newHead，再将newHead指向tmp,重复执行，相当于头插
		{
			SListNode *tmp = cur;
			tmp->_next = newHead;
			newHead = tmp;
			cur = cur->_next;
		}
		head = newHead;
	}
}
/*合并两个排序的链表
非递归：两个指针，比较连个节点的值，升序，小的先尾插
递归：子问题化，若一个人链表的一个节点已经取走，将下一个节点当作头节点，即子问题化；
*/
/*
void MergeSList(SListNode *& head1, SListNode *& head2)  //升序 非递归
{
	if (head1 == NULL)
		head1 = head2;
	SListNode *newHead = NULL;
	SListNode *cur = newHead;
	SListNode * prev = cur;
	while (head1 != NULL ||  head2 != NULL)
	{
		if (head1 == NULL)  //若有一个先为空
		{
			cur->_next = head2;
			break;
		}
		if (head2 == NULL)
		{
			cur->_next = head1;
			break;
		}

		//两个链表均不为空
		if (head1->_data < head2->_data)
		{
			cur = head1;
			head1 = head1->_next;
			if (prev)
				prev->_next = cur;
		}
		else
		{
			cur = head2;
			head2 = head2->_next;
			if (prev)
				prev->_next = cur;
		}
		prev = cur;
		prev->_next = NULL;

		if (newHead == NULL)  //将newHead指向链表的头；
		{
			newHead = prev;
		}
	}

	head1 = newHead;
	head2 = NULL;  //最后head2至空；
}*/

SListNode * MergeSList(SListNode * head1,SListNode * head2)  //升序；
{
	if (head1 == NULL)
		return head2;
	if (head2 == NULL)
		return head1;

	SListNode * newHead = NULL;

	if (head1->_data < head2->_data)
	{
		newHead = head1;
		newHead->_next = MergeSList(head1->_next, head2);
	}
	else
	{
		newHead = head2;
		newHead->_next = MergeSList(head1, head2->_next);
	}

	return newHead;
}

void TestSList()
{
	SListNode * head;
	InitSList(head);
	PushBack(head,1);
	PushBack(head, 3);
	PushBack(head, 8);
	PushBack(head, 10);
	PopBack(head);
	PrintSList(head);
	//PrintReseveSList(head);

	/*cout << FindRKNode(head, 2)._data << endl;
	DeleteNonTailNode(&FindRKNode(head, 2));
	PrintSList(head);*/

	/*Reverse(head); //逆至测试
	PrintSList(head);*/

	SListNode *head2;
	InitSList(head2);
	PushBack(head2,2);
	PushBack(head2, 4);
	PushBack(head2, 9);
	PushBack(head2, 12);
	PushBack(head2, 15);
	PushBack(head2, 18);

	//MergeSList(head,head2); //非递归合并测试;
	
	/*SListNode *head3; //递归合并测试;
	head3 = MergeSList(head,head2);
	PrintSList(head3);*/
}
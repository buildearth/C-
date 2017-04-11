#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

//������ ������� c����

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

//void InitSList(SListNode ** head, int x) //�����Ƕ���ָ�룬����һ��ָ�봫��ȥ����ֵ���ݣ��൱�ڿ�����һ����ʱָ�����������ñ�ԭ����ָ�룻
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
//	if (*Head == NULL) //û������
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

//��c++�п��Դ��������������ָ�룻
void InitSList(SListNode *& head)
{
	head = NULL;
}

void PushBack(SListNode *& head, int  x) //β��
{
	if (head == NULL)
	{
		head = new SListNode(x); //c++����ʹ��new����ռ䣬�ͷ�Ҳ������delete��
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

void PopBack(SListNode *& head) //βɾ
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
	while (cur->_next != NULL) //�ҵ�β�ڵ㣻
	{
		prev = cur;
		cur = cur->_next;
	}

	delete cur;
	prev->_next = NULL;

}

void PrintReseveSList(SListNode *head)  //�����ӡ����
{
	if (head == NULL)
		return;
	PrintReseveSList(head->_next);
	cout << head->_data << " ";
}

void PrintSList(SListNode *head)  //��ӡ����
{
	while (head != NULL)
	{
		cout << head->_data << " ";
		head = head->_next;
	}

	cout << endl;
}

void RemoveNode(SListNode *&head, int value) //ɾ��ֵΪvalue�ĵ�һ���ڵ�
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

size_t Size(SListNode * head)  //�����ȼ���С
{
	size_t count = 0;
	while (head != NULL)
	{
		count++;
		head = head->_next;
	}
	return count;
}
/*�ҵ���������k���ڵ�
��һ�����������ĳ��ȣ�������k�����Ǵӵ��������ĵ�Size - k������Ҫ������������;
���������ÿ���ָ�룬��ָ��ָ��ͷ����ָ������K����Ȼ������ͬʱ�ߣ�ֱ����ָ���ߵ�NUll������β������ʱ��ָ����ڵ�����k���ڵ㣻
*/
//SListNode & FindRKNode(SListNode * head,int k) //��һ
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
SListNode & FindRKNode(SListNode * head, int k) //��������ָ��
{
	SListNode *fast = head;  
	for (int i = 0; i < k; i++) //����K��
		fast = fast->_next;
	
	SListNode *slow = head;

	while (fast != NULL)
	{
		fast = fast->_next;
		slow = slow->_next;
	}

	return *slow;
}
/*ɾ��һ����ͷ����ķ�β�ڵ�
��ͷ��û�и���ͷ�ڵ㣬ֻ������Ҫɾ���Ľڵ㣻
˼�룺�������һ���ڵ��ֵ��������ɾ����һ���ڵ㣻
*/
void DeleteNonTailNode(SListNode * node)
{
	assert(node->_next); //�ж��Ƿ���β�ڵ㣻

	SListNode *next = node->_next;
	swap(node->_data,next->_data); //�������ڵ�����ݽ��н���;
	node->_next = next->_next;

	delete next;
}

/*���������
��һ������һ���µ�ͷ�ڵ㣬��ͷ��β������������ÿ���ڵ�ͷ�嵽�������ϣ��������������O(N);
���������Գ��Խ�ָ�뷭ת��
*/
void Reverse(SListNode *& head)
{
	if (head == NULL || head->_next == NULL) //������ֻ��һ���ڵ�����޽ڵ㣬��������
	{
		return;
	}
	else
	{
		SListNode *newHead = NULL;
		SListNode *cur = head;
		while (cur)  //��tmp��nextָ��newHead���ٽ�newHeadָ��tmp,�ظ�ִ�У��൱��ͷ��
		{
			SListNode *tmp = cur;
			tmp->_next = newHead;
			newHead = tmp;
			cur = cur->_next;
		}
		head = newHead;
	}
}
/*�ϲ��������������
�ǵݹ飺����ָ�룬�Ƚ������ڵ��ֵ������С����β��
�ݹ飺�����⻯����һ���������һ���ڵ��Ѿ�ȡ�ߣ�����һ���ڵ㵱��ͷ�ڵ㣬�������⻯��
*/
/*
void MergeSList(SListNode *& head1, SListNode *& head2)  //���� �ǵݹ�
{
	if (head1 == NULL)
		head1 = head2;
	SListNode *newHead = NULL;
	SListNode *cur = newHead;
	SListNode * prev = cur;
	while (head1 != NULL ||  head2 != NULL)
	{
		if (head1 == NULL)  //����һ����Ϊ��
		{
			cur->_next = head2;
			break;
		}
		if (head2 == NULL)
		{
			cur->_next = head1;
			break;
		}

		//�����������Ϊ��
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

		if (newHead == NULL)  //��newHeadָ�������ͷ��
		{
			newHead = prev;
		}
	}

	head1 = newHead;
	head2 = NULL;  //���head2���գ�
}*/

SListNode * MergeSList(SListNode * head1,SListNode * head2)  //����
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

	/*Reverse(head); //��������
	PrintSList(head);*/

	SListNode *head2;
	InitSList(head2);
	PushBack(head2,2);
	PushBack(head2, 4);
	PushBack(head2, 9);
	PushBack(head2, 12);
	PushBack(head2, 15);
	PushBack(head2, 18);

	//MergeSList(head,head2); //�ǵݹ�ϲ�����;
	
	/*SListNode *head3; //�ݹ�ϲ�����;
	head3 = MergeSList(head,head2);
	PrintSList(head3);*/
}
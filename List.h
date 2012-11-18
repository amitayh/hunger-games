#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>

class ListNode
{
    void* data;
    ListNode *prev, *next;

public:
    ListNode(void* data = NULL, ListNode* prev = NULL, ListNode* next = NULL);

    void SetPrev(ListNode* prev);
    void SetNext(ListNode* next);

    void* GetData();
    ListNode* GetNext();
    ListNode* GetPrev();
};

class List
{
    ListNode head, tail; // Dummy nodes
    int size;

public:
    List();
    ~List();

    void Insert(void* data, ListNode* after);
    void Remove(ListNode* node);
    void Push(void* data);
    void* Pop();

    void* Peek();
    ListNode* Find(void* data);
    ListNode* GetHead();
    ListNode* GetTail();
    int GetSize();
    bool IsEmpty();
};

class ListIterator
{
    List* list;
    ListNode* current;
public:
    ListIterator(List* list);

    bool Done();
    ListNode* Current();
};

#endif
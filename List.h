#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>

class ListNode
{
    void *data;
    ListNode *prev, *next;

public:
    ListNode(void *data = NULL, ListNode *prev = NULL, ListNode *next = NULL);

    void SetPrev(ListNode *prev);
    void SetNext(ListNode *next);

    void *GetData() const;
    ListNode *GetNext() const;
    ListNode *GetPrev() const;
};

class List
{
    ListNode head, tail; // Dummy nodes
    int size;

public:
    List();
    ~List();

    void Insert(void *data, ListNode *after);
    void Remove(ListNode *node);
    void Push(void *data);
    void *Pop();

    ListNode *Find(const void *data);
    ListNode *GetHead();
    ListNode *GetTail();
    void *Peek() const;
    int GetSize() const;
    bool IsEmpty() const;
};

class ListIterator
{
    List *list;
    ListNode *current;
public:
    ListIterator(List *list);

    ListNode *Current();
    bool Done() const;
};

#endif
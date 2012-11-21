#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>

class ListNode
{
    const void *data;
    ListNode *prev, *next;

public:
    ListNode(const void *data = NULL, ListNode *prev = NULL, ListNode *next = NULL);

    void SetPrev(ListNode *prev);
    void SetNext(ListNode *next);

    const void *GetData() const;
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

    void Insert(const void *data, ListNode *after);
    void Remove(ListNode *node);
    void Push(const void *data);
    const void *Pop();

    ListNode *Find(const void *data) const;
    const ListNode *GetHead() const;
    const ListNode *GetTail() const;
    const void *Peek() const;
    int GetSize() const;
    bool IsEmpty() const;
};

class ListIterator
{
    const List *list;
    ListNode *current;
public:
    ListIterator(const List &list);

    ListNode *Current();

    bool Done() const;
};

#endif
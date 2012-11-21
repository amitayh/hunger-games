#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>

class ListNode
{
    const void* data;
    ListNode* prev;
    ListNode* next;

public:
    ListNode(const void* data = NULL, ListNode* prev = NULL, ListNode* next = NULL);

    void setPrev(ListNode* prev);
    void setNext(ListNode* next);

    const void* getData() const;
    ListNode* getNext() const;
    ListNode* getPrev() const;
};

class List
{
    ListNode head, tail; // Dummy nodes
    int size;

public:
    List();
    ~List();

    void insert(const void* data, ListNode* after);
    void remove(ListNode* node);
    void push(const void* data);
    const void* pop();

    ListNode* find(const void* data) const;
    const ListNode* getHead() const;
    const ListNode* getTail() const;
    const void* peek() const;
    int getSize() const;
    bool isEmpty() const;
};

class ListIterator
{
    const List* list;
    ListNode* current;
public:
    ListIterator(const List& list);

    ListNode* getCurrent();

    bool done() const;
};

#endif
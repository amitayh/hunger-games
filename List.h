#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>

class List
{
public:
    // List node
    class Node
    {
        const void* data;
        Node* prev;
        Node* next;
    public:
        Node(const void* data = NULL, Node* prev = NULL, Node* next = NULL);
        const void* getData() const;
        friend class List;
    };

    // List iterator
    class Iterator
    {
        const List* list;
        Node* current;
    public:
        Iterator(const List& list);
        Node* getCurrent();
        bool done() const;
    };

    List();
    ~List();

    void insert(const void* data, Node* after);
    void remove(Node* node);
    void push(const void* data);
    const void* pop();

    Node* find(const void* data) const;
    const void* peek() const;
    int getSize() const;
    bool isEmpty() const;

private:
    Node head, tail; // Dummy nodes
    int size;
};

#endif
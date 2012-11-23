#include "List.h"

// List node implementation

List::Node::Node(const void* data, Node* prev, Node* next) {
    this->data = data;
    this->prev = prev;
    this->next = next;
}

const void* List::Node::getData() const {
    return data;
}

// List container implementation

List::List() {
    head.next = &tail;
    tail.prev = &head;
    size = 0;
}

List::~List() {
    while (!isEmpty()) {
        pop();
    }
}

void List::insert(const void* data, Node* after) {
    Node* node = new Node(data, after, after->next);
    after->next->prev = node;
    after->next = node;
    size++;
}

void List::remove(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    size--;
}

void List::push(const void* data) {
    insert(data, tail.prev);
}

const void* List::pop() {
    if (size) {
        Node* node = tail.prev;
        const void* data = node->data;
        remove(node);
        return data;
    }
    return NULL;
}

List::Node* List::find(const void* data) const {
    Node* result = NULL;
    Node* current;
    Iterator it(*this);
    while (!result && !it.done()) {
        current = it.getCurrent();
        if (current->getData() == data) {
            result = current;
        }
    }
    return result;
}

const void* List::peek() const {
    return size ? head.next->data : NULL;
}

int List::getSize() const {
    return size;
}

bool List::isEmpty() const {
    return (size == 0);
}

// List iterator implementation

List::Iterator::Iterator(const List& list) {
    this->list = &list;
    current = list.head.next;
}

List::Node* List::Iterator::getCurrent() {
    List::Node* node = current;
    current = current->next;
    return node;
}

bool List::Iterator::done() const {
    return (current == &list->tail);
}
#include "List.h"

// List node implementation

ListNode::ListNode(const void* data, ListNode* prev, ListNode* next) {
    this->data = data;
    this->prev = prev;
    this->next = next;
}

void ListNode::setPrev(ListNode* prev) {
    this->prev = prev;
}

void ListNode::setNext(ListNode* next) {
    this->next = next;
}

const void* ListNode::getData() const {
    return data;
}

ListNode* ListNode::getNext() const {
    return next;
}

ListNode* ListNode::getPrev() const {
    return prev;
}

// List container implementation

List::List() {
    head.setNext(&tail);
    tail.setPrev(&head);
    size = 0;
}

List::~List() {
    while (!isEmpty()) {
        pop();
    }
}

void List::insert(const void* data, ListNode* after) {
    ListNode* node = new ListNode(data, after, after->getNext());
    after->getNext()->setPrev(node);
    after->setNext(node);
    size++;
}

void List::remove(ListNode* node) {
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
    delete node;
    size--;
}

void List::push(const void* data) {
    insert(data, tail.getPrev());
}

const void* List::pop() {
    if (size) {
        ListNode* node = tail.getPrev();
        const void* data = node->getData();
        remove(node);
        return data;
    }
    return NULL;
}

ListNode* List::find(const void* data) const {
    ListNode* result = NULL;
    ListNode* current;
    ListIterator it(*this);
    while (!result && !it.done()) {
        current = it.getCurrent();
        if (current->getData() == data) {
            result = current;
        }
    }
    return result;
}

const ListNode* List::getHead() const {
    return &head;
}

const ListNode* List::getTail() const {
    return &tail;
}

const void* List::peek() const {
    return size ? head.getNext()->getData() : NULL;
}

int List::getSize() const {
    return size;
}

bool List::isEmpty() const {
    return (size == 0);
}

// List iterator implementation

ListIterator::ListIterator(const List& list) {
    this->list = &list;
    current = list.getHead()->getNext();
}

ListNode* ListIterator::getCurrent() {
    ListNode* node = current;
    current = current->getNext();
    return node;
}

bool ListIterator::done() const {
    return (current == list->getTail());
}
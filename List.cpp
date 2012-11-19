#include "List.h"

// List node implementation

ListNode::ListNode(void* data, ListNode* prev, ListNode* next) {
    this->data = data;
    this->prev = prev;
    this->next = next;
}

void ListNode::SetPrev(ListNode* prev) {
    this->prev = prev;
}

void ListNode::SetNext(ListNode* next) {
    this->next = next;
}

void* ListNode::GetData() const {
    return data;
}

ListNode* ListNode::GetNext() const {
    return next;
}

ListNode* ListNode::GetPrev() const {
    return prev;
}

// List container implementation

List::List() {
    head.SetNext(&tail);
    tail.SetPrev(&head);
    size = 0;
}

List::~List() {
    while (!IsEmpty()) {
        Pop();
    }
}

void List::Insert(void* data, ListNode* after) {
    ListNode* node = new ListNode(data, after, after->GetNext());
    after->GetNext()->SetPrev(node);
    after->SetNext(node);
    size++;
}

void List::Remove(ListNode* node) {
    node->GetPrev()->SetNext(node->GetNext());
    node->GetNext()->SetPrev(node->GetPrev());
    delete node;
    size--;
}

void List::Push(void* data) {
    Insert(data, tail.GetPrev());
}

void* List::Pop() {
    if (size) {
        ListNode* node = tail.GetPrev();
        void* data = node->GetData();
        Remove(node);
        return data;
    }
    return NULL;
}

ListNode* List::Find(void* data) {
    ListIterator it(this);
    ListNode* result = NULL,* current;
    while (!result && !it.Done()) {
        current = it.Current();
        if (current->GetData() == data) {
            result = current;
        }
    }
    return result;
}

ListNode* List::GetHead() {
    return &head;
}

ListNode* List::GetTail() {
    return &tail;
}

void* List::Peek() const {
    return size ? head.GetNext()->GetData() : NULL;
}

int List::GetSize() const {
    return size;
}

bool List::IsEmpty() const {
    return (size == 0);
}

// List iterator implementation

ListIterator::ListIterator(List* list) {
    this->list = list;
    current = list->GetHead()->GetNext();
}

ListNode* ListIterator::Current() {
    ListNode* node = current;
    current = current->GetNext();
    return node;
}

bool ListIterator::Done() const {
    return (current == list->GetTail());
}
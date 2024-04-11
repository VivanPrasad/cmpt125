#include "Stack.h"
#include <iostream>

Stack::Stack() {
    Stack::list = LinkedList();
}
Stack::~Stack() {
    //Cleanup stack by removing list
    Stack::list.removeList();
}
void Stack::push(double val) {
    Stack::list.appendListNode(val);
}
void Stack::pop() {
    if (Stack::isEmpty()) {
        std::cerr << "ERROR: Cannot pop on empty stack\n";
        return;
    }
    Stack::list.removeListNodeN(Stack::list.length());
}
double Stack::top() const {
    ListNode* current = Stack::list.getHead();
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current->value;
}
bool Stack::isEmpty() const {
    return (bool)(Stack::list.getHead() == nullptr);
}
void Stack::displayStack() const {
    ListNode* current = Stack::list.getHead();
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;  
    }
    std::cout << "\n";
}
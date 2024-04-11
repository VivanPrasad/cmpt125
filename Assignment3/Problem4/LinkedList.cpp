#include "LinkedList.h"
#include <iostream>
#include <math.h>

#define DBL_EPS 0.00001

/*---------------CLASS IMPLEMENTATION FILE---------------*/
LinkedList::LinkedList()
{
    LinkedList::head = nullptr;
}
LinkedList::~LinkedList()
{
    //Cleanup linked list
    removeList();
}
bool LinkedList::isEmpty() const {
    if (getHead() == nullptr) return true;
    else return false;
}
void LinkedList::displayList() const {
    ListNode* current = LinkedList::head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << "\n";
}
int LinkedList::length() const {
    int count = 0;
    ListNode* current = LinkedList::head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}
void LinkedList::insertListNode(double val) {
    ListNode *newListNode = new ListNode;
    
    if (newListNode == nullptr) {
        std::cout << "ERROR: Memory allocation failed.\n";
        return;
    }
    newListNode->value = val;
    
    ListNode* current = LinkedList::head;
    /* Head is nullptr,*/
    if (current == nullptr || val > current->value) {
        newListNode->next = current;
        LinkedList::head = newListNode;
        return;
    }
    while (current->next != nullptr 
            && current->value > val) {
        current = current->next;
    }
    newListNode->next = current->next;
	current->next = newListNode;
    return;
}
void LinkedList::removeListNodeN(int n) {
    if (LinkedList::isEmpty()) {
        std::cerr << "ListNode not found at index: " << n 
            << "\n"; }

    ListNode* current = LinkedList::head;
    ListNode* prev = nullptr;
    for (int i=1;i<n;i++)
    {
        if (current == nullptr) {
            std::cerr << "ListNode not found at index: " 
                << n << "\n";
            return;
        } 
        prev = current;
        current = current->next;
    }
    prev->next = current->next;
    delete current;
}

void LinkedList::removeListNode(double val) {
    if (LinkedList::isEmpty()) {
        std::cerr << "Cannot remove from empty list: " 
            << val << "\n";
    }
    ListNode* current = LinkedList::head;
    ListNode* prev = nullptr;

    /* If the node to be deleted is the head node */
    if (current != NULL 
            && fabs(current->value - val) < DBL_EPS) {
		LinkedList::head = current->next;
		delete current;
        return;
	}
    
    /* Traverse the list to find the node to be deleted */
    while (current != nullptr 
            && fabs(current->value - val) > DBL_EPS) {
        prev = current;
        current = current->next;
    }
    
    /* If the node to be deleted is found, delete it */
    if (current != nullptr) {
        prev->next = current->next;
        delete current;
    } else std::cerr << "ERROR: List Node with value " 
        << val << " not found\n";
}
void LinkedList::appendListNode(double val) {
    ListNode* newListNode = new ListNode;
    
	if (newListNode == nullptr) {
        std::cout << "ERROR: Memory allocation failed.\n";
        return;
    }

    newListNode->value = val;
    newListNode->next = nullptr;
	/* 	If the list is empty, make the new 
		node the head of the list */
	if (LinkedList::getHead() == nullptr) 
	{
		LinkedList::head = newListNode;
		return;
	}

	/* 	Otherwise, traverse the list to 
		find the last node */
	ListNode* current = LinkedList::head;
	while (current->next != nullptr) {
		current = current->next;
	}
	/* Insert the new node after the last node */
	current->next = newListNode;
}
void LinkedList::removeList() {
    ListNode* current = getHead();
    while (current != nullptr) {
        ListNode* temp = current;
        delete current;
        current = temp->next;
        delete temp;
    }
}
ListNode* LinkedList::getHead() const {
    return LinkedList::head;
}

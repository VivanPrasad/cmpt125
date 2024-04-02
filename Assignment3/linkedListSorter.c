#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    double value;
    struct ListNode* next;
} ListNode;

typedef struct LinkedList {
    struct ListNode* head;
} LinkedList;

LinkedList* createLinkedList();
void freeLinkedList(LinkedList* list);
void displayList(const LinkedList* list);
void insertListNode(LinkedList* list, double val);
void removeListNode(LinkedList* list, double val);
void appendListNode(LinkedList* list, double val);
ListNode * createNode(double val);
LinkedList* createLinkedList();

LinkedList* InsertionListDescendingIter(const LinkedList* head);
void SelectionListDescendingRec(const LinkedList* head);

int main(void)
{
    return EXIT_SUCCESS;
}




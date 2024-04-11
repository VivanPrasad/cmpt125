#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// PROBLEM 3

/*----------------------DEFINITIONS----------------------*/
#define DBL_EPS 0.00001

typedef struct ListNode {
	double value;
	struct ListNode* next;
} ListNode;

typedef struct LinkedList {
	struct ListNode* head;
} LinkedList;

/*----------------------PROTOTYPES-----------------------*/

LinkedList* createLinkedList();
void freeLinkedList(LinkedList* list);
ListNode * createNode(double val);
void displayList(const LinkedList* list);
void insertListNode(LinkedList* list, double val); 
void appendListNode(LinkedList* list, double val);
LinkedList* InsertionListDescendingIter(const LinkedList* list);

void SelectionListDescendingRec(ListNode* current);
ListNode* findMax(ListNode* current, ListNode* maxNode);
void swapValues(ListNode* node1, ListNode* node2);

/*---------------------MAIN PROGRAM----------------------*/
int main(void) {

	/*two tests referred to in problem*/
	/* you will probably want the make additional tests yourself*/

	/* Create a new linked list */
	struct LinkedList* list;
	list = createLinkedList();
	if (list == NULL) {
		printf("Failed to create linked list.\n");
		return EXIT_FAILURE;
	}

	/* Insert some nodes into the linked list */
	appendListNode(list, 1); 
	appendListNode(list, 2);
	appendListNode(list, 3);
	appendListNode(list, 4);
	appendListNode(list, 5);
	appendListNode(list, 10);
	appendListNode(list, 6);
	appendListNode(list, 7);
	appendListNode(list, 8);
	appendListNode(list, 9);
	
	struct LinkedList* sortedlist;
	sortedlist = InsertionListDescendingIter(list);
	// Added error when the created sorted list is NULL
	if (sortedlist == NULL) {
		printf("Failed to create sorted linked list.\n");
		return EXIT_FAILURE;
	}
	printf("Original linked list: \n");
	displayList(list);
	printf("Insertion sort sorted linked list: \n");
	displayList(sortedlist);
	printf("\n\n");
	/* Free memory allocated for the linked list */
	freeLinkedList(list);
	freeLinkedList(sortedlist);

	list = createLinkedList();
	if (list == NULL) {
		printf("Failed to create linked list.\n");
		return EXIT_FAILURE;
	}

	appendListNode(list, 108);
	appendListNode(list, 201);
	appendListNode(list, 333);
	appendListNode(list, 49);
	appendListNode(list, 550);
	appendListNode(list, 670);
	appendListNode(list, 723);
	printf("Original List \n");
	displayList(list);
	SelectionListDescendingRec(list->head);
	printf("Selection sort sorted List\n");
	displayList(list);
	/* Free memory allocated for the linked list */
	freeLinkedList(list);
	return EXIT_SUCCESS;
}

/* Code written for assignment 3 below*/
/*----------------------DEFINITIONS----------------------*/

void swapValues(ListNode* node1, ListNode* node2)
{
	//Swap using dynamic double value (kinda pointless)
	double *old_node1_value = (double *)
		malloc(sizeof(double));
	*old_node1_value = node1->value; //Set to node1 value
	node1->value = node2->value;
	node2->value = *old_node1_value;
	free(old_node1_value); //Free dynamic double value
}

/*	Recursively finds the pointer to 
	the ListNode with the largest value. */
ListNode* findMax(ListNode* current, ListNode* maxNode)
{
	if (current == NULL) return maxNode; //Base case

	if (current->value > maxNode->value)
	{
		maxNode = current;
	}
	findMax(current->next,maxNode);

}

LinkedList* InsertionListDescendingIter(const LinkedList* list)
{
	struct LinkedList *sortedlist;
	sortedlist = createLinkedList();
	if (sortedlist == NULL) return NULL;

	const struct ListNode* current = list->head;
	while (current != NULL)
	{
		insertListNode(sortedlist,current->value);
		current = current->next;
	}
	return sortedlist;
}

/*--------------------GIVEN FRAMEWORK--------------------*/

void SelectionListDescendingRec(ListNode* current) 
{
	if (current == NULL) return;

	ListNode* maxNode = findMax(current, current);
	swapValues(current, maxNode);

	SelectionListDescendingRec(current->next);
}

/*-----------------LINKEDLIST.C FUNCTIONS----------------*/

/* Function to append a new node with the given 
value to the end of the linked list */
void appendListNode(LinkedList* list, double val) 
{
	ListNode* newListNode = NULL;
	newListNode = createNode(val);
	if (newListNode) 
	{

		/* 	If the list is empty, make the new 
			node the head of the list */
		if (list->head == NULL) 
		{
			list->head = newListNode;
			return;
		}

		/* 	Otherwise, traverse the list to 
			find the last node */
		ListNode* current = list->head;
		while (current->next != NULL) 
		{
			current = current->next;
		}

		/* Insert the new node after the last node */
		current->next = newListNode;
	}
	else
	{
		printf("Memory allocation failed.\n");
	}
}

/* Function to insert a new node with the 
given value in ascending order */
void insertListNode(LinkedList* list, double val) 
{
	ListNode *newListNode;
	newListNode = createNode(val);
	if (newListNode)
	{
		/* 	If the list is empty or the new node's value 
			is less than the value of the head node,
		   	insert the new node at the front. */
		if (list->head == NULL || val > list->head->value)
		{
			newListNode->next = list->head;
			list->head = newListNode;
			return;
		}

		/* 	Otherwise, traverse the list to find the 
			correct position to insert the new node. */
		ListNode* current = list->head;
		while (current->next != NULL 
			&& current->next->value > val)
		{
			current = current->next;
		}

		/* Insert the new node after the current node. */
		newListNode->next = current->next;
		current->next = newListNode;
	}
	else printf("Memory allocation failed.\n");
}

/* Function to initialize a new linked list */
LinkedList* createLinkedList() {
	LinkedList* list = NULL;
	list = (LinkedList*)malloc(sizeof(LinkedList));
	if (list != NULL) {
		list->head = NULL;
	}
	return list;
}

/* Function to free memory allocated for the linked list */
void freeLinkedList(struct LinkedList* list) 
{
	struct ListNode* current = list->head;
	while (current != NULL) 
	{
		struct ListNode* temp = current;
		current = current->next;
		free(temp);
	}
	free(list);
}

ListNode* createNode(double val)
{
	ListNode* newListNode = NULL;
	newListNode = (ListNode*)malloc(sizeof(ListNode));
	if (newListNode != NULL) 
	{
		newListNode->value = val;
		newListNode->next = NULL;
	}
	return newListNode;
}

void displayList(const struct LinkedList* list) 
{
	const struct ListNode* current = NULL;
	current = list->head;
	while (current != NULL)
	{
		printf("%lf ", current->value);
		current = current->next;
	}
	printf("\n");
}

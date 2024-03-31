#include <iostream>
#include "LinkedList.h"
#include "Stack.h"

int main() {
	LinkedList list;

	// Insert some nodes at the front of the linked list
	list.insertListNode(3.3);
	list.insertListNode(5.5);
	list.insertListNode(7.7);
	list.insertListNode(2.2);
	list.insertListNode(6.6);

	// Print the linked list
	std::cout << "Linked list: ";
	list.displayList();

	// Remove a node from the linked list
	list.removeListNode(5.5);

	// Append a node to the end of the linked list
	list.appendListNode(9.9);

	// Print the modified list
	std::cout << "Modified linked list: ";
	list.displayList();

	// Remove nodes from list
	list.removeListNode(7.7);
	list.removeListNode(2.2);
	list.removeListNode(9.9);

	// Print the modified list
	std::cout << "Modified linked list: ";
	list.displayList();

	list.removeList();

	Stack stack;

	// Push elements onto the stack
	stack.push(10);
	stack.push(20);
	stack.push(30);

	// Display the stack
	std::cout << "Stack: ";
	stack.displayStack();

	// Pop an element from the stack
	stack.pop();

	// Display the stack after popping
	std::cout << "Stack after pop: ";
	stack.displayStack();

	// Display the top element of the stack
	std::cout << "Top element: " << stack.top() << std::endl;

	return 0;
}

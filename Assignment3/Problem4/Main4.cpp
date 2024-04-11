#include <iostream>
#include "LinkedList.cpp"
#include "Stack.cpp"

/* Based on Driver.cpp Testing File for Problem #4 */

int main(void) {
	LinkedList list;
	
	// Insert some nodes at the front of the linked list
	list.insertListNode(1.0);
	list.insertListNode(1.01);
	list.insertListNode(1.001);
	list.insertListNode(1.0001);
	list.insertListNode(1.5);

	// Print the linked list
	std::cout << "Linked list: ";
	list.displayList();

	// Remove a node from the linked list
	list.removeListNode(1.01);

	// Append a node to the end of the linked list
	list.appendListNode(9.9);

	// Print the modified list
	std::cout << "Modified linked list: ";
	list.displayList();

	// Remove nodes from list
	list.removeListNode(1.0); // Should give error
	list.removeListNode(1.5);
	list.removeListNode(9.9);
	// Print the modified list
	std::cout << "Modified linked list: ";
	list.displayList();

	list.removeList();
	
	Stack stack;
	// Push elements onto the stack
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);

	// Display the stack
	std::cout << "Stack: ";
	stack.displayStack();

	// Pop an element from the stack
	stack.pop();
	stack.pop();
	stack.pop();
	// Display the stack after popping
	std::cout << "Stack after 3 pops: ";
	stack.displayStack();

	// Display the top element of the stack
	std::cout << "Top element: " << stack.top() << std::endl;
	return 0;
}

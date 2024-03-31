#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct ListNode {
	double value;
	ListNode* next;
};

class LinkedList {
private:
	ListNode* head;

public:
	LinkedList();
	~LinkedList();
	bool isEmpty() const;
	void displayList() const;
	int length() const;
	void insertListNode(double val);
	void removeListNodeN(int n);
	void removeListNode(double val);
	void appendListNode(double val); 
	void removeList();
	ListNode* getHead() const;
}; 

#endif // LINKEDLIST_H

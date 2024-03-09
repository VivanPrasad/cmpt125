#include <stdio.h>
#include <stdlib.h>

/* Define the structure for the stack */
typedef struct {
	int* stackArray; /* Pointer to the stack array */
	int stackSize;   /* Size of the stack */
	int top;         /* Index of the top element */
} IntStack;

/* Function prototypes */
IntStack* createIntStack(int sizeValue);
IntStack* copyIntStack(const IntStack* stackToCopy);
void destroyIntStack(IntStack* stack);
void push(IntStack* stack, int newValue);
void pop(IntStack* stack, int* oldValue);
int isEmpty(const IntStack* stack);
int isFull(const IntStack* stack);

/* Function to create a new stack */
IntStack* createIntStack(int sizeValue) {
	if (sizeValue <= 0) {
		sizeValue = 1;
		printf("Stack was given a non-positive size: reset to 1\n");
	}
	IntStack* stack = (IntStack*)malloc(sizeof(IntStack));
	stack->stackSize = sizeValue;
	stack->stackArray = (int*)malloc(sizeValue * sizeof(int));
	stack->top = -1;
	return stack;
}

/* Function to create a copy of an existing stack */
IntStack* copyIntStack(const IntStack* stackToCopy) {
	IntStack* newStack = createIntStack(stackToCopy->stackSize);
	for (int i = 0; i <= stackToCopy->top; i++) {
		newStack->stackArray[i] = stackToCopy->stackArray[i];
	}
	newStack->top = stackToCopy->top;
	return newStack;
}

/* Function to destroy a stack and free memory */
void destroyIntStack(IntStack* stack) {
	free(stack->stackArray);
	free(stack);
}

/* Function to push a value onto the stack */
void push(IntStack* stack, int newValue) {
	if (isFull(stack)) {
		printf("The stack is full\n");
	}
	else {
		stack->top++;
		stack->stackArray[stack->top] = newValue;
	}
}

/* Function to pop a value from the stack */
void pop(IntStack* stack, int* oldValue) {
	if (isEmpty(stack)) {
		printf("The stack is empty\n");
	}
	else {
		*oldValue = stack->stackArray[stack->top];
		stack->top--;
	}
}

/* Function to check if the stack is empty */
int isEmpty(const IntStack* stack) {
	return stack->top == -1;
}

/* Function to check if the stack is full */
int isFull(const IntStack* stack) {
	return stack->top == stack->stackSize - 1;
}

int main() {

	int poppedValue = 0;
	/* Example usage */
	IntStack* stack = createIntStack(5);
	IntStack* copiedStack;
	pop(stack, &poppedValue);
	push(stack, 10);
	push(stack, 20);
	push(stack, 30);
	push(stack, 33);
	push(stack, 55);
	push(stack, 99);
	isFull(stack);
	push(stack, 101);
	for (int K = 0; K < 3; K++)
	{
		pop(stack, &poppedValue);
		printf("Popped value: %d\n", poppedValue);
	}
	push(stack, 88);
	for (int K = 0; K < 3; K++)
	{
		pop(stack, &poppedValue);
		printf("Popped value: %d\n", poppedValue);
	}

	destroyIntStack(stack);
	return 0;
}

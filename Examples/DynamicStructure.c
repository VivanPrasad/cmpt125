
#include <stdio.h>
#include <stdlib.h>

/* Define the DynamicAlloc structure*/
struct DynamicAlloc {
	int size;
	int *arr; /* pointer only */
	int myarr[23];
};
typedef struct DynamicAlloc structWithDynArray;

void printStructWithDynArray(structWithDynArray *array);

int main() {
	/* Declare an instance of the DynamicAlloc structure */
	structWithDynArray mystruct;

	/* Set the size */
	mystruct.size = 10;

	/* Initialize arr pointer */
	mystruct.arr = (int *)malloc(mystruct.size * sizeof(int));
	if (mystruct.arr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	/* Initialize arr array */
	for (int i = 0; i < mystruct.size; i++) {
		mystruct.arr[i] = i * 3;
	}

	/* Initialize myarr array */
	for (int i = 0; i < 23; i++) {
		mystruct.myarr[i] = i * 2;
	}

	/* Print all elements in the structure */
	printStructWithDynArray(&mystruct);
	printf("\n");
	free(mystruct.arr);
	return 0;
}

/* Function to print the contents of the DynamicAlloc structure */
void printStructWithDynArray(structWithDynArray *array) {
	printf("Size: %d\n", array->size);
	printf("arr: ");
	for (int i = 0; i < array->size; i++) {
		printf("%d ", array->arr[i]);
	}
	printf("\n");
	printf("myarr: ");
	for (int i = 0; i < 23; i++) {
		printf("%d ", array->myarr[i]);
	}
	printf("\n");
}


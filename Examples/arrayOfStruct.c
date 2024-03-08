#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define the Car structure */
typedef struct CarInfo {
	int year;
	char make[64];
	int mileage;
	float price;
} Car;

/* Define the DynamicAlloc structure without arr and myarr */
typedef struct DynamicAlloc {
	int size;
	Car *cars;   /* array of cars */
} CarArray;

/* Function prototypes */
void printCarArray(CarArray *carArray);

int main() {
	/* Initialize an instance of the DynamicAlloc structure */
	CarArray myCarArray;

	/* Set the size */
	myCarArray.size = 3;

	/* Allocate memory for cars array */
	myCarArray.cars = (Car *)malloc(myCarArray.size * sizeof(Car));
	if (myCarArray.cars == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	/* Initialize cars array */
	for (int i = 0; i < myCarArray.size; i++) {
		myCarArray.cars[i].year = 2020 - i;
		sprintf(myCarArray.cars[i].make, "Car Make %d", i + 1);
		myCarArray.cars[i].mileage = 10000 * i;
		myCarArray.cars[i].price = 20000.0 + i * 500;
	}

	/* Print all elements in the structure */
	printf("Contents of myCarArray:\n");
	printCarArray(&myCarArray);

	/* Free the memory allocated for the cars array */
	free(myCarArray.cars);

	return 0;
}

/* Function to print the contents of the DynamicAlloc structure */
void printCarArray(CarArray *carArray) {
	printf("Size: %d\n", carArray->size);
	printf("Cars:\n");
	for (int i = 0; i < carArray->size; i++) {
		printf("Car %d:\n", i + 1);
		printf("  Year: %d\n", carArray->cars[i].year);
		printf("  Make: %s\n", carArray->cars[i].make);
		printf("  Mileage: %d\n", carArray->cars[i].mileage);
		printf("  Price: %.2f\n", carArray->cars[i].price);
	}
}

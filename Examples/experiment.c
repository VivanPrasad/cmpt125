
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


#define MAXEXP 10

const double DBL_EPSILON = 0.000001;

/* Globally define structures
   Defined globally so that the structures can be used in all functions in
   this file. */


   /* A new type of variable can be defined using the typedef structure
	  The new type can then be used like any other type in the remainder of
	  the application */
typedef struct
{
	int measurementNum;  /* Number used to label this measurement */
	int date;            /* Date measurement was taken DD/MM/YYYY */
	int numOfComponents; /* Number of components tested */
	int duration;        /* Time taken for test */
	double temperature;  /* Celsius temperature at which test is done */
	int numFailures;     /* Number of tested components that failed */
} labMeasurement;


/* The structure can be defined without defining a new variable type
   When an instance of the structure is declared the keyword struct must
   be used along with the name of the structure */
struct experiment
{
	char description[80];           /* name of experiment */
	int numMeasurements;            /* number of measurments in experiment */
	labMeasurement measures[MAXEXP];/* array of MAXEXP measurements */
	double percentFailures[MAXEXP]; /* percent of tested components failed */
	double tempScaled[MAXEXP];      /* fahranheit temperature */
};


/* declare the functions that will be defined and used in this file
   note that functions are declared globally so they can be used in all
   functions defined in this file */
void printLabMeasurement(const labMeasurement *measure);
void printExperiment(const struct experiment *e1);
labMeasurement readLabMeasurement(FILE *fileInput);
bool compareLabMeasurements(const labMeasurement *meas1, const labMeasurement *meas2);
struct experiment initializeExperiment(FILE* fileInput);
bool compareExperiment(const struct experiment *e1, const struct experiment *e2);


int main()
{
	struct experiment e1;
	struct experiment e2;
	labMeasurement m1;
	labMeasurement m2;
	labMeasurement m3;
	FILE* fileInput;


	/* Open  the file, inputfile, containing the experimental data */
	fileInput = fopen("inputfileL32.txt", "r");
	if (fileInput == NULL)
	{
		printf("File not opened successfully\n");
		return 1;
	}

	/* read the experimental data for experiment e1 from the file
	   copy the values from recorded in experiment structure e1
	   into experiment structure e2, then print the contents of e2 */
	e1 = initializeExperiment(fileInput);
	printExperiment(&e1);
	e2 = e1;

	// compare the copy to the original experiment, shold be identical 
	if (compareExperiment(&e1, &e2))
	{
		printf("\n\nthe experments are identical\n");
	}

	// change 1 component of e2 then recompare and show e1 != e2 
	e2.percentFailures[4] = 0.11;
	if (!compareExperiment(&e1, &e2))
	{
		printf("\nthe experments are different\n");
	}


	/* Tests using only the labMeasurement structure */
	printf("\n\n\n");
	m1 = e1.measures[0];
	printLabMeasurement(&m1);
	m2 = readLabMeasurement(fileInput);
	printLabMeasurement(&m2);
	m3 = readLabMeasurement(fileInput);
	printLabMeasurement(&m3);

	if (!compareLabMeasurements(&m1, &m2))
	{
		printf("measurements 1 and 2 are different\n");
	}
	if (compareLabMeasurements(&m1, &m3))
	{
		printf("measurements 1 and 3 are identical\n");
	}
	fclose(fileInput);
	return 0;
}

labMeasurement readLabMeasurement(FILE* fileInput)
{
	/* Read the values of each element in a structure of labMeasurement
	   from a input file connected to the application through stream fileInput
	   Example of returning a structure
	   Program Author: Janice Regan
	   Latest revision: February 2024 */

	   /* Declare local variables (Only available in this function) */
	labMeasurement measure;

	fscanf(fileInput, "%d", &(measure.measurementNum));
	fscanf(fileInput, "%d", &(measure.date));
	fscanf(fileInput, "%d", &(measure.numOfComponents));
	fscanf(fileInput, "%d", &(measure.duration));
	fscanf(fileInput, "%lf", &(measure.temperature));
	fscanf(fileInput, "%d", &(measure.numFailures));
	return measure;
}

void printLabMeasurement(const labMeasurement *measure)
{
	/* Print, with annotation, the value of each element
	   in the structure of type labMeasurement
	   Program Author: Janice Regan
	   Latest revision: February 2024 */

	printf("\nMeasurement Number: %d", measure->numOfComponents);
	printf("\nDate MM/DD/YYYY: %d", measure->date);
	printf("\nNumber of components tested: %d", measure->numOfComponents);
	printf("\nDuration of experiment: %d", measure->duration);
	printf("\nTemperature for test: %lf", measure->temperature);
	printf("\nNumber (of MAXEXP) of failed components: %d\n",
		measure->numFailures);
}

bool compareLabMeasurements(const labMeasurement *meas1, const labMeasurement *meas2)
{
	/* Compare the value of each element in one structure of
	   type labMeasurement with the value of the corresponding
	   element in a second structure of type labMeasurement
	   If the value of all elements in both structures are
	   identical return 0(structures equal), otherwise return 1
	   Example of passing a structure by pointer */

	   /* Program Author: Janice Regan
		  Latest revision: February 2024 */

	if (meas1->measurementNum != meas2->measurementNum)
	{
		return false;
	}
	if (meas1->date != meas2->date)
	{
		return false;
	}
	if (meas1->numOfComponents != meas2->numOfComponents)
	{
		return false;
	}
	if (meas1->duration != meas2->duration)
	{
		return false;
	}
	if (meas1->numFailures != meas2->numFailures)
	{
		return false;
	}
	if (fabs(meas1->temperature - meas2->temperature) > DBL_EPSILON)
	{
		return 1;
	}
	return true;
}

struct experiment initializeExperiment(FILE *fileInput)
{
	/* Read the values of each element in a structure of type experiment
	   from a input file connected to the application through stream fileInput
	   Program Author: Janice Regan
	   Latest revision: February 2024 */

	   /* Declare local variables (only exist in this function) */
	struct experiment e1;

	fscanf(fileInput, "%s", &(e1.description[0]));
	fscanf(fileInput, "%d", &(e1.numMeasurements));

	for (int i = 0; i < e1.numMeasurements; i++)
	{
		e1.measures[i] = readLabMeasurement(fileInput);
		e1.tempScaled[i] = 32.0 + (9.0 / 5.0)* e1.measures[i].temperature;
		e1.percentFailures[i] = (e1.measures[i].numFailures /
			(double)e1.measures[i].numOfComponents);
	}
	return e1;
}

void printExperiment(const struct experiment *e1)
{
	/* Print, with annotation, the value of each element
	   in the structure of type experiment
	   Example of passing a pointer to a structure
	   IN C can only pass the structure or a pointer to it */

	   /* Program Author: Janice Regan
		  Latest revision: February 2024 */

	printf("Experiment Title: %s\n", e1->description);
	printf("Number of measurements in experiment is %d\n",
		e1->numMeasurements);
	/* NOTE: declaring i in the for loop is only valid
		 in compilers supporting C99 and newer standards
		 in compilers supporting earlier standards
		 int i; must be declared outside the for loop*/
	for (int i = 0; i < e1->numMeasurements; i++)
	{
		printLabMeasurement(&e1->measures[i]);
		printf("Percent of components that failed is %lf\n",
			e1->percentFailures[i]);
		printf("Temperature in degrees Fahrenheit: %lf\n",
			e1->tempScaled[i]);
	}

}


bool compareExperiment(const struct experiment* e1, const struct experiment* e2)
{
	/* Compare the value of each element in one structure of
	   type experiment with the value of the corresponding
	   element in a second structure of type experiment
	   If the value of all elements in both structures are
	   identical return 0(structures equal), otherwise return 1 */

	   /* Program Author: Janice Regan
		  Latest revision: February 2024 */


	if (strcmp(e1->description, e2->description) != 0)
	{
		return false;
	}
	if (e1->numMeasurements != e2->numMeasurements)
	{
		return false;
	}
	for (int i = 0; i < e1->numMeasurements; i++)
	{
		if (!compareLabMeasurements(&(e1->measures[i]), &(e2->measures[i])))
		{
			return false;
		}
		if (fabs(e1->percentFailures[i] - e2->percentFailures[i]) > DBL_EPSILON)
		{
			return false;
		}
		if (fabs(e1->tempScaled[i] - e2->tempScaled[i]) > DBL_EPSILON)
		{
			return false;
		}
	}
	return true;
}

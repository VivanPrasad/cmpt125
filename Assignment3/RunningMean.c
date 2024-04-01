#include <stdio.h>
#include <stdlib.h>

#define NUM_TRIES 3
#define SCAN_SUCCESS 1

void RunningMean(double* measurements,
    double* runningMean, int numInRunningMean)
{
}

FILE* getInputFile(void)
{
    char inputFileName[50];
    FILE* inputFile = NULL;
    for (int i=1;i<=NUM_TRIES;i++)
    {
        printf("Enter the name of the input file: ");
        scanf("%s",&inputFileName);
        inputFile = fopen(inputFileName,"r");
        if (inputFile == NULL)
        {
            fprintf(stderr,"ERROR: Input file %s not opened\n",inputFileName);
        }
        else break;
        if (i==NUM_TRIES)
        {
            fprintf(stderr,"ERROR: too many failures \
opening input file\n");
            return NULL;
        }
    }
    return inputFile;
}

int getNumMeas(int* numMeas)
{
    for (int i=1;i<=NUM_TRIES;i++)
    {
        printf("Enter the number of measurements: ");
        if (scanf("%d",numMeas) != SCAN_SUCCESS)
        {
            fprintf(stderr,"ERROR: Did not read an integer\n");
        }
        else if (*numMeas < 1 || *numMeas > 40)
        {
            fprintf(stderr,"ERROR: numMeas is out of \
range\n%7senter 0<numMeas<=40\n"," ");
        }
        else break;
        
        if (i==NUM_TRIES) //Third attempt and incorrect
        {
            fprintf(stderr,"ERROR: too many \
failures reading the number of measurements\n");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

void printRunningMean(int numMeas, double *myRunningMean)
{
    printf("The running means are\n");
    for (int i=0;i<numMeas;i++)
    {
        printf("%10.2lf",myRunningMean[i]);
        if ((i%5)==0) printf("\n");
    }
}
int main(void)
{
    FILE* inputFile = getInputFile();
    int numMeas;
    double* myMeasurements = NULL;
    double* myRunningMean = NULL;

    if (inputFile == NULL) return EXIT_FAILURE;
    if (getNumMeas(&numMeas) == EXIT_FAILURE) return EXIT_FAILURE;
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: input file is empty\n");
        return EXIT_FAILURE;
    }

    myMeasurements = (double*)malloc(numMeas*sizeof(double));
    if (myMeasurements == NULL)
    {
        fprintf(stderr,"ERROR: cannot allocate memory\n");
        return EXIT_FAILURE;
    }
    
    myRunningMean = (double*)malloc(numMeas*sizeof(double));
    if (myRunningMean == NULL)
    {
        fprintf(stderr,"ERROR: cannot allocate memory\n");
        return EXIT_FAILURE;
    }

    for (int i=0;i<numMeas;i++)
    {
        myRunningMean[i] = 0.0;
        myMeasurements[i] = 0.0;
        if (feof(inputFile))
        {
            if (i<4)
            {
                fprintf(stderr,"ERROR: insufficient data \
to calculate a running average\n");
                return EXIT_FAILURE;
            }
            else 
            {
                fprintf(stderr,"ERROR: fewer than numMeas \
measurements in the file\n");
                break;
            }
        }
        fscanf(inputFile,"%lf",myMeasurements[i]);
        printf("%lf",myMeasurements[i]);
    }
    
    printRunningMean(numMeas,myRunningMean);
    fclose(inputFile);
    free(myMeasurements); myMeasurements = NULL;
    free(myRunningMean); myRunningMean = NULL;
    return 0;
} 
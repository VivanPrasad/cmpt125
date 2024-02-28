#include <stdio.h>
#include <stdlib.h>

#define INPUT_ATTEMPTS 3
// Clears input buffer
void clear_stdin(void)
{
    int c; do{c = getchar();} while (c!='\n'); 
}

// Gets the initial seed and generates the pesudorandom number set
int get_seed(void)
{
    unsigned int seed;

    int attempts = INPUT_ATTEMPTS;
    // If no more attempts, terminate

    while (attempts > 0)
    {
        // Ask user for seed
        printf("Enter the integer value of the seed for the game: ");

        // Read the input and sets the seed variable
        if (scanf("%u",&seed) == 0)
        {
            fprintf(stderr,"ERROR: seed did not have an acceptable value\n");
            clear_stdin(); // Clear stdin buffer
            attempts -= 1;
        }
        else if (seed < 2 || seed > 32767) // Check range
        {
            fprintf(stderr,"ERROR: seed to use was not in the acceptable range\n");
            clear_stdin(); // Clear stdin buffer
            attempts -= 1;
        } else break;
    }
    if (attempts == 0) 
    {
        fprintf(stderr,"ERROR: too many tries entering data\n");
        return 1;
    }

    srand(seed); // Seed the pseudorandom number generator using seed
    return 0;
}
int main(void)
{
    get_seed(); // 3 Attempts
    return 0;
}
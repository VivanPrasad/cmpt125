#include <stdio.h>
#include <stdlib.h>

#define ANSWER_DIGITS 6 // Number of digits in the sequence
#define MIN_DIGIT 0 // Smallest possible digit to guess
#define MAX_DIGIT 9 // Greatest possible digit to guess

int get_seed(void) // Gets the initial seed
{
    unsigned int *seed = (unsigned int*)malloc(sizeof(unsigned int));
    
    // Ask user for seed (assuming case is always correct)
    printf("Enter the integer value of the seed for the game: ");

    scanf("%u",seed); // Read the input and sets the seed variable
    srand(*seed); // Seed the pseudorandom number generator using seed
    
    free(seed); seed = NULL; // Free the dynamic seed variable
    
    return 0;
}

int play(void) // Play the game
{ 
    int answer[ANSWER_DIGITS];
    for (int i; i < ANSWER_DIGITS; i++)
    {
        answer[i] = rand() % (MAX_DIGIT + 1 - MIN_DIGIT) + MIN_DIGIT; 
        // Sets digits of answer from 0 to 9
        printf("%u ",answer[i]);
    }
    return 0;
}

int main(void) // Main Scope
{
    // Asks the user for game seed
    get_seed();
    play();
    return 0;
}
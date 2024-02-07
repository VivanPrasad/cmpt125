#include <stdio.h>
#include <stdlib.h>

int main(void) // Main Scope
{
    
    // Asks the user for game seed
    unsigned int seed;
    printf("Enter the integer value of the seed for the game: ");
    scanf("%i",&seed);
    srand(seed);


}
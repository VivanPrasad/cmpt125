#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int new_answer(int array[ANSWER_DIGITS])
{
    for (int i=0; i < ANSWER_DIGITS; i++)
    {
        array[i] = rand() % (MAX_DIGIT + 1 - MIN_DIGIT) + MIN_DIGIT; 
        // Sets digits of answer from 0 to 9
    }
    return 0;
}
int print_answer(int array[ANSWER_DIGITS])
{
    for (int i=0; i < ANSWER_DIGITS; i++)
    {
        printf("%-2d", array[i]);
    }
    printf("\n");
}

int print_tutorial(void)
{
    printf("For each turn enter 6 digits 0 <= digit <= 9\n");
    printf("Spaces of tabs in your response will be ignored\n\n");
}

int get_digit(char digit)
{
    for (int n=0;n<=9;n++)
    {
        if (digit == (48+n)) return n;
    }
}

bool is_same_digit(int d1, int d2)
{
    return ((bool)(d1==d2));
}

int check_guess(void)
{
    
    return 0;
}
int new_game(void) // Play the game
{ 
    int *answer = NULL;
    answer = (int*)malloc(ANSWER_DIGITS*sizeof(int));
    new_answer(answer); // Generates the sranded answer
    
    print_tutorial(); // Prints initial tutorial

    while (1==1)
    {
        printf("Enter your guess, %d Digits\n", ANSWER_DIGITS);
        int current_guess[ANSWER_DIGITS];
        char current_char;
        fscanf(stdin,"%c",&current_char);
        int digits_left = ANSWER_DIGITS;
        while (true==true)
        {
            while (true==true)
            {
                fscanf(stdin,"%c",&current_char);
                if (current_char==10) break;
                if ((current_char < 48 || current_char > 57) && !(current_char==32) )
                {
                    printf("ERROR: A character in your guess was not a digit or a white space\n\n");
                    digits_left = -2;
                    break;
                } else if (current_char >= 48 && current_char <= 57)
                {
                    current_guess[ANSWER_DIGITS-digits_left] = get_digit(current_char);
                    digits_left -= 1;
                }
            }
            if (digits_left < 1) break;
            else if (!(digits_left==-2))
            {
                printf("You need to enter %d more digits to complete your guess\n",digits_left);
            }
            else break;
        }
        if (digits_left > -2)
        {
            printf("Guess: ");
            print_answer(current_guess);
        }
        else digits_left = ANSWER_DIGITS;
    }
    free(answer); answer = NULL;
    return 0;
}

int main(void) // Main Scope
{
    // Asks the user for game seed
    get_seed();
    new_game();
    return 0;
}
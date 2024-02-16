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

int print_guess(int array[ANSWER_DIGITS])
{
    for (int i=0; i < ANSWER_DIGITS; i++)
    {
        printf("%-2d", array[i]);
    }
}

int print_tutorial(void)
{
    printf("For each turn enter 6 digits 0 <= digit <= 9\n");
    printf("Spaces of tabs in your response will be ignored\n");
}

int get_digit(char digit) // Returns the integer version of the character digit
{
    for (int n=MIN_DIGIT;n<=MAX_DIGIT;n++)
    {
        if (digit == (48+n)) return n;
    }
}

bool is_answer(int guess[ANSWER_DIGITS],int answer[ANSWER_DIGITS])
{
    int correct = 0;
    for (int g=0;g<ANSWER_DIGITS;g++)
    {
        for (int a=0;a<ANSWER_DIGITS;a++)
        {
            if ((a==g) && (answer[a]==guess[g])) correct += 1;
        }
    }
    if (correct == ANSWER_DIGITS) return true;
    else return false;
            
}
int check_guess(int guess_number, int guess[ANSWER_DIGITS], int answer[ANSWER_DIGITS])
{
    int correct = 0; //In the answer, in the correct space
    int partial = 0; //In the answer, not in the correct space

    int answerc[ANSWER_DIGITS], guessc[ANSWER_DIGITS];
    for (int i=0;i<ANSWER_DIGITS;i++) { // Deep copy of answer and guess
        answerc[i] = answer[i];
        guessc[i] = guess[i]; }

    for (int g=0;g<ANSWER_DIGITS;g++)
    {
        for (int a=0;a<ANSWER_DIGITS;a++)
        {
            if ((a==g) && (answerc[a]==guessc[g]))
            {
                correct += 1;
                answerc[a] = -1;
                guessc[g] = -2;
            }
            else if (guessc[g]==answerc[a])
            {
                partial += 1;
                answerc[a] = -1;
                guessc[g] = -2;
            }
        }
    }
    printf("Guess %d: ",guess_number+1);
    print_guess(guess);
    printf("- %d correct, %d partially correct.\n",correct,partial);
    return 0;
}

int new_game(void) // Play the game
{ 
    int *answer = NULL;
    answer = (int*)malloc(ANSWER_DIGITS*sizeof(int));
    new_answer(answer); // Generates the sranded answer

    int guesses[80][ANSWER_DIGITS];
    char current_char;
    int digits_left;
    int number_guesses = 0; // Total guesses

    print_tutorial(); // Prints initial tutorial
    fscanf(stdin,"%c",&current_char); //Reads initial character for input

    while (1) // Core Game Loop
    {
        printf("\nEnter your guess, %d digits\n", ANSWER_DIGITS);
        digits_left = ANSWER_DIGITS;
        while (1)
        {
            while (1)
            {
                fscanf(stdin,"%c",&current_char);
                if (current_char==10) break;
                else if (current_char >= 48 && current_char <= 57 && digits_left > 0)
                {
                    guesses[number_guesses][ANSWER_DIGITS-digits_left] = get_digit(current_char);
                    digits_left -= 1;
                } else if (!(current_char==32) && digits_left > 0)
                {
                    printf("ERROR: A character in your guess was not a digit or a white space\n\n");
                    digits_left = -1; // -1 is an error
                    break;
                }
            }
            if (digits_left < 1) break;
            else
            {
                printf("You need to enter %d more digits to complete your guess\n",digits_left);
            }
        }
        if (digits_left == 0) //The guess will print ONLY if the 6 digits were
        {
            number_guesses += 1;
            if (is_answer(guesses[number_guesses-1],answer)==true){
                printf("YOU DID IT!!\n");
                for (int x=0;x<number_guesses;x++)
                {
                    check_guess(x,guesses[x],answer);
                }
                break;
            } else 
            {
                for (int x=0;x<number_guesses;x++)
                {
                    check_guess(x,guesses[x],answer);
                }
            }
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
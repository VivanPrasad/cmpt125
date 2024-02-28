#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ANSWER_DIGITS 6 // Number of digits in the sequence
#define MIN_DIGIT 0 // Smallest possible digit to guess
#define MAX_DIGIT 9 // Greatest possible digit to guess
#define MAX_GUESSES 100 // Highest possible amount of guesses

#define ZERO_CHAR 48 // '0' zero character value
#define NINE_CHAR 57 // '9' nine character value
#define NEWLINE_CHAR 10 // '\n' newline character value
#define SPACE_CHAR 32 // ' ' space character value


void clear_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c!='\n');
}
// Gets the initial seed and generates the pesudorandom number set
int get_seed(void)
{
    unsigned int *seed = (unsigned int*)malloc(sizeof(unsigned int));
    // Ask user for seed (assuming case is always correct)
    printf("Enter the integer value of the seed for the game: ");
    
    // Read the input and sets the seed variable
    if (scanf("%u",seed) == 0) // If unsuccessful (scanf return 0):
    {
        // Recursive error calling
        printf("Try again you made an error\n");
        clear_stdin(); // Clears input buffer
        get_seed(); 
    }

    srand(*seed); // Seed the pseudorandom number generator using seed
    
    free(seed); seed = NULL; // Free the dynamic seed variable
    
    return 0;
}

// Generates a new answer
int new_answer(int array[ANSWER_DIGITS])
{
    for (int i=0; i < ANSWER_DIGITS; i++)
    {
        array[i] = rand() % (MAX_DIGIT + 1 - MIN_DIGIT) + MIN_DIGIT; 
        // Sets digits of answer from 0 to 9
    }
    return 0;
}

// Prints the string of the guess array separated by spaces
int print_guess(int array[ANSWER_DIGITS])
{
    for (int i=0; i < ANSWER_DIGITS; i++)
    {
        printf("%-2d", array[i]);
    }
    return 0;
}

// Prints the starting instructions
int print_tutorial(void) 
{
    printf("For each turn enter 6 digits 0 <= digit <= 9\n");
    printf("Spaces of tabs in your response will be ignored\n");
    return 0;
}

// Returns the integer version of the char
int get_digit(char digit) 
{
    for (int n=MIN_DIGIT;n<=MAX_DIGIT;n++)
    {
        if (digit == (48+n)) return n;
    }
    return -1;
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
    // Returns true if the number correct is the number of digits
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
                // Checks for an exact correct answer
                correct += 1;
                
                /* Sets the correct answer and guess to two
                separate values to ensure no repeated numbers*/
                answerc[a] = -1;
                guessc[g] = -2; 
            }
            else if (guessc[g]==answerc[a])
            {
                // Checks for if the guess value exists in the answer
                partial += 1;

                /* Sets the correct answer and guess to two
                separate values to ensure no repeated numbers*/
                answerc[a] = -1;
                guessc[g] = -2;
            }
        }
    }

    // Outputs the guess in the correct format
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

    int guesses[MAX_GUESSES][ANSWER_DIGITS];
    char current_char; // Current character being read from stdin
    int digits_left; // The remaining digits to read
    int number_guesses = 0; // Total guesses

    print_tutorial(); // Prints initial instructions
    clear_stdin();  // Clears input buffer

    while (number_guesses < MAX_GUESSES) // Core Game Loop
    {
        printf("\nEnter your guess, %d digits\n", ANSWER_DIGITS);
        digits_left = ANSWER_DIGITS; // Resets digits left for new guess
        while (1==1)
        {
            while (1==1) // Reading response loop
            {
                fscanf(stdin,"%c",&current_char);
                //Reads until newline character
                if (current_char==NEWLINE_CHAR) break; 
                
                else if (current_char >= ZERO_CHAR && current_char <= NINE_CHAR && digits_left > 0)
                {
                    //If the character read is in the digit range
                    guesses[number_guesses][ANSWER_DIGITS-digits_left] = get_digit(current_char);
                    digits_left -= 1;
                } 
                
                else if (!(current_char==SPACE_CHAR) && digits_left > 0)
                {
                    /* If the character detected wasn't a space 
                    OR a valid digit, output a soft-error*/
                    printf("ERROR: A character in your guess was not a digit or a white space\n");
                    digits_left = -1; // -1 is an error
                }
            }
            
            if (digits_left < 1) break; // Don't print out message below

            printf("You need to enter %d more digits to complete your guess\n",digits_left);
        }
        if (digits_left == 0) //The guess will print ONLY if 6 digits were inputted
        {
            number_guesses += 1; // Increments number of guesses (successful guess)

            // Checks if the guess is the same as the answer
            if (is_answer(guesses[number_guesses-1],answer)==true)
            {
                printf("YOU DID IT!!\n");
                for (int x=0;x<number_guesses;x++)
                {
                    check_guess(x,guesses[x],answer);
                }
                break; // Exits if that is the case
            }

            // Otherwise, it continues to check correctness
            for (int x=0;x<number_guesses;x++)
            {
                check_guess(x,guesses[x],answer);
            }
        }
        else digits_left = ANSWER_DIGITS;
    }
    // Frees dynamic answer variable
    free(answer); answer = NULL;
    return 0;
}

int main(void) // Main Scope
{
    get_seed(); // Asks the user for game seed
    new_game(); // Starts a new game
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define INPUT_ATTEMPTS 3
#define NUM_PER_ROW 10
#define COL_FORMAT "%5d"

/*         PROTOTYPE FUNCTIONS         */
void clear_stdin(void);

int get_seed(void);

int get_num_dice(int*); 
int get_num_sides(int*); 
int get_num_rolls(int*);

int roll_dice(int, int);
/*--------------------------------------*/

// Clears input buffer
void clear_stdin(void)
{
    int c; do{c = getchar();} while (c!='\n'); 
}

// Gets the initial seed and generates the pesudorandom number set
int get_seed(void)
{
    unsigned int seed;

    // If no more attempts, terminate

    for (int a=INPUT_ATTEMPTS;a>=0;a--)
    {
        if (a==0) 
        {
            fprintf(stderr,"ERROR: too many tries entering data\n");
            return 1;
        }
        // Ask user for seed
        printf("Enter a positive integer seed for random number generation: ");

        // Read the input and sets the seed variable
        if (scanf("%u",&seed) == 0)
        {
            fprintf(stderr,"ERROR: seed did not have an acceptable value\n");
            clear_stdin(); // Clear stdin buffer
        }
        else if (seed < 2 || seed > 32767) // Check range
        {
            fprintf(stderr,"ERROR: seed to use was not in the acceptable range\n");
            clear_stdin(); // Clear stdin buffer
        } 
        else break;
    }

    srand(seed); // Seed the pseudorandom number generator using seed
    return 0;
}

// Gets the number of dice
int get_num_dice(int *num_dice)
{
     // Number of Dice
    for (int a=INPUT_ATTEMPTS; a>=0;a--)
    {
        if (a==0)
        {
            fprintf(stderr,"Too many tries entering data\n");
            return 1;
        }
        
        printf("Enter the number of dice: ");

        if (scanf("%d",num_dice)==0)
        {
            fprintf(stderr,"ERROR: number of dice did not have an \
acceptable value\n\n");
            clear_stdin();
        }
        else if (*num_dice < 2 || *num_dice > 50)
        {
            fprintf(stderr,"ERROR: number of dice was not in the \
acceptable range\n2 <= number of dice <= 50\n\n");
            clear_stdin();
        }
        else break;
    }
}

// Gets the number of sides on each dice
int get_num_sides(int *num_sides)
{
     // Number of Dice
    for (int a=INPUT_ATTEMPTS; a>=0;a--)
    {
        if (a==0)
        {
            fprintf(stderr,"Too many tries entering data\n");
            return 1;
        }
        
        printf("Enter the number of sides on each die: ");

        if (scanf("%d",num_sides)==0)
        {
            fprintf(stderr,"ERROR: number of sides did not have an \
acceptable value\nnumber of sides should be 4,6,8,10 or 20\n\n");
            clear_stdin();
        }
        else switch (*num_sides)
        {
            case 4:
            case 6:
            case 8:
            case 10:
            case 20:
                return 0;
                break;
            default:
                fprintf(stderr,"ERROR: number of sides did not have an \
acceptable value\nnumber of sides should be 4,6,8,10 or 20\n\n");
                clear_stdin();
                break;
        }
    }
}

// Gets the number of rolls
int get_num_rolls(int *num_rolls)
{
     // Number of Dice
    for (int a=INPUT_ATTEMPTS; a>=0;a--)
    {
        if (a==0)
        {
            fprintf(stderr,"Too many tries entering data\n");
            return 1;
        }
        
        printf("Enter the number of rolls of the die: ");

        if (scanf("%d",num_rolls)==0)
        {
            fprintf(stderr,"ERROR: number of rolls did not have an \
acceptable value\n\n");
            clear_stdin();
        }
        else if (*num_rolls < 10 || *num_rolls > 10000)
        {
            fprintf(stderr,"ERROR: number of rolls was not in the \
acceptable range\n10 <= number of dice <= 10000\n\n");
            clear_stdin();
        }
        else break;
    }
}

int roll_dice(int num_dice,int num_sides)
{
    int sum = 0;
    for (int i=0;i<num_dice;i++)
    {
        sum += rand() % num_sides;
    }
    return sum;
}
/* MAIN DICE PROGRAM */
int main(void)
{
    int num_dice, num_sides, num_rolls;
    get_seed();

    get_num_dice(&num_dice);
    get_num_sides(&num_sides);
    get_num_rolls(&num_rolls);

    int current_roll;
    printf(" The numbers rolled are:\n");

    for (int r=0;r<((num_rolls-(num_rolls%10))/10);r++)
    {
        for (int c=0;c<10;c++)
        {
            current_roll = roll_dice(num_dice,num_sides);
            printf(COL_FORMAT,current_roll);
        }
        printf("\n");
    }
    return 0;
}
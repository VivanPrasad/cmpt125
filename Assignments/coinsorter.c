#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Coin Sorting Machine

typedef struct CoinType {
    char name[100];
    float weight, weight_variance;
    float diameter, diameter_variance;
    int coins_in_roll;
    bool is_bent;

} Coin;

typedef struct DynamicAlloc {
    int size;
    Coin *coins;
} CoinArray;

/* Function prototypes */
int print_summary(FILE *stream);

int main(void)
{
    FILE *config_file = NULL;
    FILE *input_file = NULL;
    FILE *export_file = NULL;
    
    char config_file_name[1024];
    char input_file_name[1024];

    CoinArray coin_array; // Dynamic coin array
    coin_array.coins = (Coin *)malloc(coin_array.size * sizeof(Coin));

    print_summary(stdout);
    print_summary(export_file);
    return 0;
}

int print_summary(FILE *stream)
{
    fprintf(stdout, "\n\n\n"); //Step 27
    return 0;
}
/* Coin Sorter Functionality
1. Coin will be a structure that has all 6 properties.
Coin will be constructed for every line of the input file
2. Prompt user for config file to configure the coin sorter
3. Open config file and check lines: see CONFIG FILE ENTRY FORMAT
4. If it did not open correctly, print errors
5. Read number of coin types in config file, print errors
6. Read each coin type data, print errors
7. Place the values in dynamic structures, in a dynamic struc array
8. Prompt user for input file and check
9. Open input file
10. Check if file opened, 3 attempts, print errors
11. Prompt and read name of output file
12. Open output file to export simulation
Check if file opened, 3 attempts, print errors
13. Read number of lines in coin input file
(first integer in the file, number of lines[1,5000])
14. Verify number of lines/coins read, print errors
15. For each line: see INPUT FILE ENTRY FORMAT
16. print errors 
17. print errors
18. If extra data than stated, ignore
if a coin is bent, ignore all other data
else if the weight and diameter are not in range, coin type is other
else if image of coin matches
*/

/* CONFIG FILE ENTRY FORMAT
- numCoins [1,5]
- name  weight[0.0,40.0g] weight_variance[0.1,4.0g] diameter[0.0,60.0mm] diameter_variance[0.1,3.0mm] coins_in_roll[5,50]
*/


/* INPUT FILE ENTRY FORMAT
<weight> <diameter> <usable/bent> <BothSidesMatch/OneSideMatches/NoMatch>
any number of spaces/tabs in between
*/

/* ------ KEEP IN MIND ------ */
// All prompts should be printed only to the screen
// All output should be printed to stdout and to the output file
// All error messages should be printed only to stderr
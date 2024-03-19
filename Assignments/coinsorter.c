#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Coin Sorting Machine

# define NAME_MAX_LENGTH 1024
typedef struct CoinType {
    char name[100];
    float weight, weight_variance;
    float diameter, diameter_variance;
    int roll_capacity;
    bool is_bent;

} Coin;

typedef struct DynamicAlloc {
    int size;
    Coin *coins;
} CoinTypes;

/* Function prototypes */
int print_summary(FILE *stream);

int main(void) {
    FILE *config_file = NULL;
    FILE *input_file = NULL;
    FILE *export_file = NULL;
    
    char config_file_name[NAME_MAX_LENGTH];
    char input_file_name[NAME_MAX_LENGTH];
    char output_file_name[NAME_MAX_LENGTH];

    for (int attempt=1;attempt<=4;attempt++) {
        
        printf("Please enter the name of the configuration file: ");
        scanf("%s",&config_file_name);
        
        config_file = fopen(config_file_name,"r");
        
        if (config_file != NULL) break;
        else if (attempt != 4) {
            fprintf(stderr,"ERROR: The opening of the configuration file, %s, failed.\n",config_file_name);
        } else {
            fprintf(stderr,"ERROR: Exceeded the maximum number of tries to open the configuration file.\n",config_file_name);
            return EXIT_FAILURE;
        }
    }
    
    /* ---Reading File--- */
    CoinTypes coin_types; // Declare coin array

    if (feof(config_file)) {
        fprintf(stderr,"ERROR: at the end of file, no more data in the file.\n");
        fclose(config_file);
        return 1;
    } else if (fscanf(config_file, "%d\n",&coin_types.size) != 1) {
        fprintf(stderr,"ERROR: data corrupt, could not read any digits into the variable\n");
        fclose(config_file);
        return 1;
    } else if (coin_types.size <= 0 || coin_types.size > 5) {
        fprintf(stderr,"ERROR: the value of the number of coin types is out of range.\n");
        fclose(config_file);
        return 1;
    }
    
    coin_types.coins = (Coin *)malloc(coin_types.size * sizeof(Coin));

    for (int i=0;i<coin_types.size;i++) {
        if (feof(config_file)) {
            fprintf(stderr,"ERROR: Not enough rows (types) in the configuration file\n");
            fclose(config_file); free(coin_types.coins); coin_types.coins = NULL;
            return 1;
        } 
        
        fscanf(config_file, "%s ",&coin_types.coins[i].name);
        printf("%s ",coin_types.coins[i].name);
        
        if (fscanf(config_file, "%f", &coin_types.coins[i].weight) != 1) {
            fprintf(stderr,"ERROR: Could not read the weight of the coin\n");
            fclose(config_file); free(coin_types.coins); coin_types.coins = NULL;
            return 1;
        } else if (coin_types.coins[i].weight < 0.0 || coin_types.coins[i].weight > 40.0) {
            fprintf(stderr,"ERROR: Weight of the coin is out of range\n");
            fclose(config_file); free(coin_types.coins); coin_types.coins = NULL;
            return 1;
        }
        if (fscanf(config_file,"%f",&coin_types.coins[i].weight_variance) != 1) {
            fprintf(stderr,"ERROR: Could not read the variance of the weight of the coin\n");
            fclose(config_file); free(coin_types.coins); coin_types.coins = NULL;
            return 1;
        }
        if (fscanf(config_file,"%f",&coin_types.coins[i].diameter) != 1) {
            fprintf(stderr,"ERROR: Could not read the diameter of the coin\n");
            fclose(config_file); free(coin_types.coins); coin_types.coins = NULL;
            return 1;
        }
        if (fscanf(config_file,"%f",&coin_types.coins[i].diameter_variance) != 1) {
            fprintf(stderr,"ERROR: Could not read the variance of the diameter of the coin\n");
            fclose(config_file); free(coin_types.coins); coin_types.coins = NULL;
            return 1;
        }
        if (fscanf(config_file,"%d\n",&coin_types.coins[i].roll_capacity) != 1) {
            fprintf(stderr,"ERROR: Could not read the roll capacity\n");
            fclose(config_file); free(coin_types.coins); coin_types.coins = NULL;
            return 1;
        }
    }
    
    
    free(coin_types.coins);
    coin_types.coins = NULL;
    
    //print_summary(stdout);
    //print_summary(export_file);
    return 0;
}

int print_summary(FILE *stream)
{
    fprintf(stream, "\n\n\n"); //Step 27
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
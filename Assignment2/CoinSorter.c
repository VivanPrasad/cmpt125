// --- CoinSorter.c ---
// Description: Identifies and sorts coins within the given config and input
// files. Exports a file with data about the results and coin counts
// Author: M. Vivan Prasad
// Last Modified: 03/22/24

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

# define NAME_MAX_LENGTH 1024 // Max file name length
# define TEXT_LENGTH 20
// Containers
# define BENT_CAPACITY 300.0 //container 300.0 grams
# define OTHER_CAPACITY 200.0 //container 200.0 grams

typedef struct CoinType {
    char name[100];
    double weight;
    double diameter;
    double weight_variance;
    double diameter_variance;
    int roll_capacity;

    int coins_in_roll; //Current coins in roll
    int num_rolls; //Number of rolls currently filled
} Coin;

typedef struct DynamicAlloc {
    int size;
    Coin* coins;
} CoinTypes;

typedef struct CoinEntry {
    double weight;
    double diameter;
    char quality[TEXT_LENGTH];
    char image[TEXT_LENGTH];
} Entry;

struct Container {
    double weight; //Current weight of the container
    double capacity; //How much weight the container can hold
    int num_coins; // How many coins are in the current container
    struct Container* next; //Next container in the linked list
};

struct ContainerList {
    struct Container* head; //Initial container in the linked list
    char name[TEXT_LENGTH];
};

struct Container* create_container(double capacity) {
    struct Container* new = NULL;
    new = (struct Container*)malloc(sizeof(struct Container));
    if (new != NULL) {
        new->weight = 0.0;
        new->capacity = capacity;
        new->num_coins = 0;
        new->next = NULL;
        return new;
    }
    return NULL;
}
// Create a new linked list of containers (stars with 1 empty container)
struct ContainerList* create_container_list(double capacity) {
    struct ContainerList *list = NULL;
    list = (struct ContainerList*)malloc(sizeof(struct ContainerList));
    if (list != NULL) {
		list->head = create_container(capacity);
	}
    return list;
}
// Free all containers and the list
void free_containers(struct ContainerList*list) {
    struct Container* current = list->head;
    while (current->next != NULL) {
        struct Container* temp = current;
        current = current->next;
        free(temp); temp = NULL;
    }
    free(list); list = NULL;
}

// Get the number of full containers in the list
int get_container_count(struct ContainerList* list) {
	int count = 0;
	struct Container* current = list->head;
	while (current->next != NULL) {
		count++; //If full
		current = current->next;
	}
	return (count); //Last container in the list cannot be full
}
double get_total_weight(struct ContainerList* list) {
    struct Container* current = list->head;
    double total = current->weight;
    while (current->next != NULL) {
		current = current->next;
        total += current->weight;
	}
    return total;
}
int get_total_coins(struct ContainerList* list) {
    struct Container* current = list->head;
    int total = current->num_coins;
    while (current->next != NULL) {
        current = current->next;
		total += current->num_coins;
	}
    return total;
}
double get_container_weight(struct ContainerList* list) {
    struct Container* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    return current->weight;
}
int get_container_coins(struct ContainerList* list) {
    struct Container* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    return current->num_coins;
}
// Add the coin to the container, creates a new one if needed
void add_to_container(struct ContainerList* list,double weight) {
    struct Container* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    if (fabs(current->weight+weight) >= current->capacity) {
        current->next = create_container(list->head->capacity);
        current->next->num_coins += 1;
        current->next->weight += weight;
    } 
    else {
        current->weight += weight;
        current->num_coins += 1;
        
    }
}

void add_to_wrapper(Coin *coin) {
    //Create a new wrapping roll if roll reaches capacity
    if (coin->coins_in_roll == coin->roll_capacity)
    {
        coin->num_rolls += 1; //Num rolls increases
        coin->coins_in_roll = 1; 
    } else coin->coins_in_roll += 1;
     // Add coin to roll
}

void print_summary(FILE* stream, CoinTypes *coin_types, 
int other_total, int other_containers, int other_coins, double other_weight,
double bent_weight) { //Step 27

    fprintf(stream, "\n\n\n");
    for (int i=0;i<coin_types->size;i++) {
        fprintf(stream,"The Coin Sorter made %d rolls of %s.\n",
coin_types->coins[i].num_rolls,coin_types->coins[i].name);
        fprintf(stream,"There are %d %s in the partially full roll.\n",
coin_types->coins[i].coins_in_roll,coin_types->coins[i].name);
    }
    fprintf(stream,"The Coin Sorter processed %d other coins.\n", 
other_total);
    fprintf(stream,"The other coins filled %d containers\n",
other_containers);
    fprintf(stream,"There were %d other coins in the partially full \
container\n",other_coins);
    fprintf(stream,"The total weight of the other coins was %lf grams\n",
other_weight);
    fprintf(stream,"The Coin Sorter processed %lf g of bent coins\n",
bent_weight);
}

int str_to_double(const char *str, double *result) {
    char *endp;
    double converted;
    converted = strtod(str, &endp);
    if (*endp != '\0' || endp == str) return 0;
    *result = converted;
    return 1;
}

int str_to_integer(const char *str, long int *result) {
    char *endp;
    long int converted;
    converted = strtol(str, &endp, 10);
    if (*endp != '\0' || endp == str) return 0;
    *result = converted;
    return 1;
}

void clear_stream(FILE*stream)
{
    int c;
    do {
        c = fgetc(stream);
    } while (c!='\n');
}

FILE* get_config_file() {
    FILE* config_file = NULL;
    char config_file_name[NAME_MAX_LENGTH];

    for (int attempt=1;attempt<=3;attempt++) {
        
        printf("Please enter the name of the configuration file: ");
        scanf("%s",&config_file_name);
        
        config_file = fopen(config_file_name,"r");
        
        if (config_file != NULL) break;

        else if (attempt < 3) {
            fprintf(stderr,"ERROR: The opening of the configuration \
file, %s, failed.\n",config_file_name);
        } else {
            fprintf(stderr,"ERROR: Exceeded the maximum number of tries \
to open the configuration file.\n",config_file_name);
            return NULL;
        }
    }
    return config_file;
}

FILE* get_input_file() {
    FILE* input_file = NULL;
    char input_file_name[NAME_MAX_LENGTH];

    // PROMPT 3 TIMES
    for (int attempt=1;attempt<=3;attempt++) {
        
        printf("Type the name of the coin input file: ");
        scanf("%s",&input_file_name);
        
        input_file = fopen(input_file_name,"r");
        
        if (input_file != NULL) break;

        else if (attempt < 3) {
            fprintf(stderr,"ERROR: File %s is not open for \
coin input\n",input_file_name);
        } else {
            fprintf(stderr,"ERROR: You exceeded maximum number of tries \
allowed for entering the coin input file name.\n",input_file_name);
            return NULL;
        }
    }
    return input_file;
}

FILE *get_output_file() {
    FILE *output_file = NULL;
    char output_file_name[NAME_MAX_LENGTH];
    for (int attempt=1;attempt<=3;attempt++) {
        
        printf("Type the name of the output file which will hold \
the simulation results: ");
        scanf("%s",&output_file_name);
        
        output_file = fopen(output_file_name,"w");
        
        if (output_file != NULL) break;

        else if (attempt < 3) {
            fprintf(stderr,"ERROR: File %s is not open \
for output\n",output_file_name);
        } else {
            fprintf(stderr,"ERROR: You exceeded maximum number of tries \
allowed for entering the coin ouput file name.\n",output_file_name);
            return NULL;
        }
    }
    return output_file;
}
// Apprend data to the coin types: return -1 if unable to categorize (other)
// else, return the index of the coin to access wrapper
int process_entry(Entry *entry,CoinTypes *types) {
    // Iterate through the coin types to find entry matches
    Coin coin;
    for (int i=0;i<types->size;i++) {
        coin = types->coins[i];
        // Checking if the coin is within weight,diameter variance and
        // both image sides match the reference
        if ((fabs(coin.weight - entry->weight) <= (coin.weight_variance + 0.00001)) && 
            (fabs(coin.diameter - entry->diameter) <= (coin.diameter_variance + 0.00001)) &&
            strcmp(entry->image,"BothSidesMatch")==0)
        {
            return i;
        }
    }
    return -1;
}
int main(void) {
    FILE *config_file = NULL;
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    
    CoinTypes coin_types; // Declare coin array
    int num_coins; // Number of coins (input file)

    Entry entry; // Struct for current line entry of input file

    // Variables for the bent and current container data
    struct ContainerList* bent = create_container_list(BENT_CAPACITY);
    struct ContainerList* other = create_container_list(OTHER_CAPACITY);
    int other_containers = 0; //Number of other containers filled

    config_file = get_config_file(); // Get config file from input
    if (config_file == NULL) return EXIT_FAILURE;

    /* ------ CONFIG FILE READING ------ */
    if (feof(config_file)) { //EMPTY
        fprintf(stderr,"ERROR: at the end of file, no more \
data in the file.\n");
        fclose(config_file);
        return EXIT_FAILURE;
    } else if (fscanf(config_file, "%d",&coin_types.size) != 1) {
        fprintf(stderr,"ERROR: data corrupt, could not read any digits \
into the variable\n");
        fclose(config_file);
        return EXIT_FAILURE;
    } else if (coin_types.size <= 0 || coin_types.size > 5) { //RANGE
        fprintf(stderr,"ERROR: the value of the number of coin types \
is out of range.\n");
        fclose(config_file);
        return EXIT_FAILURE;
    }

    coin_types.coins = (Coin *)malloc(coin_types.size * sizeof(Coin)); 

    clear_stream(config_file);
    if (coin_types.coins == NULL) {
        fprintf(stderr,"ERROR: Unable to allocate memory for a \
CoinType structure\n");
        fclose(config_file);
        return EXIT_FAILURE;
    }
    
    //Repeat reading data (coin_types.size) times
    for (int i=0;i<coin_types.size;i++) {
        // CHECK IF LINE HAS DATA
        if (feof(config_file)) {
            fprintf(stderr,"ERROR: Not enough rows (types) \
in the configuration file\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL; //Cleanup file + dynamic
            return EXIT_FAILURE;
        }
        // COIN NAME READING
        fscanf(config_file, "%s",&coin_types.coins[i].name);
        // COIN WEIGHT READING
        if (fscanf(config_file, "%lf", //VALUE
        &coin_types.coins[i].weight) != 1) {
            fprintf(stderr,"ERROR: Could not read the weight of the coin\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
        } else if (coin_types.coins[i].weight <= 0.0 || //RANGE
        coin_types.coins[i].weight > 40.0) {
            fprintf(stderr,"ERROR: Weight of the coin is out of range\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
        }

        // WEIGHT VARIANCE READING
        if (fscanf(config_file,"%lf", //VALUE
        &coin_types.coins[i].weight_variance) != 1) {
            fprintf(stderr,"ERROR: Could not read the variance of the \
weight of the coin\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
        } else if (coin_types.coins[i].weight_variance <= 0.1 || //RANGE
         coin_types.coins[i].weight_variance > 4.0) {
            fprintf(stderr,"ERROR: Variance of the weight of the coin \
is out of range\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
         }
        
        // DIAMETER READING
        if (fscanf(config_file,"%lf", //VALUE
        &coin_types.coins[i].diameter) != 1) {
            fprintf(stderr,"ERROR: Could not read the diameter of the coin\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
        } else if (coin_types.coins[i].diameter <= 0.0 || //RANGE
        coin_types.coins[i].diameter > 60.0) {
            fprintf(stderr,"ERROR: Diameter of the coin is out of range\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
        }

        // DIAMETER VARIANCE READING
        
        if (fscanf(config_file,"%lf", //VALUE
        &coin_types.coins[i].diameter_variance) != 1) {
            fprintf(stderr,"ERROR: Could not read the variance \
of the diameter of the coin\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
        } else if (coin_types.coins[i].diameter_variance <= 0.1 || //RANGE
        coin_types.coins[i].diameter_variance > 3.0) {
            fprintf(stderr,"ERROR: Variance of the diameter of the coin \
is out of range\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
        }

        // ROLL CAPACITY READING
        if (fscanf(config_file,"%d", //VALUE
        &coin_types.coins[i].roll_capacity) != 1) {
            fprintf(stderr,"ERROR: Could not read the roll capacity\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
        } else if (coin_types.coins[i].roll_capacity < 5 || //RANGE
        coin_types.coins[i].roll_capacity > 50) {
            fprintf(stderr, "ERROR: Roll capacity for the coin is \
out of range\n");
            fclose(config_file);
            free(coin_types.coins); coin_types.coins = NULL;
            return EXIT_FAILURE;
        }

        coin_types.coins[i].coins_in_roll = 0; //Initialize coins in roll to 0
        coin_types.coins[i].num_rolls = 0; //Initialize filled rolls to 0
        
        char c; fscanf(config_file,"\n",&c); // Clear remaining line
    }
    
    fclose(config_file); // Close config file, data received

    input_file = get_input_file(); // Get input file by input
    if (input_file == NULL) return EXIT_FAILURE;

    output_file = get_output_file(); // Get output file by input
    if (output_file == NULL) return EXIT_FAILURE;

    /*----------------------------------------------------------------------*/
    
    
    /* ------ INPUT FILE READING ------ */
    
    if (feof(input_file)) {
        fprintf(stderr,"ERROR: Coin input file is empty \
data in the file.\n");
        fclose(input_file);
        free(coin_types.coins); coin_types.coins = NULL;
        return EXIT_FAILURE;
    } else if (fscanf(input_file, "%d",&num_coins) != 1) {
        fprintf(stderr,"ERROR: First piece of data in the coin input file is \
not an integer\n");
        fclose(input_file);
        free(coin_types.coins); coin_types.coins = NULL;
        return EXIT_FAILURE;
    } else if (num_coins < 1 || num_coins > 5000) { //RANGE
        fprintf(stderr,"ERROR: The number of coins is out of range\n");
        fclose(input_file);
        free(coin_types.coins); coin_types.coins = NULL;
        return EXIT_FAILURE;
    }
    clear_stream(input_file);
    
    //Repeat reading input data (num_coins) times from (1 to num_coins)
    for (int i=1; i<=num_coins;i++) {

        //printf("%lf %lf %s %s\n",
        //entry_weight, entry_diameter,entry_quality,entry_image);

        // ENTRY WEIGHT READING
        if (feof(input_file)) { //END OF FILE
            fprintf(stderr,"ERROR: No more data\nSimulation \
completed early before line %d of input\n",i);
            break; //END EARLY
        } 
        char weight_str[10]; 
        fscanf(input_file,"%s",&weight_str);
        if (str_to_double(weight_str,&entry.weight) != 1) { //VALUE
            fprintf(stderr,"ERROR: Weight value read, \
on line %d, is not a double\nSimulation terminated early: \
Please correct your data file\n",i);
            break; //END EARLY
        } else if (entry.weight <= 0.0 || entry.weight > 40.0) { //RANGE
            fprintf(stderr,"ERROR: Weight out of range, \
ignoring line %d in the input file\n",i);
            clear_stream(input_file);
            continue;
        }

        // ENTRY DIAMETER READING
        if (feof(input_file)) { //END OF FILE
            fprintf(stderr,"ERROR: Weight measurement only,\
ignoring line %d in the input file\n",i);
            clear_stream(input_file);
            continue;
        } 
        char diameter_str[8]; 
        fscanf(input_file,"%s",&diameter_str);
        if (str_to_double(diameter_str,&entry.diameter) != 1) { //VALUE
            fprintf(stderr,"ERROR: Diameter value read \
on line %d is not a double\nSimulation terminated early: \
Please correct your data file\n",i);
            break; //END EARLY
        } else if (entry.diameter <= 0.0 || entry.diameter > 60.0) { //RANGE
            fprintf(stderr,"ERROR: Diameter out of range, \
ignoring line %d in the input file\n",i);
            clear_stream(input_file);
            continue;
        }

        //ENTRY QUALITY READING
        if (feof(input_file)) { //END OF FILE
            fprintf(stderr,"ERROR: Weight and diameter measurements\
\nIgnoring line %i of the input file\n",i);
            break; //END EARLY
        } else if (fscanf(input_file,"%s",&entry.quality) != 1) { //VALUE
            fprintf(stderr,"ERROR: Diameter value read \
on line %d is not a double\nSimulation terminated early: \
Please correct your data file\n",i);
            break; //END EARLY
        } else if (strcmp(entry.quality,"bent")!=0 && //STRING VALIDATING
        strcmp(entry.quality,"usable")!=0) { 
            fprintf(stderr,"ERROR: Result of test to determine \
if coin is bent at line %d is invalid\nIgnoring this line of data\n",i);
            clear_stream(input_file);
            continue;
        }

        //ENTRY IMAGE READING
        if (feof(input_file)) {
            fprintf(stderr,"ERROR: Weight and diameter measurements \
and bent string only\nIgnoring line %d of the input file\n",i);
            clear_stream(input_file);
            continue;
        } else if (fscanf(input_file,"%s",&entry.image) != 1) { //VALUE
            fprintf(stderr,"ERROR: image processing result \
at line %d is invalid\nIgnoring this line of data\n",i);
            clear_stream(input_file);
            continue;
        } else if (strcmp(entry.image,"NoMatch") != 0 && //VALIDITY
        strcmp(entry.image,"OneSideMatches") != 0 && 
        strcmp(entry.image,"BothSidesMatch") != 0) {
            fprintf(stderr,"ERROR: image processing result at line %d is \
invalid\nIgnoring this line of data\n",i);
            clear_stream(input_file);
            continue;
        }
        
        char c; fscanf(input_file,"\n",&c); // Clear remaining line

        // PROCESSING ENTRY DATA FROM LINE
        int entry_type = process_entry(&entry,&coin_types);
        if (strcmp(entry.quality,"bent") == 0) {
            add_to_container(bent,entry.weight);
            printf("The Coin Sorter has sent this coin to the bent coin \
container\nThe coins in the bent coin container now weigh %lf grams\n",
get_container_weight(bent));
            fprintf(output_file,"The Coin Sorter has sent this coin to \
the bent coin container\nThe coins in the bent coin container now weigh %lf \
grams\n", get_container_weight(bent));
        } //If not bent, it will process: if unable to categorize, add to other
        else if (entry_type != -1) {
            // Add entry to the given categorized type
            add_to_wrapper(&coin_types.coins[entry_type]);
            printf("The Coin Sorter has sent one coin to the %s's wrapper\n",
coin_types.coins[entry_type].name);
            fprintf(output_file,"The Coin Sorter has sent one coin to the \
%s's wrapper\n",
coin_types.coins[entry_type].name);
            if (coin_types.coins[entry_type].coins_in_roll ==
            coin_types.coins[entry_type].roll_capacity) {
            printf("The %s wrapper is now full\nThe %s wrapper has now \
been replaced\n",coin_types.coins[entry_type].name,
coin_types.coins[entry_type].name);
            fprintf(output_file,"The %s wrapper is now full\nThe %s wrapper \
has now been replaced\n",coin_types.coins[entry_type].name,
coin_types.coins[entry_type].name);
            } 
            else {
                printf("There are now %d coins in the %s's wrapper\n",
coin_types.coins[entry_type].coins_in_roll,
coin_types.coins[entry_type].name);
                fprintf(output_file, "There are now %d coins in the \
%s's wrapper\n", coin_types.coins[entry_type].coins_in_roll,
coin_types.coins[entry_type].name);
            }
        } else { //Else other container addition will be processed
            int limit = get_container_weight(other)+entry.weight;
            add_to_container(other,entry.weight);
            
            printf("The Coin Sorter has sent this coin to the other coin \
container\n");
            fprintf(output_file, "The Coin Sorter has sent this coin \
to the other coin container\n");

            if (limit >= OTHER_CAPACITY) {
                printf("This coin does not fit in the other coin \
container\nThe other coin container has been replaced\n");
                fprintf(output_file,"This coin does not fit in the other \
coin container\nThe other coin container has been replaced\n");
                printf("The coin in the other coin container \
now weigh %lf grams\n", get_container_weight(other));
            fprintf(output_file,"The coin in the other coin container \
now weigh %lf grams\n", get_container_weight(other));

            } else {
            printf("The coins in the other coin container \
now weigh %lf grams\n", get_container_weight(other));
            fprintf(output_file,"The coins in the other coin container \
now weigh %lf grams\n", get_container_weight(other));
            }
        } 
    } // END OF ENTRY READING CATEGORIZING LOOP

    fclose(input_file);
    //Cleanup dynamically allocated memory for coin types
    
    print_summary(stdout,&coin_types,get_total_coins(other),
get_container_count(other),get_container_coins(other),
get_total_weight(other), get_total_weight(bent));
    print_summary(output_file,&coin_types,get_total_coins(other),
get_container_count(other),get_container_coins(other),
get_total_weight(other), get_total_weight(bent));

    fclose(output_file);
    free(coin_types.coins); coin_types.coins = NULL;
    free_containers(bent); free_containers(other);

    
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

// COLORS
#define WHITE "\e[38;5;7m"
#define RED "\e[38;5;1m"
#define GREEN "\e[38;5;10m"
#define BLUE "\e[0;34m"

#define NUM_COLORS 4
#define NUM_DIRECTIONS 4
#define FILE_TEXT_LENGTH 100

#define ROBOT 64
enum initTypeList { Random=1, Checker=2, AllWhite=3};

struct Robot {
    int x, y;
    int direction;
    int paintColor;
};

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed);
void InitBoardChecker(int **board, int numRows, int numCols); 
void InitBoardAllWhite(int **board, int numRows, int numCols); 

int InitBoard(int **board, int numRows, int numCols, enum initTypeList initTypeValue, unsigned int seed);
int InitRobots(struct Robot *robots, int numRows, int numCols, int numRobots,unsigned int seed);

int nextBoard(int **board, int numRows, int numCols, int numRobots, struct Robot *robots);

void printSquare(int value);
void printRobot(int color);
void printBoard(int **board, int numRows, int numCols, int numRobots, struct Robot *robots);
void fprintBoard(FILE *outputFile, int **board, int numRows, int numCols, int numRobots, struct Robot *robots);

int main(void)
{
    FILE* inputFile = NULL; // File to import data
    char inputName[FILE_TEXT_LENGTH]; 
    
    FILE* outputFile = NULL; // File to export data
    char outputName[FILE_TEXT_LENGTH]; 

    int numRows, numCols; // 50 to 300 inclusive
    int numRobots; // 1 to 10 inclusive
    enum initTypeList initTypeValue; // 1 to 3 inclusive
    unsigned int initSeed; //10 to 32767 inclusive
    int numTurns; //10 to 5000 inclusive
    int printInterval; // 1 to turns inclusive

    for (int attempt=1;attempt<=5;attempt++) // 5 attempts to read input file
    {
        printf("Enter the name of the input file: ");
        scanf("%s",inputName);
        inputFile = fopen(inputName,"r");
        if (inputFile==NULL)
        {
            printf("ERROR: Input file not opened correctly.\n");
            if (attempt==5)
            {
                printf("ERROR: Failed to open the input file 5 times. Terminating the program.\n");
                return 1;
            }
        } else break;
    }
    
    // OUTPUT FILE NAME READING
    if (feof(inputFile)) 
    {
        fprintf(stderr,"ERROR: Output file name was not in the input file (reached eof)\n");
        return 1;
    }
    fscanf(inputFile,"%s\n",&outputName);
    outputFile = fopen(outputName,"w"); // Open and make the export file
    
    // NUMBER OF ROWS READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The number of rows was not in the input file (reached eof)\n");
        fprintf(outputFile,"ERROR: The number of rows was not in the input file (reached eof)\n");
        return 1;
    }
    fscanf(inputFile,"%d\n",&numRows);
    if (numRows < 20 || numRows > 300)
    {
        fprintf(stderr,"ERROR: The number of rows was outside the specified range (50 to 300 inclusive)\n");
        fprintf(outputFile,"ERROR: The number of rows was outside the specified range (50 to 300 inclusive)\n");
        return 1;
    }

    // NUMBER OF COLUMNS READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The number of columns was not in the input file (reached eof)\n");
        fprintf(outputFile,"ERROR: The number of columns was not in the input file (reached eof)\n");
        return 1;
    }
    fscanf(inputFile,"%d\n",&numCols);
    if (numCols < 20 || numCols > 300)
    {
        fprintf(stderr,"ERROR: The number of columns was outside the specified range (50 to 300 inclusive)\n");
        fprintf(outputFile,"ERROR: The number of columns was outside the specified range (50 to 300 inclusive)\n");
        return 1;
    }

    // NUMBER OF ROBOTS READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The number of robots was not in the input file (reached eof)\n");
        fprintf(outputFile,"ERROR: The number of robots was not in the input file (reached eof)\n");
    }
    fscanf(inputFile,"%d\n",&numRobots);
    if (numRobots < 1 || numRobots > 10)
    {
        fprintf(stderr,"ERROR: The number of robots was outside the specified range (1 to 10 inclusive)\n");
        fprintf(outputFile,"ERROR: The number of robots was outside the specified range (1 to 10 inclusive)\n");
        return 1;
    }

    // BOARD TYPE READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The initTypeValue was not in the input file (reached eof)\n");
        fprintf(outputFile,"ERROR: The initTypeValue was not in the input file (reached eof)\n");
    }
    fscanf(inputFile,"%d\n",&initTypeValue);

    // SEED READING
    if (feof(inputFile))
    {
        fprintf(stderr,"ERROR: The initTypeValue was not in the input file (reached eof)\n");
        fprintf(outputFile,"ERROR: The initTypeValue was not in the input file (reached eof)\n");
    }
    fscanf(inputFile,"%u\n",&initSeed);
    fscanf(inputFile,"%d\n",&numTurns);
    fscanf(inputFile,"%d\n",&printInterval);
    fclose(inputFile);

    /*------------GAME SETUP STUFF------------*/

    int **boardpp = NULL; // BOARD SETUP
    boardpp = (int**)malloc(numRows*sizeof(int*));
    if (boardpp == NULL)
	{
		fprintf(stderr,"ERROR: array of pointers for could not be allocated\n");
        fprintf(stderr,"ERROR: array of pointers for could not be allocated\n");
		return 100;
	}
	boardpp[0] = (int*)malloc(numRows*numCols*sizeof(int));
	if (boardpp[0] == NULL)
	{
		fprintf(stderr,"ERROR: Array storage could not be allocated\n");
        fprintf(stderr,"ERROR: Array storage could not be allocated\n");
		free(boardpp);
		return 100;
	}
	for (int i=1;i<numRows;i++)
	{
		boardpp[i] = boardpp[0] + (i*numCols);
	}
    InitBoard(boardpp,numRows,numCols,initTypeValue,initSeed);

    struct Robot *robots = NULL; // ROBOT SETUP
    robots = (struct Robot*)malloc(numRobots*sizeof(struct Robot)); // Declare dynamic array of robots
    if (robots == NULL)
    {
        fprintf(stderr,"ERROR: Array storage could not be allocated\n");
        fprintf(stderr,"ERROR: Array storage could not be allocated\n");
        free(robots); robots = NULL;
		return 100;
    }
    InitRobots(robots,numRows,numCols,numRobots,initSeed);

    for (int t=0;t<=numTurns;t++)
    {
        if (t==0 || t==(numTurns) || (t%printInterval==0)) 
        {
            printf("Turn %d\n",t);
            fprintf(outputFile,"Turn %d\n",t);
            printBoard(boardpp,numRows,numCols,numRobots, robots);
            fprintBoard(outputFile,boardpp,numRows,numCols,numRobots, robots);
        }
        nextBoard(boardpp,numRows,numCols,numRobots,robots);
    }

    fclose(outputFile);
    free(robots); robots = NULL;
    free(boardpp); boardpp = NULL;
    free(boardpp[0]); boardpp[0] = NULL;
    
    return 0;
}

int InitRobots(struct Robot *robots, int numRows, int numCols, int numRobots,unsigned int seed)
{
    srand(seed); // Initialize the random number generator
    for (int i=0;i<numRobots;i++) // Initialize each robot at a random position, direction and color
    {
        robots[i].x = rand() % numCols;
        robots[i].y = rand() % numRows;
        robots[i].direction = rand() % NUM_DIRECTIONS + 1;
        robots[i].paintColor = rand() % NUM_COLORS + 1;
        //printf("Robot %d - Pos: (%d, %d) - Dir: %d - Col: %d\n",
        //i+1,robots[i].x,robots[i].y,robots[i].direction,robots[i].paintColor);
    }
    return 0;
}

int InitBoard(int **boardpp, int numRows, int numCols, enum initTypeList initTypeValue, unsigned int seed)
{
    switch (initTypeValue)
    {
        case 1:
            InitBoardRand(boardpp,numRows,numCols,seed); break;
        case 2:
            InitBoardChecker(boardpp,numRows,numCols); break;
        case 3:
            InitBoardAllWhite(boardpp,numRows,numCols); break;
        default: break;
    }
    return 0;
}

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed)
{
    srand(seed);
    for (int r=0;r<numRows;r++)
    {
        for (int c=0;c<numCols;c++)
        {
            board[r][c] = rand() % NUM_COLORS + 1;
        }
    }
}
void InitBoardChecker(int **board, int numRows, int numCols)
{
    int checkerColor;
    for (int r=0;r<numRows;r++)
    {
        if (r%2==0) checkerColor = 1;// White on even rows
        else checkerColor = 2; // Red on odd rows
        for (int c=0;c<numCols;c++)
        {
            board[r][c] = checkerColor;
            checkerColor = ((checkerColor)%2)+1; // Alternate White and Red 
        }
    }
}
void InitBoardAllWhite(int **board, int numRows, int numCols)
{
    for (int r=0;r<numRows;r++) 
    {
        for (int c=0;c<numCols;c++) 
        {
            board[r][c] = 1;
        }
    }
}

/* BOARD SIMULATION FUNCTIONS */
int nextBoard(int **board, int numRows, int numCols, int numRobots, struct Robot *robots)
{
    int current_tile; //Color of the tile the robot is standing on AFTER moving
    printf("%d",numRobots);
    for (int i=0;i<numRobots;i++)
    {
        current_tile = board[robots[i].y][robots[i].x];
        board[robots[i].y][robots[i].x] = robots[i].paintColor;
        switch (robots[i].direction)
        {
            case 1: // NORTH
                if (robots[i].y > 0) robots[i].y -= 1;
                break;
            case 2: // SOUTH
                if (robots[i].y < (numRows-1)) robots[i].y += 1;
                break;
            case 3: // EAST
                if (robots[i].x < (numCols-1)) robots[i].x += 1;
                break;
            case 4: // WEST
                if (robots[i].x > 0) robots[i].x -= 1;
                break;
        }
        current_tile = board[robots[i].y][robots[i].x];
        robots[i].direction = (robots[i].direction+current_tile-1)%4 + 1;
    }
    return 0;
}
/*----------OUTPUT FUNCTIONS----------*/
void printSquare(int value)
{
    switch (value)
    {
        case 1: printf(WHITE"%2d",value); break;
        case 2: printf(RED"%2d",value); break;
        case 3: printf(GREEN"%2d",value); break;
        case 4: printf(BLUE"%2d",value); break;
    }
}

void printRobot(int color)
{
    switch (color)
    {
        case 1: printf(WHITE"%2c",ROBOT); break;
        case 2: printf(RED"%2c",ROBOT); break;
        case 3: printf(GREEN"%2c",ROBOT); break;
        case 4: printf(BLUE"%2c",ROBOT); break;
    }
}
// Prints board state to stdout
void printBoard(int **board, int numRows, int numCols, int numRobots, struct Robot *robots)
{
    for (int r=0;r<numRows;r++)
    {
        for (int c=0;c<numCols;c++)
        {
            int robot = -1;
            for (int i=0;i<numRobots;i++)
            {
                if ((robots[i].x)==c && (robots[i].y)==r) robot = i;
            }
            if (robot>-1) printRobot(robots[robot].paintColor);
            else printSquare(board[r][c]);
        }
        printf("\n");
    }
    printf(WHITE"\n\n");
}

// Prints board state to outputFile
void fprintBoard(FILE *outputFile, int **board, int numRows, int numCols, int numRobots, struct Robot *robots)
{
    for (int r=0;r<numRows;r++)
    {
        for (int c=0;c<numCols;c++)
        {
            fprintf(outputFile,"%2d",board[r][c]);
        }
        fprintf(outputFile,"\n");
    }
    fprintf(outputFile,"\n\n");
}
/* Constraints
- Do not use global variables.
- Use named constants, not literal values.
- You may use Global constants for constants that are needed in multiple functions.
- You should follow the class coding standard.
- Use the following structures and enumerations. This is a minimum set, you may use more 
if you wish. You can only change the parts of the structure definition outside of the {}.
 enum initTypeList{ Random = 1, Checkerboard, AllWhite};
*/

/*
1) Begin your program by reading the name of the input file containing the parameters for the
game (into a character array). Try a maximum of five times. Use the following prompts and
error messages.
Enter the name of the input file:
ERROR: Input file not opened correctly.
ERROR: Failed to open the input file 5 times. Terminating the program.
2) Read the following quantities from the input file. These values must be read in the order they
are mentioned in the following list.
- The number of rows in the board you wish to use (20 to 300 inclusive)
- The number of columns in the board you wish to use (20 to 300 inclusive)
- The number of robots to include (1 to 10 inclusive)
- The index indicating the type of initialization for the board (Random=1,
Checkerboard=2 or AllWhite=3). USE A GLOBAL ENUM FOR THE TYPE OF
INITIALIZATION.
- Read the seed initSeed for the choosing of random colours (unsigned int between 10
and 32767 inclusive)
 The number of turns (10 to 5000 inclusive)
 The output will be saved every interval turns. The interval must be in the range one
to number of turns inclusive. The output will be printed for turn 0 (initial state), turn
interval, turn 2xinterval …. turn number of turns -1
 The name of the output file in which the results will be saved.
For each integer value, you should check if the value was read, if the value was corrupted,
and if the value is in range. If the value supplied fails any of these tests you should print an
error message to stderr then clean up and terminate the code. All error messages should be
printed both to stderr and to your output file. Use the appropriate messages from the
following list for each error message.
ERROR: The number of rows was not in the input file (reached eof)
ERROR: The number of rows could not be read due to corrupt data in the file
ERROR: The number of rows was outside the specified range (50 to 300 inclusive)
ERROR: The number of columns was not in the input file (reached eof)
ERROR: The number of columns could not be read due to corrupt data in the file
ERROR: The number of columns was outside the specified range (50 to 300 inclusive)
ERROR: The number of robots was not in the input file (reached eof)
ERROR: The number of robots could not be read due to corrupt data in the file
ERROR: The number of robots was outside the specified range (1 to 10 inclusive)
ERROR: The initTypeValue was not in the input file (reached eof)
ERROR: The initTypeValue could not be read due to corrupt data in the file
ERROR: The initTypeValue was outside the specified range (1 to 3 inclusive)
ERROR: The initSeed was not in the input file (reached eof)
ERROR: The initSeed could not be read due to corrupt data in the file
ERROR: The initSeed was outside the specified range (10 to 32767 inclusive)
Follow the same pattern for the error messages for the number of turns and the printing
interval.
3) Dynamically allocate one 2-D integer array with identifier boardpp and with dimensions
number of rows by number of columns. Check that the allocations have worked and print the
following error messages if the allocation fails. After printing an error message, clean up, and
terminate the program. This array represents the gameboard. This array will hold the integer
representations of the colours of the squares (White=1, Red=2, Green=3, Blue=4)
ERROR: array of pointers for could not be allocated
ERROR: Array storage could not be allocated
Dynamically allocate one 1-D array of structures of length numRobots.
4) You will then initialize the board by calling function InitBoard with the following prototype.
This function will call the selected individual initialization functions.
 int InitBoard( int **boardpp, int numRows, int numCols,
 enum initTypeList mylist, unsigned int seed);
 The initialization function will be chosen to create one of the three possible initial board types
 described below

Initial Board type Rand: The colour of each square randomly chosen from the four available
colours. For each square, the probability of any one of the colours being chosen will be equal.
This function is posted with the description of the assignment. The provided function
initializes using srand(initSeed) immediately before determining the colour of the first square
(0,0). The colour of the squares are initialized by one, using one call to rand for each square.
The first square (0,0) will use the first random number generated by rand(). Initialization will
proceed along a row, then on to the start of the next row. This is the same ordering as the
ordering of elements in memory. To assure a matching random board please use the provided
function for this initialization method.
 void InitBoardRand(int **board, int numRows, int numCols,
 unsigned int seed);
Initial Board type Checkerboard: White and red checkerboard pattern with upper left square
(0,0) initialized to white.
 void InitBoardChecker(int **board, int numRows, int numCols);
Initial Board type AllWhite: All squares in the board initialized to white.
 void InitBoardAllWhite(int **board, int numRows, int numCols);
5) Randomly place each robot on the board, assign the direction it is facing, and assign the
colour of paint it is carrying. To do these things use the following algorithm. To compare to
the provided output (get the same random numbers) order is very important.
 Initialize the random number generator srand(seed)
 For each robot (robot(1), robot(2), … , robot(number of robots -1)
 Robot x coordinate = rand() % numCols;
 Robot y coordinate = rand() % numRows;
 Direction robot is facing= rand() % NUM_DIRECTIONS + 1;
 Colour of paint the robot is carrying = rand() % NUM_COLOURS + 1;
6) Run the game for the number of turns requested. For each turn each robot will move forward,
then rotate, and then change the colour of the square it has moved onto.
7) You will print the board into the output file and to the screen every interval turns. The output
will be printed for turn 0 (initial state), turn interval, turn 2xinterval …. turn number of turns
-1. The final turn need not be a multiple of interval.
8) I am providing you with a print function that will display the board in colour on your terminal
(it works only for the terminal, it does not work for writing into a file). This should help you
when you are debugging.
9) Sample outputs for comparison will be posted in the next few days
*/
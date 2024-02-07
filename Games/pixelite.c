#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //
#include <dirent.h> // For opening directories
#include <windows.h> // For terminal manipulation
#include <stdbool.h> // For boolean values
#include <string.h> // For string functions

// KEY BINDS (6)
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13

// WORLD TILESET
#define GRASS_TILE 46 // "
#define STONE_TILE 45 // -
#define WATER_TILE 126 // ~ // It's just water...
#define SEED_TILE 44 // , // Grows into a tree after 10 seconds
#define CAVE_TILE 
#define TREE_TILE 84 // T
#define BRICK_TILE 35 // #
#define VOID_TILE 32 // space

// WORLD ENTITY TILES
#define PLAYER_TILE 64 // @ 
#define SKELETON_TILE 37 // %
#define SNAKE_TILE 38 // &
#define WOLF_TILE 60 // <

// COLORS
#define BLACK "\e[38;5;0m"
#define WHITE "\e[38;5;7m"
#define GREY "\e[38;5;243m"
#define GREEN "\e[38;5;10m"
#define BLUE "\e[0;34m"
#define RED "\e[38;5;1m"
#define YELLOW "\e[38;5;11m"
#define BROWN "\e[38;5;3m"
#define MAGENTA "\e[38;5;5m"
#define CYAN "\e[38;5;6m"

char world[32][16]; 
short WIDTH = 16; short HEIGHT = 8;
short type=0;
short size=0;
char key;

typedef struct Player{
   short x;
   short y;
   short mode;
} Player;

Player * spawnPlayer(short ix,short iy)
{
    Player *newPlayer;
    newPlayer = (Player*)malloc(sizeof(Player));

    newPlayer->x = ix;
    newPlayer->y = iy;
    newPlayer->mode = 0;
    return newPlayer;
    free(newPlayer);
    newPlayer = NULL;
}

const int quit(void){
    //system("cls");
    printf(WHITE);
    exit(0);
}

int runGame(void);
int saveWorld(short x, short y);
int titleScreen(void);

int generateWorld(short type, short size)
{
    WIDTH = 16 + (8*size);
    HEIGHT = 8 + (4*size);
    switch (type){
        case 0: // Forest
            for (short r=0;r<HEIGHT;r++){
                for (short c=0;c<WIDTH;c++){
                    if (rand() % 15 < 14) world[c][r] = GRASS_TILE;
                    else world[c][r] = TREE_TILE;
                    }
                }
            break;
        case 1: // Shore
            for (short r=0;r<HEIGHT;r++){
                for (short c=0;c<WIDTH;c++){
                    short offset = 3+(rand() % (HEIGHT/2+(HEIGHT/8)));
                    if (r>offset) world[c][r] = WATER_TILE;
                    else if (rand() % 12 <11) world[c][r] = GRASS_TILE;
                    else world[c][r] = TREE_TILE;
                }
            }
            break;
        case 2: // Mountain
            for (short r=0;r<HEIGHT;r++){
                for (short c=0;c<WIDTH;c++){
                    short offset = 2+(rand() % (WIDTH/2+HEIGHT/2));
                    if (r<offset && c<offset) world[c][r] = STONE_TILE;
                    else if (rand() % 12 <11) world[c][r] = GRASS_TILE;
                    else world[c][r] = TREE_TILE;}}
            break;
        default:
            break;
    }
    runGame();
    return 0;
}

const char *getFileNameExt(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void setCursor(short x, short y) // Move the terminal cursor to a position
{
    COORD c = {x, y};
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void hideCursor(void) // Hide the terminal cursor
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void showCursor(void){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void setText(short x, short y, char text) {
    setCursor(x,y);
    printf("%c",text);
}

char getTile(short x, short y) { // Returns the tile character
    return world[x][y];
}
void setTile(short x, short y, char tile) {
    world[x][y] = tile;
    setCursor(x,y);
    switch(tile){
        case GRASS_TILE:
            printf(GREEN"%c",GRASS_TILE);
            break;
        case WATER_TILE:
            printf(BLUE"%c",WATER_TILE);
            break;
        case STONE_TILE:
            printf(GREY"%c",STONE_TILE);
            break;
        case TREE_TILE:
            printf(BROWN"%c",TREE_TILE);
            break;
        case VOID_TILE:
            printf(BLACK"%c",VOID_TILE);
            break;
        default:
            printf(WHITE"%c",tile);
            break;
    }
}
void breakTile(short x, short y) {
    setCursor(x,y);
    printf(RED"+");
    switch (world[x][y])
    {
    case TREE_TILE:
        world[x][y] = GRASS_TILE;
        break;
    case GRASS_TILE:
        world[x][y] = STONE_TILE;
        break;
    case STONE_TILE:
        world[x][y] = VOID_TILE;
        break;
    default:
        break;
    }
    Sleep(70);
    setTile(x,y,world[x][y]);
}
void movePlayer(short x, short y) 
{
    setCursor(x,y);
    printf(WHITE"%c",PLAYER_TILE);
}
int refreshWorld(Player *player)
{
    for (int r=0;r<HEIGHT;r++){
        for (int c=0;c<WIDTH;c++){
            setTile(c,r,world[c][r]);
        }
        printf("\n");}
    return 0;
}
int runGame(void) {
    bool running = TRUE;
    Player *player = spawnPlayer(4,4);
    system("cls");
    printf(GREEN"Loading World..."WHITE);
    Sleep(500);
    system("cls");
    refreshWorld(player);
    movePlayer(player->x,player->y);
    do{
        hideCursor();
        key = getch();
       short oldPlayerPos[2] = { player->x, player->y };
        
        if (player->mode==0) setTile(player->x,player->y,world[player->x][player->y]);
        switch (key){
            case KEY_RIGHT:
                player->x = (player->x + 1) % WIDTH;
                break;
            case KEY_LEFT:
                if (player->x == 0) player->x = WIDTH-1;
                else player->x -= 1;
                break;
            case KEY_DOWN:
                player->y = (player->y + 1) % HEIGHT;
                break;
            case KEY_UP:
                if (player->y == 0) player->y = HEIGHT-1;
                else player->y -= 1;
                break;
            case KEY_ENTER:
                player->mode = 1;
                setCursor(player->x,player->y);
                printf(RED"%c",PLAYER_TILE);
                break;
            case KEY_ESC:
                saveWorld(player->x,player->y);
                running = FALSE;
                break;
            default:
                break;
        }
        
        if (getTile(player->x,player->y)==TREE_TILE || getTile(player->x,player->y)==BRICK_TILE || player->mode>0)
        {
            if (player->mode == 1) {
                if (player->x == oldPlayerPos[0] && player->y == oldPlayerPos[1]) continue;
                else {
                    breakTile(player->x,player->y);
                    player->mode = 0;
                }
            }
            
            player->x = oldPlayerPos[0];
            player->y = oldPlayerPos[1];
        }
        if (player->mode == 0) movePlayer(player->x,player->y);
    } while (running==TRUE);
    return 0;
}
FILE * getSaveFile(short index){
    DIR* folder;
    struct dirent *entry;
    char saveName[20];
    short saves = 0;
    folder = opendir(".");
    while (entry=readdir(folder)){
        if (strcmp(getFileNameExt(entry->d_name),"txt")==0){
            if (saves == index) return fopen(entry->d_name,"r");
            saves++;
        } else continue;
    }
    closedir(folder);
    free(entry);
    free(folder);
}

int loadWorld(void) {
    DIR* folder;
    FILE *saveFile = NULL;
    char saveName[20];
    struct dirent *entry;
    short saves = 0;
    bool running = TRUE;
    folder = opendir(".");
    
    system("cls");
    printf(BLUE"Load World\n\n");
    while (entry=readdir(folder)){
        if (strcmp(getFileNameExt(entry->d_name),"txt")==0){
        saves++;
        printf("\e[38;5;%im %d: ",(rand() % 255)+1,saves);
        printf("%s\n",strtok(entry->d_name,".txt"));
        }
        else continue;
    }
    closedir(folder);
    free(folder);
    free(entry);
    if (saves==0) {
        printf(GREY"No Save Data\nReturning to Menu...");
        running = FALSE;
        Sleep(500);
        titleScreen();
    } else printf(RED" Delete a World");
    //scanf("%s", saveName);
    //selectedFile = fopen(saveName,"r");
    short selected = 0;
    do{
        for (short r=0;r<=saves;r++){
            setText(0,r+2,(r==selected) ? 62 : 32); //empty space if not selected
        }
        key = getch();
        switch (key){
            case KEY_DOWN:
                if (selected < saves) selected += 1;
                break;
            case KEY_UP:
                if (selected > 0) selected -= 1;
                break;
            case KEY_ESC:
                running = FALSE;
                system("cls");
                titleScreen();
                break;
            case KEY_ENTER:
                setCursor(1,selected+2);
                if (selected == saves) {
                    FILE *deleteFile = NULL;
                    char deleteFileName[30];
                    printf(GREY" Enter Save to Delete: "BROWN);
                    scanf("%s",&deleteFileName);
                    deleteFile = fopen(strcat(deleteFileName,".txt"),"r");
                    if ((deleteFile == NULL)==FALSE)
                    {
                        fclose(deleteFile);
                        remove(deleteFileName);
                        system("cls");
                        printf(RED"Deleted successfully\nRefreshing..."WHITE);
                        Sleep(500);
                        running = FALSE;
                        loadWorld();
                    }
                    else{
                        system("cls");
                        printf(MAGENTA"Unable to delete save file\nRefreshing..."WHITE);
                        Sleep(500);
                        running = FALSE;
                        loadWorld();}
                } else {
                    saveFile = getSaveFile(selected);
                    short x, y, size;
                    fscanf(saveFile,"%hd %hd %hd",&x,&y,&size);
                    WIDTH = 16 + (8*size);
                    HEIGHT = 8 + (4*size);
                    fscanf(saveFile,"\n","");
                    for (short r=0;r<HEIGHT;r++){
                        for (short c=0;c<WIDTH;c++){
                            fscanf(saveFile,"%c",&world[c][r]);}
                        fscanf(saveFile,"\n","");}
                    running = FALSE;
                    runGame();
                    }
                break;
            }
                
        } while (running==TRUE);
    closedir(folder);
    return 0;
}
int saveWorld(short x,short y) {
    system("cls");
    FILE *saveFile = NULL;
    char saveName[20] = ".";
    showCursor();
    system("cls");
    printf(MAGENTA"Enter a Single-Word with No Extension\n"
    YELLOW"Save World As: "WHITE);
    scanf("%s",&saveName);
    saveFile = fopen(strcat(saveName,".txt"),"w");
    if ((saveFile == NULL)==FALSE) {
        fprintf(saveFile, "%d %d %d\n",x,y,((WIDTH-16)/8));
        for (int r=0;r<HEIGHT;r++) {
            for (int c=0;c<WIDTH;c++) {
                fprintf(saveFile,"%c",world[c][r]);
            }
            fprintf(saveFile,"\n");
        }
        printf(GREEN"World Saved Successfully as '%s'"GREY"\nExiting...\n\n"WHITE,saveName);
        Sleep(500);
    } else {
        printf(RED"World Not Saved"GREY"\nExiting...\n\n"WHITE);
    }
    fclose(saveFile);
    quit();
    return 0;
}

int createWorld(void) {
    const char worldTypes[3][11] = {"Forest    ","Shore     ","Mountain  "};
    const char worldSizes[3][10] = {"Tiny  ","Normal","Grand "};
    const char settings[3][10] = {"Type:","Size:","Create"};
    short selected=0;
    system("cls");
    printf(GREY"Create New World\n\n"
           WHITE">Type: "GREEN"%s\n"
           WHITE" Size: "YELLOW"%s\n"
           CYAN" Create World",worldTypes[type],worldSizes[size]);
    hideCursor();
    do{
        printf(CYAN);
        for (int r=0;r<=2;r++){
            setText(0,r+2,(r==selected) ? 62 : 32); //empty space if not selected
        }
        key = getch();
        switch (key){
            case KEY_DOWN:
                if (selected < 2) selected += 1;
                break;
            case KEY_UP:
                if (selected > 0) selected -= 1;
                break;
            case KEY_ESC:
                system("cls");
                titleScreen();
                break;
            case KEY_ENTER:
                setCursor(1,selected+2);
                switch (selected) {
                    case 0:
                        type = (type + 1) % 3;
                        printf(WHITE"%s "GREEN"%s", settings[selected], worldTypes[type]);
                        break;
                    case 1:
                        size = (size + 1) % 3;
                        printf(WHITE"%s "YELLOW"%s", settings[selected], worldSizes[size]);
                        break;
                    case 2:
                        system("cls");
                        generateWorld(type,size);
                        break;
                    default: break;
                }
                break;
            default:
                break;
        }
    } while(TRUE == TRUE);
}
int titleScreen(void) {
    system("cls");
    hideCursor();
    printf(GREEN"Pixelite\n\n"
           CYAN" New\n"
           BLUE" Load\n"
           MAGENTA" Exit"
           RED);
    short *selected = (short*)calloc(1,sizeof(short));
    bool running = TRUE;
    do{
        for (short r=0;r<=2;r++){
            setText(0,r+2,32);
        }
        setText(0,*selected+2,62);
        key = getch();
        switch (key){
            case KEY_DOWN:
                if (*selected < 2) *selected += 1;
                break;
            case KEY_UP:
                if (*selected > 0) *selected -= 1;
                break;
            case KEY_ESC: quit();
                break;
            case KEY_ENTER:
                switch (*selected) {
                    free(selected);
                    case 0: createWorld();
                        break;
                    case 1: loadWorld();
                        break;
                    case 2: 
                        quit();
                        break;} 
                break;
            default: break;
        }
    } while(running == TRUE);
}
int main(void){
    hideCursor();
    titleScreen();
    return 0;
}
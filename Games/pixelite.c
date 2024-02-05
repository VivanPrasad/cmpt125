#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //
#include <windows.h> // For terminal manipulation
#include <stdbool.h> // For boolean values

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13

// WORLD TILESET
#define GRASS_TILE 34 // ,
#define STONE_TILE 45 // -
#define WATER_TILE 126 // ~
#define TREE_TILE 190 // ×
#define BRICK_TILE 35 // #
#define PLAYER_TILE 64 // @ 

#define WHITE "\e[0;37m"
#define GREY "\e[38;5;248m"
#define GREEN "\e[0;32m"
#define BLUE "\e[0;34m"
#define RED "\e[0;33m"

char world[32][16]; 
short WIDTH = 16; short HEIGHT = 8;
short type=0, location=0, size=0;

typedef struct Player{
    int x;
    int y;
} Player;

int runGame(void);
int generateWorld(int type, int size){
    WIDTH = 16 + (8*size);
    HEIGHT = 8 + (4*size);
    switch (type){
        case 0: // Forest
            for (int r=0;r<HEIGHT;r++){
                for (int c=0;c<WIDTH;c++){
                    world[c][r] = GRASS_TILE;}}
            break;
        case 1: // Shore
            for (int r=0;r<HEIGHT;r++){
                for (int c=0;c<WIDTH;c++){
                    world[c][r] = WATER_TILE;}}
            break;
        case 2: // Mountain
            for (int r=0;r<HEIGHT;r++){
                for (int c=0;c<WIDTH;c++){
                    world[c][r] = STONE_TILE;}}
            break;
        default:
            break;
    }
    runGame();
    return 0;
}
Player * spawnPlayer(int ix, int iy){
    Player *newPlayer;
    newPlayer = (Player*)malloc(sizeof(Player));

    newPlayer->x = ix;
    newPlayer->y = iy;
    return newPlayer;
}

void setCursor(int x, int y) // Move the terminal cursor to a position
{
    COORD c = {x, y};
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hideCursor() // Hide the terminal cursor
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

char getTile(int x, int y) { // Returns the tile character
    return world[x][y];
}
void setText(int x, int y, char text) {
    setCursor(x,y);
    printf("%c",text);
}

void setTile(int x, int y, char tile) {
    world[x][y] = tile;
    setCursor(x,y);
    switch(world[x][y]){
        case GRASS_TILE:
            printf(GREEN"%c",GRASS_TILE);
            break;
        case WATER_TILE:
            printf(BLUE"%c",WATER_TILE);
            break;
        case STONE_TILE:
            printf(GREY"%c",STONE_TILE);
            break;
        default:
            printf(WHITE"%c",world[x][y]);
            break;
    }
}
void movePlayer(int x, int y) {
    setCursor(x,y);
    printf(WHITE"%c",PLAYER_TILE);}
int refreshWorld(Player *player){
    for (int r=0;r<HEIGHT;r++){
        for (int c=0;c<WIDTH;c++){
            setTile(c,r,world[c][r]);
        }
        printf("\n");}
    return 0;}

int runGame(void) {
    bool running = TRUE;
    char key;
    Player *player = spawnPlayer(4,4);
    system("cls");
    refreshWorld(player);
    movePlayer(player->x,player->y);
    do{
        key = getch();
        hideCursor();
        setTile(player->x,player->y,world[player->x][player->y]);
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
            case KEY_ESC:
                system("cls");
                exit(0);
                running = FALSE;
                break;
            default:
                continue;
        }
        movePlayer(player->x,player->y);
    } while (running==TRUE);
}

/* Save Data
<type> <location> <size>
<world data>
*/
int loadSave(void) {
    FILE *save;
    char saveName[20];

    short type, location, size;
    system("cls");
    while (save == NULL){
        printf("Enter Save File Name: ");
        scanf("%s", saveName);
        save = fopen(saveName,"r");}
    return 0;
}

int saveWorld(void) {
    FILE *export;
    export = fopen("save.txt","w");
    fprintf(export, "%d %d %d\n",type,location,size);
    fclose(export);
    return 0;
}

int createWorld(void) {
    const char worldTypes[3][11] = {"Forest    ","Shore     ","Mountain  "};
    const char worldSizes[3][10] = {"Tiny  ","Normal","Grand "};
    const char settings[3][10] = {"Type:","Size:","Create"};
    short selected=0;
    bool running = TRUE;
    char key;
    system("cls");
    printf("Create New World\n\n>Type: %s\n Size: %s\n Create World",worldTypes[type],worldSizes[size]);
    hideCursor();
    do{
        for (int r=0;r<=2;r++){
            setText(0,r+2,(r==selected) ? 62 : 32); //empty space if not selected
        }
        setText(0,selected+2,62);
        key = getch();
        switch (key){
            case KEY_DOWN:
                if (selected < 2) selected += 1;
                break;
            case KEY_UP:
                if (selected > 0) selected -= 1;
                break;
            case KEY_ESC:
                running = FALSE;
                system("cls");
                exit(0);
                break;
            case KEY_ENTER:
                setCursor(1,selected+2);
                switch (selected) {
                    case 0:
                        type = (type + 1) % 3;
                        printf("%s %s", settings[selected], worldTypes[type]);
                        break;
                    case 1:
                        size = (size + 1) % 3;
                        printf("%s %s", settings[selected], worldSizes[size]);
                        break;
                    case 2:
                        running = FALSE;
                        system("cls");
                        generateWorld(type,size);
                        break;
                    default: break;
                }
                break;
            default:
                break;
        }
    } while(running == TRUE);
}
int titleScreen(void) {
    system("cls");
    hideCursor();
    printf("Pixelite\n\n New\n Load\n Exit");
    bool running = true;
    int selected = 0;
    char key;
    do{
        for (int r=0;r<=2;r++){
            setText(0,r+2,32);
        }
        setText(0,selected+2,62);
        key = getch();
        switch (key){
            case KEY_DOWN:
                if (selected < 2) selected += 1;
                break;
            case KEY_UP:
                if (selected > 0) selected -= 1;
                break;
            case KEY_ESC:
                running = FALSE;
                system("cls");
                exit(0);
                break;
            case KEY_ENTER:
                switch (selected) {
                    case 0:
                        running = FALSE;
                        system("cls");
                        createWorld();
                        break;
                    case 1:
                        loadSave();
                        break;
                    case 2:
                        running = FALSE;
                        system("cls");
                        exit(0);
                        break;
                    default: break;
                } break;
            default: break;
        }
    } while(running == TRUE);
}
int main(void){
    titleScreen();
    return 0;
}
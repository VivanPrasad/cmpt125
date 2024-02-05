#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13

#define WIDTH 24
#define HEIGHT 8

// TILESET
#define DIRT_TILE 46 // "."
#define WATER_TILE
#define PLAYER_TILE 64



char world[WIDTH][HEIGHT]; 
enum worldSize {
    MINI=0,
    NORMAL=1,
    GRAND=2,
};
typedef struct Player{
    int x;
    int y;
    int health;
} Player;

int setupWorld(void){
    for (int r=0;r<HEIGHT;r++){
        for (int c=0;c<WIDTH;c++){
            world[r][c] = DIRT_TILE;}}
    return 0;
}
Player * setupPlayer(void){
    Player *newPlayer;
    newPlayer = (Player*)malloc(sizeof(Player));

    newPlayer->health = 3;
    newPlayer->x=(WIDTH/2);
    newPlayer->y=(HEIGHT/2);
    return newPlayer;
}

void setCursor(int x, int y)
{
    COORD c = { x, y };  
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

void hideCursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

char getTile(int x, int y) {
    return world[x][y];
}
void setText(int x, int y, char text) {
    setCursor(x,y);
    printf("%c",text);
}

void setTile(int x, int y, char tile) {
    world[x][y] = tile;
    setText(x,y,tile);
}
int display(Player *player){
    for (int r=0;r<HEIGHT;r++){
        for (int c=0;c<WIDTH;c++){
            if (r==player->y && c==player->x) printf("%c",PLAYER_TILE);
            else printf("%c",world[r][c]);}
        printf("\n");}
    return 0;
}

int runGame(void) {
    char key;
    setupWorld();
    Player *player = setupPlayer();
    system("cls");
    display(player);
    do{
        key = getch();
        hideCursor();
        setTile(player->x,player->y,DIRT_TILE);
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
            default:
                continue;
        }
        setTile(player->x,player->y,PLAYER_TILE);
    } while (1==1);
}

int createWorld(void) {
    bool running = true;
    const char worldTypes[4][9] = {"Forest","Shore","Desert","Mountain"};
    const char worldDifficulties[3][9] = {"Kind","Moderate","Harsh"};
    const char worldSizes[3][9] = {"Tiny","Normal","Grand"};

    int selected = 0;
    int type = 0;
    int difficulty = 0;
    int size = 0;
    char key;
    do{
        system("cls");
        hideCursor();
        printf("Create New World\n\n Type: %s\n Location: %s\n Size: %s\n Create World",worldTypes[type],worldDifficulties[difficulty],worldSizes[size]);
        key = getch();
        hideCursor();
        for (int r=0;r<=3;r++){
            setText(0,r+2,32);
        }
        setText(0,selected+2,62);
        switch (key){
            case KEY_DOWN:
                if (selected < 3) selected += 1;
                break;
            case KEY_UP:
                if (selected > 0) selected -= 1;
                break;
            case KEY_ESC:
                running = FALSE;
                exit(0);
                break;
            case KEY_ENTER:
                switch (selected) {
                    case 0:
                        type = (type + 1) % 4;
                        break;
                    case 1:
                        difficulty = (difficulty + 1) % 3;
                        break;
                    case 2:
                        size = (size + 1) % 3;
                        break;
                    case 3:
                        running = FALSE;
                        runGame();
                        break;
                    default:
                        break;
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
    printf("Pixelite\n\n>New\n Load\n Exit");
    bool running = true;
    int selected = 0;
    char key;
    do{
        key = getch();
        hideCursor();
        for (int r=0;r<=2;r++){
            setText(0,r+2,32);
        }
        switch (key){
            case KEY_DOWN:
                if (selected < 2) selected += 1;
                break;
            case KEY_UP:
                if (selected > 0) selected -= 1;
                break;
            case KEY_ESC:
                running = FALSE;
                exit(0);
                break;
            case KEY_ENTER:
                switch (selected) {
                    case 0:
                    case 1:
                        running = FALSE;
                        createWorld();
                        break;
                    case 2:
                        running = FALSE;
                        exit(0);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        setText(0,selected+2,62);
    } while(running == TRUE);
}
int main(void){
    titleScreen();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27

#define EMPTY_TILE 46 // "."
#define PLAYER_TILE 64
#define WIDTH 80
#define HEIGHT 24


char world[WIDTH][HEIGHT]; 
typedef struct Player{
    int x;
    int y;
    int health;
} Player;

int setupWorld(void){
    for (int r=0;r<HEIGHT;r++){
        for (int c=0;c<WIDTH;c++){
            world[r][c] = EMPTY_TILE;}}
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

void gotoxy(int x, int y)
{
    COORD c = { x, y };  
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

char getPosition(int x, int y);
int display(Player *player){
    gotoxy(0,0);
    for (int r=0;r<HEIGHT;r++){
        for (int c=0;c<WIDTH;c++){
            if (r==player->y && c==player->x) printf("%c",PLAYER_TILE);
            else printf("%c",world[r][c]);}
        printf("\n");}
    return 0;
}
int main(void){
    hidecursor();
    system("cls");
    setupWorld();
    Player *player = setupPlayer();
    char key;
    do{
        display(player);
        key = getch();
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
    } while(key != 27);
    return 0;
}
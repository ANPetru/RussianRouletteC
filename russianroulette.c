#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
  #include <unistd.h>
#ifndef NULL
#define NULL 0
#endif

typedef struct player player_t;

struct player
{
    char *name;
    bool isDead;
};

void initPlayers();
void printPlayers();
void playTurn();
void getNextPlayer();
void initGun();
void killPlayer();
void checkWin();
void printShooting (int miliseconds);

int numPlayers;
int currentPlayer = 0;
player_t *players;
bool gameOver = false;
bool bullets[6];
int bullet;


int main(int argc, char const *argv[])
{
    system("clear");
    bool exit = false;
    while (!exit){
        char line [20];
        printf("Enter number of players(2-8):\n");
        fgets(line,20,stdin);
        numPlayers = atoi(line);
        if (numPlayers >=2 && numPlayers <=8){
            exit = true;
        }
        system("clear");
    }
    players = malloc(sizeof(player_t) * numPlayers);
    initPlayers();
    initGun();
    while (!gameOver){
        playTurn();
    }
    return 0;
}

void playTurn(){
    printf("\033[1;36m%s\033[0m's turn.\nEnter '\033[0;36m1\033[0m' to play turn | '\033[0;36m2\033[0m' to see stats:\n", players[currentPlayer].name);
    char line [20];
    fgets(line,20,stdin);
    if (atoi(line) == 1){
        srand(time(NULL));
        bool exit = false;
        int randBullet;
        while (!exit) {
            randBullet = rand() % 6;
            exit = bullets[randBullet];
        }
        system("clear");
        printShooting(400);
        if (randBullet == bullet){
            printf("\033[1;31m");
            printf("BOOM!\n");
            printf("\033[0m");
            killPlayer();
        } else {
            printf("\033[1;32m");
            printf("*click*\n");
            printf("\033[0m");
            bullets[randBullet] = false;
        }
        getNextPlayer();
    } else if (atoi(line) == 2){
        system("clear");
        printPlayers();
    } else {
        system("clear");
    }
}

void killPlayer(){
    printf("\033[1;31m");
    printf("%s got shot!\n", players[currentPlayer].name);
    printf("\033[0m");
    players[currentPlayer].isDead = true;
    checkWin();
    initGun();
}

void initGun(){
    for (int i = 0; i< sizeof(bullets)/sizeof(bool);i++){
        bullets[i] = true;
    }
    srand(time(NULL));
    bullet = (rand() % (0 - 5 + 1)) + 0; 
}

void getNextPlayer(){
    int tempInd = currentPlayer +1;
    bool exit = false;
    while (!exit){
        exit = true;
        if(tempInd>= numPlayers){
            tempInd = 0;
            exit = false;
        } else if(players[tempInd].isDead) {
            tempInd++;
            exit = false;
        } else {
            exit = true;
        }
    }
    currentPlayer = tempInd;
}

void initPlayers(){
    for(int i = 0; i < numPlayers; i++){
        printf("Enter name for Player %d:\n", i+1);
        char name [10];
        fgets(name, 10,stdin);
        int len=strlen(name); 
        if(name[len-1]=='\n')
            name[len-1]='\0';
        players[i].name = malloc(sizeof(char) * 10);
        strcpy(players[i].name, name);
        players[i].isDead = false;
        system("clear");
    }
}

void printPlayers(){
    for (int i = 0; i< numPlayers; i++) {
        printf("%s is ", players[i].name);
        if (players[i].isDead){
            printf("\033[1;31m");
            printf("dead\n");
            printf("\033[0m");
        } else {
            printf("\033[1;32m");
            printf("alive\n");
            printf("\033[0m");
        }
    }
}

void checkWin() {
    int playersAlive = 0;
    for (int i = 0; i < numPlayers; i++) {
        if (!players[i].isDead){
            playersAlive++;
        }
    }
    if (playersAlive == 1) {
        getNextPlayer();
        printf("\n---------------------------------------\n");
        printPlayers();
        printf("---------------------------------------\n\n\n");
        printf("\033[1;32m");
        printf("\t%s WON THE GAME!\n\n\n\n", players[currentPlayer]);
        printf("\033[0m");

        gameOver = true;
    }
}

void printShooting (int miliseconds) {
    printf("\033[1;36m");

    printf("Shooting %s", players[currentPlayer]);
    fflush(stdout);
    usleep(miliseconds* 1000);
    printf(".");
    fflush(stdout);
    usleep(miliseconds * 1000);
    printf(".");
    fflush(stdout);
    usleep(miliseconds* 1000);
    printf(".");
    fflush(stdout);
    printf("\033[0m");
}
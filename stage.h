#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "monster.h"

#ifndef STAGE
#define STAGE

// struct termios orig_termios;
void enableRawMode();
void disableRawMode();
char getCharTypedByUser();

struct Player
{
    char *name;
    double hpMax;
    unsigned int shield;
    double damage;
    unsigned int spectralShoot; // TRUE OR FALSE
    unsigned int percingShoot;  // TRUE OR FALSE
    unsigned int flight;        // TRUE OR FALSE
    Object *object[100];
    unsigned int currX;
    unsigned int currY;
    int currStageX;
    int currStageY;
};
typedef struct Player Player;

void initializePlayer(Player *player);
void freePlayer(Player *player);

struct Stage
{
    int **stageArea; // LA FORME DE L'ETAGE
    int **stageAreaReal[9][9];
    unsigned int rows; // =9
    unsigned int cols; // =9
    unsigned int spawnX;
    unsigned int spawnY;
};
typedef struct Stage Stage;

void initializeStage(Stage *stage);
void printAllRoomOfStage(Stage *stage);
void freeStage(Stage *stage);

void initializeGame(Stage *stage, Player *player);
void printCurrentRoomOfPlayer(Stage *stage, Player *player);
void play(Stage *stage, Player *player);

#endif

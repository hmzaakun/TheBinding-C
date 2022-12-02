#include <stdio.h>
#include <stdlib.h>
#include "object.h"

#ifndef STAGE
#define STAGE

struct Stage
{
    int **stageArea; // LA FORME DE L'ETAGE
    int **stageAreaReal[9][9];
    unsigned int rows; // =9
    unsigned int cols; // =9
    int playerCurrentRoomInStage[9][9];
};
typedef struct Stage Stage;

void initializeStage(Stage *stage);
void printAllRoomOfStage(Stage *stage);
void freeStage(Stage *stage);
void printStage(Stage *stage);

struct Player
{
    char *name;
    double hpMax;
    unsigned int shield;
    double damage;
    unsigned int spectralShoot; // TRUE OR FALSE
    unsigned int percingShoot;  // TRUE OR FALSE
    unsigned int flight;        // TRUE OR FALSE
    Object object[100];
    unsigned int currentXLocation;
    unsigned int currentYLocation;
};
typedef struct Player Player;

#endif

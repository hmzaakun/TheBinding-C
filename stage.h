#include <stdio.h>
#include <stdlib.h>

#ifndef STAGE
#define STAGE

struct Stage
{
    int **arrayOfRoom[14]; // LES ROOMS DE L'ETAGE
    int **stage;           // LA FORME DE L'ETAGE
};
typedef struct Stage Stage;

void initializeStage(Stage *stage, FILE *f);
void printStage(Stage *stage);
void freeStage(Stage *stage);

#endif

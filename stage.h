#include <stdio.h>
#include <stdlib.h>

#ifndef STAGE
#define STAGE

struct Stage
{
    int **stageArea; // LA FORME DE L'ETAGE
    int **stageAreaReal[9][9];
    unsigned int rows;
    unsigned int cols;
};
typedef struct Stage Stage;

void initializeStage(Stage *stage);
void printStage(Stage *stage);
void freeStage(Stage *stage);

#endif

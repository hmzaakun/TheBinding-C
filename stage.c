#include "stage.h"
#include "room.h"
#include <time.h>
#include<stdlib.h>

void delay(unsigned milliseconds)
{
    clock_t pause;
    clock_t start;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    start = clock();
    while( (clock() - start) < pause );
}

void initializeStage(Stage *stage, FILE *f)
{
    // INITIALISATION DES MAPS QU'IL Y AURA
    stage->arrayOfRoom[0] = createSpawnRoom(9, 15);
    printf("GENERATING THE STAGE, PLZ WAIT...\n");
    for (int i = 1; i <= 10; i++)
    {
        stage->arrayOfRoom[i] = importRandomRoomFromFile(f);
        delay(1000);
    }
    // stage->arrayOfRoom[11] BOSS ROOM
    // stage->arrayOfRoom[12] BOSS ITEM ROOM
    // stage->arrayOfRoom[13] ITEM ROOM

    // GENERATION DE LA FORME DE L'ETAGE
    stage->stage = createEmptyRoom(5, 5);
}

void freeStage(Stage *stage)
{
    for (int i = 0; i < 14; i++)
    {
        freeArray2D(stage->arrayOfRoom[i], 9);
    }
    free(stage);
}


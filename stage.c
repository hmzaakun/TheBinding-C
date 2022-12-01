#include "stage.h"
#include "room.h"
#include <time.h>

void initializeStage(Stage *stage)
{
    stage->rows = 9;
    stage->cols = 9;
    srand(time(NULL));

    stage->stageArea = createEmptyRoom(stage->rows, stage->cols);
    // Les croix sont les emplacements ou il n'y a pas de room
    for (int i = 0; i < stage->rows; i += 1)
    {
        for (int j = 0; j < stage->cols; j += 1)
        {
            stage->stageArea[i][j] = 'X';
        }
    }

    /* Defining the place of the spawn randomly*/
    unsigned int spawnCol;
    unsigned int spawnRow;
    int flag = 0;
    while (flag != 1)
    {
        spawnRow = rand() % 9;
        if (spawnRow > 2 && spawnRow < 7)
            flag = 1;
    }
    delay(1000);
    flag = 0;
    while (flag != 1)
    {
        spawnCol = rand() % 9;
        if (spawnCol > 2 && spawnCol < 7)
            flag = 1;
    }
    // printf("SpawnRows : %d SpawnCols : %d\n", spawnRow, spawnCol);
    stage->stageArea[spawnRow][spawnCol] = 'S';

    int finished = 0;
    unsigned int count = 1;
    while (finished != 1)
    {
        /* Choix de la case ou se placer pour rajouter une room à côté */
        unsigned int newRow;
        unsigned int newCol;
        unsigned int waitChoosingCase = 0;
        while (waitChoosingCase != 1)
        {
            for (int i = 1; i < stage->rows - 1; i += 1)
            {
                for (int j = 1; j < stage->cols - 1; j += 1)
                {
                    if (stage->stageArea[i][j] != 'X')
                    {
                        unsigned int chanceToChooseCase = rand() % 4;
                        if (chanceToChooseCase == 0)
                        {
                            newRow = i;
                            newCol = j;
                            waitChoosingCase = 1;
                        }
                    }
                }
            }
        }

        /* Randomisation de la case d'après (gauche, droite, haut ou bas) */
        unsigned int test = rand() % 2;
        // delay(50);
        if (test == 0)
        {
            unsigned int roomRowNext = rand() % 3; // Cas 0 Row + 0 / Cas 1 Row + 1 / Cas 2 Row - 1
            if (roomRowNext == 0)
            {
                unsigned int caseZeroTest = rand() % 2; // Cas 0 Col + 1 - Cas 1 Col - 1
                if (caseZeroTest == 0)
                {
                    if ((newCol + 1) <= stage->cols)
                    {
                        if (stage->stageArea[newRow][newCol + 1] == 'X')
                        {
                            stage->stageArea[newRow][newCol + 1] = 'R';
                            // printf("newRow : %d newCol: %d\n", newRow, newCol);
                            // printf("Count : %d\n", count);
                            // printf("case 1\n");
                            // printArray2D(stage->stageArea, stage->rows, stage->cols);
                            count++;
                        }
                    }
                }
                else if (caseZeroTest == 1)
                {
                    if ((newCol - 1) >= 0)
                    {
                        if (stage->stageArea[newRow][newCol - 1] == 'X')
                        {
                            stage->stageArea[newRow][newCol - 1] = 'R';
                            // printf("newRow : %d newCol: %d\n", newRow, newCol);
                            // printf("Count : %d\n", count);
                            // printf("case 2\n");
                            // printArray2D(stage->stageArea, stage->rows, stage->cols);
                            count++;
                        }
                    }
                }
            }
            else if (roomRowNext == 1)
            {
                if (newRow + 1 < stage->rows)
                {
                    if (stage->stageArea[newRow + 1][newCol] == 'X')
                    {
                        stage->stageArea[newRow + 1][newCol] = 'R';
                        // printf("newRow : %d newCol: %d\n", newRow, newCol);
                        // printf("Count : %d\n", count);
                        // printf("case 3\n");
                        // printArray2D(stage->stageArea, stage->rows, stage->cols);
                        count++;
                    }
                }
            }
            else if (roomRowNext == 2)
            {
                if (newRow - 1 >= 0)
                {
                    if (stage->stageArea[newRow - 1][newCol] == 'X')
                    {
                        stage->stageArea[newRow - 1][newCol] = 'R';
                        // printf("newRow : %d newCol: %d\n", newRow, newCol);
                        // printf("Count : %d\n", count);
                        // printf("case 4\n");
                        // printArray2D(stage->stageArea, stage->rows, stage->cols);
                        count++;
                    }
                }
            }
        }
        else if (test == 1)
        {
            unsigned int roomColNext = rand() % 3;
            if (roomColNext == 0)
            {
                unsigned int caseZeroTest = rand() % 2; // Cas 0 Col + 1 - Cas 1 Col - 1
                if (caseZeroTest == 0)
                {
                    if ((newRow + 1) <= stage->rows)
                    {
                        if (stage->stageArea[newRow + 1][newCol] == 'X')
                        {
                            stage->stageArea[newRow + 1][newCol] = 'R';
                            // printf("newRow : %d newCol: %d\n", newRow, newCol);
                            // printf("Count : %d\n", count);
                            // printf("case 5\n");
                            // printArray2D(stage->stageArea, stage->rows, stage->cols);
                            count++;
                        }
                    }
                }
                else if (caseZeroTest == 1)
                {
                    if ((newRow - 1) >= 0)
                    {
                        if (stage->stageArea[newRow - 1][newCol] == 'X')
                        {
                            stage->stageArea[newRow - 1][newCol] = 'R';
                            // printf("newRow : %d newCol: %d\n", newRow, newCol);
                            // printf("Count : %d\n", count);
                            // printf("case 6\n");
                            // printArray2D(stage->stageArea, stage->rows, stage->cols);
                            count++;
                        }
                    }
                }
            }
            else if (roomColNext == 1)
            {
                if (newCol + 1 < stage->cols)
                {
                    if (stage->stageArea[newRow][newCol + 1] == 'X')
                    {
                        stage->stageArea[newRow][newCol + 1] = 'R';
                        // printf("newRow : %d newCol: %d\n", newRow, newCol);
                        // printf("Count : %d\n", count);
                        // printf("case 7\n");
                        // printArray2D(stage->stageArea, stage->rows, stage->cols);
                        count++;
                    }
                }
            }
            else if (roomColNext == 2)
            {
                if (newCol - 1 >= 0)
                {
                    if (stage->stageArea[newRow][newCol - 1] == 'X')
                    {
                        stage->stageArea[newRow][newCol - 1] = 'R';
                        // printf("newRow : %d newCol: %d\n", newRow, newCol);
                        // printf("Count : %d\n", count);
                        // printf("case 8\n");
                        // printArray2D(stage->stageArea, stage->rows, stage->cols);
                        count++;
                    }
                }
            }
        }

        if (count == 14)
            finished = 1;
    }

    for (int i = 0; i < stage->rows; i += 1)
    {
        for (int j = 0; j < stage->cols; j += 1)
        {
            if (stage->stageArea[i][j] == 'R')
            {
                stage->stageAreaReal[i][j] = importRandomRoomFromFile();
            }
            else if (stage->stageArea[i][j] == 'S')
            {
                stage->stageAreaReal[i][j] = createSpawnRoom(9, 15);
            }
        }
    }
}

void freeStage(Stage *stage)
{
    freeArray2D(stage->stageArea, 9);
    for (int i = 0; i < stage->rows; i += 1)
    {
        for (int j = 0; j < stage->cols; j += 1)
        {
            if (stage->stageArea[i][j] != 'X')
            {
                freeArray2D(stage->stageAreaReal[i][j], 9);
            }
        }
    }
    free(stage);
}
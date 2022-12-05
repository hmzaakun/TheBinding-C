#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <ctype.h>
#include "stage.h"
#include "room.h"

struct termios orig_termios;

void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

char getCharTypedByUser()
{
    char c;
    enableRawMode();
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
    {
        // printf("%d ('%c')\r\n", c, c);
        return c;
    }
}

void ifDoor(Stage *stage, Player *player)
{
    if (player->currY == 7)
    {
        if (player->currX == 0) // Porte du haut
        {
            player->currStageX -= 1;
            player->currX = 7;
        }
        else // Porte du bas
        {
            player->currStageX += 1;
            player->currX = 1;
        }
    }
    else if (player->currX == 4)
    {
        if (player->currY == 0) // Porte de gauche
        {
            player->currStageY -= 1;
            player->currY = 13;
        }
        else // Porte de droite
        {
            player->currStageY += 1;
            player->currY = 1;
        }
    }
    stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = 'P';
    // printCurrentRoomOfPlayer(stage, player);
}

void play(Stage *stage, Player *player)
{
    initializeGame(stage, player);
    // printAllRoomOfStage(stage);

    int inGame = 1;
    while (inGame != 0)
    {
        char c = getCharTypedByUser();
        disableRawMode();
        system("clear");
        // printf("%c\r\n", c);
        if (c == 'z')
        {
            if (stage->stageAreaReal[player->currStageX][player->currStageY][player->currX - 1][player->currY] == ' ')
            {
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = ' ';
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX - 1][player->currY] = 'P';
                player->currX = player->currX - 1;
            }
            else if (stage->stageAreaReal[player->currStageX][player->currStageY][player->currX - 1][player->currY] == 'D')
            {
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = ' ';
                player->currX = player->currX - 1;
                ifDoor(stage, player);
            }
        }
        else if (c == 's')
        {
            if (stage->stageAreaReal[player->currStageX][player->currStageY][player->currX + 1][player->currY] == ' ')
            {
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = ' ';
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX + 1][player->currY] = 'P';
                player->currX = player->currX + 1;
            }
            else if (stage->stageAreaReal[player->currStageX][player->currStageY][player->currX + 1][player->currY] == 'D')
            {
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = ' ';
                player->currX = player->currX + 1;
                ifDoor(stage, player);
            }
        }
        else if (c == 'q')
        {
            if (stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY - 1] == ' ')
            {
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = ' ';
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY - 1] = 'P';
                player->currY = player->currY - 1;
            }
            else if (stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY - 1] == 'D')
            {
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = ' ';
                player->currY = player->currY - 1;
                ifDoor(stage, player);
            }
        }
        else if (c == 'd')
        {
            if (stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY + 1] == ' ')
            {
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = ' ';
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY + 1] = 'P';
                player->currY = player->currY + 1;
            }
            else if (stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY + 1] == 'D')
            {
                stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = ' ';
                player->currY = player->currY + 1;
                ifDoor(stage, player);
            }
        }
        else if (c == 'b')
        {
            inGame = 0;
        }
        printArray2D(stage->stageArea, stage->rows, stage->cols);
        printf("\n");
        printCurrentRoomOfPlayer(stage, player);
    }
}

void initializeGame(Stage *stage, Player *player)
{
    initializeStage(stage);
    initializePlayer(player);
    printArray2D(stage->stageArea, stage->rows, stage->cols);
    printf("\n");

    player->currStageX = stage->spawnX;
    player->currStageY = stage->spawnY;
    stage->stageAreaReal[player->currStageX][player->currStageY][player->currX][player->currY] = 'P';
    printCurrentRoomOfPlayer(stage, player);
}

void printCurrentRoomOfPlayer(Stage *stage, Player *player)
{
    printArray2D(stage->stageAreaReal[player->currStageX][player->currStageY], 9, 15);
}

void initializeStage(Stage *stage)
{
    printf("Generating the stage, wait a few second...\n");
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
    my_delay(800);
    flag = 0;
    while (flag != 1)
    {
        spawnCol = rand() % 9;
        if (spawnCol > 2 && spawnCol < 7)
            flag = 1;
    }
    // printf("SpawnRows : %d SpawnCols : %d\n", spawnRow, spawnCol);
    stage->stageArea[spawnRow][spawnCol] = 'S';
    stage->spawnX = spawnRow;
    stage->spawnY = spawnCol;

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
            for (int i = 0; i < stage->rows; i += 1)
            {
                for (int j = 0; j < stage->cols; j += 1)
                {
                    if (stage->stageArea[i][j] != 'X')
                    {
                        unsigned int chanceToChooseCase = rand() % 4;
                        // my_delay(50);
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
        // my_delay(50);
        if (test == 0)
        {
            unsigned int roomRowNext = rand() % 3; // Cas 0 Row + 0 / Cas 1 Row + 1 / Cas 2 Row - 1
            // my_delay(50);
            if (roomRowNext == 0)
            {
                unsigned int caseZeroTest = rand() % 2; // Cas 0 Col + 1 - Cas 1 Col - 1
                // my_delay(50);
                if (caseZeroTest == 0)
                {
                    if ((newCol + 1) < stage->cols)
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
            // my_delay(50);
            if (roomColNext == 0)
            {
                unsigned int caseZeroTest = rand() % 2; // Cas 0 Row + 1 - Cas 1 Row - 1
                // my_delay(50);
                if (caseZeroTest == 0)
                {
                    if ((newRow + 1) < stage->rows)
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

    /* Remplacement des 'R' par des vrais rooms */
    for (int i = 0; i < stage->rows; i += 1)
    {
        for (int j = 0; j < stage->cols; j += 1)
        {
            if (stage->stageArea[i][j] == 'R')
            {
                stage->stageAreaReal[i][j] = importRandomRoomFromFile();
                my_delay(800);
            }
            else if (stage->stageArea[i][j] == 'S')
            {
                stage->stageAreaReal[i][j] = createSpawnRoom(9, 15);
            }
            else
                stage->stageAreaReal[i][j] = createEmptyRoom(9, 15);
        }
    }

    /* Changement des portes au bon endroit */
    for (int i = 0; i < stage->rows; i += 1)
    {
        for (int j = 0; j < stage->cols; j += 1)
        {
            if (stage->stageArea[i][j] != 'X')
            {
                if (i + 1 < 9)
                {
                    if (stage->stageArea[i + 1][j] != 'X')
                    {
                        // printf("case1\n");
                        stage->stageAreaReal[i][j][8][7] = 'D'; // Porte du bas
                    }
                }
                if (i - 1 >= 0)
                {
                    if (stage->stageArea[i - 1][j] != 'X')
                    {
                        // printf("case2\n");
                        stage->stageAreaReal[i][j][0][7] = 'D'; // Porte du haut
                    }
                }
                if (j + 1 < 15)
                {
                    if (stage->stageArea[i][j + 1] != 'X')
                    {
                        // printf("case3\n");
                        stage->stageAreaReal[i][j][4][14] = 'D'; // Porte de droite
                    }
                }
                if (j - 1 >= 0)
                {
                    if (stage->stageArea[i][j - 1] != 'X')
                    {
                        // printf("case4\n");
                        stage->stageAreaReal[i][j][4][0] = 'D'; // Porte de gauche
                    }
                }
            }
        }
    }
}

void initializePlayer(Player *player)
{
    player->name = duplicateString("Theo");
    player->hpMax = 10;
    player->shield = 1;
    player->damage = 2;
    player->spectralShoot = 0;
    player->percingShoot = 0;
    player->flight = 0;
    // Milieu du spawn
    player->currX = 4;
    player->currY = 7;
}

void printAllRoomOfStage(Stage *stage)
{
    for (int i = 0; i < stage->rows; i += 1)
    {
        for (int j = 0; j < stage->cols; j += 1)
        {
            if (stage->stageArea[i][j] != 'X')
            {
                printArray2D(stage->stageAreaReal[i][j], 9, 15);
                printf("\n");
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
            freeArray2D(stage->stageAreaReal[i][j], 9);
        }
    }
    // free(stage);
}

void freePlayer(Player *player)
{
    free(player->name);
    // free(player);
}
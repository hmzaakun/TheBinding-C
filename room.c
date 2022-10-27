#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int **importRandomRoomFromFile(FILE *f)
{
    unsigned int nbrOfRoom = getNumberOfMapInFile(f);
    srand(time(NULL));
    unsigned int randomRoomId = rand() % nbrOfRoom + 1;
    return importRoomFromFile(f, randomRoomId);
}

void deleteRoom(FILE *f, unsigned int index)
{
    int numberOfMap = getNumberOfMapInFile(f);
    if (numberOfMap == 0 || index > numberOfMap)
    {
        printf("L'index de la map a supprimer n'existe pas dans le fichier");
        return;
    }

    if (f != NULL)
    {
        fseek(f, 0, SEEK_SET); // Pointeur au début du fichier
        char str[100];
        fgets(str, 100, f); // Récupère la première ligne du fichier
        printf("%s", str);

        unsigned int rows = 0;
        unsigned int columns = 0;
        printf("Room recherche : %d\n", index);
        getRoomInformations(f, str, &rows, &columns, index);
        // INFORMATIONS ON SELECTED ROOM
        // printf("%s", str);
        // printf("rows : %d\n", rows);
        // printf("columns : %d\n", columns);

        for (int i = 0; i < 100; i++)
        {
            str[i] = 127;
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        return;
    }
}

unsigned int getRowsInSelectedRoom(FILE *f, unsigned int index)
{
    if (f != NULL)
    {
        char str[100];
        unsigned int rows = 0;
        unsigned int columns = 0;
        getRoomInformations(f, str, &rows, &columns, index);
        return rows;
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        return 0;
    }
}
unsigned int getColumnsInSelectedRoom(FILE *f, unsigned int index)
{
    if (f != NULL)
    {
        char str[100];
        unsigned int rows = 0;
        unsigned int columns = 0;
        getRoomInformations(f, str, &rows, &columns, index);
        return columns;
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        return 0;
    }
}

void getRoomInformations(FILE *f, char str[], unsigned int *rows, unsigned int *columns, unsigned int index)
{
    if (f != NULL)
    {
        unsigned int bool = 0;
        fseek(f, 0, SEEK_SET);
        // printf("RECHERCHE NBR DE MAP TOTAL...\n");
        char str[100];
        fgets(str, 100, f);
        fgets(str, 100, f);
        while (bool != 1)
        {
            unsigned int idRoom = 0;
            *rows = 0;
            *columns = 0;
            if (str[0] == '[')
            {
                // GET NBR ROWS JUSQUA 99 MAX
                if (str[2] != '|')
                {
                    *rows += str[2] - 48;
                    *rows += (str[1] - 48) * 10;
                }
                else
                {
                    *rows += str[1] - 48;
                }
                // GET INDICE & COLUMN JUSQUA 99 MAX
                for (int i = 0; i < 100; i++)
                {
                    // GET COLUMNS
                    if (str[i] == '|')
                    {
                        if (str[i + 2] != ']')
                        {
                            *columns += str[i + 2] - 48;
                            *columns += (str[i + 1] - 48) * 10;
                        }
                        else
                        {
                            *columns += (str[i + 1] - 48);
                        }
                    }
                    // GET INDICE (ID DE LA PIECE) JUSQUA 99 MAX
                    if (str[i] == ']')
                    {
                        if (str[i + 2] > '9' && str[i + 2] < '0')
                        {
                            idRoom += (str[i + 1] - 48) * 10;
                            idRoom += str[i + 2] - 48;
                            // printf("%d", str[2]);
                        }
                        else
                        {
                            idRoom += str[i + 1] - 48;
                            // printf("%d:", indice);
                        }
                        if (idRoom == index)
                            bool = 1;
                    }
                }
            }
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        return;
    }
}

int **importRoomFromFile(FILE *f, unsigned int index)
{
    int numberOfMap = getNumberOfMapInFile(f);
    if (numberOfMap == 0)
    {
        printf("Impossible d'importer une ROOM\n");
        return 0;
    }
    if (index > numberOfMap)
    {
        printf("L'index de la map n'existe pas dans le fichier");
        return 0;
    }

    if (f != NULL)
    {
        char str[100];
        unsigned int rows = 0;
        unsigned int columns = 0;
        printf("Room recherche : %d\n", index);
        getRoomInformations(f, str, &rows, &columns, index);
        // INFORMATIONS ON SELECTED ROOM
        // printf("%s", str);
        printf("rows : %d\n", rows);
        printf("columns : %d\n", columns);

        int **arena = createEmptyRoom(rows, columns);
        for (int i = 0; i < rows; i++)
        {
            fgets(str, 100, f);
            // printf("%s", str);
            int count = 0;
            // for (int j = 0; j < columns * 2; j++) //SI Y A DES ESPACES DANS LE FICHIER
            // {
            //     if (j % 2 == 0)
            //     {
            //         arena[i][count] = str[j];
            //         // printf("%c ", str[j]);
            //         // printf("%c ", arena[i][count]);
            //         count++;
            //     }
            // }
            for (int j = 0; j < columns; j++)
            {
                arena[i][count] = str[j];
                // printf("%c ", str[j]);
                // printf("%c ", arena[i][count]);
                count++;
            }
            // printf("\n");
        }
        printArray2D(arena, rows, columns);
        return arena;
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        return 0;
    }
}

unsigned int getNumberOfMapInFile(FILE *f)
{
    unsigned int numberOfMap = 0;
    if (f != NULL)
    {
        fseek(f, 0, SEEK_SET);
        // printf("RECHERCHE NBR DE MAP TOTAL...\n");
        char str[100];
        fgets(str, 100, f); // Récupère la première ligne du fichier
        // printf("%s", str);
        if (str[0] == '{') // Traitement pour récupérer le nbr de map dans le fichier
        {
            int nbrChiffreInNumber = 0; // Pour déterminer le nbr de chiffre dans le fichier
            for (unsigned int i = 1; i < 100; i++)
            {
                if (str[i] == '}')
                {
                    nbrChiffreInNumber = i - 1;
                }
            }
            for (unsigned int i = nbrChiffreInNumber; i > 0; i--) // Détermine le nbr de map dans le fichier
            {
                numberOfMap += (str[i] - 48) * pow(10, nbrChiffreInNumber - i);
            }
            // printf("Number of ID in file : %d\n", numberOfMap);
            return numberOfMap;
        }
        else
        {

            printf("Erreur le fichier correspondant ne peut pas être lu, vérifier son format");
            return 0;
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        return 0;
    }
}

void initalizingSpawnRoom(int **arr, unsigned int rows, unsigned int columns)
{
    // Mettre les murs définissant la map
    for (int i = 0; i < rows; i += 1)
    {
        arr[i][0] = 'W';
        arr[i][columns - 1] = 'W';
    }
    for (int i = 0; i < columns; i += 1)
    {
        arr[0][i] = 'W';
        arr[rows - 1][i] = 'W';
    }
    // Ajout des portes de sorties
    arr[0][columns / 2] = 'D';
    arr[rows - 1][columns / 2] = 'D';
    arr[rows / 2][0] = 'D';
    arr[rows / 2][columns - 1] = 'D';
}

int **createEmptyRoom(unsigned int rows, unsigned int columns) // SIZE 9x15
{
    int **arena = malloc(sizeof(int *) * rows);
    for (int i = 0; i < rows; i += 1)
    {
        arena[i] = malloc(sizeof(int) * columns);
        for (int j = 0; j < columns; j += 1)
        {
            arena[i][j] = ' ';
        }
    }
    return arena;
}

void freeArray2D(int **arr, unsigned int rows)
{
    for (int i = 0; i < rows; i += 1)
    {
        free(arr[i]);
    }
    free(arr);
}

void printArray2D(int **arr, unsigned int rows, unsigned int columns)
{
    for (int i = 0; i < rows; i += 1)
    {
        for (int j = 0; j < columns; j += 1)
        {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
}

int **createSpawnRoom(unsigned int rows, unsigned int columns)
{
    int **arena = createEmptyRoom(rows, columns);
    initalizingSpawnRoom(arena, rows, columns);
    return arena;
}
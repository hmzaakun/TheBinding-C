#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int **importRandomRoomFromFile()
{
    unsigned int nbrOfRoom = getNumberOfMapInFile();
    srand(time(NULL));
    unsigned int randomRoomId = rand() % nbrOfRoom + 1;
    return importRoomFromFile(randomRoomId);
}

void addRoom()
{
    FILE *f = fopen("maps.rtbob", "r");
    char chaine[100] = "";
    FILE *temp = fopen("tempAdd.txt", "w");
    int row = 0;
    int i;
    if (f != NULL)
    {

        while (fgets(chaine, 100, f) != NULL)
        {
            ++row;
            if (row == 1)
            {
                fprintf(temp, "{%d}", getNumberOfMapInFile() + 1);
                fputs("\n", temp);
            }
            else
            {
                fputs(chaine, temp);
            }
        }
        fclose(f);
        fclose(temp);
        FILE *temp = fopen("tempAdd.txt", "a");

        row = 0;

        fprintf(temp, "[9|15]%d", getNumberOfMapInFile() + 1);
        fputs("\nWWWWWWWDWWWWWWW\n", temp);
        for (i = 0; i < 7; i++)
        {
            row++;
            if (row / 2 == (9 / 2))
            {
                fputs("D             D\n", temp);
            }
            else
            {
                fputs("W             W\n", temp);
            }
        }
        fputs("WWWWWWWDWWWWWWW\n", temp);
        fclose(temp);

        temp = fopen("tempAdd.txt", "r+");
        f = fopen("maps.rtbob", "w");

        while (fgets(chaine, 100, temp) != NULL)
        {
            fputs(chaine, f);
        }

        fclose(temp);
        fclose(f);
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
    }
}

void showRoomId()
{
    FILE *f = fopen("maps.rtbob", "r");
    unsigned int index;
    do
    {
        printf("index?\n");
        scanf("%d", &index);
    } while (index <= 1 || index >= getNumberOfMapInFile());

    char chaine[100];
    int rowStart = 1 + 10 * (index - 1);
    int rowEnd = rowStart + 8;
    int row = 0;
    int newCount = 0;
    int i;
    if (f != NULL)
    {
        fseek(f, 0, SEEK_SET);
        fgets(chaine, 100, f);
        fgets(chaine, 100, f);

        while (fgets(chaine, 100, f) != NULL)
        {
            ++row;
            if (row >= rowStart && row <= rowEnd)
            {
                printf("%d:%s", newCount++, chaine);
            }
        }

        fseek(f, 0, SEEK_SET);
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
    }
}
void updateRoom()
{
    FILE *temp = NULL;
    FILE *f = fopen("maps.rtbob", "r");
    temp = fopen("tempModif.txt", "w+");
    char chaine[100] = "";
    char chaine1[100] = "";
    int row = 0;

    int numberOfMap = getNumberOfMapInFile();
    int ligne;
    int col;
    char mat;
    int dowhile = 0;
    unsigned int index;

    do
    {
        printf("index?\n");
        scanf("%d", &index);
    } while (index <= 1 || index >= getNumberOfMapInFile());

    int startDel = 1 + (index - 1) * 10;
    int endDel = startDel + 9;
    showRoomId();

    do
    {

        if (dowhile)
        {
            printf("Réessaye avec un chiffre entre 1 et 7");
        }
        else
        {
            printf("Ligne?\n");
        }

        scanf("%d", &ligne);
        dowhile++;
    } while (ligne < 1 || ligne > 7);
    dowhile = 0;
    do
    {
        if (dowhile)
        {
            printf("Réessaye avec un nombre entre 1 et 13");
        }
        else
        {
            printf("Colonne?\n");
        }
        scanf("%d", &col);
        dowhile++;
    } while (col < 1 || col > 13);
    dowhile = 0;
    do
    {
        if (dowhile)
        {
            printf("Réessaye avec un charactere R G H S");
        }
        else
        {
            printf("Quelle matériel\n");
        }
        scanf(" %c", &mat);
        dowhile++;
    } while (mat != 'R' && mat != 'G' && mat != 'H' && mat != 'S');

    if (f != NULL)
    {
        fseek(f, 0, SEEK_SET);

        while (fgets(chaine, 100, f) != NULL)
        {
            fputs(chaine, temp);
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
    }

    fclose(f);
    f = fopen("maps.rtbob", "w+");
    fseek(temp, 0, SEEK_SET);

    while (fgets(chaine1, 100, temp) != NULL)
    {
        row++;
        if (((startDel + 2) + ligne) == row)
        {
            chaine1[col] = mat;
        }
        fputs(chaine1, f);
    }

    fclose(temp);
    fclose(f);

    return;
}

void deleteRoom()

{
    FILE *f = fopen("maps.rtbob", "r");
    int unsigned index;
    do
    {
        printf("index?\n");
        scanf("%d", &index);
    } while (index <= 1 || index >= getNumberOfMapInFile());

    FILE *temp = NULL;

    temp = fopen("tempDelete.txt", "w+");
    char chaine[100] = "";
    char chaine1[100] = "";
    int row = 0;

    int startDel = 1 + (index - 1) * 10;
    int endDel = startDel + 9;
    int numberOfMap = getNumberOfMapInFile();

    do
    {
        printf("index?\n");
        scanf("%d", &index);
    } while (index <= 1 || index >= getNumberOfMapInFile());

    if (numberOfMap == 0 || index > numberOfMap)
    // penser a enlever le if pcq on va fair un menu donc on pourra faire un do while numberOfMap == 0 || index > numberOfMap
    {
        printf("L'index de la map a supprimer n'existe pas dans le fichier");
        return;
    }

    if (f != NULL)
    {
        fseek(f, 0, SEEK_SET);

        while (fgets(chaine, 100, f) != NULL)
        {

            ++row;

            if (row != 1 && row >= startDel && row <= endDel)
            {
                fputs("", temp);
            }
            else
            {
                if (row == 1)
                {
                    fprintf(temp, "{%d}", getNumberOfMapInFile() - 1);
                    fputs("\n", temp);
                }
                else if (row % 10 == 2 && row > (endDel + 1))
                {
                    chaine[6]--;

                    fputs(chaine, temp);
                }
                else
                {
                    fputs(chaine, temp);
                }
            }
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
    }

    fclose(f);
    f = fopen("maps.rtbob", "w+");
    fseek(temp, 0, SEEK_SET);
    while (fgets(chaine1, 100, temp) != NULL)
    {
        fputs(chaine1, f);
    }
    fclose(temp);

    return;
}

unsigned int getRowsInSelectedRoom()
{
    FILE *f = fopen("maps.rtbob", "r");
    unsigned int index;
    do
    {
        printf("index?\n");
        scanf("%d", &index);
    } while (index <= 1 || index >= getNumberOfMapInFile());

    if (f != NULL)
    {
        char str[100];
        unsigned int rows = 0;
        unsigned int columns = 0;
        getRoomInformations(f, str, &rows, &columns, index);
        fclose(f);
        return rows;
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        fclose(f);
        return 0;
    }
}
unsigned int getColumnsInSelectedRoom()
{
    FILE *f = fopen("maps.rtbob", "r");
    unsigned int index;
    do
    {
        printf("index?\n");
        scanf("%d", &index);
    } while (index <= 1 || index >= getNumberOfMapInFile());

    if (f != NULL)
    {
        char str[100];
        unsigned int rows = 0;
        unsigned int columns = 0;
        getRoomInformations(f, str, &rows, &columns, index);
        fclose(f);
        return columns;
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        fclose(f);
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
        while (bool != 1)
        {
            fgets(str, 100, f);
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

int **importRoomFromFile(unsigned int index)
{
    int numberOfMap = getNumberOfMapInFile();
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

    FILE *f = fopen("maps.rtbob", "r");
    if (f != NULL)
    {
        char str[100];
        unsigned int rows = 0;
        unsigned int columns = 0;
        // printf("Room recherche : %d\n", index);
        getRoomInformations(f, str, &rows, &columns, index);
        // INFORMATIONS ON SELECTED ROOM
        // printf("%s", str);
        // printf("rows : %d\n", rows);
        // printf("columns : %d\n", columns);

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
        // printArray2D(arena, rows, columns);
        fclose(f);
        return arena;
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        fclose(f);
        return 0;
    }
}

unsigned int getNumberOfMapInFile()
{
    FILE *f = fopen("maps.rtbob", "r");
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
            fclose(f);
            return numberOfMap;
        }
        else
        {
            printf("Erreur le fichier correspondant ne peut pas être lu, vérifier son format");
            fclose(f);
            return 0;
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        fclose(f);
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
    // arr[0][columns / 2] = 'D';
    // arr[rows - 1][columns / 2] = 'D';
    // arr[rows / 2][0] = 'D';
    // arr[rows / 2][columns - 1] = 'D';
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

void delay(int number_of_milli_seconds)
{
    int milli_seconds = number_of_milli_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}
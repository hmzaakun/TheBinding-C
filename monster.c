#include "monster.h"
#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

Monster *importMonsterByName(FILE *f, char name[])
{
}

Monster *importRandomMonster(FILE *f)
{
    unsigned int nbrOfMonster = getNumberOfMonsterInFile(f);
    srand(time(NULL));
    unsigned int randomMonsterId = rand() % nbrOfMonster + 1;
    printf("ID du random Monster : %d\n", randomMonsterId);
    return importMonsterById(f, randomMonsterId);
}

void getMonsterInformation(FILE *f, char str[], Monster *monster)
{
    if (f != NULL)
    {
        fgets(str, 100, f);
        // printf("%s", str);
        if (str[0] == 'n' && str[1] == 'a' && str[2] == 'm' && str[3] == 'e' && str[4] == '=')
        {
            char name[20];
            for (int j = 5; j < 26; j++)
            {
                if (str[j] != '\n')
                {
                    name[j - 5] = str[j];
                }
            }
            monster->name = duplicateString(name);
        }
        else if (str[0] == 'h' && str[1] == 'p' && str[2] == 'M' && str[3] == 'a' && str[4] == 'x')
        {
            char doubleHpMax[5];
            for (int i = 0; i < 10; i++)
            {
                if (str[i] < '9' && str[i] > '0' || str[i] == '.')
                {
                    doubleHpMax[i - 6] = str[i];
                }
            }
            monster->hpMax = atof(doubleHpMax);
        }
        else if (str[0] == 's' && str[1] == 'h' && str[2] == 'o' && str[3] == 'o' && str[4] == 't')
        {
            monster->shoot = 1;
        }
        else if (str[0] == 's' && str[1] == 's' && str[2] == '=')
        {
            monster->spectralShot = 1;
        }
        else if (str[0] == 'f' && str[1] == 'l' && str[2] == 'i' && str[3] == 'g' && str[4] == 'h' && str[5] == 't')
        {
            monster->flight = 1;
        }
    }
}

Monster *importMonsterById(FILE *f, unsigned int id)
{
    int numberOfMonsterInFile = getNumberOfMonsterInFile(f);
    if (numberOfMonsterInFile == 0)
    {
        printf("Pas de monstre dans le fichier, l'import est impossible\n");
        return 0;
    }
    if (id > numberOfMonsterInFile)
    {
        printf("L'id du monstre n'existe pas dans le fichier");
        return 0;
    }
    // printf("Number of monster in file : %d\n", numberOfMonsterInFile);

    Monster *monster = malloc(sizeof(Monster));
    initializeMonster(monster);
    char str[100];
    if (f != NULL)
    {
        int counter = 0;
        while (counter != id)
        {
            fgets(str, 100, f);
            if (str[0] == '-' && str[1] == '-' && str[2] == '-')
            {
                counter++;
            }
        }
        if (id < numberOfMonsterInFile)
        {
            do
            {
                getMonsterInformation(f, str, monster);
            } while (!(str[0] == '-' && str[1] == '-' && str[2] == '-'));
        }
        else if (id == numberOfMonsterInFile)
        {
            for (int i = 0; i < 5; i++)
            {
                getMonsterInformation(f, str, monster);
            }
        }
        return monster;
    }
    else
    {
        printf("Erreur le fichier n'est pas ouvert !\n");
    }
}

void initializeMonster(Monster *monster)
{
    monster->hpMax = 0;
    monster->shoot = 0;
    monster->spectralShot = 0;
    monster->flight = 0;
}

unsigned int getNumberOfMonsterInFile(FILE *f)
{
    return getNumberOfMapInFile(f);
}

char *duplicateString(char *str)
{
    if (str == NULL)
        return NULL;
    int size = strlen(str);
    char *newStr = malloc(sizeof(char) * (size + 1));
    return strcpy(newStr, str);
}

void printMonster(Monster *monster)
{
    printf("MONSTER INFORMATIONS :\n");
    printf("name : %s\n", monster->name);
    printf("hpMax : %.2f\n", monster->hpMax);
    printf("shoot : %u\n", monster->shoot);
    printf("spectral shoot : %u\n", monster->spectralShot);
    printf("flight : %u\n", monster->flight);
}

void freeMonster(Monster *monster)
{
    free(monster->name);
    free(monster);
}

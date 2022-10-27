#include "monster.h"
#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

Monster *importMonsterByName(FILE *f, char name[])
{
    Monster *monster = malloc(sizeof(Monster));
    monster->name = duplicateString(name);
    monster->hpMax = 10;
    monster->shoot = 1;
    monster->spectralShot = 0;
    monster->flight = 1;
    return monster;
}

Monster *importRandomMonster(FILE *f)
{
    Monster *monster = malloc(sizeof(Monster));

    return monster;
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
    printf("Number of monster in file : %d\n", numberOfMonsterInFile);

    Monster *monster = malloc(sizeof(Monster));
    char str[100];
    if (f != NULL)
    {
        int bool = 0;
        int counter = 0;
        do
        {
            fgets(str, 100, f);
            if (str[0] == '-' && str[1] == '-' && str[2] == '-')
            {
                counter++;
                for (int i = 0; i < 4; i++)
                {
                    fgets(str, 100, f);
                    if (str[0] == 'n' && str[1] == 'a' && str[2] == 'm' && str[3] == 'e' && str[4] == '=')
                    {
                        for (int j = 0; j < 100; j++)
                        {
                        }
                        // monster->name = duplicateString(name);
                    }
                }
            }
            if (counter == id)
            {
                bool = 1;
            }
        } while (bool == 0);
    }
    else
    {
        printf("Erreur le fichier n'est pas ouvert !\n");
    }

    return monster;
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
    printf("hpMax : %d\n", monster->hpMax);
    printf("shoot : %d\n", monster->shoot);
    printf("spectral shoot : %d\n", monster->spectralShot);
    printf("flight : %d\n", monster->flight);
}

void freeMonster(Monster *monster)
{
    free(monster->name);
    free(monster);
}

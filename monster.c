#include "monster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Monster *importMonsterByName(char name[])
{
    Monster *monster = malloc(sizeof(Monster));
    monster->name = duplicateString(name);
    monster->hpMax = 10;
    monster->shoot = 1;
    monster->spectralShot = 0;
    monster->flight = 1;
    return monster;
}

Monster *importRandomMonster()
{
    Monster *monster = malloc(sizeof(Monster));

    return monster;
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

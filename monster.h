#include <stdio.h>
#include <stdlib.h>

#ifndef MONSTER
#define MONSTER

struct Monster
{
    char *name;
    unsigned int hpMax;
    unsigned int shoot;        // TRUE OR FALSE
    unsigned int spectralShot; // TRUE OR FALSE
    unsigned int flight;       // TRUE OR FALSE
};
typedef struct Monster Monster;

Monster *importMonsterByName(FILE *f, char name[]);
Monster *importMonsterById(FILE *f, unsigned int id);
Monster *importRandomMonster(FILE *f);
unsigned int getNumberOfMonsterInFile(FILE *f);
char *duplicateString(char *);
void printMonster(Monster *monster);
void freeMonster(Monster *monster);

#endif
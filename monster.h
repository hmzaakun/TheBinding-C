#include <stdio.h>
#include <stdlib.h>

#ifndef MONSTER
#define MONSTER

struct Monster
{
    char *name;
    double hpMax;
    unsigned int shoot;        // TRUE OR FALSE
    unsigned int spectralShot; // TRUE OR FALSE
    unsigned int flight;       // TRUE OR FALSE
};
typedef struct Monster Monster;

Monster *importMonsterByName(FILE *f, char name[]); // PAS UTILE DE DEV SA PR L'INSTANT
Monster *importMonsterById(FILE *f, unsigned int id);
Monster *importRandomMonster(FILE *f);
void getMonsterInformation(FILE *f, char str[], Monster *monster);
void initializeMonster(Monster *monster);
unsigned int getNumberOfMonsterInFile(FILE *f);
char *duplicateString(char *);
void printMonster(Monster *monster);
void freeMonster(Monster *monster);

#endif
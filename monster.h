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

/*Fonctions d'import*/
Monster *importMonsterByName(FILE *f, char name[]); // PAS UTILE DE DEV SA PR L'INSTANT
Monster *importMonsterById(FILE *f, unsigned int id);
Monster *importRandomMonster(FILE *f);
unsigned int getNumberOfMonsterInFile(FILE *f);

/*Fonction d'aide à ne pas utiliser dans le main*/
void getMonsterInformation(FILE *f, char str[], Monster *monster);
void initializeMonster(Monster *monster);
char *duplicateString(char *);
void addMonsterToFile(FILE *f); // Ajoute les infos à la fin du fichiers mais reste le nbr de monstre à modifier

/*Fonctions utilitaire*/
void removeMonsterById(FILE *f, unsigned int id);
void modifyMonsterById(FILE *f, unsigned int id);
void addMonster(); // Ajoute le monstre voulu à la fin du fichier
void printMonster(Monster *monster);
void printAllMonster(FILE *f);
void freeMonster(Monster *monster);

#endif
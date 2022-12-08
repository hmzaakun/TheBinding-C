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
Monster *importMonsterByName(char name[]); // PAS UTILE DE DEV SA PR L'INSTANT
Monster *importMonsterById(unsigned int id);
Monster *importRandomMonster();
unsigned int getNumberOfMonsterInFile();

/*Fonction d'aide à ne pas utiliser dans le main*/
void getMonsterInformation(FILE *f, char str[], Monster *monster);
void initializeMonster(Monster *monster);
char *duplicateString(char *);
void addMonsterToFile(); // Ajoute les infos à la fin du fichiers mais reste le nbr de monstre à modifier

/*Fonctions utilitaire*/
void removeMonsterById(unsigned int id);
void removeMonster();
void modifyMonsterById(unsigned int id);
void modifyMonster();
void addMonster(); // Ajoute le monstre voulu à la fin du fichier
void printMonster(Monster *monster);
void printAllMonster();
void freeMonster(Monster *monster);

#endif

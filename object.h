#include <stdio.h>
#include <stdlib.h>

#ifndef OBJECT
#define OBJECT

struct Object
{
    char *name;
    double hpMax;
    unsigned int shield;
    double damage;
    unsigned int spectralShoot; // TRUE OR FALSE
    unsigned int percingShoot;  // TRUE OR FALSE
    unsigned int flight;        // TRUE OR FALSE
};
typedef struct Object Object;

/*Fonctions d'import*/
Object *importObjectByName(FILE *f, char name[]); // PAS DEV
Object *importObjectById(FILE *f, unsigned int id);
Object *importRandomObject(FILE *f);
unsigned int getNumberOfObjectInFile(FILE *f);

/*Fonctions d'aide à ne pas utiliser dans le main*/
void getObjectInformation(FILE *f, char str[], Object *object);
void initializeObject(Object *object);
void addObjectToFile(FILE *f); // Ajoute les infos à la fin du fichiers mais reste le nbr de monstre à modifier

/*Fonctions utilitaires*/
void printObject(Object *object);
void printAllObjects(FILE *f);
void modifyObjectById(FILE *f, unsigned int id);
void addObject(); // Ajoute le monstre voulu à la fin du fichier, le fichier ne doit pas être préalablement ouvert
void freeObject(Object *object);
void removeObjectById(FILE *f, unsigned int id);

#endif
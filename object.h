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

Object *importObjectByName(FILE *f, char name[]);
Object *importObjectById(FILE *f, unsigned int id);
Object *importRandomObject(FILE *f);
void initializeObject(Object *object);
void getObjectInformation(FILE *f, char str[], Object *object);
unsigned int getNumberOfObjectInFile(FILE *f);
void printObject(Object *object);
void freeObject(Object *object);

#endif
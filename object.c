#include "object.h"
#include "monster.h"

Object *importObjectByName(FILE *f, char name[])
{
    Object *object = malloc(sizeof(Object));
    object->name = duplicateString(name);
    object->damage = 10;
    object->shield = 3;
    object->hpMax = 10;
    object->percingShoot = 1;
    object->spectralShoot = 0;
    object->flight = 1;
    return object;
}

Object *importObjectById(FILE *f, unsigned int id)
{
}

Object *importRandomObject(FILE *f)
{
}

unsigned int getNumberOfObjectInFile(FILE *f)
{
    return getNumberOfMonsterInFile(f);
}

void printObject(Object *object)
{
    printf("OBJECT INFORMATIONS :\n");
    printf("name : %s\n", object->name);
    printf("shield : %d\n", object->shield);
    printf("damage : %d\n", object->damage);
    printf("spectral shoot : %d\n", object->spectralShoot);
    printf("percing shoot : %d\n", object->percingShoot);
    printf("flight : %d\n", object->flight);
}

void freeObject(Object *object)
{
    free(object->name);
    free(object);
}
#include "object.h"
#include "monster.h"
#include <time.h>

Object *importObjectByName(FILE *f, char name[])
{
    Object *object = malloc(sizeof(Object));
    object->name = duplicateString(name);
    initializeObject(object);
    return object;
}

Object *importRandomObject(FILE *f)
{
    unsigned int nbrOfObject = getNumberOfObjectInFile(f);
    srand(time(NULL));
    unsigned int randomObjectId = rand() % nbrOfObject + 1;
    printf("ID du random Object : %d\n", randomObjectId);
    return importObjectById(f, randomObjectId);
}

Object *importObjectById(FILE *f, unsigned int id)
{
    int numberOfObjectInFile = getNumberOfObjectInFile(f);
    if (numberOfObjectInFile == 0)
    {
        printf("Pas d'objet dans le fichier, l'import est impossible\n");
        return 0;
    }
    if (id > numberOfObjectInFile)
    {
        printf("L'id de l'objet n'existe pas dans le fichier");
        return 0;
    }
    // printf("Number of monster in file : %d\n", numberOfMonsterInFile);

    Object *object = malloc(sizeof(Object));
    initializeObject(object);
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
        if (id < numberOfObjectInFile)
        {
            do
            {
                getObjectInformation(f, str, object);
            } while (!(str[0] == '-' && str[1] == '-' && str[2] == '-'));
        }
        else if (id == numberOfObjectInFile)
        {
            for (int i = 0; i < 5; i++)
            {
                getObjectInformation(f, str, object);
            }
        }
        return object;
    }
    else
    {
        printf("Erreur le fichier n'est pas ouvert !\n");
    }
}

void getObjectInformation(FILE *f, char str[], Object *object)
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
            object->name = duplicateString(name);
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
            object->hpMax = atof(doubleHpMax);
        }
        else if (str[0] == 'd' && str[1] == 'm' && str[2] == 'g')
        {
            char damage[5];
            for (int i = 0; i < 10; i++)
            {
                if (str[i] < '9' && str[i] > '0' || str[i] == '.')
                {
                    damage[i - 4] = str[i];
                }
            }
            object->damage = atof(damage);
        }
        else if (str[0] == 's' && str[1] == 'h' && str[2] == 'i' && str[3] == 'e' && str[4] == 'l' && str[5] == 'd')
        {
            char shield[5];
            for (int i = 0; i < 10; i++)
            {
                if (str[i] < '9' && str[i] > '0')
                {
                    shield[i - 7] = str[i];
                }
            }
            object->shield = atoi(shield);
        }
        else if (str[0] == 's' && str[1] == 's' && str[2] == '=')
        {
            object->spectralShoot = 1;
        }
        else if (str[0] == 'p' && str[1] == 's' && str[2] == '=')
        {
            object->percingShoot = 1;
        }
        else if (str[0] == 'f' && str[1] == 'l' && str[2] == 'i' && str[3] == 'g' && str[4] == 'h' && str[5] == 't')
        {
            object->flight = 1;
        }
    }
}

void initializeObject(Object *object)
{
    object->damage = 0;
    object->shield = 0;
    object->hpMax = 0;
    object->percingShoot = 0;
    object->spectralShoot = 0;
    object->flight = 0;
}

unsigned int getNumberOfObjectInFile(FILE *f)
{
    return getNumberOfMonsterInFile(f);
}

void printObject(Object *object)
{
    printf("OBJECT INFORMATIONS :\n");
    printf("Name : %s\n", object->name);
    printf("Hp Max : %.2f\n", object->hpMax);
    printf("Damage : %.2f\n", object->damage);
    printf("Shield : %u\n", object->shield);
    printf("Spectral Shoot : %u\n", object->spectralShoot);
    printf("Percing Shoot : %u\n", object->percingShoot);
    printf("Flight : %u\n", object->flight);
}

void freeObject(Object *object)
{
    free(object->name);
    free(object);
}
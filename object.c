#include "object.h"
#include "monster.h"
#include <time.h>
#include <math.h>

Object *importObjectByName(char name[])
{
    // Object *object = malloc(sizeof(Object));
    // object->name = duplicateString(name);
    // initializeObject(object);
    // return object;
}
void modifyObject(){
unsigned int id;
 do
    {
        printf("id?\n");
        scanf("%d", &id);
    } while (id<= 1 || id >= getNumberOfObjectInFile());

}

void modifyObjectById(unsigned int id)
{
    removeObjectById(id);
    addObject();
}

void addObject()
{
    FILE *temp = NULL;
    temp = fopen("temp.itbob", "w+");

    int numberOfObjectInFile = getNumberOfObjectInFile();

    FILE *f = fopen("objects.itbob", "r");
    if (f != NULL)
    {
        char str[100];
        char ch;
        sprintf(str, "%d", numberOfObjectInFile + 1); // Convertir nbr to string
        fputc('{', temp);
        fputs(str, temp);
        fputc('}', temp);
        fputc('\n', temp);
        fgets(str, 100, f); // récupère la première ligne inutile désormais

        while ((ch = getc(f)) != EOF)
            putc(ch, temp);

        fclose(f);
        fclose(temp);
        remove("objects.itbob");
        rename("temp.itbob", "objects.itbob");
        /*Ajoute les informations à la fin du fichier reste le nbr de monstre à modifier*/
        addObjectToFile();
    }
}

void addObjectToFile()
{
    FILE *f = fopen("objects.itbob", "a");
    if (f != NULL)
    {
     getchar();
        char toWrite[100];
        fputs("---\n", f);
        printf("Nom de l'object :\n");
        fputs("name=", f);
        fputs(fgets(toWrite, 30, stdin), f);
        // fputc('\n', f);

        printf("hpMax (float ex:5.5) :\n");
        fputs("hpMax=", f);
        fputs(fgets(toWrite, 30, stdin), f);
        // fputc('\n', f);

        printf("Shield (entier non signé):\n");
        fputs("shield=", f);
        fputs(fgets(toWrite, 30, stdin), f);
        // fputc('\n', f);

        printf("Damage (float ex:4.5) :\n");
        fputs("dmg=", f);
        fputs(fgets(toWrite, 30, stdin), f);
        // fputc('\n', f);

        printf("Spectral Shoot (true ou false) :\n");
        fgets(toWrite, 30, stdin);
        if (toWrite[0] == 't' && toWrite[1] == 'r' && toWrite[2] == 'u' && toWrite[3] == 'e')
        {
            fputs("ss=", f);
            fputs(toWrite, f);
            // fputc('\n', f);
        }

        printf("Percing Shoot (true ou false) :\n");
        fgets(toWrite, 30, stdin);
        if (toWrite[0] == 't' && toWrite[1] == 'r' && toWrite[2] == 'u' && toWrite[3] == 'e')
        {
            fputs("ss=", f);
            fputs(toWrite, f);
            // fputc('\n', f);
        }

        printf("Flight (true ou false):\n");
        fgets(toWrite, 30, stdin);
        if (toWrite[0] == 't' && toWrite[1] == 'r' && toWrite[2] == 'u' && toWrite[3] == 'e')
        {
            fputs("flight=", f);
            fputs(toWrite, f);
            // fputc('\n', f);
        }

        fclose(f);
    }
    else
    {
        printf("impossible de lire le fichier");
        fclose(f);
    }
}
void removeObject()
{
unsigned int id;
 printf("id?\n");
 scanf("%d", &id);
 removeObjectById(id);
}

void removeObjectById(unsigned int id)
{
    FILE *f = fopen("objects.itbob", "r");
    int numberOfObjectInFile = getNumberOfObjectInFile();
    if (numberOfObjectInFile == 0)
    {
        printf("Pas d'objet dans le fichier, impossible de delete un objet\n");
        return;
    }
    if (id > numberOfObjectInFile)
    {
        printf("L'id de l'objet n'existe pas dans le fichier");
        return;
    }

    FILE *temp = NULL;
    temp = fopen("temp.itbob", "w+");

    if (f != NULL)
    {
        char str[100];
        int counter = 1;
        sprintf(str, "%d", numberOfObjectInFile - 1); // Convertir nbr to string
        fputc('{', temp);
        fputs(str, temp);
        fputc('}', temp);
        fputc('\n', temp);
        fgets(str, 100, f); // récupère la première ligne inutile
        while (counter != id)
        {
            fgets(str, 100, f);
            if (str[0] == '-' && str[1] == '-' && str[2] == '-')
            {
                counter++;
            }
            if (counter != id)
            {
                fputs(str, temp);
            }
        }
        if (id < numberOfObjectInFile)
        {
            int bool = 0;
            fgets(str, 100, f);
            while (bool != 1)
            {
                fgets(str, 100, f);
                if (str[0] == '-' && str[1] == '-' && str[2] == '-')
                {
                    fputs(str, temp);
                    bool = 1;
                }
            }
            while (counter != numberOfObjectInFile - 1)
            {
                fgets(str, 100, f);
                fputs(str, temp);
                if (str[0] == '-' && str[1] == '-' && str[2] == '-')
                {
                    counter++;
                }
            }
            char ligneAvant[100];
            int isSameLine = 0;
            for (int i = 0; i < 5; i++)
            {
                fgets(str, 100, f);
                if (ligneAvant[0] == str[0] && ligneAvant[1] == str[1] && ligneAvant[2] == str[2] && ligneAvant[3] == str[3])
                {
                    fclose(f);
                    fclose(temp);
                    remove("objects.itbob");
                    rename("temp.itbob", "objects.itbob");
                    return;
                }
                fputs(str, temp);
                for (int i = 0; i < 100; i++)
                {
                    ligneAvant[i] = str[i];
                }
            }
        }
        fclose(f);
        fclose(temp);
        remove("objects.itbob");
        rename("temp.itbob", "objects.itbob");
    }
    else
    {
        printf("erreur de lecture\n");
        fclose(f);
    }
}

Object *importRandomObject()
{
    unsigned int nbrOfObject = getNumberOfObjectInFile();
    srand(time(NULL));
    unsigned int randomObjectId = rand() % nbrOfObject + 1;
    printf("ID du random Object : %d\n", randomObjectId);
    return importObjectById(randomObjectId);
}


Object *importObjectById(unsigned int id)
{
    int numberOfObjectInFile = getNumberOfObjectInFile();
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

    FILE *f = fopen("objects.itbob", "r");
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
        fclose(f);
        return object;
    }
    else
    {
        printf("Erreur le fichier n'est pas ouvert !\n");
        fclose(f);
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

void printAllObjects()
{
    for (unsigned int i = 1; i <= getNumberOfObjectInFile(); i++)
    {
        Object *object = importObjectById(i);
        printObject(object);
        freeObject(object);
    }
}



unsigned int getNumberOfObjectInFile()
{
    FILE *f = fopen("objects.itbob", "r");
    unsigned int numberOfObject = 0;
    if (f != NULL)
    {
        fseek(f, 0, SEEK_SET);
        // printf("RECHERCHE NBR DE MAP TOTAL...\n");
        char str[100];
        fgets(str, 100, f); // Récupère la première ligne du fichier
        // printf("%s", str);
        if (str[0] == '{') // Traitement pour récupérer le nbr de map dans le fichier
        {
            int nbrChiffreInNumber = 0; // Pour déterminer le nbr de chiffre dans le fichier
            for (unsigned int i = 1; i < 100; i++)
            {
                if (str[i] == '}')
                {
                    nbrChiffreInNumber = i - 1;
                }
            }
            for (unsigned int i = nbrChiffreInNumber; i > 0; i--) // Détermine le nbr de map dans le fichier
            {
                numberOfObject += (str[i] - 48) * pow(10, nbrChiffreInNumber - i);
            }
            // printf("Number of ID in file : %d\n", numberOfMap);
            fclose(f);
            return numberOfObject;
        }
        else
        {
            printf("Erreur le fichier correspondant ne peut pas être lu, vérifier son format");
            fclose(f);
            return 0;
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        fclose(f);
        return 0;
    }
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
    // free(object);
}

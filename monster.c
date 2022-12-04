#include "monster.h"
#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

Monster *importMonsterByName(char name[])
{
}

void printAllMonster()
{
    FILE *f = fopen("monsters.mtbob", "r");
    for (unsigned int i = 1; i <= getNumberOfMonsterInFile(); i++)
    {
        Monster *monster = importMonsterById(i);
        printMonster(monster);
    }
    fclose(f);
}

Monster *importRandomMonster()
{
    unsigned int nbrOfMonster = getNumberOfMonsterInFile();
    srand(time(NULL));
    unsigned int randomMonsterId = rand() % nbrOfMonster + 1;
    // printf("ID du random Monster : %d\n", randomMonsterId);
    return importMonsterById(randomMonsterId);
}

void modifyMonsterById(unsigned int id)
{
    FILE *f = fopen("monsters.mtbob", "r");
    removeMonsterById(id);
    addMonster();
    fclose(f);
}

void addMonster()
{
    FILE *temp = NULL;
    temp = fopen("temp.mtbob", "w+");

    int numberOfMonsterInFile = getNumberOfMonsterInFile();

    FILE *f = fopen("monsters.mtbob", "r");
    if (f != NULL)
    {
        char str[100];
        char ch;
        sprintf(str, "%d", numberOfMonsterInFile + 1); // Convertir nbr to string
        fputc('{', temp);
        fputs(str, temp);
        fputc('}', temp);
        fputc('\n', temp);
        fgets(str, 100, f); // récupère la première ligne inutile désormais

        while ((ch = getc(f)) != EOF)
            putc(ch, temp);

        fclose(f);
        fclose(temp);
        remove("monsters.mtbob");
        rename("temp.mtbob", "monsters.mtbob");
        /*Ajoute les informations à la fin du fichier reste le nbr de monstre à modifier*/
        addMonsterToFile();
    }
}

void addMonsterToFile()
{
    FILE *f = fopen("monsters.mtbob", "a");
    if (f != NULL)
    {
        char toWrite[100];
        fputs("---", f);

        printf("Nom du monstre :\n");
        fputs("name=", f);
        fputs(fgets(toWrite, 30, stdin), f);
        // fputc('\n', f);

        printf("hpMax (float ex:5.5) :\n");
        fputs("hpMax=", f);
        fputs(fgets(toWrite, 30, stdin), f);
        // fputc('\n', f);

        printf("Shoot (true ou false) :\n");
        fgets(toWrite, 30, stdin);
        if (toWrite[0] == 't' && toWrite[1] == 'r' && toWrite[2] == 'u' && toWrite[3] == 'e')
        {
            fputs("shoot=", f);
            fputs(toWrite, f);
            // fputc('\n', f);
            printf("Spectral Shoot (true ou false) :\n");
            fgets(toWrite, 30, stdin);
            if (toWrite[0] == 't' && toWrite[1] == 'r' && toWrite[2] == 'u' && toWrite[3] == 'e')
            {
                fputs("ss=", f);
                fputs(toWrite, f);
                // fputc('\n', f);
            }
        }

        printf("Flight (true ou false) :\n");
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

void removeMonsterById(unsigned int id)
{
    int numberOfMonsterInFile = getNumberOfMonsterInFile();
    if (numberOfMonsterInFile == 0)
    {
        printf("Pas de monstre dans le fichier, impossible de delete un monstre\n");
        return;
    }
    if (id > numberOfMonsterInFile)
    {
        printf("L'id du monstre n'existe pas dans le fichier");
        return;
    }

    FILE *f = fopen("monsters.mtbob", "r");
    FILE *temp = NULL;
    temp = fopen("temp.mtbob", "w+");

    if (f != NULL)
    {
        char str[100];
        int counter = 1;
        sprintf(str, "%d", numberOfMonsterInFile - 1); // Convertir nbr to string
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
        if (id < numberOfMonsterInFile)
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
            while (counter != numberOfMonsterInFile - 1)
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
                    remove("monsters.mtbob");
                    rename("temp.mtbob", "monsters.mtbob");
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
        remove("monsters.mtbob");
        rename("temp.mtbob", "monsters.mtbob");
    }
    else
    {
        printf("erreur de lecture\n");
        fclose(f);
    }
}

void getMonsterInformation(FILE *f, char str[], Monster *monster)
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
            monster->name = duplicateString(name);
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
            monster->hpMax = atof(doubleHpMax);
        }
        else if (str[0] == 's' && str[1] == 'h' && str[2] == 'o' && str[3] == 'o' && str[4] == 't')
        {
            monster->shoot = 1;
        }
        else if (str[0] == 's' && str[1] == 's' && str[2] == '=')
        {
            monster->spectralShot = 1;
        }
        else if (str[0] == 'f' && str[1] == 'l' && str[2] == 'i' && str[3] == 'g' && str[4] == 'h' && str[5] == 't')
        {
            monster->flight = 1;
        }
    }
}

Monster *importMonsterById(unsigned int id)
{
    FILE *f = fopen("monsters.mtbob", "r");
    int numberOfMonsterInFile = getNumberOfMonsterInFile();
    if (numberOfMonsterInFile == 0)
    {
        printf("Pas de monstre dans le fichier, l'import est impossible\n");
        return 0;
    }
    if (id > numberOfMonsterInFile)
    {
        printf("L'id du monstre n'existe pas dans le fichier");
        return 0;
    }
    // printf("Number of monster in file : %d\n", numberOfMonsterInFile);

    Monster *monster = malloc(sizeof(Monster));
    initializeMonster(monster);
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
        if (id < numberOfMonsterInFile)
        {
            do
            {
                getMonsterInformation(f, str, monster);
            } while (!(str[0] == '-' && str[1] == '-' && str[2] == '-'));
        }
        else if (id == numberOfMonsterInFile)
        {
            for (int i = 0; i < 5; i++)
            {
                getMonsterInformation(f, str, monster);
            }
        }
        fclose(f);
        return monster;
    }
    else
    {
        printf("Erreur le fichier n'est pas ouvert !\n");
        fclose(f);
    }
}

void initializeMonster(Monster *monster)
{
    monster->hpMax = 0;
    monster->shoot = 0;
    monster->spectralShot = 0;
    monster->flight = 0;
}

unsigned int getNumberOfMonsterInFile()
{
    FILE *f = fopen("monsters.mtbob", "r");
    unsigned int numberOfMonster = 0;
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
                numberOfMonster += (str[i] - 48) * pow(10, nbrChiffreInNumber - i);
            }
            // printf("Number of ID in file : %d\n", numberOfMap);
            fclose(f);
            return numberOfMonster;
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
    printf("hpMax : %.2f\n", monster->hpMax);
    printf("shoot : %u\n", monster->shoot);
    printf("spectral shoot : %u\n", monster->spectralShot);
    printf("flight : %u\n", monster->flight);
}

void freeMonster(Monster *monster)
{
    free(monster->name);
    free(monster);
}
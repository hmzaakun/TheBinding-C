#include "monster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Monster *importMonsterByName(FILE *f, char name[])
{
    Monster *monster = malloc(sizeof(Monster));
    monster->name = duplicateString(name);
    monster->hpMax = 10;
    monster->shoot = 1;
    monster->spectralShot = 0;
    monster->flight = 1;
    return monster;
}

Monster *importRandomMonster(FILE *f)
{
    Monster *monster = malloc(sizeof(Monster));

    return monster;
}

Monster *importMonsterById(FILE *f, unsigned int id)
{
    int numberOfMonsterInFile = getNumberOfMonsterInFile(f);
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

    Monster *monster = malloc(sizeof(Monster));
    printf("number of monster : %d", numberOfMonsterInFile);

    return monster;
}

char *duplicateString(char *str)
{
    if (str == NULL)
        return NULL;
    int size = strlen(str);
    char *newStr = malloc(sizeof(char) * (size + 1));
    return strcpy(newStr, str);
}

unsigned int getNumberOfMonsterInFile(FILE *f)
{
    unsigned int numberOfMonster = 0;
    if (f != NULL)
    {
        fseek(f, 0, SEEK_SET);
        printf("RECHERCHE NBR DE MONSTRE TOTAL...\n");
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
            printf("Number of monster in file : %d\n", numberOfMonster);
            return numberOfMonster;
        }
        else
        {

            printf("Erreur le fichier correspondant ne peut pas être lu, vérifier son format");
            return 0;
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier");
        return 0;
    }
}

void printMonster(Monster *monster)
{
    printf("MONSTER INFORMATIONS :\n");
    printf("name : %s\n", monster->name);
    printf("hpMax : %d\n", monster->hpMax);
    printf("shoot : %d\n", monster->shoot);
    printf("spectral shoot : %d\n", monster->spectralShot);
    printf("flight : %d\n", monster->flight);
}

void freeMonster(Monster *monster)
{
    free(monster->name);
    free(monster);
}

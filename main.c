#include <stdio.h>
#include <stdlib.h>
#include "room.h"
#include "monster.h"
#include "object.h"

int main(int argc, char *argv[])
{
    // FILE *maps = fopen("maps.rtbob", "r");
    // int **arena = importRandomRoomFromFile(maps);
    // freeArray2D(arena, 9);
    // fclose(maps);

    // FILE *monsters = fopen("monsters.mtbob", "r");
    // Monster *monster = importRandomMonster(monsters);
    // printMonster(monster);
    // freeMonster(monster);

    FILE *objects = fopen("objects.itbob", "r");
    Object *object = importRandomObject(objects);
    printObject(object);
    freeObject(object);
    return 0;
}
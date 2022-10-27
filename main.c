#include <stdio.h>
#include <stdlib.h>
#include "room.h"
#include "monster.h"
#include "object.h"

int main(int argc, char *argv[])
{
    FILE *maps = fopen("maps.rtbob", "r");

    int **arena = importRandomRoomFromFile(maps);
    freeArray2D(arena, 9);
    fclose(maps);

    // deleteRoom(maps, 3);

    // FILE *monsters = fopen("monsters.mtbob", "r");
    // Monster *monster = importMonsterById(monsters, 5);
    // // printMonster(monster);
    // freeMonster(monster);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "room.h"
#include "monster.h"
#include "object.h"

int main(int argc, char *argv[])
{
    FILE *maps = fopen("maps.rtbob", "r");

    //char str[100];
    //printf("%c", test[0]);
    //fgets(str, 100, maps);
  	deleteRoom(maps,1);
   
    fclose(maps);

    // deleteRoom(maps, 3);

    // FILE *monsters = fopen("monsters.mtbob", "r");
    // Monster *monster = importMonsterById(monsters, 5);
    // // printMonster(monster);
    // freeMonster(monster);
    return 0;
}

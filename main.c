#include <stdio.h>
#include <stdlib.h>
#include "room.h"

int main(int argc, char *argv[])
{
    FILE *maps = fopen("maps.rtbob", "r");
    int **arena = importRoomFromFile(maps, 3);
    // printf("rows : %d\n", getRowsInSelectedRoom(maps, 3));
    // printf("columns : %d\n", getColumnsInSelectedRoom(maps, 3));
    freeArray2D(arena, 9);
    // int **arena2 = importRoomFromFile(maps, 2);
    // freeArray2D(arena2, 9);

    // deleteRoom(maps, 3);

    fclose(maps);
    return 0;
}
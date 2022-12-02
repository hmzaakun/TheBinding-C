#include <stdio.h>
#include <stdlib.h>
#include "room.h"
#include "monster.h"
#include "object.h"
#include "stage.h"

int main(int argc, char *argv[])
{
    // int **arena = importRandomRoomFromFile();
    // printArray2D(arena, 9, 15);
    // freeArray2D(arena, 9);

    // removeMonsterById(1);
    // printAllMonster();
    // Monster *monster = importRandomMonster();
    // printMonster(monster);
    // freeMonster(monster);
    // addMonster();

    // removeObjectById(4);
    // addObject();
    // printAllObjects();
    // Object *object = importRandomObject();
    // printObject(object);
    // freeObject(object);

    Stage stage;
    initializeStage(&stage);
    printArray2D(stage.stageArea, stage.rows, stage.cols);
    // printAllRoomOfStage(&stage);
    freeStage(&stage);

    return 0;
}
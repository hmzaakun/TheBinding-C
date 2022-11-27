#include <stdio.h>
#include <stdlib.h>

#ifndef ROOM
#define ROOM
void addRoom();
void deleteRoom(unsigned int index); // EN DEVELOPEMENT
void showRoomId(int index); // EN DEVELOPEMENT
void updateRoom();
int **importRoomFromFile(unsigned int index);
int **importRandomRoomFromFile();
void getRoomInformations(char str[], unsigned int *rows, unsigned int *columns, unsigned int index);
unsigned int getNumberOfMapInFile();
unsigned int getRowsInSelectedRoom(unsigned int index);
unsigned int getColumnsInSelectedRoom(unsigned int index);
int **createEmptyRoom(unsigned int rows, unsigned int columns);
int **createSpawnRoom(unsigned int rows, unsigned int columns);
void initalizingSpawnRoom(int **arr, unsigned int rows, unsigned int columns);
void printArray2D(int **arr, unsigned int rows, unsigned int columns);
void freeArray2D(int **arr, unsigned int rows);

#endif

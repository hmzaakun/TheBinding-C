#include <stdio.h>
#include <stdlib.h>

#ifndef ROOM
#define ROOM
void addRoom();
void deleteRoom(); // EN DEVELOPEMENT
void showRoomId(); // EN DEVELOPEMENT
void updateRoom();
int **importRoomFromFile();
int **importRandomRoomFromFile();
void getRoomInformations(char str[], unsigned int *rows, unsigned int *columns);
unsigned int getNumberOfMapInFile();
unsigned int getRowsInSelectedRoom();
unsigned int getColumnsInSelectedRoom();
int **createEmptyRoom(unsigned int rows, unsigned int columns);
int **createSpawnRoom(unsigned int rows, unsigned int columns);
void initalizingSpawnRoom(int **arr, unsigned int rows, unsigned int columns);
void printArray2D(int **arr, unsigned int rows, unsigned int columns);
void freeArray2D(int **arr, unsigned int rows);

#endif

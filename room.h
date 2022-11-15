#include <stdio.h>
#include <stdlib.h>

#ifndef ROOM
#define ROOM
void addRoom(FILE *f);
void deleteRoom(FILE *f, unsigned int index); // EN DEVELOPEMENT
void showRoomId(FILE *f,int index); // EN DEVELOPEMENT
int **importRoomFromFile(FILE *f, unsigned int index);
int **importRandomRoomFromFile(FILE *f);
void getRoomInformations(FILE *f, char str[], unsigned int *rows, unsigned int *columns, unsigned int index);
unsigned int getNumberOfMapInFile(FILE *f);
unsigned int getRowsInSelectedRoom(FILE *f, unsigned int index);
unsigned int getColumnsInSelectedRoom(FILE *f, unsigned int index);
int **createEmptyRoom(unsigned int rows, unsigned int columns);
int **createSpawnRoom(unsigned int rows, unsigned int columns);
void initalizingSpawnRoom(int **arr, unsigned int rows, unsigned int columns);
void printArray2D(int **arr, unsigned int rows, unsigned int columns);
void freeArray2D(int **arr, unsigned int rows);

#endif

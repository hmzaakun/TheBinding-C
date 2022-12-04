#include <stdio.h>
#include <stdlib.h>

#ifndef ROOM
#define ROOM

void addRoom();
void deleteRoom(); // EN DEVELOPEMENT
void showRoomId(); // EN DEVELOPEMENT
void updateRoom();
int **importRoomFromFile(unsigned int index);
int **importRandomRoomFromFile();
void getRoomInformations(FILE *f, char str[], unsigned int *rows, unsigned int *columns, unsigned int index);
unsigned int getNumberOfMapInFile();
unsigned int getRowsInSelectedRoom();
unsigned int getColumnsInSelectedRoom();
int **createEmptyRoom(unsigned int rows, unsigned int columns);
int **createSpawnRoom(unsigned int rows, unsigned int columns);
void initalizingSpawnRoom(int **arr, unsigned int rows, unsigned int columns);
void printArray2D(int **arr, unsigned int rows, unsigned int columns);
void freeArray2D(int **arr, unsigned int rows);
void delay(int number_of_milli_seconds);    // Ne semble pas fonctionner sur linux
void my_delay(int number_of_milli_seconds); // Fonctionne sur linux

#endif
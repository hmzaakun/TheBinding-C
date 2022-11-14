#include <stdio.h>
#include <stdlib.h>
#include "object.h"

#ifndef GAME
#define GAME

struct Player
{
    char *name;
    double hpMax;
    unsigned int shield;
    double damage;
    unsigned int spectralShoot; // TRUE OR FALSE
    unsigned int percingShoot;  // TRUE OR FALSE
    unsigned int flight;        // TRUE OR FALSE
    Object object[100];
    unsigned int currentXLocation;
    unsigned int currentYLocation;
};
typedef struct Player Player;

#endif
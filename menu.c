#include <stdio.h>
#include <stdlib.h>
#include "room.h"
#include "monster.h"
#include "object.h"
#include "stage.h"


void playBob(){

Stage stage;
    Player player;
    play(&stage, &player);
    // initializeStage(&stage);
    // printArray2D(stage.stageArea, 9, 9);
    freeStage(&stage);
    freePlayer(&player);
    menu();
    
    }
    
void menuParametre(){
    int choix;
  
    do {
     system("clear");
        printf("\nMONSTRE => 1\n");
        printf("ROOM => 2\n");
        printf("OBJET => 3\n");
          printf("RETOUR => 4\n");
        printf("QUITTER => 5\n");
         printf("Votre choix =>:");
        scanf(" %d", &choix);
    }while(choix != 1 && choix != 2 && choix != 3  && choix != 4  && choix != 5);
  system("clear");
    switch( choix )
    {

        case 1:
          menuParametreMonstre();
            break;
        case 2:
            menuParametreRoom();
            break;
              case 3:
           menuParametreObjet();
            break;
              case 4:
            menu();
            break;
              case 5:
           return;
            break;
        case 6:

            return;

        default:;


    }

}

void menu(){
    int choix;
     
    do {
     system("clear");
        printf("\nJEU => 1\n");
        printf("PARAMETRE => 2\n");
        printf("QUITTER => 3\n");
        printf("Votre choix =>:");
        scanf("%d", &choix);
    }while(choix != 1 && choix != 2 && choix != 3);
  system("clear");
  
    switch ( choix )
    {
        case 1:
   playBob();
   
            break;
        case 2:
            menuParametre();
            break;
        case 3:
            return;
            break;
        default:;

    }

}







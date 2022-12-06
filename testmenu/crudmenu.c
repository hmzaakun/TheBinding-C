#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

void menuParametreMonstre(){
	int choix;
    
    do {
    system("clear");
        printf("\nAJOUTER => 1\n");
        printf("SUPPRIMER => 2\n");
        printf("MODIF => 3\n");
        printf("RETOUR => 4\n");
        printf("QUITTER => 5\n");
         printf("Votre choix =>:");
        scanf("%d", &choix);
    }while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5);
system("clear");
    switch( choix )
    {

        case 1:
          menuParametreMonstre();
            break;
        case 2:
          menuParametreMonstre();
            break;
        case 3:
        menuParametreMonstre();
            break;
        case 4:
            menuParametre();
            break;
        case 5:

            return;

        default:;


    }
 
    return;

}

void menuParametreObjet(){
	int choix;
   
    do {
    system("clear");
        printf("\nAJOUTER => 1\n");
        printf("SUPPRIMER => 2\n");
        printf("MODIF => 3\n");
        printf("RETOUR => 4\n");
        printf("QUITTER => 5\n");
         printf("Votre choix =>:");
        scanf("%d", &choix);
    }while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5);
system("clear");
    switch( choix )
    {

        case 1:
            menuParametreObjet();
            break;
        case 2:
           menuParametreObjet();
            break;
         case 3:
           menuParametreObjet();
            break;
    	case 4:
           // 
           menuParametre();
            break;
        case 5:

            return;

        default:;


    }

  
    return;

}

void menuParametreRoom(){
	int choix;
    system("clear");
    do {
    system("clear");
        printf("\nAJOUTER => 1\n");
        printf("SUPPRIMER => 2\n");
        printf("MODIF => 3\n");
        printf("RETOUR => 4\n");
        printf("QUITTER => 5\n");
        printf("Votre choix =>:");
        scanf("%d", &choix);
    }while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5);
  system("clear");
    switch( choix )
    {

        case 1:
        // fonc
          menuParametreRoom();
            break;
        case 2:
         menuParametreRoom();
            break;
         case 3:
          menuParametreRoom();
          case 4:
            menuParametre();
            break;
        case 5:

            return;

        default:;


    }

  
    return;

}

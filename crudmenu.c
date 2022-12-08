#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

void menuParametreMonstre(){
	int choix;
    
    do {
    system("clear");
     	printf("\n     Monstre\n");
        printf("\nAJOUTER => 1\n");
        printf("SUPPRIMER => 2\n");
        printf("MODIF => 3\n");
        printf("SHOW => 4\n");
        printf("RETOUR => 5\n");
        printf("QUITTER => 6\n");
         printf("Votre choix =>:");
        scanf("%d", &choix);
    }while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6);
system("clear");
    switch( choix )
    {

        case 1:
          addMonster();
          menuParametreMonstre();
            break;
        case 2:
        removeMonster();
          menuParametreMonstre();
            break;
        case 3:
        modifyMonster();
        menuParametreMonstre();
            break;
          case 4:
        printAllMonster();
       menuParametreMonstre();
            break;
        case 5:
      menuParametre();
            break;
        case 6:

            return;

        default:;


    }
 
    return;

}

void menuParametreObjet(){
	int choix;
   
    do {
    system("clear");
     	printf("\n     Objet\n");
        printf("\nAJOUTER => 1\n");
        printf("SUPPRIMER => 2\n");
        printf("MODIF => 3\n");
        printf("SHOW => 4\n");
        printf("RETOUR => 5\n");
        printf("QUITTER => 6\n");
         printf("Votre choix =>:");
        scanf("%d", &choix);
    }while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6);
system("clear");
    switch( choix )
    {

        case 1:
            addObject();
            menuParametreObjet();
            break;
        case 2:
        	removeObject();
           menuParametreObjet();
            break;
         case 3:
         modifyObject();
           menuParametreObjet();
            break;
    	case 4:
           printAllObjects();
           menuParametre();
            break;
            case 5:
           removeObject();
           menuParametre();
            break;
        case 6:

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
     	printf("\n     ROOM\n");
        printf("\nAJOUTER => 1\n");
        printf("SUPPRIMER => 2\n");
        printf("MODIF => 3\n");
        printf("SHOW => 4\n");
        printf("RETOUR => 5\n");
        printf("QUITTER => 6\n");
        printf("Votre choix =>:");
        scanf("%d", &choix);
    }while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6);
  system("clear");
    switch( choix )
    {

        case 1:
          addRoom();
          menuParametreRoom();
         break;
        case 2:
         deleteRoom();
         menuParametreRoom();
         break;
         case 3:
          updateRoom();
          menuParametreRoom();
           break;
          
          case 4:
            showRoom();
            menuParametreRoom();
            break;
             case 5:
            menuParametre();
            break;
        case 6:
            return;

        default:;


    }

  
    return;

}

#include "Commandes.h"

void newCommande() {
    int choix = rand() % (getGame()->nbRecettes - 1);
    getGame()->commandes[getGame()->nbCommandes].recette = getGame()->recettes[choix];
    printf("Nouvelle recette: %s\n", getGame()->commandes[getGame()->nbCommandes].recette.nom);
    getGame()->commandes[getGame()->nbCommandes].timer = ((rand() % 2) + 1) * 5 + 45;
    getGame()->nbCommandes++;
}


void AfficherCommande() {
   int coos[3]= {27,45,32};
   int posLig1 = 10, posCol1 = 10; // Position de départ
   int EspaceHorizontalEntreLesRectangle = 30;
   int LargeurRectangle = 0, LongueurRectangle = 0;

    if (getGraphic()->fs) {
        LargeurRectangle = 150;
        LongueurRectangle = 220;
    } else {
        LargeurRectangle = 90;
        LongueurRectangle = 105;
    }

   for ( int i = 0; i < getGame()->nbCommandes; i++) {
       int xLogo = 54 + (i* (LargeurRectangle + EspaceHorizontalEntreLesRectangle) );

       if (strcmp(getGame()->commandes[0].recette.nom, "Hamburger") == 0) {
           circlefill(getCorrectBuffer(), xLogo, 42 , 25, makecol(50,20,100));
       } else if (strcmp(getGame()->commandes[0].recette.nom, "Soupe") == 0) {
           circlefill(getCorrectBuffer(), xLogo, 42 , 25, makecol(50,20,100));
       }

       stretch_sprite(getCorrectBuffer(),getGraphic()->textures.ticket,20,350,110,140);

       for (int j = 0;  coos[j]< getGame()->commandes[i].recette.nbIngredients; i++) {
           if (getGame()->commandes[i].recette.ingredients[i].nom == SALADE) {
               circlefill(getCorrectBuffer(), coos[j] + i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle) , 70, 10, makecol(50, 180, 200));
           } else if (getGame()->commandes[i].recette.ingredients[i].nom == PAIN) {
               circlefill(getCorrectBuffer(), coos[j]+ i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle), 70, 10, makecol(50, 180, 200));
           } else if (getGame()->commandes[i].recette.ingredients[i].nom == TOMATE) {
               circlefill(getCorrectBuffer(), coos[j]+ i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle), 70, 10, makecol(50, 180, 200));
           } else if (getGame()->commandes[i].recette.ingredients[i].nom == STEAK) {
               circlefill(getCorrectBuffer(), coos[j]+ i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle), 70, 10, makecol(50, 180, 200));
           } else if (getGame()->commandes[i].recette.ingredients[i].nom == OEUF) {
               circlefill(getCorrectBuffer(), coos[j]+ i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle), 70, 10, makecol(50, 180, 200));
           } else if (getGame()->commandes[i].recette.ingredients[i].nom == POTATO) {
               circlefill(getCorrectBuffer(), coos[j]+ i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle), 70, 10, makecol(50, 180, 200));
           }
       }
   }
}

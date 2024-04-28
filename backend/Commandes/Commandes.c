#include "Commandes.h"

void copyRecipeToCommande(s_commande *dest, s_recette *src) {
    for (int i = 0; i < src->nbIngredients; i++) {
        dest->recette.ingredients[i] = src->ingredients[i];
    }
    dest->recette.nbIngredients = src->nbIngredients;
    strcpy(dest->recette.nom, src->nom);
}

void newCommande() {
    int choix = (rand() % (getGame()->nbRecettes));
    copyRecipeToCommande(&getGame()->commandes[getGame()->nbCommandes], &getGame()->recettes[choix]);
    printf("Nouvelle recette: %s\n", getGame()->commandes[getGame()->nbCommandes].recette.nom);
    getGame()->commandes[getGame()->nbCommandes].timer = ((rand() % 2) + 1) * 5 + 45;
    getGame()->nbCommandes++;
    getGame()->commandes[getGame()->nbCommandes].angle = ftofix((float) (rand() % 200 - 100) / 10);
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

   stretch_sprite(getCorrectBuffer(),getGraphic()->textures.BAR,0,350,600,40);
   stretch_sprite(getCorrectBuffer(),getGraphic()->textures.PlancheH,0,380,600,140);

   for ( int i = 0; i < getGame()->nbCommandes; i++) {
       int xLogo = (i* (LargeurRectangle + EspaceHorizontalEntreLesRectangle) );

       if (strcmp(getGame()->commandes[i].recette.nom, "Hamburger") == 0) {
           circlefill(getCorrectBuffer(), xLogo, 42 , 25, makecol(50,20,100));
       } else if (strcmp(getGame()->commandes[i].recette.nom, "Soupe") == 0) {
           circlefill(getCorrectBuffer(), xLogo, 42 , 25, makecol(50,250,100));
       }

       set_clip_rect(getCorrectBuffer(), 0, 375, getCorrectWidth(), getCorrectHeight());
       rotate_scaled_sprite(getCorrectBuffer(),getGraphic()->textures.ticket,xLogo, 340, getGame()->commandes[i].angle, ftofix((float) 110 / getGraphic()->textures.ticket->w));
       set_clip_rect(getCorrectBuffer(), 0, 0, getCorrectWidth(), getCorrectHeight());

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

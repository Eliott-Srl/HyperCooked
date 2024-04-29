#include "Commandes.h"

void copyRecipeToCommande(s_commande *dest, s_recette *src) {
    for (int i = 0; i < src->nbIngredients; i++) {
        dest->recette.ingredients[i] = src->ingredients[i];
    }
    dest->recette.nbIngredients = src->nbIngredients;
    strcpy(dest->recette.nom, src->nom);
}

void newCommande() {
    if (getGame()->nbCommandes >= NB_COMMANDES_MAX) {
        return;
    }

    int choix = (rand() % (getGame()->nbRecettes));
    copyRecipeToCommande(&getGame()->commandes[getGame()->nbCommandes], &getGame()->recettes[choix]);
    // printf("Nouvelle recette: %s\n", getGame()->commandes[getGame()->nbCommandes].recette.nom);
    getGame()->commandes[getGame()->nbCommandes].timer = ((rand() % 2) + 1) * 5 + 45;
    getGame()->nbCommandes++;
    getGame()->commandes[getGame()->nbCommandes].angle = ftofix((float) (rand() % 200 - 100) / 10);
}


void AfficherCommande() {
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

   stretch_sprite(getCorrectBuffer(),getGraphic()->textures.BAR,0,350,getCorrectWidth(),40);
   stretch_sprite(getCorrectBuffer(),getGraphic()->textures.PlancheH,0,380,getCorrectWidth(),140);

   for ( int i = 0; i < getGame()->nbCommandes; i++) {
       int xLogo = 10 + (i* (LargeurRectangle + EspaceHorizontalEntreLesRectangle) );

       set_clip_rect(getCorrectBuffer(), 0, 375, getCorrectWidth(), getCorrectHeight());
       rotate_scaled_sprite(getCorrectBuffer(),getGraphic()->textures.ticket,xLogo, 340, getGame()->commandes[i].angle, ftofix((float) 110 / getGraphic()->textures.ticket->w));
       set_clip_rect(getCorrectBuffer(), 0, 0, getCorrectWidth(), getCorrectHeight());

       if (strcmp(getGame()->commandes[i].recette.nom, "Hamburger") == 0) {
           stretch_sprite(getCorrectBuffer(),getGraphic()->textures.burger,37 + xLogo,408,38,38);
       } else if (strcmp(getGame()->commandes[i].recette.nom, "Salade") == 0) {
           stretch_sprite(getCorrectBuffer(),getGraphic()->textures.Salade,37 + xLogo,408,38,38);
       }

       int coosX[4]= {25,25,90,90};
       int coosY[4] = {400,435,435,400};

       for (int j = 0;  j < getGame()->commandes[i].recette.nbIngredients; j++) {
           if (getGame()->commandes[i].recette.ingredients[j].nom == SALADE) {
               stretch_sprite(getCorrectBuffer(),getGraphic()->textures.Laitue,coosX[j] + i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle),coosY[j],18,18);
           } else if (getGame()->commandes[i].recette.ingredients[j].nom == PAIN) {
               stretch_sprite(getCorrectBuffer(),getGraphic()->textures.Pain,coosX[j] + i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle),coosY[j],18,18);
           } else if (getGame()->commandes[i].recette.ingredients[j].nom == TOMATE) {
               stretch_sprite(getCorrectBuffer(),getGraphic()->textures.tomate,coosX[j] + i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle),coosY[j],18,18);
           } else if (getGame()->commandes[i].recette.ingredients[j].nom == STEAK) {
               stretch_sprite(getCorrectBuffer(),getGraphic()->textures.steak,coosX[j] + i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle),coosY[j],18,18);
           } else if (getGame()->commandes[i].recette.ingredients[j].nom == OEUF) {
               stretch_sprite(getCorrectBuffer(),getGraphic()->textures.Oeuf,coosX[j] + i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle),coosY[j],18,18);
           } else if (getGame()->commandes[i].recette.ingredients[j].nom == POTATO) {
               stretch_sprite(getCorrectBuffer(),getGraphic()->textures.PommeDeTerre,coosX[j] + i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle),coosY[j],18,18);
           }
       }
   }
}

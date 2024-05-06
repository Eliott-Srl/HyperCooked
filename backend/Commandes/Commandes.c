#include "Commandes.h"

int recetteAvailable(int choix) {
    for (int i = 0; i < getGame()->nbRecettes; i++) {
        if (getGame()->recetteAvailable[i] == choix) {
            return 1;
        }
    }
    return 0;
}

void newCommande() {
    if (getGame()->nbCommandes >= NB_COMMANDES_MAX) {
        return;
    }

    int choix;
    do {
        choix = (rand() % (getGame()->nbRecettesAvailable));
    } while (!recetteAvailable(choix));

    for (int i = 0; i < getGame()->recettes[choix].nbIngredients; i++) {
        getGame()->commandes[getGame()->nbCommandes].recette.ingredients[i] = getGame()->recettes[choix].ingredients[i];
    }
    getGame()->commandes[getGame()->nbCommandes].recette.nbIngredients = getGame()->recettes[choix].nbIngredients;
    getGame()->commandes[getGame()->nbCommandes].recette.nom = getGame()->recettes[choix].nom;

    getGame()->commandes[getGame()->nbCommandes].timer = ((rand() % 2) + 1) * 5 + 45;
    getGame()->nbCommandes++;
    getGame()->commandes[getGame()->nbCommandes].angle = ftofix((float) (rand() % 200 - 100) / 10);
}

void AfficherCommande() {
    if (getGame()->quitting) {
        return;
    }

    int EspaceHorizontalEntreLesRectangle = 30;
    int LargeurRectangle;

    if (getGraphic()->fs) {
        LargeurRectangle = 150;
    } else {
        LargeurRectangle = 90;
    }

    stretch_sprite(getCorrectBuffer(), getGraphic()->textures.bar, 0,(int) (getGraphic()->fs ? (float) getCorrectHeight() - 205 : (float) getCorrectHeight() - 100),getCorrectWidth(), 40);
    stretch_sprite(getCorrectBuffer(), getGraphic()->textures.plancheH, 0,(int) (getGraphic()->fs ? (float) getCorrectHeight() - 180 : (float) getCorrectHeight() - 70),getCorrectWidth(),   (int) (getGraphic()->fs ? 140 * getCorrectRatio() : (float) 140));

    for (int i = 0; i < getGame()->nbCommandes; i++) {
        int xLogo = 10 + (i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle));

        set_clip_rect(getCorrectBuffer(), 0, (int) (getGraphic()->fs ? 1005 : (float) 375), getCorrectWidth(),getCorrectHeight());
        rotate_scaled_sprite(getCorrectBuffer(), getGraphic()->textures.ticket, xLogo,(int) (getGraphic()->fs ? 980 : (float) 340),
                             getGame()->commandes[i].angle,ftofix((float) 110 / (float) getGraphic()->textures.ticket->w));
        set_clip_rect(getCorrectBuffer(), 0, 0, (int) ((float)getCorrectWidth() * getCorrectRatio()), (int)((float)getCorrectHeight() * getCorrectRatio()));

        stretch_sprite(getCorrectBuffer(), getTextureByRecette(getGame()->commandes[i].recette.nom), 37 + xLogo, (int) (getGraphic()->fs ? 900 : (float) 408), (int) (getGraphic()->fs ? 38 * getCorrectRatio() : (float) 38), (int) (getGraphic()->fs ? 38 * getCorrectRatio() : (float) 38));

        int coosX[4] = {25, 90};
        int coosY[4] = {400, 435};
        int coosY2[4] = {972, 1104};

        for (int j = 0; j < getGame()->commandes[i].recette.nbIngredients; j++) {
            BITMAP *ingredient = getTextureByIngredientName(getGame()->commandes[i].recette.ingredients[j].nom);

            if (ingredient != NULL) {
                stretch_sprite(getCorrectBuffer(),
                               getTextureByIngredientName(getGame()->commandes[i].recette.ingredients[j].nom),
                               coosX[(int) j/2] + i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle), (int) (getGraphic()->fs ? (float) coosY2[j%2]: (float) coosY[j%2]), (int) ((float)18 * (float) getCorrectRatio()), (int) ((float)18 * (float) getCorrectRatio()));
            }
        }
    }
}
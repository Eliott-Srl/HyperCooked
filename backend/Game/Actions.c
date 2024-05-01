#include "Actions.h"

void executeFunctionForEveryBlockReachable(s_joueur *joueur, void (*fonction)(s_joueur*, int, int)) {
    for (int k = 0; k < HAUTEUR; k++) {
        for (int s = 0; s < LARGEUR; s++) {
            if (hypotSq((int) joueur->x, (int) joueur->y, getOffsetX() + s * getCorrectCaseSize() + getCorrectCaseSize() / 2, getOffsetY() + k * getCorrectCaseSize() + getCorrectCaseSize() / 2, 4 * getCorrectCaseSize() / 6)) {
                fonction(joueur, k, s);
            }
        }
    }
}

void meuble(s_joueur *joueur, int k, int s) {
    if (getGame()->matrice[k][s].typeMeuble == SOL) {
        return;
    }

    if (joueur->en_main == NOTHING && getGame()->matrice[k][s].objet.nbStockes == 0) {
        return;
    }

    char filename[STRMAX];
    sprintf(filename, "[%s] pour intéragir", strcmp(getGame()->joueurs[0].nom, joueur->nom) == 0 ? "LSHIFT" : "RSHIFT");
    textout_centre_ex(getCorrectBuffer(), font, filename, getOffsetX() + (int) ((float) s * (float) getCorrectCaseSize() + (float) getCorrectCaseSize() / 2), getOffsetY() + (int) ((float) k * (float) getCorrectCaseSize() + (float) getCorrectCaseSize() / 2), makecol(255, 255, 255), -1);
}

BITMAP *getTextureByObjectName(e_objet objet) {
    switch (objet) {
        /*
        case POELE:
            return getGraphic()->textures.poele;
        case MARMITE:
            return getGraphic()->textures.marmite;
        case ASSIETTE:
            return getGraphic()->textures.assiette;
        case EXTINCTEUR:
            return getGraphic()->textures.extincteur;
        */
        default:
            return NULL;
    }
}

void neFaitRien(s_joueur* joueur, int i, int j) {
    // Ne rien faire
}

void planDeTravail(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET && getGame()->matrice[i][j].objet.type == NONE) {
        getGame()->matrice[i][j].objet = joueur->handObjet;
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == INGREDIENT && getGame()->matrice[i][j].objet.nourriture[0].nom == PAS_D_INGREDIENT) {
        getGame()->matrice[i][j].objet.type = STOCKEUR;
        getGame()->matrice[i][j].objet.nourriture[0] = joueur->handIngredient;
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == NOTHING) {
        if (getGame()->matrice[i][j].objet.type == STOCKEUR) {
            joueur->handIngredient = getGame()->matrice[i][j].objet.nourriture[0];
            joueur->en_main = INGREDIENT;
            getGame()->matrice[i][j].objet.nourriture[0].nom = PAS_D_INGREDIENT;
            getGame()->matrice[i][j].objet.type = NONE;
        } else if (getGame()->matrice[i][j].objet.type != NONE) {
            joueur->handObjet = getGame()->matrice[i][j].objet;
            joueur->en_main = OBJET;
            getGame()->matrice[i][j].objet.type = NONE;
        }
    }
}

void plancheADecouper(s_joueur* joueur, int i, int j) {
    /*
    if (joueur->en_main == INGREDIENT) {
        getGame()->matrice[i][j].objet.nourriture[0] = joueur->handIngredient;
        joueur->en_main = NOTHING;
    }
     */
}

void comptoir(s_joueur* joueur, int i, int j) {
    /*
    if (joueur->en_main == OBJET) {
        s_commande commandFind;
        int good = verificationDeLaRecette(&joueur->handObjet, &commandFind);
        joueur->en_main = NOTHING;
        if (good) {
            // TODO: Calculate score
        } else {
            printf("La commande n'était pas bonne");
        }
    }
    */
}

void coffre(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == NOTHING) {
        joueur->en_main = INGREDIENT;
        joueur->handIngredient.cuit = NON;
        joueur->handIngredient.coupe = 0;
        joueur->handIngredient.nom = getGame()->matrice[i][j].objet.nourriture[0].nom;
        joueur->handIngredient.coupable = getGame()->matrice[i][j].objet.nourriture[0].coupable;
        joueur->handIngredient.cuisson = getGame()->matrice[i][j].objet.nourriture[0].cuisson;
    }
}

void plaqueDeCuisson(s_joueur* joueur, int i, int j) {
    /*
    if (joueur->en_main == INGREDIENT
    && ((getGame()->matrice[i][j].objet.type == MARMITE
      && getGame()->matrice[i][j].objet.nbStockes < getGame()->matrice[i][j].objet.stockageMax)
     || (getGame()->matrice[i][j].objet.type == POELE
      && getGame()->matrice[i][j].objet.nbStockes < 1))) {
        getGame()->matrice[i][j].objet.nourriture[getGame()->matrice[i][j].objet.nbStockes] = joueur->handIngredient;
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == OBJET && getGame()->matrice[i][j].objet.type == NONE) {
        getGame()->matrice[i][j].objet = joueur->handObjet;
        joueur->en_main = NOTHING;
    }
    */
}

void poubelle(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == OBJET) {
        joueur->handObjet.nbStockes = 0;
        joueur->en_main = NOTHING;
    }
    joueur->score -= 10;
}

void interact(s_joueur* joueur, int i, int j) {
    getGame()->matrice[i][j].action(joueur, i, j);
}

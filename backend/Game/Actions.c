#include "Actions.h"

void executeFunctionForEveryBlockReachable(s_joueur *joueur, void (*fonction)(s_joueur*, int, int)) {
    for (int k = 0; k < HAUTEUR; k++) {
        for (int s = 0; s < LARGEUR; s++) {
            if (hypotSq((int) joueur->x, (int) joueur->y, (int) getCorrectOffsetX() + s * getCorrectCaseSize() + getCorrectCaseSize() / 2, (int) getCorrectOffsetY() + k * getCorrectCaseSize() + getCorrectCaseSize() / 2, 4 * getCorrectCaseSize() / 6)) {
                fonction(joueur, k, s);
            }
        }
    }
}

void showInteractions(s_joueur *joueur, int k, int s) {
    if (getGame()->matrice[k][s].typeMeuble == SOL) {
        return;
    }

    if (joueur->en_main == NOTHING
     && getGame()->matrice[k][s].objet.nbStockes == 0) {
        return;
    }

    if (joueur->en_main == NOTHING
     && getGame()->matrice[k][s].objet.nbStockes != 0
     && getTime() - getGame()->matrice[k][s].timer < getSupposedTimerByFurnitures(getGame()->matrice[k][s].typeMeuble)) {
        return;
    }

    if (joueur->en_main == INGREDIENT
     && getGame()->matrice[k][s].objet.nbStockes >= getGame()->matrice[k][s].objet.stockageMax) {
        return;
    }

    if (joueur->en_main == INGREDIENT
     && getGame()->matrice[k][s].typeMeuble == PLANCHE_A_DECOUPER
     && getIngredientAfterCutting(joueur->handIngredient.nom) == PAS_D_INGREDIENT) {
        return;
    }

    if (joueur->en_main == OBJET
     && getGame()->matrice[k][s].objet.type != NONE) {
        return;
    }

    char filename[STRMAX];
    sprintf(filename, "[%s] pour intéragir", strcmp(getGame()->joueurs[0].nom, joueur->nom) == 0 ? "LSHIFT" : "RSHIFT");
    textout_centre_ex(getCorrectBuffer(), font, filename, (int) (getCorrectOffsetX() + (float) s * (float) getCorrectCaseSize() + (float) getCorrectCaseSize() / 2), (int) (
            getCorrectOffsetY() + (float) k * (float) getCorrectCaseSize() + (float) getCorrectCaseSize() / 2), makecol(255, 255, 255), -1);
}

BITMAP *getTextureByObjectName(e_objet objet) {
    switch (objet) {
        case POELE:
            return getGraphic()->textures.poele;
        case ASSIETTE:
            return getGraphic()->textures.assiette;
        /*
        case MARMITE:
            return getGraphic()->textures.marmite;
        case EXTINCTEUR:
            return getGraphic()->textures.extincteur;
        */
        default:
            return getGraphic()->textures.invalidTexture;
    }
}

void neFaitRien(s_joueur* joueur, int i, int j) {
    // Ne rien faire
}

void planDeTravail(s_joueur* joueur, int i, int j) {
    s_meuble *meuble = &getGame()->matrice[i][j];

    if (joueur->en_main == OBJET && meuble->objet.type == NONE) {
        meuble->objet = joueur->handObjet;
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == INGREDIENT && meuble->objet.nbStockes == 0) {
        meuble->objet.type = STOCKEUR;
        meuble->objet.nourriture[0] = joueur->handIngredient;
        joueur->en_main = NOTHING;
        meuble->objet.nbStockes = 1;
    } else if (joueur->en_main == NOTHING) {
        if (meuble->objet.type == STOCKEUR) {
            joueur->handIngredient = meuble->objet.nourriture[0];
            joueur->en_main = INGREDIENT;
            meuble->objet.nbStockes = 0;
            meuble->objet.type = NONE;
        } else if (meuble->objet.type != NONE) {
            joueur->handObjet = meuble->objet;
            joueur->en_main = OBJET;
            meuble->objet.type = NONE;
        }
    }
}

void plancheADecouper(s_joueur* joueur, int i, int j) {
    s_meuble *meuble = &getGame()->matrice[i][j];

    if (joueur->en_main == INGREDIENT
     && getIngredientAfterCutting(joueur->handIngredient.nom) != PAS_D_INGREDIENT
     && meuble->timer == -1
     && meuble->objet.nbStockes == 0) {
        meuble->objet.nourriture[0] = joueur->handIngredient;
        joueur->en_main = NOTHING;
        meuble->timer = getTime();
        meuble->objet.nbStockes = 1;
    } else if (joueur->en_main == NOTHING
            && getTime() - meuble->timer > getSupposedTimerByFurnitures(PLANCHE_A_DECOUPER)
            && meuble->objet.nbStockes == 1) {
        joueur->handIngredient.nom = getIngredientAfterCutting(meuble->objet.nourriture[0].nom);
        joueur->en_main = INGREDIENT;
        joueur->handIngredient.coupable = 0;
        joueur->handIngredient.coupe = 1;
        joueur->handIngredient.cuit = 0;
        joueur->handIngredient.cuisson = getCuissonByIngredient(joueur->handIngredient.nom);
        meuble->objet.nourriture[0].nom = PAS_D_INGREDIENT;
        meuble->timer = -1;
        meuble->objet.nbStockes = 0;
    }
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
    s_meuble *meuble = &getGame()->matrice[i][j];

    if (joueur->en_main == INGREDIENT
     && meuble->objet.nbStockes < meuble->objet.stockageMax
     && meuble->objet.type != NONE
     && meuble->objet.type == getFurnitureByCooking(joueur->handIngredient.cuisson)
     && meuble->timer == -1) {
        meuble->objet.nourriture[meuble->objet.nbStockes] = joueur->handIngredient;
        joueur->en_main = NOTHING;
        meuble->objet.nbStockes++;
        if (meuble->objet.nbStockes == meuble->objet.stockageMax) {
            meuble->timer = getTime();
        }
    } else if (joueur->en_main == OBJET
            && meuble->objet.type == NONE
            && meuble->timer == -1) {
        meuble->objet = joueur->handObjet;
        joueur->en_main = NOTHING;
        if (meuble->objet.nbStockes == meuble->objet.stockageMax) {
            meuble->timer = getTime();
        }
    } else if (joueur->en_main == NOTHING
            && getTime() - meuble->timer > getSupposedTimerByFurnitures(meuble->typeMeuble)
            && meuble->objet.type != NONE
            && meuble->objet.nbStockes == meuble->objet.stockageMax) {
        for (int k = 0; k < meuble->objet.nbStockes; k++) {
            meuble->objet.nourriture[k].cuit = 1;
            meuble->objet.nourriture[k].cuisson = NON;
            meuble->objet.nourriture[k].nom = getIngredientAfterCooking(meuble->objet.nourriture[k].nom);
        }
        joueur->handObjet = meuble->objet;
        joueur->en_main = OBJET;
        meuble->objet.nbStockes = 0;
        meuble->timer = -1;
        meuble->objet.type = NONE;
    } else if (joueur->en_main == NOTHING
            && meuble->objet.type != NONE) {
        meuble->timer = -1;
        joueur->handObjet = meuble->objet;
        joueur->en_main = OBJET;
        meuble->objet.type = NONE;
    }
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

#include "Actions.h"

void executeFunctionForEveryBlockReachable(s_game *game, s_joueur *joueur, void (*fonction)(s_game*, s_joueur*, int, int)) {
    for (int k = 0; k < HAUTEUR; k++) {
        for (int s = 0; s < LARGEUR; s++) {
            if (hypotSq((int) joueur->x, (int) joueur->y, (int) getCorrectOffsetX(game) + s * getCorrectCaseSize(game) + getCorrectCaseSize(game) / 2, (int) getCorrectOffsetY(game) + k * getCorrectCaseSize(game) + getCorrectCaseSize(game) / 2, 4 * getCorrectCaseSize(game) / 6)) {
                fonction(game, joueur, k, s);
            }
        }
    }
}

void showInteractions(s_game *game, s_joueur *joueur, int k, int s) {
    if (game->matrice[k][s].typeMeuble == SOL) {
        return;
    }

    if (joueur->en_main == NOTHING
     && game->matrice[k][s].objet.nbStockes == 0
     && game->matrice[k][s].typeMeuble != GENERATEUR_ASSIETTE
     && game->matrice[k][s].objet.type == NONE) {
        return;
    }

    if (joueur->en_main == NOTHING
     && game->matrice[k][s].objet.nbStockes != 0
     && getTime(game) - game->matrice[k][s].timer < getSupposedTimerByFurnitures(game->matrice[k][s].typeMeuble)) {
        return;
    }

    if (joueur->en_main == INGREDIENT
     && game->matrice[k][s].objet.nbStockes >= game->matrice[k][s].objet.stockageMax) {
        return;
    }

    if (joueur->en_main == INGREDIENT
     && game->matrice[k][s].typeMeuble == PLANCHE_A_DECOUPER
     && getIngredientAfterCutting(joueur->handIngredient.nom) == PAS_D_INGREDIENT) {
        return;
    }

    if (joueur->en_main == OBJET
     && game->matrice[k][s].objet.nbStockes == 0
     && (game->matrice[k][s].objet.type != NONE || game->matrice[k][s].typeMeuble == PLANCHE_A_DECOUPER)) {
        return;
    }

    char filename[STRMAX];
    sprintf(filename, "[%s] pour intéragir", strcmp(game->joueurs[0].nom, joueur->nom) == 0 ? "LSHIFT" : "RSHIFT");
    textout_centre_ex(getCorrectBuffer(game), font, filename, (int) (getCorrectOffsetX(game) + (float) s * (float) getCorrectCaseSize(game) + (float) getCorrectCaseSize(game) / 2), (int) (
            getCorrectOffsetY(game) + (float) k * (float) getCorrectCaseSize(game) + (float) getCorrectCaseSize(game) / 2), makecol(255, 255, 255), -1);
}

BITMAP *getTextureByObjectName(s_game *game, e_objet objet) {
    switch (objet) {
        case POELE:
            return game->graphic.textures.poele;
        case ASSIETTE:
            return game->graphic.textures.assiette;
        /*
        case MARMITE:
            return game->graphic.textures.marmite;
        case EXTINCTEUR:
            return game->graphic.textures.extincteur;
        */
        default:
            return game->graphic.textures.invalidTexture;
    }
}

void neFaitRien(s_game *game, s_joueur* joueur, int i, int j) {
    // Ne rien faire
}

void planDeTravail(s_game *game, s_joueur* joueur, int i, int j) {
    s_meuble *meuble = &game->matrice[i][j];

    if (joueur->en_main == OBJET && meuble->objet.type == NONE) {
        meuble->objet = joueur->handObjet;
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == OBJET
            && joueur->handObjet.type == ASSIETTE
            && joueur->handObjet.stockageMax > meuble->objet.nbStockes
            && meuble->objet.nbStockes > 0) {
        joueur->handObjet.nourriture[joueur->handObjet.nbStockes] = meuble->objet.nourriture[meuble->objet.nbStockes - 1];
        joueur->handObjet.nbStockes++;
        meuble->objet.nbStockes--;
    } else if (joueur->en_main == OBJET
            && joueur->handObjet.nbStockes < meuble->objet.stockageMax
            && meuble->objet.type == ASSIETTE
            && joueur->handObjet.nbStockes > 0) {
        meuble->objet.nourriture[meuble->objet.nbStockes] = joueur->handObjet.nourriture[joueur->handObjet.nbStockes - 1];
        meuble->objet.nbStockes++;
        joueur->handObjet.nbStockes--;
    } else if (joueur->en_main == INGREDIENT && meuble->objet.nbStockes == 0 && meuble->objet.type == NONE) {
        meuble->objet.type = STOCKEUR;
        meuble->objet.nourriture[0] = joueur->handIngredient;
        joueur->en_main = NOTHING;
        meuble->objet.nbStockes = 1;
    } else if (joueur->en_main == INGREDIENT && meuble->objet.nbStockes < meuble->objet.stockageMax && meuble->objet.type != NONE) {
        meuble->objet.nourriture[meuble->objet.nbStockes] = joueur->handIngredient;
        joueur->en_main = NOTHING;
        meuble->objet.nbStockes++;
    } else if (joueur->en_main == NOTHING) {
        if (meuble->objet.type == STOCKEUR) {
            joueur->handIngredient = meuble->objet.nourriture[0];
            joueur->en_main = INGREDIENT;
            meuble->objet.nbStockes = 0;
            meuble->objet.type = NONE;
            meuble->objet.nbStockes = 0;
        } else if (meuble->objet.type != NONE) {
            joueur->handObjet = meuble->objet;
            joueur->en_main = OBJET;
            meuble->objet.type = NONE;
            meuble->objet.nbStockes = 0;
        }
    }
}

void plancheADecouper(s_game *game, s_joueur* joueur, int i, int j) {
    s_meuble *meuble = &game->matrice[i][j];

    if (joueur->en_main == INGREDIENT
     && getIngredientAfterCutting(joueur->handIngredient.nom) != PAS_D_INGREDIENT
     && meuble->timer == -1
     && meuble->objet.nbStockes == 0) {
        meuble->objet.nourriture[0] = joueur->handIngredient;
        joueur->en_main = NOTHING;
        meuble->timer = getTime(game);
        meuble->objet.nbStockes = 1;
    } else if (joueur->en_main == NOTHING
            && getTime(game) - meuble->timer > getSupposedTimerByFurnitures(PLANCHE_A_DECOUPER)
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
    } else if (joueur->en_main == OBJET && joueur->handObjet.type == ASSIETTE
            && getTime(game) - meuble->timer > getSupposedTimerByFurnitures(PLANCHE_A_DECOUPER)
            && meuble->objet.nbStockes == 1
            && joueur->handObjet.nbStockes < joueur->handObjet.stockageMax) {
        meuble->objet.nourriture[0].nom = getIngredientAfterCutting(meuble->objet.nourriture[0].nom);
        meuble->objet.nourriture[0].cuit = 0;
        meuble->objet.nourriture[0].coupe = 1;
        meuble->objet.nourriture[0].coupable = (getIngredientAfterCutting(meuble->objet.nourriture[0].nom) != PAS_D_INGREDIENT);
        meuble->objet.nourriture[0].cuisson = getCuissonByIngredient(meuble->objet.nourriture[0].nom);
        joueur->handObjet.nourriture[joueur->handObjet.nbStockes] = meuble->objet.nourriture[0];
        joueur->handObjet.nbStockes++;
        meuble->objet.type = NONE;
        meuble->timer = -1;
        meuble->objet.nbStockes = 0;
    }
}

void comptoir(s_game *game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET) {
        s_commande commandFind;
        int good = verificationDeLaRecette(game, &joueur->handObjet, &commandFind);
        joueur->en_main = NOTHING;
        if (good) {
            enleverCommande(game, &commandFind);
            game->score += (getTime(game) - commandFind.debut) / 1000;
        } else {
            joueur->score -= 10;
            allegro_message("La commande n'était pas bonne !");
        }
    }
}

void coffre(s_game *game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == NOTHING) {
        joueur->en_main = INGREDIENT;
        joueur->handIngredient.cuit = NON;
        joueur->handIngredient.coupe = 0;
        joueur->handIngredient.nom = game->matrice[i][j].objet.nourriture[0].nom;
        joueur->handIngredient.coupable = game->matrice[i][j].objet.nourriture[0].coupable;
        joueur->handIngredient.cuisson = game->matrice[i][j].objet.nourriture[0].cuisson;
    }
}

void plaqueDeCuisson(s_game *game, s_joueur* joueur, int i, int j) {
    s_meuble *meuble = &game->matrice[i][j];

    if (joueur->en_main == INGREDIENT
     && meuble->objet.nbStockes < meuble->objet.stockageMax
     && meuble->objet.type != NONE
     && meuble->objet.type == getFurnitureByCooking(joueur->handIngredient.cuisson)
     && meuble->timer == -1
     && meuble->objet.nourriture[0].cuit == 0) {
        meuble->objet.nourriture[meuble->objet.nbStockes] = joueur->handIngredient;
        joueur->en_main = NOTHING;
        meuble->objet.nbStockes++;
        if (meuble->objet.nbStockes == meuble->objet.stockageMax) {
            meuble->timer = getTime(game);
        }
    } else if (joueur->en_main == OBJET
            && (joueur->handObjet.type == POELE || joueur->handObjet.type == MARMITE)
            && meuble->objet.type == NONE
            && meuble->timer == -1) {
        meuble->objet = joueur->handObjet;
        joueur->en_main = NOTHING;
        if (meuble->objet.nbStockes == meuble->objet.stockageMax) {
            meuble->timer = getTime(game);
        }
    } else if (joueur->en_main == OBJET
            && meuble->objet.type == ASSIETTE) {
        meuble->timer = -1;
    } else if ((joueur->en_main == NOTHING || (joueur->en_main == OBJET && joueur->handObjet.type == ASSIETTE))
            && getTime(game) - meuble->timer > getSupposedTimerByFurnitures(meuble->typeMeuble)
            && meuble->objet.type != NONE
            && meuble->objet.nbStockes == meuble->objet.stockageMax) {
        meuble->objet.nourriture[0].nom = getIngredientAfterCooking(meuble->objet.nourriture[0].nom);
        meuble->objet.nourriture[0].cuit = 1;
        meuble->objet.nourriture[0].cuisson = NON;
        meuble->objet.nourriture[0].coupe = (getIngredientAfterCutting(meuble->objet.nourriture[0].nom) != PAS_D_INGREDIENT);
        meuble->objet.nbStockes = 1;

        if (joueur->en_main == NOTHING) {
            joueur->handObjet = meuble->objet;
            joueur->en_main = OBJET;
            meuble->objet.type = NONE;
        } else {
            if (joueur->handObjet.nbStockes + 1 > joueur->handObjet.stockageMax) {
                meuble->timer = -1;
                return;
            }
            joueur->handObjet.nourriture[joueur->handObjet.nbStockes] = meuble->objet.nourriture[0];
            joueur->handObjet.nbStockes++;
        }
        meuble->objet.nbStockes = 0;
        meuble->timer = -1;
    } else if (joueur->en_main == NOTHING
            && meuble->objet.type != NONE) {
        meuble->timer = -1;
        joueur->handObjet = meuble->objet;
        joueur->en_main = OBJET;
        meuble->objet.type = NONE;
    }
}

void poubelle(s_game *game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == OBJET) {
        joueur->handObjet.nbStockes = 0;
        joueur->en_main = OBJET;
    }
    joueur->score -= 10;
}

void generateurAssiette(s_game *game, s_joueur *joueur, int i, int j) {
    if (joueur->en_main == NOTHING) {
        joueur->en_main = OBJET;
        joueur->handObjet = game->matrice[i][j].objet;
        joueur->handObjet.nbStockes = 0;
        game->matrice[i][j].objet.type = ASSIETTE;
    }
}

void interact(s_game *game, s_joueur* joueur, int i, int j) {
    game->matrice[i][j].action(game, joueur, i, j);
}

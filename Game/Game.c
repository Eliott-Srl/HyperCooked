#include "Game.h"

int verificationDeLaRecette(s_game* game, s_objet* plat, s_commande* commandeFind) {
    int a;
    for (int i = 0; i < game->nbCommandes; i++) {
        *commandeFind = game->commandes[i];
        if (commandeFind->recette.nbIngredients == plat->nbStockes) {
            a = 0;
            for (int j = 0; j < plat->nbStockes; j++) {
                if(plat->nourriture[j].nom == commandeFind->recette.ingredients[0].nom
                && plat->nourriture[j].coupe == commandeFind->recette.ingredients[0].coupe
                && plat->nourriture[j].cuit == commandeFind->recette.ingredients[0].cuit) {
                    a++;
                }
            }

            if (a == plat->nbStockes) {
                return 1;
            }
        }
    }
    return 0;
}

void neFaitRien(s_game* game, s_joueur* joueur) {
    return;
}

void planDeTravail(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET) {
        game->matrice[i][j].objet = joueur->hand_objet;
        joueur->en_main = NOTHING;
    }
}

void plancheADecouper(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        game->matrice[i][j].objet.nourriture[0] = joueur->hand_ingredient.type;
        joueur->en_main = NOTHING;
    }
}

void comptoir(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET) {
        s_commande commandFind;
        int good = verificationDeLaRecette(game, &joueur->hand_objet, &commandFind);
        joueur->en_main = NOTHING;
        if (good) {
            // TODO: Calculate score
        } else {
            printf("La commande n'était pas bonne");
        }
    }
}

void coffre(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == NOTHING) {
        joueur->en_main = INGREDIENT;
        joueur->hand_ingredient.en_main = 1;
        joueur->hand_ingredient.type.cuit = NON;
        joueur->hand_ingredient.type.coupe = 0;
        joueur->hand_ingredient.type.nom = game->matrice[i][j].objet.nourriture[0].nom;
        joueur->hand_ingredient.type.coupable = game->matrice[i][j].objet.nourriture[0].coupable;
        joueur->hand_ingredient.type.cuisson = game->matrice[i][j].objet.nourriture[0].cuisson;
    }
}

void plaqueDeCuisson(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        if (game->matrice[i][j].objet.type == MARMITE && game->matrice[i][j].objet.nbStockes < game->matrice[i][j].objet.stockageMax) {
            game->matrice[i][j].objet.nourriture[game->matrice[i][j].objet.nbStockes] = joueur->hand_ingredient.type;
            joueur->en_main = NONE;
        } else if (game->matrice[i][j].objet.type == POELE && game->matrice[i][j].objet.nbStockes < 1) {
            game->matrice[i][j].objet.nourriture[game->matrice[i][j].objet.nbStockes] = joueur->hand_ingredient.type;
            joueur->en_main = NONE;
        }
    } else if (joueur->en_main == OBJET) {
        if (game->matrice[i][j].objet.type == NONE) {
            game->matrice[i][j].objet = joueur->hand_objet;
            joueur->en_main = NONE;
        }
    }
}

void poubelle(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        joueur->en_main = NONE;
    } else if (joueur->en_main == OBJET) {
        joueur->hand_objet.nbStockes = 0;
        joueur->en_main = NONE;
    }
}
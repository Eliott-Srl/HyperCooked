#include "Actions.h"

void deplacerPersonnage(s_joueur* joueur, int veloX, int veloY) {
    s_game *game = getGame();
    // Nouvelles positions potentielles
    int newX = joueur->pos.x + veloX;
    int newY = joueur->pos.y + veloY;

    // Vérifier les collisions avec les meubles
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (collisions(newX, newY, joueur->dimensions, joueur->dimensions, i * getCorrectCaseSize(), j * getCorrectCaseSize(), getCorrectCaseSize(), getCorrectCaseSize())) {
                // Il y a une collision, ne pas bouger
                return;
            }
        }
    }

    s_joueur *autre_joueur;
    // Vérifier les collisions avec les autres personnages
    if (game->joueurs[0].couleur.r == joueur->couleur.r && game->joueurs[0].couleur.g == joueur->couleur.g && game->joueurs[0].couleur.b == joueur->couleur.b) {
        autre_joueur = &game->joueurs[1];
    } else {
        autre_joueur = &game->joueurs[0];
    }

    if (collisions(newX, newY, joueur->dimensions, joueur->dimensions, autre_joueur->pos.x, autre_joueur->pos.y, autre_joueur->dimensions, autre_joueur->dimensions)) {
        // Il y a une collision avec un autre personnage, ne pas bouger
        return;
    }

    // Déplacer le personnage aux nouvelles positions
    joueur->pos.x = newX;
    joueur->pos.y = newY;
}

void deplacerPersonnages() {
    s_coo velo_perso1 = {0, 0};
    s_coo velo_perso2 = {0, 0};

    if (key[KEY_Z]) {
        velo_perso1.y = -1;
    }
    if (key[KEY_S]) {
        velo_perso1.y = 1;
    }
    if (key[KEY_Q]) {
        velo_perso1.x = -1;
    }
    if (key[KEY_D]) {
        velo_perso1.x = 1;
    }
    if (key[KEY_UP]) {
        velo_perso2.y = -1;
    }
    if (key[KEY_DOWN]) {
        velo_perso2.y = 1;
    }
    if (key[KEY_LEFT]) {
        velo_perso2.x = -1;
    }
    if (key[KEY_RIGHT]) {
        velo_perso2.x = 1;
    }

    deplacerPersonnage(&getGame()->joueurs[0], velo_perso1.x, velo_perso1.y);
    deplacerPersonnage(&getGame()->joueurs[1], velo_perso2.x, velo_perso2.y);
}

void neFaitRien(s_joueur* joueur) {
    return;
}

void planDeTravail(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET) {
        getGame()->matrice[i][j].objet = joueur->handObjet;
        joueur->en_main = NOTHING;
    }
}

void plancheADecouper(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        getGame()->matrice[i][j].objet.nourriture[0] = joueur->handIngredient.type;
        joueur->en_main = NOTHING;
    }
}

void comptoir(s_joueur* joueur, int i, int j) {
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
}

void coffre(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == NOTHING) {
        joueur->en_main = INGREDIENT;
        joueur->handIngredient.enMain = 1;
        joueur->handIngredient.type.cuit = NON;
        joueur->handIngredient.type.coupe = 0;
        joueur->handIngredient.type.nom = getGame()->matrice[i][j].objet.nourriture[0].nom;
        joueur->handIngredient.type.coupable = getGame()->matrice[i][j].objet.nourriture[0].coupable;
        joueur->handIngredient.type.cuisson = getGame()->matrice[i][j].objet.nourriture[0].cuisson;
    }
}

void plaqueDeCuisson(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        if (getGame()->matrice[i][j].objet.type == MARMITE && getGame()->matrice[i][j].objet.nbStockes < getGame()->matrice[i][j].objet.stockageMax) {
            getGame()->matrice[i][j].objet.nourriture[getGame()->matrice[i][j].objet.nbStockes] = joueur->handIngredient.type;
            joueur->en_main = NONE;
        } else if (getGame()->matrice[i][j].objet.type == POELE && getGame()->matrice[i][j].objet.nbStockes < 1) {
            getGame()->matrice[i][j].objet.nourriture[getGame()->matrice[i][j].objet.nbStockes] = joueur->handIngredient.type;
            joueur->en_main = NONE;
        }
    } else if (joueur->en_main == OBJET) {
        if (getGame()->matrice[i][j].objet.type == NONE) {
            getGame()->matrice[i][j].objet = joueur->handObjet;
            joueur->en_main = NONE;
        }
    }
}

void poubelle(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        joueur->en_main = NONE;
    } else if (joueur->en_main == OBJET) {
        joueur->handObjet.nbStockes = 0;
        joueur->en_main = NONE;
    }
}
#include "Game.h"
#include <time.h>
#include <stdio.h>

int timer() {
    int seconde = 90;
    int score = 0;

    // Obtenir le temps actuel
    time_t start_time = time(NULL);
    time_t current_time = 0;
    int elapsed_time = 0;

    // Obtenir le temps actuel
    current_time = time(NULL);

    // Calculer le temps écoulé en secondes
    elapsed_time = difftime(current_time, start_time);
}

// Fonction pour déplacer un personnage tout en évitant les collisions avec les meubles
void deplacerPersonnage(s_game* game, s_joueur* joueur, int dx, int dy) {
    int tailleCase = 10;
    // Nouvelles positions potentielles
    int newX = joueur->pos.x + dx;
    int newY = joueur->pos.y + dy;

    // Vérifier les collisions avec les meubles
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (collisions(newX, newY, joueur->dimensions, joueur->dimensions, i * tailleCase, j * tailleCase, tailleCase, tailleCase)) {
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

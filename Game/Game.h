#ifndef HYPERCOOKED_GAME_H
#define HYPERCOOKED_GAME_H

#include "../recettes/Recettes.h"

typedef struct {
    s_color couleur;
    char nom[STRMAX];
    s_coo pos;
    int en_main;
    s_ingredient_physique *hand_ingredient;
    //s_objet *hand_objet;
} s_joueur;

typedef struct {
    s_recette recettes[NB_RECETTES_MAX];
    int nb_recettes;
    s_commande commandes[NB_COMMANDES_MAX];
    s_joueur joueurs[2];
    int score;
} s_game;

#endif //HYPERCOOKED_GAME_H

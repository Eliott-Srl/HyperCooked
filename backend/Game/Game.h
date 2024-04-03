#ifndef HYPERCOOKED_GAME_H
#define HYPERCOOKED_GAME_H

#include "../Commandes/Recettes.h"
#include "../Matrice/meubles.h"
#include "../backend.h"

typedef enum {
    NOTHING,
    INGREDIENT,
    OBJET
} e_typeEnMain;

typedef struct {
    s_color couleur;
    char nom[STRMAX];
    s_coo pos;
    int dimensions;
    int en_main;
    s_ingredient_physique hand_ingredient;
    s_objet hand_objet;
} s_joueur;

typedef struct {
    s_recette recettes[NB_RECETTES_MAX];
    int nb_recettes;
    s_commande commandes[NB_COMMANDES_MAX];
    int nbCommandes;
    s_meuble matrice[HAUTEUR][LARGEUR];
    s_joueur joueurs[2];
    int score;
    int temps;
} s_game;

#endif //HYPERCOOKED_GAME_H

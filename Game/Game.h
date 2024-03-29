#ifndef HYPERCOOKED_GAME_H
#define HYPERCOOKED_GAME_H

#include "../Recettes/Recettes.h"
#include "../Matrice/meubles.h"

typedef enum {
    NOTHING,
    INGREDIENT,
    OBJET
} e_typeEnMain;

typedef struct {
    s_color couleur;
    char nom[STRMAX];
    s_coo pos;
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
    int taille;
    s_joueur joueurs[2];
    int score;
    int temps;
} s_game;

void deplacerPersonnage(s_game *game, s_joueur *joueur,int dx, int dy);
void creationJoueurs();
int timer();
void Collision();
int verificationDeLaRecette(s_game* game, s_objet* plat, s_commande* commandeFind);

#endif //HYPERCOOKED_GAME_H

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
    int temps;
} s_game;

// Structure représentant un personnage
typedef struct {
    int x; // Position x du personnage
    int y; // Position y du personnage
    int largeur; // Largeur du personnage
    int hauteur; // Hauteur du personnage
} Personnage;

// Structure représentant un meuble
typedef struct {
    TypeMeuble type; // Type du meuble
    int x; // Position x du meuble
    int y; // Position y du meuble
    int largeur; // Largeur du meuble
    int hauteur; // Hauteur du meuble
} Meuble;

void creationJoueurs();

void collision ();

void deplacerPersonnage(Personnage *personnage, int dx, int dy, Meuble meubles[], int nbMeubles, Personnage autresPersonnages[], int nbAutresPersonnages);


void afficherMatrice(int *tab);



#endif //HYPERCOOKED_GAME_H

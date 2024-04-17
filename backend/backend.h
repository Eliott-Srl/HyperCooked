#ifndef HYPERCOOKED_BACKEND_H
#define HYPERCOOKED_BACKEND_H

#define STRMAX 120
#define HAUTEUR 12
#define LARGEUR 20
#define NB_RECETTES_MAX 10
#define NB_INGREDIENTS_MAX 10
#define NB_COMMANDES_MAX 5

typedef struct {
    int x;
    int y;
} s_coo;

typedef struct {
    int r;
    int g;
    int b;
} s_color;

typedef enum {
    SALADE,
    PAIN,
    TOMATE,
    STEAK,
    OEUF,
    POTATO,
} e_ingredients;

typedef enum {
    NON,
    A_LA_MARMITE,
    A_LA_POELE
} e_cuisson;

typedef struct {
    e_ingredients nom;
    e_cuisson cuisson;
    int cuit;
    int coupable;
    int coupe;
} s_ingredient;

typedef struct {
    char nom[STRMAX];
    s_ingredient ingredients[NB_INGREDIENTS_MAX];
    int nbIngredients;
} s_recette;

typedef struct {
    int timer;
    s_recette recette;
} s_commande;

typedef struct {
    s_ingredient type;
    int en_main;
    // here we need to add a pointer to the texture
} s_ingredient_physique;

typedef enum {
    SOL,
    PLAN_DE_TRAVAIL,
    PLANCHE_A_DECOUPER,
    COMPTOIR,
    COFFRE,
    PLAQUE_A_CUISSON,
    POUBELLE
} e_meubles;

typedef enum {
    NONE,
    POELE,
    MARMITE,
    ASSIETTE,
    EXTINCTEUR,
    STOCKEUR
} e_objet;

typedef enum {
    SANS = 0,
    UN_SLOT = 1,
    TROIS_SLOTS = 3,
    RECETTE = 10
} e_stockage;

typedef struct {
    e_objet type;
    s_ingredient nourriture[10];
    e_stockage stockageMax;
    int nbStockes;
} s_objet;

typedef struct {
    e_meubles type_meuble;
    s_objet objet;
    void (*action)();
} s_meuble;


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
    s_commande commandes[NB_COMMANDES_MAX];
    int nbCommandes;
    int temps;
    int score;
} s_partie;

typedef struct {
    s_meuble matrice[HAUTEUR][LARGEUR];
    s_joueur joueurs[2];
    s_partie partie;
    int partie_actuelle;
    s_recette recettes[NB_RECETTES_MAX];
    int nb_recettes;
} s_game;

#include "Utils/Utils.h"
#include "Matrice/meubles.h"
#include "Commandes/Recettes.h"
#include "Game/Game.h"
#include "allezgros/Allezgros.h"

#endif //HYPERCOOKED_BACKEND_H

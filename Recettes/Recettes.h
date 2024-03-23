#ifndef HYPERCOOKED_RECETTES_H
#define HYPERCOOKED_RECETTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../types.h"
#include "../Game/Game.h"

#define NB_RECETTES_MAX 10
#define NB_INGREDIENTS_MAX 10
#define NB_COMMANDES_MAX 5

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
    s_ingredient type;
    int en_main;
    // here we need to add a pointer to the texture
} s_ingredient_physique;

s_recette *load();
void freeRecettes(s_recette *recettes);
void crearecettes(s_game *game);

#endif //HYPERCOOKED_RECETTES_H

#ifndef HYPERCOOKED_RECETTES_H
#define HYPERCOOKED_RECETTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"

#define NB_RECETTES_MAX 10
#define NB_INGREDIENTS_MAX 10
#define NB_COMMANDES_MAX 5

typedef enum {
    SALADE,
    PAIN,
    TOMATE,
    STEAK
} e_ingredients;

typedef enum {
    NON,
    MARMITE,
    POELE
} e_cuisson;

typedef struct {
    e_ingredients nom;
    e_cuisson cuisson;
    int coupable;
    int coupe;
} s_ingredient;

typedef struct {
    char nom[STRMAX];
    e_ingredients ingredients[NB_INGREDIENTS_MAX];
} s_recette;

typedef struct {
    int timer;
    s_recette recette;
} s_commande;

typedef struct {
    s_ingredient type;
    int en_main;
    s_coo pos;
    // here we need to add a pointer to the texture
} s_ingredient_physique;

s_recette *load();
void freeRecettes(s_recette *recettes);

#endif //HYPERCOOKED_RECETTES_H

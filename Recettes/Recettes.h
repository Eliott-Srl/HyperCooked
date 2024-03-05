#ifndef HYPERCOOKED_RECETTES_H
#define HYPERCOOKED_RECETTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"

#define NB_RECETTES_MAX 10
#define NB_INGREDIENTS_MAX 10

typedef enum {
    SALADE,
    PAIN,
    TOMATE,
    STEAK
} e_ingredients;

typedef enum {
    PASCUIT,
    SAIGNANT,
    CUIT,
    TROPCUIT,
    CRAME
} e_cuisson;

typedef struct {
    char nom[STRMAX];
    e_ingredients ingredients[NB_INGREDIENTS_MAX];
} s_recette;

typedef struct {
    int x;
    int y;
} coo;

typedef struct {
    s_recette recettes[NB_RECETTES_MAX];
} s_game;

void load();

#endif //HYPERCOOKED_RECETTES_H

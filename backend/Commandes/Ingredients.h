#ifndef HYPERCOOKED_INGREDIENTS_H
#define HYPERCOOKED_INGREDIENTS_H

#include "../backend.h"

BITMAP *getTextureByIngredientName(e_ingredients ingredients);
int coupableByIngredient(e_ingredients ingredient);
int cuissonByIngredient(e_ingredients ingredient);

#endif //HYPERCOOKED_INGREDIENTS_H

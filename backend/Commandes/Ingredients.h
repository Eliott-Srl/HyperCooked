#ifndef HYPERCOOKED_INGREDIENTS_H
#define HYPERCOOKED_INGREDIENTS_H

#include "../backend.h"

BITMAP *getTextureByIngredientName(s_game *game, e_ingredients ingredients);
int getCuissonByIngredient(e_ingredients ingredient);
int getIngredientAfterCooking(e_ingredients ingredient);
int getFurnitureByCooking(e_cuisson cuisson);
int getIngredientAfterCutting(e_ingredients ingredient);

#endif //HYPERCOOKED_INGREDIENTS_H

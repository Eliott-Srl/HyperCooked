#ifndef HYPERCOOKED_RECETTES_H
#define HYPERCOOKED_RECETTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../backend.h"

BITMAP *getTextureByRecette(s_game *game, e_recettes recette);
void loadRecipes(s_game *game);
int verificationDeLaRecette(s_game *game, s_objet *plat, s_commande *commandeFind);

#endif //HYPERCOOKED_RECETTES_H

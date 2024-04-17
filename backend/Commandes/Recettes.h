#ifndef HYPERCOOKED_RECETTES_H
#define HYPERCOOKED_RECETTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../backend.h"

void loadRecipes(s_game* game);
void freeRecettes(s_recette *recettes);
void newRecette(s_game *game);
int verificationDeLaRecette(s_game* game, s_objet* plat, s_commande* commandeFind);

#endif //HYPERCOOKED_RECETTES_H

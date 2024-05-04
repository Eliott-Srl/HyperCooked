#ifndef HYPERCOOKED_RECETTES_H
#define HYPERCOOKED_RECETTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../backend.h"

BITMAP *getTextureByRecette(e_recettes recette);
void loadRecipes();
int verificationDeLaRecette(s_objet *plat, s_commande *commandeFind);

#endif //HYPERCOOKED_RECETTES_H

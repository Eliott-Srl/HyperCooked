#ifndef HYPERCOOKED_RECETTES_H
#define HYPERCOOKED_RECETTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../backend.h"

void loadRecipes();
void freeRecettes(s_recette *recettes);
void newRecette();
int verificationDeLaRecette(s_objet *plat, s_commande *commandeFind);

#endif //HYPERCOOKED_RECETTES_H

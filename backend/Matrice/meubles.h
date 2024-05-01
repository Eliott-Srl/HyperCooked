#ifndef HYPERCOOKED_MEUBLES_H
#define HYPERCOOKED_MEUBLES_H

#include "../backend.h"
#include "meubles.h"
#include "../Commandes/Recettes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficherMatrice();
BITMAP *getTextureByFurnitureName(e_meubles meuble);
void initialiserMatrice(const char* file);
void hc_afficher_matrice();

#endif //HYPERCOOKED_MEUBLES_H

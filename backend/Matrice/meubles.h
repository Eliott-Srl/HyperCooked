#ifndef HYPERCOOKED_MEUBLES_H
#define HYPERCOOKED_MEUBLES_H

#include "../backend.h"
#include "meubles.h"
#include "../Commandes/Recettes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BITMAP *getTextureByFurnitureName(e_meubles meuble);
int getSupposedTimerByFurnitures(e_meubles meuble);
int getSlotByFurniture(e_meubles meuble);
void afficherMatrice();
void initialiserMatrice(const char* file);
void hc_afficher_matrice();

#endif //HYPERCOOKED_MEUBLES_H

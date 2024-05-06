#ifndef HYPERCOOKED_MEUBLES_H
#define HYPERCOOKED_MEUBLES_H

#include "../backend.h"
#include "meubles.h"
#include "../Commandes/Recettes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BITMAP *getTextureByFurnitureName(s_game *game, e_meubles meuble);
int getSupposedTimerByFurnitures(e_meubles meuble);
int getSlotsByFurniture(e_objet objet);
void *getActionByFurnitureName(e_meubles meuble);
void afficherMatrice(s_game *game);
void initialiserMatrice(s_game *game, const char* file);
void hc_afficher_matrice(s_game *game);

#endif //HYPERCOOKED_MEUBLES_H

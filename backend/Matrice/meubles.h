#ifndef HYPERCOOKED_MEUBLES_H
#define HYPERCOOKED_MEUBLES_H

#include "../backend.h"
#include "meubles.h"
#include "../Commandes/Recettes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficherMatrice(s_meuble tab[HAUTEUR][LARGEUR]);
void initialiserMatrice(s_meuble matrice_dynamique[HAUTEUR][LARGEUR], const char* file);

#endif //HYPERCOOKED_MEUBLES_H

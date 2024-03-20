#ifndef HYPERCOOKED_COMMANDES_H
#define HYPERCOOKED_COMMANDES_H
#include "../Recettes/Recettes.h"

typedef struct {
    int timer;
    s_recette recette;
} s_commande;

void genereCommande();

#endif //HYPERCOOKED_COMMANDES_H

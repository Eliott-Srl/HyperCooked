#ifndef HYPERCOOKED_COMMANDES_H
#define HYPERCOOKED_COMMANDES_H
#include "../Recettes/Recettes.h"

typedef struct {
    int timer;
    int satisfaction; //satisfaction du client de 1 à 5 -> utile pour calculer le score
    s_recette recette;
} s_commande;

void genereCommande();

#endif //HYPERCOOKED_COMMANDES_H

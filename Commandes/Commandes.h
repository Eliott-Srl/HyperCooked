#ifndef HYPERCOOKED_COMMANDES_H
#define HYPERCOOKED_COMMANDES_H
#include "../Recettes/Recettes.h"

typedef struct {
    int timer;
    int satisfaction; //satisfaction du client de 1 à 5 -> utile pour calculer le score
    s_recette recette;
} s_commande;

void genereCommande(){
    int i, choix_recette;
    s_recette stckrecette[NB_RECETTES_MAX];
    s_commande commande;
    stckrecette[NB_RECETTES_MAX] = *load();

    srand(time(NULL));
    choix_recette = rand() % NB_INGREDIENTS_MAX;
    while(i <= choix_recette){
        stckrecette[i];
        i++;
    }
    commande.recette.nom = stckrecette[NB_RECETTES_MAX].nom;
    commande.recette.ingredients = stckrecette[NB_RECETTES_MAX].ingredients;
}

int verificationDeLaRecette(s_game* game, s_objet* plat, s_commande* commandeFind) {
    int a;
    for (int i = 0; i < game->nbCommandes; i++) {
        *commandeFind = game->commandes[i];
        if (commandeFind->recette.nbIngredients == plat->nbStockes) {
            a = 0;
            for (int j = 0; j < plat->nbStockes; j++) {
                if(plat->nourriture[j].nom == commandeFind->recette.ingredients[0].nom
                   && plat->nourriture[j].coupe == commandeFind->recette.ingredients[0].coupe
                   && plat->nourriture[j].cuit == commandeFind->recette.ingredients[0].cuit) {
                    a++;
                } else {
                    break;
                }
            }

            if (a == plat->nbStockes) {
                return 1;
            }
        }
    }
    return 0;
}

#endif //HYPERCOOKED_COMMANDES_H

#include "Commandes.h"

void newCommande() {
    int choix = rand() % (getGame()->nbRecettes - 1);
    getGame()->commandes[getGame()->nbCommandes].recette = getGame()->recettes[choix];
    printf("Nouvelle recette: %s\n", getGame()->commandes[getGame()->nbCommandes].recette.nom);
    getGame()->nbCommandes++;
}
#include "meubles.h"
#include <stdio.h>

void afficherMatrice(int tab[HAUTEUR][LARGEUR]) {
    int meuble [] = { };

    for (int h = 0; h < HAUTEUR; h++) {
        for (int l = 0; l < LARGEUR; l++) {
            printf("%c", meuble[tab[h][l]]);
        }
        printf("\n");
    }
}





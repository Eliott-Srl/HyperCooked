#include "Recettes/Recettes.h"
#include "Commandes/Commandes.h"

int main() {
    s_matrice *a = (s_matrice *) malloc(sizeof(s_matrice));

    cacatoutmou(a);
    afficherMatrice(a);
     return 0;
} END_OF_MAIN();
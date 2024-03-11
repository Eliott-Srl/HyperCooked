#include "Recettes/Recettes.h"
#include <allegro.h>
#include "Matrice/meubles.h"

int main() {
    s_matrice *a = (s_matrice *) malloc(sizeof(s_matrice));

    cacatoutmou(a);
    afficherMatrice(a);
     return 0;
} END_OF_MAIN();
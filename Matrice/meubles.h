#ifndef HYPERCOOKED_MEUBLES_H
#define HYPERCOOKED_MEUBLES_H


#define HAUTEUR 20
#define LARGEUR 12


typedef enum {
    POELE,
    MARMITE,
    PLAN_DE_TRAVAIL,
    ASSIETTE,
    EXTINCTEUR,
}e_meubles;

typedef struct {
    e_meubles matrice[12][20];
}s_matrice;

void afficherMatrice(int tab[HAUTEUR][LARGEUR]);


#endif //HYPERCOOKED_MEUBLES_H

#ifndef HYPERCOOKED_MEUBLES_H
#define HYPERCOOKED_MEUBLES_H


#define HAUTEUR 12
#define LARGEUR 20


typedef enum {
    SOL,
    PLAN_DE_TRAVAIL,
    PLANCHE_A_DECOUPER,
    COMPTOIR,
    COFFRE,
    PLAQUE_A_CUISSON,
    POUBELLE
} e_meubles;

typedef enum {
    NONE,
    POELE,
    MARMITE,
    ASSIETTE,
    EXTINCTEUR
} e_objet;

typedef struct {
    e_meubles type_meuble;
    e_objet type_objet;
} s_meuble;

typedef struct {
s_meuble matrice[HAUTEUR][LARGEUR];
} s_matrice;



void afficherMatrice(s_matrice *tab);

void cacatoutmou(s_matrice *matrice_dynamique);

#endif //HYPERCOOKED_MEUBLES_H

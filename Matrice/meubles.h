#ifndef HYPERCOOKED_MEUBLES_H
#define HYPERCOOKED_MEUBLES_H


#define HAUTEUR 12
#define LARGEUR 20

#include "../Recettes/Recettes.h"
#include "../Commandes/Commandes.h"
#include "../Game/Game.h"

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
    EXTINCTEUR,
    STOCKEUR
} e_objet;

typedef enum {
    SANS = 0,
    UN_SLOT = 1,
    TROIS_SLOTS = 3,
    RECETTE = 10
} e_stockage;

typedef struct {
    e_objet type;
    s_ingredient nourriture[10];
    e_stockage stockageMax;
    int nbStockes;
} s_objet;

typedef struct {
    e_meubles type_meuble;
    s_objet objet;
    void (*action)();
} s_meuble;

void afficherMatrice(s_meuble tab[HAUTEUR][LARGEUR]);
void cacatoutmou(s_meuble matrice_dynamique[HAUTEUR][LARGEUR]);

#endif //HYPERCOOKED_MEUBLES_H

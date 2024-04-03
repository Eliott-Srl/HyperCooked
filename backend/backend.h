#ifndef HYPERCOOKED_BACKEND_H
#define HYPERCOOKED_BACKEND_H

#include "Game/Game.h"
#include "Commandes/Recettes.h"
#include "Matrice/meubles.h"
#include "Commandes/Commandes.h"

#define STRMAX 120

typedef struct {
    int x;
    int y;
} s_coo;

typedef struct {
    int r;
    int g;
    int b;
} s_color;

#include "Utils/Utils.h"
int collisions(int x1, int y1, int l1, int h1, int x2, int y2, int l2, int h2);

#include "Game/Game.h"
void deplacerPersonnage(s_game game, s_joueur *joueur, int dx, int dy);
void genereCommande();
int timer();

#include "Matrice/meubles.h"
void afficherMatrice(s_meuble tab[HAUTEUR][LARGEUR]);
void initialiserMatrice(s_meuble matrice_dynamique[12][20]);

#include "Commandes/Recettes.h"
s_recette *load();
void freeRecettes(s_recette *recettes);
void crearecettes(s_game *game);
int verificationDeLaRecette(s_game* game, s_objet* plat, s_commande* commandeFind);

#endif //HYPERCOOKED_BACKEND_H

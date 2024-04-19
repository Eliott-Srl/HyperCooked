#ifndef HYPERCOOKED_ACTIONS_H
#define HYPERCOOKED_ACTIONS_H

#include "../backend.h"

// Fonction pour déplacer un personnage tout en évitant les collisions avec les meubles
void deplacerPersonnage(s_joueur* joueur, int veloX, int veloY);
// Fonction pour gérer les entrées clavier et déplacer les deux joueurs
void deplacerPersonnages();

#endif //HYPERCOOKED_ACTIONS_H

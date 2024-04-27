#ifndef HYPERCOOKED_ACTIONS_H
#define HYPERCOOKED_ACTIONS_H

#include "../backend.h"

// Fonction pour déplacer un personnage tout en évitant les collisions avec les meubles
void deplacerPersonnageClavier(s_joueur* joueur, int veloX, int veloY);
// Fonction pour gérer les entrées clavier et déplacer les deux joueurs
void deplacerPersonnagesClavier();
// Fonction pour gérer les entrées joystick et déplacer les deux joueurs
void deplacerPersonnageJoystick();

void deplacerPersonnages();

#endif //HYPERCOOKED_ACTIONS_H

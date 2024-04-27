#ifndef HYPERCOOKED_ACTIONS_H
#define HYPERCOOKED_ACTIONS_H

#include "../backend.h"

// Fonction pour gérer les entrées joystick et déplacer les deux joueurs
void deplacerPersonnageJoystick();

void deplacerPersonnage(s_joueur* joueur, double veloX, double veloY);
void deplacerPersonnages();

#endif //HYPERCOOKED_ACTIONS_H

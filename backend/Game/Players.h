#ifndef HYPERCOOKED_PLAYERS_H
#define HYPERCOOKED_PLAYERS_H

#include "../backend.h"

void deplacerPersonnage(s_joueur* joueur, double veloX, double veloY);
void initialisePlayers(s_color c_player1, const char *n_player1, s_color c_player2, const char *n_player2);
void deplacerPersonnages();
// Fonction pour gérer les entrées joystick et déplacer les deux joueurs
void deplacerPersonnageJoystick();

#endif //HYPERCOOKED_PLAYERS_H

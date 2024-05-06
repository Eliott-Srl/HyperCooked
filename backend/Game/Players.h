#ifndef HYPERCOOKED_PLAYERS_H
#define HYPERCOOKED_PLAYERS_H

#include "../backend.h"

void deplacerPersonnage(s_game *game, s_joueur* joueur, double veloX, double veloY);
void initialisePlayers(s_game *game, s_color c_player1, const char *n_player1, s_color c_player2, const char *n_player2);
void deplacerPersonnages(s_game *game);
// Fonction pour gérer les entrées joystick et déplacer les deux joueurs
void deplacerPersonnageJoystick(s_game *game);

#endif //HYPERCOOKED_PLAYERS_H

#ifndef HYPERCOOKED_PLAYERS_H
#define HYPERCOOKED_PLAYERS_H

#include "../backend.h"

void deplacerPersonnage(s_game *game, s_joueur* joueur, double veloX, double veloY);
void changeNomJ1(s_game *game);
void changeColorJ1(s_game *game);
void changeNomJ2(s_game *game);
void changeColorJ2(s_game *game);
void reinitialiserPlayers(s_game *game);
void initialisePlayers(s_game *game);
void deplacerPersonnages(s_game *game);
// Fonction pour gérer les entrées joystick et déplacer les deux joueurs
void deplacerPersonnageJoystick(s_game *game);

#endif //HYPERCOOKED_PLAYERS_H

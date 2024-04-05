#ifndef HYPERCOOKED_GAME_H
#define HYPERCOOKED_GAME_H

#include "../backend.h"

void deplacerPersonnage(s_game* game, s_joueur* joueur, int dx, int dy);
void genereCommande();
int timer();

#endif //HYPERCOOKED_GAME_H

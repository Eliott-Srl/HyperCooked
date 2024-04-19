#ifndef HYPERCOOKED_GAME_H
#define HYPERCOOKED_GAME_H

#include "../backend.h"
#include <dirent.h>

s_game *getGame();
void hc_init();
int loadingMaps(char *maps[NB_MAPS_MAX]);
void jeu(int niveau);
void reinitialiserPartie();
void genereCommande();

#endif //HYPERCOOKED_GAME_H

#ifndef HYPERCOOKED_ONCERS_H
#define HYPERCOOKED_ONCERS_H

#include "../backend.h"

void hc_init();

int loadingMaps(char *maps[NB_MAPS_MAX]);
void initialisePlayers(s_color c_player1, const char *n_player1, s_color c_player2, const char *n_player2);
void reinitialiserPartie();
void hc_finish();

#endif //HYPERCOOKED_ONCERS_H

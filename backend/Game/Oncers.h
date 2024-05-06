#ifndef HYPERCOOKED_ONCERS_H
#define HYPERCOOKED_ONCERS_H

#include "../backend.h"

void hc_init(s_game *game);

int loadingMaps(s_game *game, char maps[NB_MAPS_MAX][STRMAX]);
void reinitialiserPartie(s_game *game);
void hc_finish(s_game *game);

#endif //HYPERCOOKED_ONCERS_H

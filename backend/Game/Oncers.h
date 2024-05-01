#ifndef HYPERCOOKED_ONCERS_H
#define HYPERCOOKED_ONCERS_H

#include "../backend.h"

void hc_init();

int loadingMaps(char maps[NB_MAPS_MAX][STRMAX]);
void reinitialiserPartie();
void hc_finish();

#endif //HYPERCOOKED_ONCERS_H

#ifndef HYPERCOOKED_OBJECTS_H
#define HYPERCOOKED_OBJECTS_H

#include "../backend.h"

void afficherPoeleOnFurniture(s_game *game, int h, int l);
void afficherPoeleInHands(s_game *game, BITMAP *bmp, s_joueur *joueur);
void afficherAssietteOnFurniture(s_game *game, int h, int l);
void afficherAssietteInHands(s_game *game, BITMAP *bmp, s_joueur *joueur);

#endif //HYPERCOOKED_OBJECTS_H

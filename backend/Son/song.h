#ifndef HYPERCOOKED_SONG_H
#define HYPERCOOKED_SONG_H

#include "../backend.h"

int charge_Sound(s_game *game, int choix);
void chargeSound(s_game *game, s_leson *leson);
void playSound(s_game *game, s_leson *leson, int index);
void freeSound(s_game *game, s_leson *leson);

#endif //HYPERCOOKED_SONG_H
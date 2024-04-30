#ifndef HYPERCOOKED_SONG_H
#define HYPERCOOKED_SONG_H

#include "../backend.h"

int charge_Sound(int choix);
void chargeSound(s_leson *leson);
void playSound(s_leson *leson, int index);
void freeSound(s_leson *leson);

#endif //HYPERCOOKED_SONG_H
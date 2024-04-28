#ifndef HYPERCOOKED_SONG_H
#define HYPERCOOKED_SONG_H

#include "../backend.h"

int charge_Sound(int choix);
void chargeSound(s_sound sound[NUM_SONS]);
void playSound(s_sound sons[NUM_SONS], int index);
void freeSound(s_sound sound[NUM_SONS]);
void liberer_sons();

#endif //HYPERCOOKED_SONG_H
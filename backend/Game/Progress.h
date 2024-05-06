#ifndef HYPERCOOKED_PROGRESS_H
#define HYPERCOOKED_PROGRESS_H

#include "../backend.h"

int getBestScoreByNiveau(int niveau);
void writeBestScoreByNiveau(int niveau, int score);
void resetProgression(s_game *game);

#endif //HYPERCOOKED_PROGRESS_H

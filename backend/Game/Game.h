#ifndef HYPERCOOKED_GAME_H
#define HYPERCOOKED_GAME_H

#include "../backend.h"
#include <dirent.h>

int getTime();
void mouseActions();
void showCustomCursor();
s_game *getGame();
void jeu(int niveau);

#endif //HYPERCOOKED_GAME_H

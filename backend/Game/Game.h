#ifndef HYPERCOOKED_GAME_H
#define HYPERCOOKED_GAME_H

#include "../backend.h"
#include <dirent.h>

s_game *getGame();
int getTime();
void mouseActions(int flags);
int getOffsetX();
int getOffsetY();
void toGame();
void toQuit();
void nope();
void showCustomCursor();
void globalKeyboardActions();
void menu();
void partie(int niveau);
void jeu();

#endif //HYPERCOOKED_GAME_H

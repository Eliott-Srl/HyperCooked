#ifndef HYPERCOOKED_GAME_H
#define HYPERCOOKED_GAME_H

#include "../backend.h"
#include <dirent.h>

int getTime(s_game *game);
int getQuitting();
void mouseActions(s_game *game);
float getCorrectOffsetX(s_game *game);
float getIncorrectOffsetX(s_game *game);
float getCorrectOffsetY(s_game *game);
float getIncorrectOffsetY(s_game *game);
void toGame(s_game *game);
void toQuit();
void toSetting(s_game *game);
void showCustomCursor(s_game *game);
void globalKeyboardActions(s_game *game);
void menu(s_game *game);
void partie(s_game *game, int niveau);
void jeu(s_game *game);

#endif //HYPERCOOKED_GAME_H

#ifndef HYPERCOOKED_SONG_H
#define HYPERCOOKED_SONG_H

#include "../backend.h"

void playBruitage(s_game *game, e_sound son);
e_sound getSoundByFurniture(s_game *game, e_meubles meuble);
void JouerLintro(s_game *game);
void stopPlayingEverything(s_game *game);

#endif //HYPERCOOKED_SONG_H
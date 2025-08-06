#include "Song.h"
#include "allegro.h"

e_sound getSoundByFurniture(s_game *game, e_meubles meuble) {
    switch (meuble) {
        case POUBELLE:
            return SON_POUBELLE;
        case GENERATEUR_ASSIETTE:
            return SON_ASSIETTE;
        case PLAQUE_DE_CUISSON:
            return SON_CUISSON;
        case PLANCHE_A_DECOUPER:
            return SON_DECOUPE;
        default:
            return NO_SOUND;
    }
}

void playBruitage(s_game *game, e_sound son) {
    if (!game->settings.music) {
        return;
    }

    if (game->sons[son].voice == -1) {
        game->sons[son].son->priority = 2;
        game->sons[son].voice = allocate_voice(game->sons[son].son);
    }

    if (voice_check(game->sons[son].voice) != NULL) {
        game->sons[son].playing = 0;
    }

    if (game->sons[son].playing) {
        return;
    }

    voice_set_volume(game->sons[son].voice, game->sons[son].volume);
    voice_set_pan(game->sons[son].voice, game->sons[son].pan);
    voice_set_playmode(game->sons[son].voice,game->sons[son].loop);
    voice_start(game->sons[son].voice);
    game->sons[son].playing = 1;
}

void JouerLintro(s_game *game) {
    playBruitage(game, INTRO);
}

void stopPlayingEverything(s_game *game) {
    for (int i = 0; i < NUM_SONS; i++) {
        if (game->sons[i].voice != -1) {
            voice_stop(game->sons[i].voice);
        }
    }
}
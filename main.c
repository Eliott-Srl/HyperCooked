#include "backend/backend.h"

int main() {
    s_game *game = malloc(sizeof(s_game));
    hc_init(game);

    game->etatJeu = DANS_MENU;

    while (!getQuitting()) {
        if (game->etatJeu == DANS_MENU || game->etatJeu == LOADING) {
            menu(game);
        } else if (game->etatJeu == PLAYING) {
            jeu(game);
        }
    }

    hc_finish(game);
    return 0;
} END_OF_MAIN()

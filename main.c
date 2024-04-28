#include "backend/backend.h"

int main() {
    hc_init();

    getGame()->etatJeu = DANS_MENU;

    while (!getGame()->quitting) {
        if (getGame()->etatJeu == DANS_MENU) {
            menu();
        } else if (getGame()->etatJeu == PLAYING) {
            jeu();
        }
    }

    hc_finish();
    return 0;
} END_OF_MAIN()

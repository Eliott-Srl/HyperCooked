#include "Game.h"
#include <time.h>
#include <stdio.h>

volatile int counter = 0;

void timer_handler() {
    counter++;
} END_OF_FUNCTION(timer_handler)

int getTime() {
    return counter;
}

void mouseActions() {
    if (mouse_b & 1) {
        printf("Click gauche\n");
    }
}

s_game *getGame() {
    static s_game *game;

    if (!game) {
        game = (s_game *) calloc(1, sizeof(s_game));
    }

    return game;
}

void showCustomCursor() {
    stretch_sprite(getCorrectBuffer(), getGraphic()->textures.cursor, mouse_x, mouse_y, 40, 40);
}

void jeu(int niveau) {
    s_game *game = getGame();
    int recettes_crees = 0;
    install_int_ex(timer_handler, SECS_TO_TIMER(1));

    do {
        hc_clear_buffers();

        if (game->etatJeu == DANS_MENU_JEU) {
            // TODO: Menu Jeu
        } else if (game->etatJeu == PLAYING) {
            hc_afficher_matrice();
            deplacerPersonnages();

            // Toutes les 40 secondes, il y a une nouvelle recette qui est rendu disponible
            if (counter >= 5 + recettes_crees * 40) {
                newCommande();
                recettes_crees++;
            }
            AfficherCommande();
        }

        showCustomCursor();

        hc_blit(getCorrectBuffer());

        if (key[KEY_F11]) {
            getGraphic()->fs = !getGraphic()->fs;
            set_gfx_mode(getGraphic()->fs ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, getGraphic()->fs ? getGraphic()->fs_width : WIDTH, getGraphic()->fs ? getGraphic()->fs_height : HEIGHT, 0, 0);
            for (int i = 0; i < 2; i++) {
                getGame()->joueurs[i].x = (getGraphic()->fs ? (float) getGame()->joueurs[i].x * getGraphic()->ratio : (float) getGame()->joueurs[i].x / getGraphic()->ratio);
                getGame()->joueurs[i].y = (getGraphic()->fs ? (float) getGame()->joueurs[i].y * getGraphic()->ratio : (float) getGame()->joueurs[i].y / getGraphic()->ratio);
            }
        }

        if (key[KEY_F3]) {
            getGraphic()->debug = !getGraphic()->debug;
        }
    } while (counter <= 90 || (game->etatJeu != DANS_MENU_JEU && game->etatJeu != PLAYING));
}

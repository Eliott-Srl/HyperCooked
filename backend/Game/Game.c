#include "Game.h"
#include <time.h>
#include <stdio.h>

volatile int counter = 0;
volatile int credit = 0;

void timer_handler() {
    counter++;
} END_OF_FUNCTION(timer_handler)

int getTime() {
    return counter;
}

void mouseActions(int flags) {
    int count = getGraphic()->nombreBoutons;
    if (flags & MOUSE_FLAG_LEFT_DOWN) {
        for (int i = 0; i < count; i++) {
            if (mouse_x > getGraphic()->boutons[i].rectangle.virtual.x
                && mouse_x < getGraphic()->boutons[i].rectangle.virtual.x + getGraphic()->boutons[i].rectangle.virtual.w
                && mouse_y > getGraphic()->boutons[i].rectangle.virtual.y
                && mouse_y < getGraphic()->boutons[i].rectangle.virtual.y + getGraphic()->boutons[i].rectangle.virtual.h
                && getGame()->etatJeu != LOADING && !getGame()->quitting) {
                getGraphic()->boutons[i].callback();
            }
        }
    }
}

s_game *getGame() {
    static s_game *game;

    if (!game) {
        game = (s_game *) calloc(1, sizeof(s_game));
    }

    return game;
}

int getOffsetX() {
    return (getCorrectWidth() - LARGEUR * getCorrectCaseSize()) / 2;
}

int getOffsetY() {
    return ((getCorrectHeight() - 70) - HAUTEUR * getCorrectCaseSize()) / 2;
}

void showCustomCursor() {
    if (getGame()->etatJeu == LOADING || getGame()->quitting) {
        return;
    }

    if (boutonsHovered()) {
        stretch_sprite(getCorrectBuffer(), getGraphic()->textures.pointer, mouse_x, mouse_y, 40, 40);
    } else {
        stretch_sprite(getCorrectBuffer(), getGraphic()->textures.cursor, mouse_x, mouse_y, 40, 40);
    }
}

void globalKeyboardActions() {
    if (key[KEY_F11]) {
        getGraphic()->fs = !getGraphic()->fs;
        set_gfx_mode(getGraphic()->fs ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, getGraphic()->fs ? getGraphic()->fs_width : WIDTH, getGraphic()->fs ? getGraphic()->fs_height : HEIGHT, 0, 0);
        for (int i = 0; i < 2; i++) {
            getGame()->joueurs[i].x = (getGraphic()->fs ? (float) getGame()->joueurs[i].x * getGraphic()->ratio : (float) getGame()->joueurs[i].x / getGraphic()->ratio);
            getGame()->joueurs[i].y = (getGraphic()->fs ? (float) getGame()->joueurs[i].y * getGraphic()->ratio : (float) getGame()->joueurs[i].y / getGraphic()->ratio);
        }
    }

    if (getGame()->etatJeu != LOADING) {
        if (key[KEY_F3]) {
            getGraphic()->debug_button = 1;
        }

        if (!key[KEY_F3] && getGraphic()->debug_button) {
            getGraphic()->debug = !getGraphic()->debug;
            getGraphic()->debug_button = 0;
        }
    }
}

void toGame() {
    getGame()->etatJeu = PLAYING;
}

void toQuit() {
    getGame()->quitting = 1;
}

void toCredit() {
    credit = 1;
}

void nope() {
    allegro_message("Nope.");
}

void menu() {
    while (getGame()->etatJeu == DANS_MENU && !credit && !getGame()->quitting) {
        hc_clear_buffers();
        clear_boutons();
        float ratio = (float) getCorrectWidth() / (float) getGraphic()->textures.menuBackground->w;
        int offsetY = (int) ((float) getCorrectHeight() - ((float) getGraphic()->textures.menuBackground->h * ratio)) / 2;


        hc_bouton_virtual(getCorrectBuffer(), (int) ((float) 884 * ratio), (int) ((float) 1035 * ratio) + offsetY,
                          (int) ((float) 148 * ratio), (int) ((float) 52 * ratio), &toGame);
        hc_bouton_virtual(getCorrectBuffer(), (int) ((float) 864 * ratio), (int) ((float) 1087 * ratio) + offsetY,
                          (int) ((float) 285 * ratio), (int) ((float) 66 * ratio), &nope);
        hc_bouton_virtual(getCorrectBuffer(), (int) ((float) 849 * ratio), (int) ((float) 1160 * ratio) + offsetY,
                          (int) ((float) 187 * ratio), (int) ((float) 58 * ratio), &toCredit);
        hc_bouton_virtual(getCorrectBuffer(), (int) ((float) 825 * ratio), (int) ((float) 1232 * ratio) + offsetY,
                          (int) ((float) 185 * ratio), (int) ((float) 54 * ratio), &toQuit);

        stretch_sprite(getCorrectBuffer(), getGraphic()->textures.menuBackground, 0, offsetY, getGraphic()->textures.menuBackground->w * ratio, getGraphic()->textures.menuBackground->h * ratio);

        hc_blit(getCorrectBuffer());
        globalKeyboardActions();
    }

    while (getGame()->etatJeu == DANS_MENU && credit && !getGame()->quitting) {
        hc_clear_buffers();
        clear_boutons();
        float ratio = (float) getCorrectWidth() / (float) getGraphic()->textures.credit->w;
        int offsetY = (int) ((float) getCorrectHeight() - ((float) getGraphic()->textures.credit->h * ratio)) / 3;

        stretch_sprite(getCorrectBuffer(), getGraphic()->textures.credit, 0, 2 * offsetY, getGraphic()->textures.credit->w * ratio, getGraphic()->textures.credit->h * ratio);

        int a = 4, b = (int) getCorrectHeight() / 11, c = getCorrectHeight() - 2 * getCorrectHeight() / 5, i = 0;
        int divisions[a];
        divideScreenVertically(divisions, a, b, c);

        hc_textprintf_centre_h(getCorrectBuffer(), divisions[i], font, makecol(255, 255, 255), -1, "Eliott Sorel");
        i++;
        hc_textprintf_centre_h(getCorrectBuffer(), divisions[i], font, makecol(255, 255, 255), -1, "Alexandre Loyer-Adnet");
        i++;
        hc_textprintf_centre_h(getCorrectBuffer(), divisions[i], font, makecol(255, 255, 255), -1, "Charles Duval");
        i++;
        hc_textprintf_centre_h(getCorrectBuffer(), divisions[i], font, makecol(255, 255, 255), -1, "Clément Pelras");

        hc_textprintf_centre_h(getCorrectBuffer(), getCorrectHeight() - (int) getCorrectHeight()/11, font, makecol(255, 255, 255), -1, "Press [SPACE] to go back to the menu.");

        if (key[KEY_SPACE]) {
            credit = 0;
        }

        hc_blit(getCorrectBuffer());
        globalKeyboardActions();
    }
}

void partie(int niveau) {
    s_game *game = getGame();
    int recettes_crees = 0;
    install_int_ex(timer_handler, SECS_TO_TIMER(1));

    do {
        hc_clear_buffers();
        clear_boutons();
        poll_joystick();

        float ratio = (float) getCorrectHeight() / (float) getGraphic()->textures.background->h;
        int offsetX = (int) ((float) getCorrectWidth() - ((float) getGraphic()->textures.background->w * ratio)) / 2;
        stretch_sprite(getCorrectBuffer(), getGraphic()->textures.background, -offsetX, 0, (int) ((float) getGraphic()->textures.background->w * ratio), (int) ((float) getGraphic()->textures.background->h * ratio));

        if (game->etatJeu == DANS_MENU_JEU) {
            // TODO: Menu Jeu
        } else if (game->etatJeu == PLAYING) {
            hc_afficher_matrice();
            deplacerPersonnages();

            // Toutes les 40 secondes, il y a une nouvelle recette qui est rendu disponible
            if (counter >= 5 + recettes_crees * 5) {
                newCommande();
                recettes_crees++;
            }
            AfficherCommande();
        }

        hc_blit(getCorrectBuffer());
        globalKeyboardActions();

        if (key[KEY_LSHIFT]) {
            getGame()->joueurs[0].shift_pressed = 1;
        }

        if (!key[KEY_LSHIFT] && getGame()->joueurs[0].shift_pressed) {
            executeFunctionForEveryBlockReachable(&game->joueurs[0], &interact);
            getGame()->joueurs[0].shift_pressed = 0;
        }

        if (key[KEY_RSHIFT]) {
            getGame()->joueurs[1].shift_pressed = 1;
        }

        if (!key[KEY_RSHIFT] && getGame()->joueurs[1].shift_pressed) {
            executeFunctionForEveryBlockReachable(&game->joueurs[1], &interact);
            getGame()->joueurs[1].shift_pressed = 0;
        }

    } while (counter <= 90 && (game->etatJeu == PLAYING || game->etatJeu == DANS_MENU_JEU) && !game->quitting);

    remove_int(timer_handler);
    game->etatJeu = LOADING;
}

void jeu() {
    getGame()->etatJeu = LOADING;
    hc_blit(getCorrectBuffer());
    while (!getGame()->quitting) {
        char maps[NB_MAPS_MAX][STRMAX];
        int nbMaps = loadingMaps(maps);

        for (int i = 0; i < nbMaps; i++) {
            if (getGame()->quitting) {
                break;
            }

            reinitialiserPartie();

            char filename[STRMAX];
            sprintf(filename, "maps/%s", maps[i]);

            initialiserMatrice(filename);

            getGame()->etatJeu = PLAYING;

            // Fin de l'écran de chargement
            s_color j1 = {255, 0, 0}, j2 = {0,0, 255};
            initialisePlayers(j1, "Stephane", j2, "Bernard");

            partie(i + 1);

            getGame()->etatJeu = LOADING;
            hc_blit(getCorrectBuffer());
        }
    }
}

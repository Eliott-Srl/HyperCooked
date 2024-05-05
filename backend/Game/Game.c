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

// This is subtle, but if you pay attention you can notice it
void afficherPause() {
    if (!getGraphic()->debug) {
        // cadrillage(screen, makecol(0, 0, 0));
        // clear(screen);
    }
    rectfill(screen, getCorrectWidth()/2 - 30, getCorrectHeight()/2 - 30, getCorrectWidth()/2 - 10, getCorrectHeight()/2 + 30, makecol(255, 255, 255));
    rectfill(screen, getCorrectWidth()/2 + 10, getCorrectHeight()/2 - 30, getCorrectWidth()/2 + 30, getCorrectHeight()/2 + 30, makecol(255, 255, 255));
}

s_game *getGame() {
    static s_game *game;

    if (!game) {
        game = (s_game *) calloc(1, sizeof(s_game));
    }

    return game;
}

float getCorrectOffsetX() {
    return ((float) getCorrectWidth() - LARGEUR * getCorrectCaseSize()) / (float) 2;
}

float getIncorrectOffsetX() {
    return ((float) getIncorrectWidth() - LARGEUR * getIncorrectCaseSize()) / (float) 2;
}

float getCorrectOffsetY() {
    return ((float) (getCorrectHeight() - 70) - HAUTEUR * getCorrectCaseSize()) / (float) 2;
}

float getIncorrectOffsetY() {
    return ((float) (getIncorrectHeight() - 70) - HAUTEUR * getIncorrectCaseSize()) / (float) 2;
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
        request_refresh_rate(FRAMERATE);
        if (set_gfx_mode(getGraphic()->fs ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, getGraphic()->fs ? getGraphic()->fs_width : WIDTH, getGraphic()->fs ? getGraphic()->fs_height : HEIGHT, 0, 0)) {
            allegro_message("Pb de mode graphique");
            allegro_exit();
            exit(EXIT_FAILURE);
        }

        set_display_switch_callback(SWITCH_OUT, &afficherPause);

        /*if (get_refresh_rate() != FRAMERATE) {
            allegro_message("Pb de framerate");
            allegro_exit();
            exit(EXIT_FAILURE);
        }*/

        for (int i = 0; i < 2; i++) {
            float rawX = ((float) getGame()->joueurs[i].x - getIncorrectOffsetX());
            getGame()->joueurs[i].x = (getGraphic()->fs ? rawX * getGraphic()->ratio : rawX / getGraphic()->ratio) + getCorrectOffsetX();
            float rawY = ((float) getGame()->joueurs[i].y - getIncorrectOffsetY());
            getGame()->joueurs[i].y = (getGraphic()->fs ? rawY * getGraphic()->ratio : rawY / getGraphic()->ratio) + getCorrectOffsetY();
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
    while ((getGame()->etatJeu == DANS_MENU || getGame()->etatJeu == LOADING) && !credit && !getGame()->quitting) {
        getGame()->etatJeu = DANS_MENU;
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
    counter = 0;
    credit = 0;
    install_int_ex(timer_handler, MSEC_TO_TIMER(1));

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
            if (counter >= 500 + recettes_crees * 2000) {
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
    } while (counter <= getGame()->duration * 1000 && (game->etatJeu == PLAYING || game->etatJeu == DANS_MENU_JEU) && !game->quitting);

    remove_int(timer_handler);
}

void jeu() {
    getGame()->etatJeu = LOADING;
    hc_blit(getCorrectBuffer());
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

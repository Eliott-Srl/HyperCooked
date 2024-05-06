#include "Game.h"
#include <time.h>
#include <stdio.h>

volatile int counter = 0;
volatile int credit = 0;
volatile int settings = 0;
volatile int quit = 0;

void timer_handler() {
    counter++;
} END_OF_FUNCTION(timer_handler)

int getTime(s_game *game) {
    return counter;
}

int getQuitting() {
    return quit;
}

void mouseActions(s_game *game) {
    int count = game->graphic.nombreBoutons;
    if (mouse_b & 1) {
        for (int i = 0; i < count; i++) {
            if (mouse_x > game->graphic.boutons[i].rectangle.virtual.x
                && mouse_x < game->graphic.boutons[i].rectangle.virtual.x + game->graphic.boutons[i].rectangle.virtual.w
                && mouse_y > game->graphic.boutons[i].rectangle.virtual.y
                && mouse_y < game->graphic.boutons[i].rectangle.virtual.y + game->graphic.boutons[i].rectangle.virtual.h
                && game->etatJeu != LOADING && !quit) {
                game->graphic.boutons[i].callback(game);
            }
        }
    }
}

void reinitialiserProgression(s_game *game) {
    // TODO: Reinitialiser la progression
}

void calibrerManettes(s_game *game) {
    // TODO: Calibrer les manettes
}

float getCorrectOffsetX(s_game *game) {
    return ((float) getCorrectWidth(game) - LARGEUR * getCorrectCaseSize(game)) / (float) 2;
}

float getIncorrectOffsetX(s_game *game) {
    return ((float) getIncorrectWidth(game) - LARGEUR * getIncorrectCaseSize(game)) / (float) 2;
}

float getCorrectOffsetY(s_game *game) {
    return ((float) (getCorrectHeight(game) - 70) - HAUTEUR * getCorrectCaseSize(game)) / (float) 2;
}

float getIncorrectOffsetY(s_game *game) {
    return ((float) (getIncorrectHeight(game) - 70) - HAUTEUR * getIncorrectCaseSize(game)) / (float) 2;
}

void showCustomCursor(s_game *game) {
    if (game->etatJeu == LOADING || quit) {
        return;
    }

    if (boutonsHovered(game)) {
        stretch_sprite(getCorrectBuffer(game), game->graphic.textures.pointer, mouse_x, mouse_y, 40, 40);
    } else {
        stretch_sprite(getCorrectBuffer(game), game->graphic.textures.cursor, mouse_x, mouse_y, 40, 40);
    }
}

void globalKeyboardActions(s_game *game) {
    if (key[KEY_F11]) {
        game->graphic.fs = !game->graphic.fs;
        request_refresh_rate(FRAMERATE);
        if (set_gfx_mode(game->graphic.fs ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, game->graphic.fs ? game->graphic.fs_width : WIDTH, game->graphic.fs ? game->graphic.fs_height : HEIGHT, 0, 0)) {
            allegro_message("Pb de mode graphique");
            allegro_exit();
            exit(EXIT_FAILURE);
        }

        /*if (get_refresh_rate() != FRAMERATE) {
            allegro_message("Pb de framerate");
            allegro_exit();
            exit(EXIT_FAILURE);
        }*/

        for (int i = 0; i < 2; i++) {
            float rawX = ((float) game->joueurs[i].x - getIncorrectOffsetX(game));
            game->joueurs[i].x = (game->graphic.fs ? rawX * game->graphic.ratio : rawX / game->graphic.ratio) + getCorrectOffsetX(game);
            float rawY = ((float) game->joueurs[i].y - getIncorrectOffsetY(game));
            game->joueurs[i].y = (game->graphic.fs ? rawY * game->graphic.ratio : rawY / game->graphic.ratio) + getCorrectOffsetY(game);
        }
    }

    if (game->etatJeu != LOADING) {
        if (key[KEY_F3]) {
            game->graphic.debug_button = 1;
        }

        if (!key[KEY_F3] && game->graphic.debug_button) {
            game->graphic.debug = !game->graphic.debug;
            game->graphic.debug_button = 0;
        }
    }
}

void toGame(s_game *game) {
    game->etatJeu = PLAYING;
}

void toQuit() {
    quit = 1;
}

void toCredit(s_game *game) {
    credit = 1;
}

void toSetting(s_game *game) {
    settings = 1;
}

void menu(s_game *game) {
    while ((game->etatJeu == DANS_MENU || game->etatJeu == LOADING) && !credit && !quit && !settings) {
        game->etatJeu = DANS_MENU;
        hc_clear_buffers(game);
        clear_boutons(game);
        float ratio = (float) getCorrectWidth(game) / (float) game->graphic.textures.menuBackground->w;
        int offsetY = (int) ((float) getCorrectHeight(game) - ((float) game->graphic.textures.menuBackground->h * ratio)) / 2;


        hc_bouton_virtual(game, getCorrectBuffer(game), (int) ((float) 884 * ratio), (int) ((float) 1035 * ratio) + offsetY,
                          (int) ((float) 148 * ratio), (int) ((float) 52 * ratio), &toGame);
        hc_bouton_virtual(game, getCorrectBuffer(game), (int) ((float) 864 * ratio), (int) ((float) 1087 * ratio) + offsetY,
                          (int) ((float) 285 * ratio), (int) ((float) 66 * ratio), &toSetting);
        hc_bouton_virtual(game, getCorrectBuffer(game), (int) ((float) 849 * ratio), (int) ((float) 1160 * ratio) + offsetY,
                          (int) ((float) 187 * ratio), (int) ((float) 58 * ratio), &toCredit);
        hc_bouton_virtual(game, getCorrectBuffer(game), (int) ((float) 825 * ratio), (int) ((float) 1232 * ratio) + offsetY,
                          (int) ((float) 185 * ratio), (int) ((float) 54 * ratio), &toQuit);

        stretch_sprite(getCorrectBuffer(game), game->graphic.textures.menuBackground, 0, offsetY, (int) ((float) game->graphic.textures.menuBackground->w * ratio), (int) ((float) game->graphic.textures.menuBackground->h * ratio));

        hc_blit(game, getCorrectBuffer(game));
        mouseActions(game);
        globalKeyboardActions(game);
    }

    while (game->etatJeu == DANS_MENU && credit && !settings && !quit) {
        hc_clear_buffers(game);
        clear_boutons(game);
        float ratio = (float) getCorrectWidth(game) / (float) game->graphic.textures.credit->w;
        int offsetY = (int) ((float) getCorrectHeight(game) - ((float) game->graphic.textures.credit->h * ratio)) / 3;

        stretch_sprite(getCorrectBuffer(game), game->graphic.textures.credit, 0, 2 * offsetY, (int) ((float) game->graphic.textures.credit->w * ratio), (int) ((float) game->graphic.textures.credit->h * ratio));

        int a = 4, b = (int) getCorrectHeight(game) / 11, c = getCorrectHeight(game) - 2 * getCorrectHeight(game) / 5, i = 0;
        int divisions[a];
        divideScreenVertically(divisions, a, b, c);

        hc_textprintf_centre_h(game, getCorrectBuffer(game), divisions[i], font, makecol(255, 255, 255), -1, "Eliott Sorel");
        i++;
        hc_textprintf_centre_h(game, getCorrectBuffer(game), divisions[i], font, makecol(255, 255, 255), -1, "Alexandre Loyer-Adnet");
        i++;
        hc_textprintf_centre_h(game, getCorrectBuffer(game), divisions[i], font, makecol(255, 255, 255), -1, "Charles Duval");
        i++;
        hc_textprintf_centre_h(game, getCorrectBuffer(game), divisions[i], font, makecol(255, 255, 255), -1, "Clément Pelras");

        hc_textprintf_centre_h(game, getCorrectBuffer(game), getCorrectHeight(game) - (int) getCorrectHeight(game)/11, font, makecol(255, 255, 255), -1, "Press [SPACE] to go back to the menu.");

        if (key[KEY_SPACE]) {
            credit = 0;
        }

        hc_blit(game, getCorrectBuffer(game));
        mouseActions(game);
        globalKeyboardActions(game);
    }

    rest(200);

    while (game->etatJeu == DANS_MENU && !credit && settings && !quit) {
        hc_clear_buffers(game);
        clear_boutons(game);

        char player[STRMAX];
        float ratio = (float) getCorrectWidth(game) / (float) game->graphic.textures.settings->w;
        int offsetY = (int) ((float) getCorrectHeight(game) - ((float) game->graphic.textures.settings->h * ratio)) / 2;
        int offsetX = 10;

        stretch_sprite(getCorrectBuffer(game), game->graphic.textures.settings, 0, offsetY, (int) ((float) game->graphic.textures.settings->w * ratio), (int) ((float) game->graphic.textures.settings->h * ratio));

        int a = 8, b = (int) 7 * getCorrectHeight(game) / 16 + 15, c = getCorrectHeight(game) - getCorrectHeight(game) / 5, i = 0;
        int divisions[a];
        divideScreenVertically(divisions, a, b, c);

        for (int j = 0; j < 2; j++) {
            sprintf(player, "Joueur %d", j + 1);

            textprintf_centre_ex(getCorrectBuffer(game), font, getCorrectWidth(game)/2 + offsetX, divisions[i], makecol(0, 0, 0), -1, "%s", player);
            i++;

            sprintf(player, "Nom: %s", game->joueurs[j].nom);

            hc_boutonfill_center(game, getCorrectBuffer(game), font, getCorrectWidth(game)/2 + offsetX, divisions[i],  getCorrectWidth(game)/5,  divisions[0] / 8, player, (j == 0 ? &changeNomJ1 : &changeNomJ2),
                                 makecol(0, 0, 0), -1);
            i++;

            sprintf(player, "Couleur: %d %d %d", game->joueurs[j].couleur.r, game->joueurs[j].couleur.g, game->joueurs[j].couleur.b);

            hc_boutonfill_center(game, getCorrectBuffer(game), font, getCorrectWidth(game)/2 + offsetX, divisions[i],  getCorrectWidth(game)/5,  divisions[0] / 8, player, (j == 0 ? &changeColorJ1 : &changeColorJ2),
                                 makecol(game->joueurs[j].couleur.r, game->joueurs[j].couleur.g, game->joueurs[j].couleur.b), -1);
            i++;
        }

        hc_boutonfill_center(game, getCorrectBuffer(game), font, getCorrectWidth(game)/2 + offsetX, divisions[i],  getCorrectWidth(game)/5,  divisions[0] / 8, "Réinitialiser progression", &reinitialiserProgression,
                             makecol(0, 0, 0), -1);
        i++;
        hc_boutonfill_center(game, getCorrectBuffer(game), font, getCorrectWidth(game)/2 + offsetX, divisions[i],  getCorrectWidth(game)/5,  divisions[0] / 8, "Calibrer les manettes", &calibrerManettes,
                             makecol(0, 0, 0), -1);

        textprintf_centre_ex(getCorrectBuffer(game), font, getCorrectWidth(game)/2 + offsetX, getCorrectHeight(game) - (int) getCorrectHeight(game)/15, makecol(255, 255, 255), -1, "Press [SPACE] to save and quit.");

        if (key[KEY_SPACE]) {
            settings = 0;
        }

        hc_blit(game, getCorrectBuffer(game));
        mouseActions(game);
        globalKeyboardActions(game);
    }
}

void partie(s_game *game, int niveau) {
    int recettes_crees = 0;
    counter = 0;
    credit = 0;
    install_int_ex(timer_handler, MSEC_TO_TIMER(1));

    do {
        hc_clear_buffers(game);
        clear_boutons(game);
        poll_joystick();

        float ratio = (float) getCorrectHeight(game) / (float) game->graphic.textures.background->h;
        int offsetX = (int) ((float) getCorrectWidth(game) - ((float) game->graphic.textures.background->w * ratio)) / 2;
        stretch_sprite(getCorrectBuffer(game), game->graphic.textures.background, -offsetX, 0, (int) ((float) game->graphic.textures.background->w * ratio), (int) ((float) game->graphic.textures.background->h * ratio));

        if (game->etatJeu == DANS_MENU_JEU) {
            // TODO: Menu Jeu
        } else if (game->etatJeu == PLAYING) {
            hc_afficher_matrice(game);
            deplacerPersonnages(game);

            // Toutes les 40 secondes, il y a une nouvelle recette qui est rendu disponible
            if (counter >= 1000 + recettes_crees * game->timeBtCommandes * 1000) {
                newCommande(game);
                recettes_crees++;
            }
            actualiserCommandes(game);
            AfficherCommande(game);
        }

        hc_blit(game, getCorrectBuffer(game));
        globalKeyboardActions(game);

        if (key[KEY_LSHIFT]) {
            game->joueurs[0].shift_pressed = 1;
        }

        if (!key[KEY_LSHIFT] && game->joueurs[0].shift_pressed) {
            executeFunctionForEveryBlockReachable(game, &game->joueurs[0], &interact);
            game->joueurs[0].shift_pressed = 0;
        }

        if (key[KEY_RSHIFT]) {
            game->joueurs[1].shift_pressed = 1;
        }

        if (!key[KEY_RSHIFT] && game->joueurs[1].shift_pressed) {
            executeFunctionForEveryBlockReachable(game, &game->joueurs[1], &interact);
            game->joueurs[1].shift_pressed = 0;
        }
    } while (counter <= game->duration * 1000 && (game->etatJeu == PLAYING || game->etatJeu == DANS_MENU_JEU) && !quit);

    remove_int(timer_handler);
}

void jeu(s_game *game) {
    game->etatJeu = LOADING;
    hc_blit(game, getCorrectBuffer(game));
    char maps[NB_MAPS_MAX][STRMAX];
    int nbMaps = loadingMaps(maps);

    for (int i = 0; i < nbMaps; i++) {
        if (quit) {
            break;
        }

        reinitialiserPartie(game);

        char filename[STRMAX];
        sprintf(filename, "maps/%s", maps[i]);

        initialiserMatrice(game, filename);

        game->etatJeu = PLAYING;

        // Fin de l'écran de chargement
        reinitialiserPlayers(game);

        partie(game, i + 1);

        game->etatJeu = LOADING;
        hc_blit(game, getCorrectBuffer(game));
    }
}

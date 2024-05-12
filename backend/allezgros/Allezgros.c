#include "Allezgros.h"

int rgbToAllegroColor(s_color color) {
    return makecol(color.r, color.g, color.b);
}

void menu_debug(s_game *game, BITMAP *source) {
    int lines = 0;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "fps: %d", get_refresh_rate());
    lines++;

    if (game->etatJeu == PLAYING) {
        textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "time: %.03f", (double) getTime(game) / 1000);
        lines++;
    }

    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "Joysticks: %d", num_joysticks);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "Joystick X: %f", (double) joy[0].stick[0].axis[0].pos / 128.0);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "Joystick Y: %f", (double) joy[0].stick[0].axis[1].pos / 128.0);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "j1: x: %03d, y: %03d", (int) game->joueurs[0].x, (int) game->joueurs[0].y);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "j2: x: %03d, y: %03d", (int) game->joueurs[1].x, (int) game->joueurs[1].y);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "Ratio normal/fullscreen: %.02f", game->graphic.ratio);
}

void hc_blit(s_game *game, BITMAP *source) {
    if (game->etatJeu != LOADING) {
        showCustomCursor(game);
    }

    if (game->graphic.debug) {
        menu_debug(game, source);
    }

    globalKeyboardActions(game);

    blit(source, screen, 0, 0, 0, 0, getCorrectWidth(game), getCorrectHeight(game));
}

int boutonsHovered(s_game *game) {
    int count = game->graphic.nombreBoutons;
    for (int i = 0; i < count; i++) {
        if (mouse_x > game->graphic.boutons[i].rectangle.virtual.x
         && mouse_x < game->graphic.boutons[i].rectangle.virtual.x + game->graphic.boutons[i].rectangle.virtual.w
         && mouse_y > game->graphic.boutons[i].rectangle.virtual.y
         && mouse_y < game->graphic.boutons[i].rectangle.virtual.y + game->graphic.boutons[i].rectangle.virtual.h) {
            return 1;
        }
    }
    return 0;
}

void divideScreenVertically(int *coos, int n, int startX, int endX) {
    int division = (endX - startX) / (n + 1);

    for (int i = 0; i < n; i++) {
        coos[i] = startX + division * (i + 1);
    }
}

s_rectangle hc_rectfill_center(BITMAP *bmp, int x, int y, int w, int h, int color) {
    if (color != -1) {
        rectfill(bmp, x - w/2, y - h/2, x + w/2, y + h/2, color);
    }

    s_rectangle rectangle;
    rectangle.virtual.x = x - w/2;
    rectangle.virtual.y = y - h/2;
    rectangle.virtual.h = h;
    rectangle.virtual.w = w;
    rectangle.color = (color != -1) * color;
    rectangle.fill = color != -1;

    return rectangle;
}

s_bouton *hc_boutonfill_center(s_game *game, BITMAP *bmp, const FONT *f, int x, int y, int w, int h, const char *text_contained, void (*callback)(s_game*), int color, int background) {
    s_bouton *boutons = (s_bouton *) realloc(game->graphic.boutons, (game->graphic.nombreBoutons + 1) * sizeof(s_bouton));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    boutons[game->graphic.nombreBoutons].bmp = bmp;
    boutons[game->graphic.nombreBoutons].virtual = 0;
    boutons[game->graphic.nombreBoutons].rectangle = hc_rectfill_center(bmp, x, y, w, h, background);
    boutons[game->graphic.nombreBoutons].callback = callback;
    boutons[game->graphic.nombreBoutons].text = (char *) text_contained;
    boutons[game->graphic.nombreBoutons].textColor = color;

    textout_centre_ex(bmp, f, text_contained, x, y, color, -1);

    game->graphic.nombreBoutons++;
    game->graphic.boutons = boutons;
    return &game->graphic.boutons[game->graphic.nombreBoutons];
}

s_bouton *hc_bouton_virtual(s_game *game, BITMAP *bmp, int x, int y, int w, int h, void (*callback)(s_game*)) {
    if (getQuitting()) {
        return NULL;
    }
    s_bouton *boutons = (s_bouton *) realloc(game->graphic.boutons, (game->graphic.nombreBoutons + 1) * sizeof(s_bouton));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    rectfill(bmp, x, y, x + w, y + h, makecol(255, 255, 255));
    boutons[game->graphic.nombreBoutons].bmp = bmp;
    boutons[game->graphic.nombreBoutons].virtual = 1;
    boutons[game->graphic.nombreBoutons].rectangle.virtual.x = x;
    boutons[game->graphic.nombreBoutons].rectangle.virtual.y = y;
    boutons[game->graphic.nombreBoutons].rectangle.virtual.h = h;
    boutons[game->graphic.nombreBoutons].rectangle.virtual.w = w;
    boutons[game->graphic.nombreBoutons].callback = callback;
    boutons[game->graphic.nombreBoutons].text = NULL;
    boutons[game->graphic.nombreBoutons].textColor = -1;

    game->graphic.nombreBoutons++;
    game->graphic.boutons = boutons;
    return &game->graphic.boutons[game->graphic.nombreBoutons];
}

// https://www.yaronet.com/topics/165128-c-retransmission-dune-liste-darguments-variables
void hc_textprintf_centre_h(s_game *game, BITMAP *bmp, int y, const FONT *f, int color, int bg, const char *format, ...) {
    va_list ap;
    char s_format[STRMAX];
    va_start(ap, format);
    vsprintf(s_format, format, ap);
    va_end(ap);

    textprintf_centre_ex(bmp, f, getCorrectWidth(game) / 2, y, color, bg, "%s", s_format);
}

void hc_textprintf_centre_v(s_game *game, BITMAP *bmp, int x, const FONT *f, int color, int bg, const char *format, ...) {
    va_list ap;
    char s_format[STRMAX];
    va_start(ap, format);
    vsprintf(s_format, format, ap);
    va_end(ap);

    textprintf_centre_ex(bmp, f, x,  getCorrectHeight(game) / 2, color, bg, "%s", s_format);
}

void hc_textprintf_centre_hv(s_game *game, BITMAP *bmp, const FONT *f, int color, int bg, const char *format, ...) {
    va_list ap;
    char s_format[STRMAX];
    va_start(ap, format);
    vsprintf(s_format, format, ap);
    va_end(ap);

    textprintf_centre_ex(bmp, f, getCorrectWidth(game) / 2, getCorrectHeight(game) / 2, color, bg, "%s", s_format);
}

void hc_clear_buffers(s_game *game) {
    switch (game->etatJeu) {
        case LOADING:
            break;
        case PLAYING:
            if (game->graphic.fs) {
                clear(game->graphic.ressources.fsBuffer);
            } else {
                clear(game->graphic.ressources.buffer);
            }
            break;
        case DANS_MENU:
            if (game->graphic.fs) {
                clear(game->graphic.ressources.fsMainMenuBuffer);
            } else {
                clear(game->graphic.ressources.mainMenuBuffer);
            }
            break;
        case DANS_MENU_JEU:
            if (game->graphic.fs) {
                clear(game->graphic.ressources.fsMenuBuffer);
            } else {
                clear(game->graphic.ressources.menuBuffer);
            }
            break;
    }
}

int getCorrectHeight(s_game *game) {
    return (game->graphic.fs ? game->graphic.fs_height : HEIGHT);
}

int getIncorrectHeight(s_game *game) {
    return (game->graphic.fs ? HEIGHT : game->graphic.fs_height);
}

int getCorrectWidth(s_game *game) {
    return (game->graphic.fs ? game->graphic.fs_width : WIDTH);
}

int getIncorrectWidth(s_game *game) {
    return (game->graphic.fs ? WIDTH : game->graphic.fs_width);
}

int getCorrectCaseSize(s_game *game) {
    return (game->graphic.fs ? game->graphic.fsTailleCase : game->graphic.tailleCase);
}

int getIncorrectCaseSize(s_game *game) {
    return (game->graphic.fs ? game->graphic.tailleCase : game->graphic.fsTailleCase);
}

int getCorrectRayon(s_game *game) {
    return (game->graphic.fs ? game->graphic.fsRayon : game->graphic.rayon);
}

float getCorrectRatio(s_game *game) {
    return (game->graphic.fs ? game->graphic.ratio : (float) 1.0);
}

BITMAP *getCorrectBuffer(s_game *game) {
    switch (game->etatJeu) {
        case LOADING:
            return (game->graphic.fs ? game->graphic.ressources.fsLoadingScreen : game->graphic.ressources.loadingScreen);
        case PLAYING:
            return (game->graphic.fs ? game->graphic.ressources.fsBuffer : game->graphic.ressources.buffer);
        case DANS_MENU:
            return (game->graphic.fs ? game->graphic.ressources.fsMainMenuBuffer : game->graphic.ressources.mainMenuBuffer);
        case SCORE:
            return (game->graphic.fs ? game->graphic.ressources.fsScoreBuffer : game->graphic.ressources.scoreBuffer);
        default:
            return NULL;
    }
}

void coverBufferWithImage(s_game *game, BITMAP *buffer, BITMAP *image, int s_w, int s_h) {
    int tailleEntierX = buffer->w / s_w;
    int offsetX = (s_w - (buffer->w - tailleEntierX * s_w)) / 2;

    int tailleEntierY = buffer->h / s_h;
    int offsetY = (s_h - (buffer->h - tailleEntierY * s_h)) / 2;

    for (int j = 0; j < tailleEntierY + 1; j++) {
        for (int i = 0; i < tailleEntierX + 1; i++) {
            stretch_sprite(buffer, image, i * s_w - offsetX, j * s_h - offsetY, s_w, s_h);
        }
    }
}

void clear_boutons(s_game *game) {
    game->graphic.nombreBoutons = 0;
    free(game->graphic.boutons);

    s_bouton *boutons = calloc(1, sizeof(s_bouton));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->graphic.boutons = boutons;
}

// It's slow, I love it
void cadrillage(BITMAP *bitmap, int color) {
    int a = 0;
    for (int j = 0; j < bitmap->h; j++) {
        for (int i = 0; i < bitmap->w; i++) {
            if (a % 2 == 0) {
                _putpixel32(bitmap, i, j, color);
            }
            a++;
        }
        a++;
    }
}

void screenshot(s_game *game) {
    char buffer[FILENAME_MAX];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "screenshot-%d-%02d-%02d-%02d-%02d-%02d.bmp", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    BITMAP *bmp = create_sub_bitmap(gui_get_screen(), 0, 0, SCREEN_W, SCREEN_H);
    int a = save_bitmap(buffer, bmp, NULL);
    destroy_bitmap(bmp);
    printf("a: %d\n", a);
    printf("Screenshot saved as %s\n", buffer);
}

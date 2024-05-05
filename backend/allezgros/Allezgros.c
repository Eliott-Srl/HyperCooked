#include "Allezgros.h"

s_graphic* getGraphic() {
    static s_graphic *graphic;
    if (!graphic) {
        graphic = (s_graphic*) malloc(sizeof(s_graphic));
    }

    return graphic;
}

int rgbToAllegroColor(s_color color) {
    return makecol(color.r, color.g, color.b);
}

void menu_debug(BITMAP *source) {
    int lines = 0;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "fps: %d", get_refresh_rate());
    lines++;

    if (getGame()->etatJeu == PLAYING) {
        textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "time: %.03f", (double) getTime() / 1000);
        lines++;
    }

    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "Joysticks: %d", num_joysticks);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "Joystick X: %f", (double) joy[0].stick[0].axis[0].pos / 128.0);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "Joystick Y: %f", (double) joy[0].stick[0].axis[1].pos / 128.0);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "j1: x: %03d, y: %03d", (int) getGame()->joueurs[0].x, (int) getGame()->joueurs[0].y);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "j2: x: %03d, y: %03d", (int) getGame()->joueurs[1].x, (int) getGame()->joueurs[1].y);
    lines++;
    textprintf_ex(source, font, 10, lines * 20 + 10, makecol(255, 255, 255), -1, "Ratio normal/fullscreen: %.02f", getGraphic()->ratio);
}

void hc_blit(BITMAP *source) {
    if (getGame()->etatJeu != LOADING) {
        showCustomCursor();
    }

    if (getGraphic()->debug) {
        menu_debug(source);
    }

    globalKeyboardActions();

    blit(source, screen, 0, 0, 0, 0, getCorrectWidth(), getCorrectHeight());
}

int boutonsHovered() {
    int count = getGraphic()->nombreBoutons;
    for (int i = 0; i < count; i++) {
        if (mouse_x > getGraphic()->boutons[i].rectangle.virtual.x
         && mouse_x < getGraphic()->boutons[i].rectangle.virtual.x + getGraphic()->boutons[i].rectangle.virtual.w
         && mouse_y > getGraphic()->boutons[i].rectangle.virtual.y
         && mouse_y < getGraphic()->boutons[i].rectangle.virtual.y + getGraphic()->boutons[i].rectangle.virtual.h) {
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
    rectfill(bmp, x - w/2, y - h/2, x + w/2, y + h/2, color);

    s_rectangle rectangle;
    rectangle.virtual.x = x;
    rectangle.virtual.y = y;
    rectangle.virtual.h = h;
    rectangle.virtual.w = w;
    rectangle.color = color;
    rectangle.fill = 1;

    return rectangle;
}

s_bouton *hc_boutonfill_center(BITMAP *bmp, const FONT *f, int x, int y, int w, int h, const char *text_contained, void (*callback)(), int color, int background) {
    s_bouton *boutons = (s_bouton *) realloc(getGraphic()->boutons, (getGraphic()->nombreBoutons + 1) * sizeof(s_bouton));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    boutons[getGraphic()->nombreBoutons].bmp = bmp;
    boutons[getGraphic()->nombreBoutons].virtual = 0;
    boutons[getGraphic()->nombreBoutons].rectangle = hc_rectfill_center(bmp, x, y, h, w, background);
    boutons[getGraphic()->nombreBoutons].callback = callback;
    boutons[getGraphic()->nombreBoutons].text = (char *) text_contained;
    boutons[getGraphic()->nombreBoutons].textColor = color;

    textout_centre_ex(bmp, f, text_contained, x, y, color, -1);

    getGraphic()->nombreBoutons++;
    getGraphic()->boutons = boutons;
    return &getGraphic()->boutons[getGraphic()->nombreBoutons];
}

s_bouton *hc_bouton_virtual(BITMAP *bmp, int x, int y, int w, int h, void (*callback)()) {
    if (getGame()->quitting) {
        return NULL;
    }
    s_bouton *boutons = (s_bouton *) realloc(getGraphic()->boutons, (getGraphic()->nombreBoutons + 1) * sizeof(s_bouton));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    rectfill(bmp, x, y, x + w, y + h, makecol(255, 255, 255));
    boutons[getGraphic()->nombreBoutons].bmp = bmp;
    boutons[getGraphic()->nombreBoutons].virtual = 1;
    boutons[getGraphic()->nombreBoutons].rectangle.virtual.x = x;
    boutons[getGraphic()->nombreBoutons].rectangle.virtual.y = y;
    boutons[getGraphic()->nombreBoutons].rectangle.virtual.h = h;
    boutons[getGraphic()->nombreBoutons].rectangle.virtual.w = w;
    boutons[getGraphic()->nombreBoutons].callback = callback;
    boutons[getGraphic()->nombreBoutons].text = NULL;
    boutons[getGraphic()->nombreBoutons].textColor = -1;

    getGraphic()->nombreBoutons++;
    getGraphic()->boutons = boutons;
    return &getGraphic()->boutons[getGraphic()->nombreBoutons];
}

// https://www.yaronet.com/topics/165128-c-retransmission-dune-liste-darguments-variables
void hc_textprintf_centre_h(BITMAP *bmp, int y, const FONT *f, int color, int bg, const char *format, ...) {
    va_list ap;
    char s_format[STRMAX];
    va_start(ap, format);
    vsprintf(s_format, format, ap);
    va_end(ap);

    textprintf_centre_ex(bmp, f, getCorrectWidth() / 2, y, color, bg, "%s", s_format);
}

void hc_textprintf_centre_v(BITMAP *bmp, int x, const FONT *f, int color, int bg, const char *format, ...) {
    va_list ap;
    char s_format[STRMAX];
    va_start(ap, format);
    vsprintf(s_format, format, ap);
    va_end(ap);

    textprintf_centre_ex(bmp, f, x,  getCorrectHeight() / 2, color, bg, "%s", s_format);
}

void hc_textprintf_centre_hv(BITMAP *bmp, const FONT *f, int color, int bg, const char *format, ...) {
    va_list ap;
    char s_format[STRMAX];
    va_start(ap, format);
    vsprintf(s_format, format, ap);
    va_end(ap);

    textprintf_centre_ex(bmp, f, getCorrectWidth() / 2, getCorrectHeight() / 2, color, bg, "%s", s_format);
}

void hc_clear_buffers() {
    switch (getGame()->etatJeu) {
        case LOADING:
            break;
        case PLAYING:
            if (getGraphic()->fs) {
                clear(getGraphic()->ressources.fsBuffer);
            } else {
                clear(getGraphic()->ressources.buffer);
            }
            break;
        case DANS_MENU:
            if (getGraphic()->fs) {
                clear(getGraphic()->ressources.fsMainMenuBuffer);
            } else {
                clear(getGraphic()->ressources.mainMenuBuffer);
            }
            break;
        case DANS_MENU_JEU:
            if (getGraphic()->fs) {
                clear(getGraphic()->ressources.fsMenuBuffer);
            } else {
                clear(getGraphic()->ressources.menuBuffer);
            }
            break;
    }
}

int getCorrectHeight() {
    return (getGraphic()->fs ? getGraphic()->fs_height : HEIGHT);
}

int getIncorrectHeight() {
    return (getGraphic()->fs ? HEIGHT : getGraphic()->fs_height);
}

int getCorrectWidth() {
    return (getGraphic()->fs ? getGraphic()->fs_width : WIDTH);
}

int getIncorrectWidth() {
    return (getGraphic()->fs ? WIDTH : getGraphic()->fs_width);
}

int getCorrectCaseSize() {
    return (getGraphic()->fs ? getGraphic()->fsTailleCase : getGraphic()->tailleCase);
}

int getIncorrectCaseSize() {
    return (getGraphic()->fs ? getGraphic()->tailleCase : getGraphic()->fsTailleCase);
}

int getCorrectRayon() {
    return (getGraphic()->fs ? getGraphic()->fsRayon : getGraphic()->rayon);
}

float getCorrectRatio() {
    return (getGraphic()->fs ? getGraphic()->ratio : (float) 1.0);
}

BITMAP *getCorrectBuffer() {
    switch (getGame()->etatJeu) {
        case LOADING:
            return (getGraphic()->fs ? getGraphic()->ressources.fsLoadingScreen : getGraphic()->ressources.loadingScreen);
        case PLAYING:
            return (getGraphic()->fs ? getGraphic()->ressources.fsBuffer : getGraphic()->ressources.buffer);
        case DANS_MENU:
            return (getGraphic()->fs ? getGraphic()->ressources.fsMainMenuBuffer : getGraphic()->ressources.mainMenuBuffer);
        case DANS_MENU_JEU:
            return (getGraphic()->fs ? getGraphic()->ressources.fsMenuBuffer : getGraphic()->ressources.menuBuffer);
    }
}

void coverBufferWithImage(BITMAP *buffer, BITMAP *image, int s_w, int s_h) {
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

void clear_boutons() {
    getGraphic()->nombreBoutons = 0;
    free(getGraphic()->boutons);

    s_bouton *boutons = calloc(1, sizeof(s_bouton));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    getGraphic()->boutons = boutons;
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

void screenshot() {
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

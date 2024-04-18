#include "Allezgros.h"

s_graphic* p_graphic;

s_graphic* get_graphic() {
    return p_graphic;
}

void set_graphic(s_graphic* new_graphic) {
    p_graphic = new_graphic;
}

int rgbToAllegroColor(s_color color) {
    return makecol(color.r, color.g, color.b);
}

void hc_blit(BITMAP *source) {
    if (p_graphic->fs) {
       blit(source, screen, 0, 0, 0, 0, FS_WIDTH, FS_HEIGHT);
    } else {
        blit(source, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
    }
}

int boutonsHovered() {
    int count = p_graphic->nombre_boutons;
    for (int i = 0; i < count; i++) {
        if (mouse_x > p_graphic->boutons[i].rectangle.x - p_graphic->boutons[i].rectangle.w / 2
         && mouse_x < p_graphic->boutons[i].rectangle.x + p_graphic->boutons[i].rectangle.w / 2
         && mouse_y > p_graphic->boutons[i].rectangle.y - p_graphic->boutons[i].rectangle.h / 2
         && mouse_y < p_graphic->boutons[i].rectangle.y + p_graphic->boutons[i].rectangle.h / 2) {
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

s_rectangle hc_rectfill_center(BITMAP *bmp, int x, int y, int h, int w, int color) {
    rectfill(bmp, x - w/2, y - h/2, x + w/2, y + h/2, color);

    s_rectangle rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.h = h;
    rectangle.w = w;
    rectangle.color = color;
    rectangle.fill = 1;

    return rectangle;
}

s_bouton *hc_boutonfill_center(BITMAP *bmp, const FONT *f, int x, int y, int h, int w, const char *text_contained, void (*callback)(), int color, int background) {
    s_bouton *boutons = (s_bouton *) realloc(p_graphic->boutons, (p_graphic->nombre_boutons + 1) * sizeof(s_bouton*));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    boutons[p_graphic->nombre_boutons].bmp = bmp;
    boutons[p_graphic->nombre_boutons].rectangle = hc_rectfill_center(bmp, x, y, h, w, background);
    boutons[p_graphic->nombre_boutons].callback = callback;
    boutons[p_graphic->nombre_boutons].text = (char *) text_contained;
    boutons[p_graphic->nombre_boutons].text_color = color;

    textout_centre_ex(bmp, f, text_contained, x, y, color, -1);

    p_graphic->nombre_boutons++;
    p_graphic->boutons = boutons;
    return &p_graphic->boutons[p_graphic->nombre_boutons];
}

// https://www.yaronet.com/topics/165128-c-retransmission-dune-liste-darguments-variables
void hc_textprintf_centre_h(BITMAP *bmp, int y, const FONT *f, int color, int bg, const char *format, ...) {
    va_list ap;
    char s_format[STRMAX];
    va_start(ap, format);
    vsprintf(s_format, format, ap);
    va_end(ap);

    if (p_graphic->fs) {
        textprintf_centre_ex(bmp, f, FS_WIDTH / 2, y, color, bg, "%s", s_format);
    } else {
        textprintf_centre_ex(bmp, f, WIDTH/2, y, color, bg, "%s", s_format);
    }
}

void hc_textprintf_centre_v(BITMAP *bmp, int x, const FONT *f, int color, int bg, const char *format, ...) {
    va_list ap;
    char s_format[STRMAX];
    va_start(ap, format);
    vsprintf(s_format, format, ap);
    va_end(ap);

    if (p_graphic->fs) {
        textprintf_centre_ex(bmp, f, x, FS_HEIGHT / 2, color, bg, "%s", s_format);
    } else {
        textprintf_centre_ex(bmp, f, x, HEIGHT/2, color, bg, "%s", s_format);
    }
}

void hc_textprintf_centre_hv(BITMAP *bmp, const FONT *f, int color, int bg, const char *format, ...) {
    va_list ap;
    char s_format[STRMAX];
    va_start(ap, format);
    vsprintf(s_format, format, ap);
    va_end(ap);

    if (p_graphic->fs) {
        textprintf_centre_ex(bmp, f, FS_WIDTH / 2, FS_HEIGHT / 2, color, bg, "%s", s_format);
    } else {
        textprintf_centre_ex(bmp, f, WIDTH/2, HEIGHT/2, color, bg, "%s", s_format);
    }
}

void clear_boutons() {
    for (int i = 0; i < p_graphic->nombre_boutons; i++) {
        free(p_graphic->boutons + i);
    }

    p_graphic->nombre_boutons = 0;
    s_bouton *boutons = realloc(p_graphic->boutons, sizeof(s_bouton *));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    p_graphic->boutons = boutons;
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

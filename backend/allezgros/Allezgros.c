#include "Allezgros.h"

s_graphic* graphic;

s_graphic* get_graphic() {
    return graphic;
}

void set_graphic(s_graphic* new_graphic) {
    graphic = new_graphic;
}

int rgbToAllegroColor(s_color color) {
    return makecol(color.r, color.g, color.b);
}

int boutonsHovered() {
    int count = graphic->nombre_boutons;
    for (int i = 0; i < count; i++) {
        if (mouse_x > graphic->boutons[i].rectangle.x - graphic->boutons[i].rectangle.w/2
         && mouse_x < graphic->boutons[i].rectangle.x + graphic->boutons[i].rectangle.w/2
         && mouse_y > graphic->boutons[i].rectangle.y - graphic->boutons[i].rectangle.h/2
         && mouse_y < graphic->boutons[i].rectangle.y + graphic->boutons[i].rectangle.h/2) {
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

s_rectangle rectfill_center(BITMAP *bmp, int x, int y, int h, int w, int color) {
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

s_bouton *boutonfill_center(BITMAP *bmp, const FONT *f, int x, int y, int h, int w, const char *text_contained, void (*callback)(), int color, int background) {
    s_bouton *boutons = (s_bouton *) realloc(graphic->boutons, (graphic->nombre_boutons + 1) * sizeof(s_bouton*));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    boutons[graphic->nombre_boutons].bmp = bmp;
    boutons[graphic->nombre_boutons].rectangle = rectfill_center(bmp, x, y, h, w, background);
    boutons[graphic->nombre_boutons].callback = callback;
    boutons[graphic->nombre_boutons].text = (char *) text_contained;
    boutons[graphic->nombre_boutons].text_color = color;

    textout_centre_ex(bmp, f, text_contained, x, y, color, -1);

    graphic->nombre_boutons++;
    graphic->boutons = boutons;
    return &graphic->boutons[graphic->nombre_boutons];
}

void clear_boutons() {
    for (int i = 0; i < graphic->nombre_boutons; i++) {
        free(graphic->boutons + i);
    }

    graphic->nombre_boutons = 0;
    s_bouton *boutons = realloc(graphic->boutons, sizeof(s_bouton *));

    if (boutons == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->boutons = boutons;
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

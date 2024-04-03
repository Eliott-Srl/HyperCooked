#include "Allezgros.h"

int rgbToAllegroColor(s_color color) {
    return makecol(color.r, color.g, color.b);
}

int elements_count = 0;
s_bouton **elements;

s_bouton **get_elements() {
    return elements;
}

int get_elements_count() {
    return elements_count;
}

void set_elements(s_bouton **new_elements) {
    elements = new_elements;
}

void set_elements_count(int new_elements_count) {
    elements_count = new_elements_count;
}

int elementHovered() {
    int count = get_elements_count();
    for (int i = 0; i < count; i++) {
        if (mouse_x > elements[i]->rectangle.x - elements[i]->rectangle.w/2
            && mouse_x < elements[i]->rectangle.x + elements[i]->rectangle.w/2
            && mouse_y > elements[i]->rectangle.y - elements[i]->rectangle.h/2
            && mouse_y < elements[i]->rectangle.y + elements[i]->rectangle.h/2) {
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

    return rectangle;
}

s_bouton *boutonfill_center(BITMAP *bmp, const FONT *f, int x, int y, int h, int w, const char *text_contained, void (*callback)(), BITMAP *pointer_sprite, int color, int background) {
    s_bouton *bouton = (s_bouton *) malloc(sizeof(s_bouton));
    bouton->bmp = bmp;
    bouton->rectangle = rectfill_center(bmp, x, y, h, w, background);
    bouton->callback = callback;
    bouton->text = (char *) text_contained;
    bouton->text_color = color;
    bouton->pointer_sprite = pointer_sprite;

    s_bouton **tmp = realloc(elements, (elements_count + 1) * sizeof(s_bouton*));
    if (tmp == NULL) {
        allegro_message("Erreur de reallocation de la mémoire");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    elements = tmp;
    elements[elements_count] = bouton;
    elements_count++;

    textout_centre_ex(bmp, f, text_contained, x, y, color, -1);

    return bouton;
}

void clear_elements() {
    for (int i = 0; i < elements_count; i++) {
        free(elements[i]);
    }

    elements_count = 0;
    elements = malloc(sizeof(s_bouton *));
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

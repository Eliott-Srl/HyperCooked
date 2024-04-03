#ifndef HYPERCOOKED_ALLEZGROS_H
#define HYPERCOOKED_ALLEZGROS_H

#include "allegro.h"
#include "../backend/backend.h"
#include <stdio.h>

typedef struct {
    int h;                          // Hauteur
    int w;                          // Largeur
    int color;                      // Couleur ( utilise makecol() )
    int x;                          // Position X du centre
    int y;                          // Position Y du centre
    int fill;                       // Si le rectangle est rempli ou non
} s_rectangle;

typedef struct {
    BITMAP *bmp;                    // Image sur laquelle on dessine
    s_rectangle rectangle;          // Instance de s_rectangle
    void (*callback)();             // Pointeur de fonction qui sera app
    char *text;                     // Texte affiché sur l'écran
    int text_color;                 // Couleur du texte affiché
    BITMAP *pointer_sprite;         // Image du curseur en mode pointeur
} s_bouton;

int rgbToAllegroColor(s_color color);
void divideScreenVertically(int *coos, int n, int startX, int endX);
s_bouton **get_elements();
int get_elements_count();
void set_elements(s_bouton **new_elements);
void set_elements_count(int new_elements_count);
int elementHovered();
s_rectangle rectfill_center(BITMAP *bmp, int x, int y, int h, int w, int color);
s_bouton *boutonfill_center(BITMAP *bmp, const FONT *f, int x, int y, int h, int w, const char *text_contained, void (*callback)(), BITMAP *pointer_sprite, int color, int background);
void clear_elements();
void screenshot();

#endif //HYPERCOOKED_ALLEZGROS_H

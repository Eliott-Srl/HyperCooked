#ifndef HYPERCOOKED_ALLEZGROS_H
#define HYPERCOOKED_ALLEZGROS_H

#include "../backend.h"
#include "allegro.h"
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
    void (*callback)();             // Pointeur de fonction qui sera appelée
    char *text;                     // Texte affiché sur l'écran
    int text_color;                 // Couleur du texte affiché
} s_bouton;

typedef struct {
    BITMAP *background;             // Fond du menu
    int menu_opened;                // Booléen qui indique l'état d'ouverture du menu
} s_menu;

typedef struct {
    BITMAP *cursor;
    BITMAP *pointer;
    int width;
    int height;
    s_bouton *boutons;
    int nombre_boutons;
} s_graphic;

s_graphic *get_graphic();
void set_graphic(s_graphic* new_graphic);
int rgbToAllegroColor(s_color color);
void divideScreenVertically(int *coos, int n, int startX, int endX);
int boutonsHovered();
s_rectangle rectfill_center(BITMAP *bmp, int x, int y, int h, int w, int color);
s_bouton *boutonfill_center(BITMAP *bmp, const FONT *f, int x, int y, int h, int w, const char *text_contained, void (*callback)(), int color, int background);
void clear_boutons();
void screenshot();

#endif //HYPERCOOKED_ALLEZGROS_H

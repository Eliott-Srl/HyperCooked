#ifndef HYPERCOOKED_ALLEZGROS_H
#define HYPERCOOKED_ALLEZGROS_H

#include <stdio.h>
#include "../backend.h"

// Retourne la structure globale qui contient toutes les infos pour l'affichage
s_graphic *getGraphic();

// Set l'adresse de la sutructure graphique sur new_graphic
void set_graphic(s_graphic* new_graphic);

// Transforme une couleur de la structure couleur en une couleur d'Allegro
int rgbToAllegroColor(s_color color);

// Affiche le buffer adapté avec la bonne taille
void hc_blit(BITMAP *source);

// Divise l'espace horizontale entre startX et endX en n parts égales
void divideScreenVertically(int *coos, int n, int startX, int endX);

// Retourne un booléen qui dit si la souris se trouve sur un des boutons customs
int boutonsHovered();

/* Crée un rectangle dont:
 * - x et y sont les coordonées du centre
 * - color est la couleur du rectangle*/
s_rectangle hc_rectfill_center(BITMAP *bmp, int x, int y, int h, int w, int color);

/* Crée un bouton custom interactif dont:
 * - x et y sont les coordonnées du centre
 * - h et w seront respectivement la hauteur et la largeur
 * - text_contained sera le texte afficher sur le bouton
 * - callback sera la fonction appelé quand on clique dessus
 * - color sera la couleur du texte
 * - background sera la couleur du bouton*/
s_bouton *hc_boutonfill_center(BITMAP *bmp,const FONT *f, int x, int y, int h, int w, const char *text_contained,
                               void (*callback)(), int color, int background);
// Crée un texte aligné sur l'axe horizontale et dont y est la distance depuis le haut de l'écran
void hc_textprintf_centre_h(BITMAP *bmp, int y, const FONT *f, int color, int bg, const char *format, ...);

// Crée un texte aligné sur l'axe verticale et dont x est la distance depuis la gauche de l'écran
void hc_textprintf_centre_v(BITMAP *bmp, int x, const FONT *f, int color, int bg, const char *format, ...);

// Crée un texte aligné sur l'axe horizontale et verticale
void hc_textprintf_centre_hv(BITMAP *bmp, const FONT *f, int color, int bg, const char *format, ...);

// En appelant cette fonction on clear le bon buffer en fonction de l'état du jeu et du mode plein écran
void hc_clear_buffers();

// Retourne la hauteur appropriée en fonction du mode plein écran
int getCorrectHeight();

// Retourne la largeur appropriée en fonction du mode plein écran
int getCorrectWidth();

// Retourne la taille d'une case appropriée en fonction du mode plein écran
int getCorrectCaseSize();

// Retourne le buffer correct en fonction du mode plein écran et de l'état du jeu
BITMAP *getCorrectBuffer();

// Couvre buffer avec image en répétant verticalement et horizontalement
void coverBufferWithImage(BITMAP *buffer, BITMAP *image, int s_w, int s_h);

// Supprime tous les boutons customs
void clear_boutons();

// Prends une capture d'écran
// Ne fonctionne pas
void screenshot();

#endif //HYPERCOOKED_ALLEZGROS_H

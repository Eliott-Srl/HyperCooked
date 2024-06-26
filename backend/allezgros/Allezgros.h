#ifndef HYPERCOOKED_ALLEZGROS_H
#define HYPERCOOKED_ALLEZGROS_H

#include <stdio.h>
#include "../backend.h"

// Retourne la structure globale qui contient toutes les infos pour l'affichage
s_graphic *getGraphic();

// Transforme une couleur de la structure couleur en une couleur d'Allegro
int rgbToAllegroColor(s_color color);

// Affiche les informations de debug
void menu_debug(s_game *game, BITMAP *source);

// Affiche le buffer adapté avec la bonne taille
void hc_blit(s_game *game, BITMAP *source);

// Divise l'espace horizontale entre startX et endX en n parts égales
void divideScreenVertically(int *coos, int n, int startX, int endX);

// Retourne un booléen qui dit si la souris se trouve sur un des boutons customs
int boutonsHovered(s_game *game);

/* Crée un rectangle dont:
 * - x et y sont les coordonées du centre
 * - color est la couleur du rectangle*/
s_rectangle hc_rectfill_center(BITMAP *bmp, int x, int y, int w, int h, int color);

/* Crée un bouton custom interactif dont:
 * - x et y sont les coordonnées du centre
 * - h et w seront respectivement la hauteur et la largeur
 * - text_contained sera le texte afficher sur le bouton
 * - callback sera la fonction appelé quand on clique dessus
 * - color sera la couleur du texte
 * - background sera la couleur du bouton*/
s_bouton *hc_boutonfill_center(s_game *game, BITMAP *bmp,const FONT *f, int x, int y, int w, int h, const char *text_contained,
                               void (*callback)(s_game*), int color, int background);

// Crée un bouton custom virtuel
s_bouton *hc_bouton_virtual(s_game *game, BITMAP *bmp, int x, int y, int w, int h, void (*callback)(s_game*));

// Crée un texte aligné sur l'axe horizontale et dont y est la distance depuis le haut de l'écran
void hc_textprintf_centre_h(s_game *game, BITMAP *bmp, int y, const FONT *f, int color, int bg, const char *format, ...);

// Crée un texte aligné sur l'axe verticale et dont x est la distance depuis la gauche de l'écran
void hc_textprintf_centre_v(s_game *game, BITMAP *bmp, int x, const FONT *f, int color, int bg, const char *format, ...);

// Crée un texte aligné sur l'axe horizontale et verticale
void hc_textprintf_centre_hv(s_game *game, BITMAP *bmp, const FONT *f, int color, int bg, const char *format, ...);

// En appelant cette fonction on clear le bon buffer en fonction de l'état du jeu et du mode plein écran
void hc_clear_buffers(s_game *game);

// Retourne la hauteur appropriée en fonction du mode plein écran
int getCorrectHeight(s_game *game);

// Retourne la hauteur inappropriée en fonction du mode plein écran
int getIncorrectHeight(s_game *game);

// Retourne la largeur appropriée en fonction du mode plein écran
int getCorrectWidth(s_game *game);

// Retourne la largeur inappropriée en fonction du mode plein écran
int getIncorrectWidth(s_game *game);

// Retourne la taille d'une case appropriée en fonction du mode plein écran
int getCorrectCaseSize(s_game *game);

// Retourne la taille d'une case inappropriée en fonction du mode plein écran
int getIncorrectCaseSize(s_game *game);

// Retourne le rayon approprié en fonction du mode plein écran
int getCorrectRayon(s_game *game);

// Retourne le ratio correct en fonction du mode plein écran
float getCorrectRatio(s_game *game);

// Retourne le buffer correct en fonction du mode plein écran et de l'état du jeu
BITMAP *getCorrectBuffer(s_game *game);

// Couvre buffer avec image en répétant verticalement et horizontalement
void coverBufferWithImage(s_game *game, BITMAP *buffer, BITMAP *image, int s_w, int s_h);

// Supprime tous les boutons customs
void clear_boutons(s_game *game);

// Fait un cadrillage sur le buffer
void cadrillage(BITMAP *bitmap, int color);

// Prends une capture d'écran
// Ne fonctionne pas
void screenshot(s_game *game);

#endif //HYPERCOOKED_ALLEZGROS_H

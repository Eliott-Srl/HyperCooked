#ifndef HYPERCOOKED_BACKEND_H
#define HYPERCOOKED_BACKEND_H

#define STRMAX 120
#define HAUTEUR 12
#define LARGEUR 20
#define NB_RECETTES_MAX 10
#define NB_INGREDIENTS_MAX 10
#define NB_COMMANDES_MAX 5

#define WIDTH 800
#define HEIGHT 600

#ifdef WIN64
#include <winuser.h>
#define FS_WIDTH GetSystemMetrics(SM_CXFULLSCREEN)
#define FS_HEIGHT GetSystemMetrics(SM_CYFULLSCREEN)
#endif

#ifndef WIN64
#define FS_WIDTH 1920;
#define FS_HEIGHT 1080;
#endif

#include "allegro.h"

typedef struct s_coo {
    int x;
    int y;
} s_coo;

typedef struct s_color {
    int r;
    int g;
    int b;
} s_color;

typedef enum e_etat_jeu {
    LOADING,
    PLAYING,
    DANS_MENU,
    DANS_MENU_JEU
} e_etat_jeu;

typedef enum e_ingredients {
    SALADE,
    PAIN,
    TOMATE,
    STEAK,
    OEUF,
    POTATO,
} e_ingredients;

typedef enum e_cuisson {
    NON,
    A_LA_MARMITE,
    A_LA_POELE
} e_cuisson;

typedef struct s_ingredient {
    e_ingredients nom;
    e_cuisson cuisson;
    int cuit;
    int coupable;
    int coupe;
} s_ingredient;

typedef struct s_recette {
    char nom[STRMAX];
    s_ingredient ingredients[NB_INGREDIENTS_MAX];
    int nbIngredients;
} s_recette;

typedef struct s_commande {
    int timer;
    s_recette recette;
} s_commande;

typedef struct s_ingredient_physique {
    s_ingredient type;
    int en_main;
    // here we need to add a pointer to the texture
} s_ingredient_physique;

typedef enum e_meubles {
    SOL,
    PLAN_DE_TRAVAIL,
    PLANCHE_A_DECOUPER,
    COMPTOIR,
    COFFRE,
    PLAQUE_A_CUISSON,
    POUBELLE
} e_meubles;

typedef enum e_objet {
    NONE,
    POELE,
    MARMITE,
    ASSIETTE,
    EXTINCTEUR,
    STOCKEUR
} e_objet;

typedef enum e_stockage {
    SANS = 0,
    UN_SLOT = 1,
    TROIS_SLOTS = 3,
    RECETTE = 10
} e_stockage;

typedef struct s_objet {
    e_objet type;
    s_ingredient nourriture[10];
    e_stockage stockageMax;
    int nbStockes;
} s_objet;

typedef struct s_meuble {
    e_meubles type_meuble;
    s_objet objet;
    void (*action)();
} s_meuble;

typedef enum e_typeEnMain {
    NOTHING,
    INGREDIENT,
    OBJET
} e_typeEnMain;

typedef struct s_joueur {
    s_color couleur;
    char nom[STRMAX];
    s_coo pos;
    int dimensions;
    int en_main;
    s_ingredient_physique hand_ingredient;
    s_objet hand_objet;
} s_joueur;

typedef struct s_partie {
    s_commande commandes[NB_COMMANDES_MAX];
    int nbCommandes;
    int temps;
    int score;
} s_partie;

typedef struct s_game {
    s_meuble matrice[HAUTEUR][LARGEUR];
    s_joueur joueurs[2];
    s_partie partie;
    s_recette recettes[NB_RECETTES_MAX];
    int nb_recettes;
} s_game;

typedef struct s_rectangle {
    int h;                          // Hauteur
    int w;                          // Largeur
    int color;                      // Couleur ( utilise makecol() )
    int x;                          // Position X du centre
    int y;                          // Position Y du centre
    int fill;                       // Si le rectangle est rempli ou non
} s_rectangle;

typedef struct s_bouton {
    BITMAP *bmp;                    // Image sur laquelle on dessine
    s_rectangle rectangle;          // Instance de s_rectangle
    void (*callback)();             // Pointeur de fonction qui sera appelée
    char *text;                     // Texte affiché sur l'écran
    int text_color;                 // Couleur du texte affiché
} s_bouton;

typedef struct s_menu {
    BITMAP *background;             // Fond du menu
    int menu_opened;                // Booléen qui indique l'état d'ouverture du menu
} s_menu;

typedef struct s_graphic {
    BITMAP *buffer;                 // BITMAP pour le double buffering
    BITMAP *fs_buffer;              // BITMAP pour le double buffering en plein écran
    BITMAP *loading_screen;         // BITMAP qui contient le loading screen
    BITMAP *fs_loading_screen;      // BITMAP qui contient le loading screen en plein écran
    BITMAP *cursor;                 // Sprite du curseur
    BITMAP *pointer;                // Sprite du pointeur
    int fs;                         // Booléen qui indique si le jeu est en plein écran
    int fs_taille_case;             // Taille d'une case de la matrice en fullscreen
    s_bouton *boutons;              // Liste des boutons customs
    int nombre_boutons;             // Nombre de boutons customs
} s_graphic;

#include "Utils/Utils.h"
#include "Matrice/meubles.h"
#include "Commandes/Recettes.h"
#include "Game/Game.h"
#include "allezgros/Allezgros.h"

#endif //HYPERCOOKED_BACKEND_H

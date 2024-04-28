#ifndef HYPERCOOKED_BACKEND_H
#define HYPERCOOKED_BACKEND_H

#define STRMAX 120
#define HAUTEUR 12
#define LARGEUR 20
#define NB_RECETTES_MAX 10
#define NB_INGREDIENTS_MAX 10
#define NB_COMMANDES_MAX 5
#define NB_MAPS_MAX 10
#define SPEED 0.1
#define WIDTH 800
#define HEIGHT 450

#include "allegro.h"

typedef struct s_coo {                           // Structure pour des vecteurs, des coordonnées
    int x;
    int y;
} s_coo;

typedef struct s_color {
    int r;                                       // Rouge
    int g;                                       // Vert
    int b;                                       // Bleu
} s_color;

typedef enum e_etat_jeu {                        // Indique l'état du jeu
    LOADING,
    PLAYING,
    DANS_MENU,
    DANS_MENU_JEU
} e_etat_jeu;

typedef enum e_ingredients {                     // Indique le type de l'ingrédient
    SALADE, //1
    PAIN,
    TOMATE,
    STEAK,
    OEUF,
    POTATO,
} e_ingredients;

typedef enum e_cuisson {                         // Indique le type de cuisson nécessaire
    NON,
    A_LA_MARMITE,
    A_LA_POELE
} e_cuisson;

typedef struct s_ingredient {
    e_ingredients nom;                           // Indique le type de l'ingrédient
    e_cuisson cuisson;                           // Indique le type de cuisson nécessaire
    int cuit;                                    // Booléen qui indique si l'ingrédient est cuit comme demandé
    int coupable;                                // Booléen qui indique si l'ingrédient est coupable
    int coupe;                                   // Booléen qui indique si l'ingrédient est coupé
} s_ingredient;

typedef struct s_recette {
    char nom[STRMAX];                            // Nom de la recette
    s_ingredient ingredients[NB_INGREDIENTS_MAX];// Tableau des ingrédients dans la recette
    int nbIngredients;                           // Nombre d'ingrédients dans la recette
} s_recette;

typedef struct s_commande {
    int timer;                                   // Temps pour réaliser la commande
    s_recette recette;                           // La recette a réalisé
    fixed angle;                                 // Angle de la carte de la commande
} s_commande;

typedef enum e_meubles {                         // Indique le type du meuble
    SOL,
    PLAN_DE_TRAVAIL,
    PLANCHE_A_DECOUPER,
    COMPTOIR,
    COFFRE,
    PLAQUE_A_CUISSON,
    POUBELLE
} e_meubles;

typedef enum e_objet {                           // Indique le type de l'objet
    NONE,
    POELE,
    MARMITE,
    ASSIETTE,
    EXTINCTEUR,
    STOCKEUR
} e_objet;

typedef enum e_stockage {                        // Inqique la taille du contenant
    SANS = 0,
    UN_SLOT = 1,
    TROIS_SLOTS = 3,
    RECETTE = 10
} e_stockage;

typedef struct s_objet {
    e_objet type;                                // Type de l'objet
    s_ingredient nourriture[NB_INGREDIENTS_MAX]; // Tableau des objets stockés actuellement
    e_stockage stockageMax;                      // Nombre maximum d'objet stockables
    int nbStockes;                               // Nombre d'objet stockés actuellement
} s_objet;

typedef struct s_meuble {
    e_meubles typeMeuble;                        // Type du meuble
    s_objet objet;                               // L'objet sur le meuble ( objet ou null )
    void (*action)();                            // Fonction appelée quand on interagit avec le meuble
} s_meuble;

typedef enum e_typeEnMain {                      // Inqique le contenu de la main du joueur
    NOTHING,
    INGREDIENT,
    OBJET
} e_typeEnMain;

typedef struct s_joueur {
    s_color couleur;                             // Couleur du joueur
    char nom[STRMAX];                            // Nom du joueur
    float x;                                     // Position x du joueur
    float y;                                     // Position y du joueur
    fixed angle;                                 // Angle du joueur
    s_ingredient handIngredient;                 // Nourriture dans la main du joueur
    s_objet handObjet;                           // Objet dans la main du joueur
    e_typeEnMain en_main;                        // Indique ce qu'il y a dans la main du joueur
} s_joueur;

typedef struct s_game {
    s_meuble matrice[HAUTEUR][LARGEUR];          // Matrice qui contient tous les meubles et leurs infos
    s_joueur joueurs[2];                         // Tableau qui contient les infos sur les deux joueurs
    s_recette recettes[NB_RECETTES_MAX];         // Tableau des recettes disponibles
    int nbRecettes;                              // Nombre de recettes disponibles
    e_etat_jeu etatJeu;                          // L'état du jeu: LOADING, PLAYING, MENU
    s_commande commandes[NB_COMMANDES_MAX];      // Tableau de commande qui contient les commandes en cours
    int nbCommandes;                             // Nombre de commandes en cours
    int score;                                   // Le score jusqu'ici
} s_game;

/*############### ALLEZGROS ###############*/
typedef struct s_rectangle {
    int h;                                       // Hauteur
    int w;                                       // Largeur
    int color;                                   // Couleur ( utilise makecol() )
    int x;                                       // Position X du centre
    int y;                                       // Position Y du centre
    int fill;                                    // Si le rectangle est rempli ou non
} s_rectangle;

typedef struct s_bouton {
    BITMAP *bmp;                                 // Image sur laquelle on dessine
    s_rectangle rectangle;                       // Instance de s_rectangle
    void (*callback)();                          // Pointeur de fonction qui sera appelée
    char *text;                                  // Texte affiché sur l'écran
    int textColor;                               // Couleur du texte affiché
} s_bouton;

typedef struct s_ressources {
    BITMAP *loadingScreen;                       // BITMAP qui contient le loading screen
    BITMAP *fsLoadingScreen;                     // BITMAP qui contient le loading screen en plein écran
    BITMAP *buffer;                              // BITMAP pour le jeu
    BITMAP *fsBuffer;                            // BITMAP pour le jeu en plein écran
    BITMAP *mainMenuBuffer;                      // BITMAP pour le menu
    BITMAP *fsMainMenuBuffer;                    // BITMAP pour le menu en plein écran
    BITMAP *menuBuffer;                          // BITMAP pour le menu pendant la partie
    BITMAP *fsMenuBuffer;                        // BITMAP pour le menu pendant la partie en plein écran
} s_ressources;

typedef struct s_textures {
    BITMAP *cursor;                              // Texture du curseur
    BITMAP *pointer;                             // Texture du pointeur
    BITMAP *player;                              // Texture du joueur
    BITMAP *sol;                                 // Texture du sol
    BITMAP *comptoir;                            // Texture du comptoir
    BITMAP *coffre;                              // Texture du coffre
    BITMAP *poubelle;                            // Texture de la poubelle
    BITMAP *plancheADecouper;                    // Texture de la planche à découper
    BITMAP *planDeTravail;                       // Texture du plan de travail
    BITMAP *plaqueDeCuisson;                     // Texture de la plaque de cuisson
    BITMAP *poele;                               // Texture de la poêle
    BITMAP *marmite;                             // Texture de la marmite
    BITMAP *assiette;                            // Texture de l'assiette
    BITMAP *extincteur;                          // Texture de l'extincteur
    BITMAP *ticket;                              // Texture du ticket
    BITMAP *BAR;                                 // Texture du bar
    BITMAP *PlancheH;  // Texture de la planche horizontale
    BITMAP *Laitue;
    BITMAP *Oeuf;
    BITMAP *Pain;
    BITMAP *PommeDeTerre;
    BITMAP *steak;
    BITMAP *tomate;
    BITMAP *burger;
    BITMAP *Salade;
} s_textures;

typedef struct s_graphic {
    int debug;                                   // Booléen qui indique si on affiche les informations de debug
    int fs_width;                                // Largeur de l'écran
    int fs_height;                               // Hauteur de l'écran
    float ratio;                                 // Ratio de la matrice
    int fs;                                      // Booléen qui indique si le jeu est en plein écran
    int tailleCase;                              // Taille d'une case de la matrice
    int fsTailleCase;                            // Taille d'une case de la matrice en fullscreen
    int rayon;                                   // Rayon du joueur
    int fsRayon;                                 // Rayon du joueur en fullscreen
    s_bouton *boutons;                           // Liste des boutons customs
    int nombreBoutons;                           // Nombre de boutons customs
    s_ressources ressources;                     // Structure qui contient les pointeurs de toutes les ressources
    s_textures textures;
} s_graphic;

#include "Utils/Utils.h"
#include "Matrice/meubles.h"
#include "Commandes/Recettes.h"
#include "Commandes/Commandes.h"
#include "Game/Game.h"
#include "Game/Actions.h"
#include "Game/Oncers.h"
#include "allezgros/Allezgros.h"

#endif //HYPERCOOKED_BACKEND_H

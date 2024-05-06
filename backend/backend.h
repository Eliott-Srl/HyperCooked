#ifndef HYPERCOOKED_BACKEND_H
#define HYPERCOOKED_BACKEND_H

#define STRMAX 120
#define HAUTEUR 12
#define LARGEUR 20
#define FRAMERATE 100
#define NB_RECETTES_MAX 10
#define NB_INGREDIENTS_MAX 10
#define NB_COMMANDES_MAX 6
#define NB_MAPS_MAX 10
#define SPEED ((get_refresh_rate() * 0.05) / 60)
#define WIDTH 800
#define HEIGHT 450
#define NUM_SONS 8

#include "allegro.h"

typedef struct s_game s_game;

/*############### UTILS ###############*/
typedef struct s_coo {                           // Structure pour des vecteurs, des coordonnées
    int x;
    int y;
} s_coo;

typedef struct s_color {
    int r;                                       // Rouge
    int g;                                       // Vert
    int b;                                       // Bleu
} s_color;


/*############### ALLEZGROS ###############*/
typedef struct s_rectangle_virtual {
    int h;                                       // Hauteur
    int w;                                       // Largeur
    int x;                                       // Position X du centre
    int y;                                       // Position Y du centre
} s_rectangle_virtual;

typedef struct s_rectangle {
    s_rectangle_virtual virtual;                 // Instance de s_rectangle_virtual
    int color;                                   // Couleur ( utilise makecol() )
    int fill;                                    // Si le rectangle est rempli ou non
} s_rectangle;

typedef struct s_bouton {
    BITMAP *bmp;                                 // Image sur laquelle on dessine
    int virtual;                                 // Booléen qui indique si le bouton est virtuel
    s_rectangle rectangle;                       // Instance de s_rectangle
    void (*callback)(s_game*);                    // Pointeur de fonction qui sera appelée
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
    BITMAP *settings;                            // BITMAP qui contient les paramètres
    BITMAP *fsSettings;                          // BITMAP qui contient les paramètres en plein écran
} s_ressources;

typedef struct s_textures {
    BITMAP *invalidTexture;                      // Texture par défaut
    BITMAP *cursor;                              // Texture du curseur
    BITMAP *pointer;                             // Texture du pointeur
    BITMAP *player;                              // Texture du joueur
    BITMAP *menuBackground;                      // Texture du fond du menu
    BITMAP *credit;                              // Texture du crédit
    BITMAP *background;                          // Texture du fond du jeu
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
    BITMAP *bar;                                 // Texture du bar
    BITMAP *plancheH;                            // Texture de la planche horizontale
    BITMAP *laitue;                              // Texture de la laitue
    BITMAP *laitueCoupee;                        // Texture de la laitue coupée
    BITMAP *oeuf;                                // Texture de l'oeuf
    BITMAP *pain;                                // Texture du pain
    BITMAP *pommeDeTerre;                        // Texture de la pomme de terre
    BITMAP *steak;                               // Texture du steak
    BITMAP *steakCuit;                           // Texture du steak cuit
    BITMAP *tomate;                              // Texture de la tomate
    BITMAP *tomateCoupee;                        // Texture de la tomate coupée
    BITMAP *burger;                              // Texture du burger
    BITMAP *salade;                              // Texture de la salade
    BITMAP *fromage;                             // Texture du fromage
    BITMAP *pizza;                               // Texture de la pizza
    BITMAP *piece;                               // Texture de la pièce
} s_textures;

typedef struct s_graphic {
    int debug;                                   // Booléen qui indique si on affiche les informations de debug
    int debug_button;                            // Booléen qui permet d'éviter le rebond du menu
    int fs;                                      // Booléen qui indique si le jeu est en plein écran
    int fs_width;                                // Largeur de l'écran
    int fs_height;                               // Hauteur de l'écran
    float ratio;                                 // Ratio de la matrice
    int tailleCase;                              // Taille d'une case de la matrice
    int fsTailleCase;                            // Taille d'une case de la matrice en fullscreen
    int rayon;                                   // Rayon du joueur
    int fsRayon;                                 // Rayon du joueur en fullscreen
    s_bouton *boutons;                           // Liste des boutons customs
    int nombreBoutons;                           // Nombre de boutons customs
    s_ressources ressources;                     // Structure qui contient les pointeurs de toutes les ressources
    s_textures textures;
} s_graphic;

/*############### JEU ###############*/
typedef enum e_etat_jeu {                        // Indique l'état du jeu
    LOADING,
    PLAYING,
    DANS_MENU,
    DANS_MENU_JEU
} e_etat_jeu;

typedef enum e_ingredients {                     // Indique le type de l'ingrédient
    PAS_D_INGREDIENT = -1,
    SALADE = 1,
    SALADE_COUPEE,
    PAIN,
    TOMATE,
    TOMATES_COUPEES,
    STEAK,
    STEAK_CUIT,
    OEUF,
    POTATO,
    FROMAGE
} e_ingredients;

typedef enum e_recettes {                     // Indique le type de l'ingrédient
    BURGER,
    P_SALADE,
    PIZZA
} e_recettes;

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
    e_recettes nom;                              // Nom de la recette
    s_ingredient ingredients[NB_INGREDIENTS_MAX];// Tableau des ingrédients dans la recette
    int nbIngredients;                           // Nombre d'ingrédients dans la recette
} s_recette;

typedef struct s_commande {
    int duration;                                   // Temps pour réaliser la commande
    int debut;                                   // Temps de début de la commande
    s_recette recette;                           // La recette a réalisé
    fixed angle;                                 // Angle de la carte de la commande
} s_commande;

typedef enum e_meubles {                         // Indique le type du meuble
    SOL,
    PLAN_DE_TRAVAIL,
    PLANCHE_A_DECOUPER,
    COMPTOIR,
    COFFRE,
    PLAQUE_DE_CUISSON,
    POUBELLE,
    GENERATEUR_ASSIETTE,
    POSITION_JOUEUR = 10
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
    RECETTE = 4
} e_stockage;

typedef struct s_objet {
    e_objet type;                                // Type de l'objet
    s_ingredient nourriture[NB_INGREDIENTS_MAX]; // Tableau des objets stockés actuellement
    e_stockage stockageMax;                      // Nombre maximum d'objet stockables
    int nbStockes;                               // Nombre d'objet stockés actuellement
} s_objet;

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
    int shift_pressed;                           // Booléen qui indique si le shift est pressé
    int score;                                   // Score du joueur
} s_joueur;

typedef struct s_meuble {
    e_meubles typeMeuble;                        // Type du meuble
    s_objet objet;                               // L'objet sur le meuble ( objet ou null )
    void (*action)(s_game*, s_joueur*, int, int);         // Fonction appelée quand on interagit avec le meuble
    int timer;                                   // Timer pour les actions
} s_meuble;

typedef struct s_game {
    s_meuble matrice[HAUTEUR][LARGEUR];          // Matrice qui contient tous les meubles et leurs infos
    s_joueur joueurs[2];                         // Tableau qui contient les infos sur les deux joueurs
    s_recette recettes[NB_RECETTES_MAX];         // Tableau des recettes disponibles dans le jeu
    e_recettes recetteAvailable[NB_RECETTES_MAX];// Tableau des recettes disponibles pour la partie
    int nbRecettes;                              // Nombre de recettes disponibles
    int nbRecettesAvailable;                     // Nombre de recettes disponibles
    int duration;                                // Durée de la partie
    int timeBtCommandes;                         // Temps écoulé
    e_etat_jeu etatJeu;                          // L'état du jeu: LOADING, PLAYING, MENU
    s_commande commandes[NB_COMMANDES_MAX + 1];  // Tableau de commande qui contient les commandes en cours
    int nbCommandes;                             // Nombre de commandes en cours
    int score;                                   // Le score jusqu'ici
    int recettes_ratees;                         // Nombre de recettes ratées
    int recettes_reussi;                         // Nombre de recettes créées
    s_graphic graphic;                           // Structure qui contient les paramètres graphiques
} s_game;

/*############### SETTINGS ###############*/
typedef struct s_sound {
    SAMPLE* son;                                // Pointeur vers l'échantillon sonore
    int volume;                                 // Volume du son
    int pan;                                    // Position stéréo du son
    int pitch;                                  // Hauteur du son
    int loop;                                   // Booléen qui indique si le son doit être joué en boucle
} s_sound;

typedef struct leson{
    s_sound sons[NUM_SONS];
}s_leson;

/*############### SETTINGS ###############*/
typedef struct s_settings {
    int volume;                                  // Volume de la musique
} s_settings;

#include "Utils/Utils.h"
#include "Matrice/meubles.h"
#include "Commandes/Recettes.h"
#include "Commandes/Commandes.h"
#include "Game/Game.h"
#include "Game/Actions.h"
#include "Game/Oncers.h"
#include "allezgros/Allezgros.h"
#include "Son/song.h"
#include "Commandes/Ingredients.h"
#include "Game/Players.h"
#include "Game/Objects.h"

#endif //HYPERCOOKED_BACKEND_H

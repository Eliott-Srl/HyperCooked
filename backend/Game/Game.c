#include "Game.h"
#include <time.h>
#include <stdio.h>

volatile int counter = 0;

void timer_handler() {
    counter++;
} END_OF_FUNCTION(timer_handler)

s_game *getGame() {
    static s_game *game;

    if (!game) {
        game = (s_game *) malloc(sizeof(s_game));
    }

    return game;
}

void hc_init() {
    allegro_init();
    set_window_title("The best game ever");

    install_mouse();
    install_keyboard();
    install_timer();

    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,WIDTH, HEIGHT, 0, 0) != 0) {
        allegro_message("Pb de mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // écran de chargement ici
    s_graphic *graphic = getGraphic();
    graphic->loadingScreen = load_bitmap("./res/img/homme.bmp", NULL);

    if (!graphic->loadingScreen) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    hc_textprintf_centre_hv(graphic->loadingScreen, font, makecol(255, 255, 255), -1, "Loading...");
    hc_blit(graphic->loadingScreen);

    graphic->fsLoadingScreen = load_bitmap("./res/img/homme.bmp", NULL);

    if (!graphic->fsLoadingScreen) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->fs = 0;
    graphic->tailleCase = 10;          // à redéfinir, je ne suis pas sûr de ça
    graphic->fsTailleCase = 20;       // à redéfinir, je ne suis pas sûr de ça non plus
    graphic->buffer = create_bitmap(WIDTH, HEIGHT);

    if (!graphic->buffer) {
        allegro_message("Erreur de création du buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->fsBuffer = create_bitmap(FS_WIDTH, FS_HEIGHT);

    if (!graphic->fsBuffer) {
        allegro_message("Erreur de création du buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    graphic->cursor = load_bitmap("./res/img/cursor.bmp", NULL);

    if (!graphic->cursor) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->pointer = load_bitmap("./res/img/pointer.bmp", NULL);

    if (!graphic->pointer) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    LOCK_VARIABLE(counter);
    LOCK_FUNCTION(timer_handler);

    s_game *game = getGame();

    if (!game) {
        allegro_message("Erreur d'allocation");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->nbRecettes = 0;
    game->etatJeu = LOADING;

    loadRecipes();
}

int loadingMaps(char *maps[NB_MAPS_MAX]) {
    int map_index = 0;

    // Récupération des maps
    struct dirent *dir;
    DIR *d = opendir("./maps/");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            // printf("%s\n", dir->d_name);
            if (startsWith(dir->d_name, "map") && endsWith(dir->d_name, ".txt")) {
                maps[map_index] = dir->d_name;
                map_index++;
            }
        }
        closedir(d);
    }

    return map_index;
}

void jeu(int niveau) {
    s_game *game = getGame();
    int recettes_crees = 0;
    install_int_ex(timer_handler, SECS_TO_TIMER(1));
    afficherMatrice(game->matrice); // afficher la matrice

    do {
        if (game->etatJeu == DANS_MENU_JEU) {
            // TODO: Menu Jeu
        } else if (game->etatJeu == PLAYING) {
            // Toutes les 20 secondes, il y a une nouvelle recette qui est rendu disponible
            if (counter > (recettes_crees + 1) * 20) {
                newRecette();
                recettes_crees++;
            }

            deplacerPersonnages();
            // afficherMatrice(game->matrice);
            hc_
        }
    } while (counter <= 90 || (game->etatJeu != DANS_MENU_JEU && game->etatJeu != PLAYING));
}

void reinitialiserPartie() {
    for (int i = 0; i < NB_COMMANDES_MAX; i++) {
        getGame()->partie.commandes[i].recette.nbIngredients = 0;
        getGame()->partie.commandes[i].timer = 0;
    }
    getGame()->partie.nbCommandes = 0;
    getGame()->partie.score = 0;
    getGame()->partie.temps = 0;
}

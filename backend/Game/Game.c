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
        game = (s_game *) calloc(1, sizeof(s_game));
    }

    return game;
}

void hc_init() {
    allegro_init();
    set_window_title("The best game ever");

    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,WIDTH, HEIGHT, 0, 0) != 0) {
        allegro_message("Pb de mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // écran de chargement ici
    s_graphic *graphic = getGraphic();

    graphic->ressources.loadingScreen = create_bitmap(WIDTH, HEIGHT);

    if (!graphic->ressources.loadingScreen) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // On doit trouver une meilleure image de fond
    BITMAP *background = load_bitmap("./res/img/homme.bmp", NULL);

    if (!background) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    coverBufferWithImage(graphic->ressources.loadingScreen, background, 32, 32);

    int fs_width, fs_height;

    if (get_desktop_resolution(&fs_width, &fs_height) != 0) {
        allegro_message("Pb graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->fs = 0;
    graphic->fs_width = fs_width;
    graphic->fs_height = fs_height;
    graphic->ratio = (float) graphic->fs_width / (float) WIDTH;
    graphic->tailleCase = 30;       // à redéfinir, je ne suis pas sûr de ça
    graphic->fsTailleCase = (int) ((float) graphic->tailleCase * graphic->ratio);

    hc_textprintf_centre_hv(graphic->ressources.loadingScreen, font, makecol(255, 255, 255), -1, "Loading...");
    blit(graphic->ressources.loadingScreen, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

    install_timer();
    install_mouse();
    install_keyboard();

    graphic->ressources.fsLoadingScreen = create_bitmap(fs_width, fs_height);

    if (!graphic->ressources.fsLoadingScreen) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    coverBufferWithImage(graphic->ressources.fsLoadingScreen, background, 32, 32);

    graphic->ressources.buffer = create_bitmap(WIDTH, HEIGHT);

    if (!graphic->ressources.buffer) {
        allegro_message("Erreur de création du buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->ressources.fsBuffer = create_bitmap(graphic->fs_width, graphic->fs_height);

    if (!graphic->ressources.fsBuffer) {
        allegro_message("Erreur de création du buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->ressources.cursor = load_bitmap("./res/img/cursor.bmp", NULL);

    if (!graphic->ressources.cursor) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->ressources.pointer = load_bitmap("./res/img/pointer.bmp", NULL);

    if (!graphic->ressources.pointer) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->ressources.player = load_bitmap("./res/img/homme.bmp", NULL);

    if (!graphic->ressources.player) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.sol = load_bitmap("./res/img/sol.bmp", NULL);

    if (!graphic->textures.sol) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.ticket = load_bitmap("./res/img/Ticket3.0.bmp", NULL);

    if (!graphic->textures.ticket) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.PlancheH = load_bitmap("./res/img/plancheH.bmp", NULL);

    if (!graphic->textures.PlancheH) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.BAR = load_bitmap("./res/img/BAR.bmp", NULL);

    if (!graphic->textures.BAR) {
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

void initialisePlayers(s_color c_player1, const char *n_player1, s_color c_player2, const char *n_player2) {
    for (int i = 0; i < 2; i++) {
        getGame()->joueurs[i].pos.x = WIDTH / 2 + ((i * 2 - 1) * getCorrectCaseSize());
        getGame()->joueurs[i].pos.y = HEIGHT / 2;
        getGame()->joueurs[i].en_main = NOTHING;
    }

    getGame()->joueurs[0].couleur = c_player1;
    strcpy(getGame()->joueurs[0].nom, n_player1);

    getGame()->joueurs[1].couleur = c_player2;
    strcpy(getGame()->joueurs[1].nom, n_player2);
void showCustomCursor() {
    stretch_sprite(getCorrectBuffer(), getGraphic()->textures.cursor, mouse_x, mouse_y, 40, 40);
}

void jeu(int niveau) {
    s_game *game = getGame();
    int recettes_crees = 0;
    install_int_ex(timer_handler, SECS_TO_TIMER(1));

    do {
        hc_clear_buffers();

        if (game->etatJeu == DANS_MENU_JEU) {
            // TODO: Menu Jeu
        } else if (game->etatJeu == PLAYING) {
            hc_afficher_matrice();
            deplacerPersonnages();

            // Toutes les 40 secondes, il y a une nouvelle recette qui est rendu disponible
            if (counter > (recettes_crees + 1) * 40) {
                newCommande();
                recettes_crees++;
            }
            AfficherCommande();
        }

        showCustomCursor();

        hc_blit(getCorrectBuffer());

        if (key[KEY_F11]) {
            getGraphic()->fs = !getGraphic()->fs;
            set_gfx_mode(getGraphic()->fs ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, getGraphic()->fs ? getGraphic()->fs_width : WIDTH, getGraphic()->fs ? getGraphic()->fs_height : HEIGHT, 0, 0);
            for (int i = 0; i < 2; i++) {
                getGame()->joueurs[i].x = (getGraphic()->fs ? (float) getGame()->joueurs[i].x * getGraphic()->ratio : (float) getGame()->joueurs[i].x / getGraphic()->ratio);
                getGame()->joueurs[i].y = (getGraphic()->fs ? (float) getGame()->joueurs[i].y * getGraphic()->ratio : (float) getGame()->joueurs[i].y / getGraphic()->ratio);
            }
        }

        if (key[KEY_F3]) {
            getGraphic()->debug = !getGraphic()->debug;
        }
    } while (counter <= 90 || (game->etatJeu != DANS_MENU_JEU && game->etatJeu != PLAYING));
}


#include "Oncers.h"

void hc_init() {
    allegro_init();
    set_window_title("HyperCooked");

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

    graphic->debug = 0;
    graphic->debug_button = 0;
    graphic->fs = 0;
    graphic->fs_width = fs_width;
    graphic->fs_height = fs_height;
    graphic->ratio = (float) graphic->fs_width / (float) WIDTH;
    graphic->tailleCase = 24;       // à redéfinir, je ne suis pas sûr de ça
    graphic->fsTailleCase = (int) ((float) graphic->tailleCase * graphic->ratio);
    graphic->rayon = 9;            // à redéfinir, je ne suis pas sûr de ça
    graphic->fsRayon = (int) ((float) graphic->rayon * graphic->ratio);
    graphic->boutons = malloc(sizeof(s_bouton *));
    graphic->nombreBoutons = 0;

    hc_textprintf_centre_hv(graphic->ressources.loadingScreen, font, makecol(255, 255, 255), -1, "Loading...");
    blit(graphic->ressources.loadingScreen, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

    install_timer();
    install_mouse();
    install_keyboard();

    if (install_joystick(JOY_TYPE_AUTODETECT) != 0) {
        allegro_message("Error initialising joystick!");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

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

    graphic->ressources.mainMenuBuffer = create_bitmap(WIDTH, HEIGHT);

    if (!graphic->ressources.mainMenuBuffer) {
        allegro_message("Erreur de création du buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->ressources.fsMainMenuBuffer = create_bitmap(getGraphic()->fs_width, getGraphic()->fs_height);

    if (!graphic->ressources.fsMainMenuBuffer) {
        allegro_message("Erreur de création du buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.cursor = load_bitmap("./res/img/cursor.bmp", NULL);

    if (!graphic->textures.cursor) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.pointer = load_bitmap("./res/img/pointer.bmp", NULL);

    if (!graphic->textures.pointer) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.player = load_bitmap("./res/img/homme.bmp", NULL);

    if (!graphic->textures.player) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.background = load_bitmap("./res/img/background.bmp", NULL);

    if (!graphic->textures.background) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.menuBackground = load_bitmap("./res/img/fond_menu.bmp", NULL);

    if (!graphic->textures.menuBackground) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.credit = load_bitmap("./res/img/credits.bmp", NULL);

    if (!graphic->textures.credit) {
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

    graphic->textures.planDeTravail = load_bitmap("./res/img/plancheH.bmp", NULL);

    if (!graphic->textures.planDeTravail) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.ticket = load_bitmap("./res/img/Ticket2.1.bmp", NULL);

    if (!graphic->textures.ticket) {
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

    graphic->textures.PlancheH = load_bitmap("./res/img/plancheH.bmp", NULL);

    if (!graphic->textures.PlancheH) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    graphic->textures.Laitue = load_bitmap("./res/img/Laitue.bmp", NULL);

    if (!graphic->textures.Laitue) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.Oeuf = load_bitmap("./res/img/Oeuf.bmp", NULL);

    if (!graphic->textures.Oeuf) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.Pain = load_bitmap("./res/img/Pain.bmp", NULL);

    if (!graphic->textures.Pain) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.PommeDeTerre = load_bitmap("./res/img/Pomme_de_terre.bmp", NULL);

    if (!graphic->textures.PommeDeTerre) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.steak = load_bitmap("./res/img/Steak.bmp", NULL);

    if (!graphic->textures.steak) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.tomate = load_bitmap("./res/img/Tomates.bmp", NULL);

    if (!graphic->textures.tomate) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.burger = load_bitmap("./res/img/Burger.bmp", NULL);

    if (!graphic->textures.burger) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.Salade = load_bitmap("./res/img/Salade.bmp", NULL);

    if (!graphic->textures.Salade) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    s_game *game = getGame();

    if (!game) {
        allegro_message("Erreur d'allocation");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->nbRecettes = 0;
    game->etatJeu = LOADING;
    game->quitting = 0;

    srand(time(NULL));

    mouse_callback = &mouseActions;
    set_close_button_callback(&toQuit);
    loadRecipes();
}

int loadingMaps(char maps[NB_MAPS_MAX][STRMAX]) {
    int map_index = 0;

    // Récupération des maps
    struct dirent *dir;
    DIR *d = opendir("./maps");
    if (d) {
        while ((dir = readdir(d)) != NULL && map_index < NB_MAPS_MAX) {
            // allegro_message("%s\n", dir->d_name);
            if (startsWith(dir->d_name, "map") && endsWith(dir->d_name, ".txt")) {
                strncpy(maps[map_index], dir->d_name, STRMAX);
                map_index++;
            }
        }
        closedir(d);
    }

    return map_index;
}

void initialisePlayers(s_color c_player1, const char *n_player1, s_color c_player2, const char *n_player2) {
    for (int i = 0; i < 2; i++) {
        getGame()->joueurs[i].x = (float) WIDTH / 2 + (float) ((i * 2 - 1) * getCorrectCaseSize());
        getGame()->joueurs[i].y = (float) HEIGHT / 2;
        getGame()->joueurs[i].en_main = NOTHING;
    }

    getGame()->joueurs[0].couleur = c_player1;
    strcpy(getGame()->joueurs[0].nom, n_player1);

    getGame()->joueurs[1].couleur = c_player2;
    strcpy(getGame()->joueurs[1].nom, n_player2);
}

void reinitialiserPartie() {
    for (int i = 0; i < NB_COMMANDES_MAX; i++) {
        getGame()->commandes[i].recette.nbIngredients = 0;
        getGame()->commandes[i].timer = 0;
    }
    getGame()->nbCommandes = 0;
    getGame()->score = 0;
}

void hc_finish() {
    free(getGame());
    free(getGraphic());
    allegro_exit();
    exit(EXIT_SUCCESS);
}

#include "Oncers.h"

void hc_init() {
    allegro_init();
    set_window_title("HyperCooked");

    set_color_depth(desktop_color_depth());
    request_refresh_rate(FRAMERATE);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,WIDTH, HEIGHT, 0, 0) != 0) {
        allegro_message("Pb de mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    /*if (get_refresh_rate() != FRAMERATE) {
        allegro_message("Pb de framerate");
        allegro_exit();
        exit(EXIT_FAILURE);
    }*/

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

    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
        allegro_message("Erreur d'initialisation du système audio.");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

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

    graphic->textures.invalidTexture = load_bitmap("./res/img/invalid_texture.bmp", NULL);

    if (!graphic->textures.invalidTexture) {
        allegro_message("Erreur de chargement de l'image");
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

    graphic->textures.comptoir = load_bitmap("./res/img/comptoir.bmp", NULL);

    if (!graphic->textures.comptoir) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.planDeTravail = load_bitmap("./res/img/marbre.bmp", NULL);

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

    graphic->textures.bar = load_bitmap("./res/img/bar.bmp", NULL);

    if (!graphic->textures.bar) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.poele = load_bitmap("./res/img/poele.bmp", NULL);

    if (!graphic->textures.poele) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.plancheH = load_bitmap("./res/img/planche2.0.bmp", NULL);

    if (!graphic->textures.plancheH) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    graphic->textures.laitue = load_bitmap("./res/img/laitue.bmp", NULL);

    if (!graphic->textures.laitue) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.laitueCoupee = load_bitmap("./res/img/laitue_coupee.bmp", NULL);

    if (!graphic->textures.laitueCoupee) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.oeuf = load_bitmap("./res/img/oeuf.bmp", NULL);

    if (!graphic->textures.oeuf) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.pain = load_bitmap("./res/img/pain.bmp", NULL);

    if (!graphic->textures.pain) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.pommeDeTerre = load_bitmap("./res/img/Pomme de terre.bmp", NULL);

    if (!graphic->textures.pommeDeTerre) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.plancheADecouper = load_bitmap("./res/img/plancheH.bmp", NULL);

    if (!graphic->textures.plancheADecouper) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.assiette = load_bitmap("./res/img/assiette.bmp", NULL);

    if (!graphic->textures.assiette) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.plaqueDeCuisson = load_bitmap("./res/img/Plaque_de_cuisson.bmp", NULL);

    if (!graphic->textures.plaqueDeCuisson) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.poubelle = load_bitmap("./res/img/poubelle.bmp", NULL);

    if (!graphic->textures.poubelle) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.steak = load_bitmap("./res/img/steak_pas_cuit.bmp", NULL);

    if (!graphic->textures.steak) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.steakCuit = load_bitmap("./res/img/steak.bmp", NULL);

    if (!graphic->textures.steakCuit) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.tomate = load_bitmap("./res/img/Tomate.bmp", NULL);

    if (!graphic->textures.tomate) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.tomateCoupee = load_bitmap("./res/img/tomates_coupees.bmp", NULL);

    if (!graphic->textures.tomateCoupee) {
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

    graphic->textures.salade = load_bitmap("./res/img/salade.bmp", NULL);

    if (!graphic->textures.salade) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    graphic->textures.pizza = load_bitmap("./res/img/pizza.bmp", NULL);

    if (!graphic->textures.pizza) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    graphic->textures.fromage = load_bitmap("./res/img/fromage.bmp", NULL);

    if (!graphic->textures.fromage) {
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
    set_display_switch_callback(SWITCH_OUT, &afficherPause);
    set_mouse_speed(10, 10);
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

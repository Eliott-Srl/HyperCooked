#include "Oncers.h"

void hc_init(s_game *game) {
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
    s_graphic *graphic = &game->graphic;

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

    coverBufferWithImage(game, graphic->ressources.loadingScreen, background, 32, 32);

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

    hc_textprintf_centre_hv(game, graphic->ressources.loadingScreen, font, makecol(255, 255, 255), -1, "Loading...");
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

    coverBufferWithImage(game, graphic->ressources.fsLoadingScreen, background, 32, 32);

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

    graphic->ressources.fsMainMenuBuffer = create_bitmap(game->graphic.fs_width, game->graphic.fs_height);

    if (!graphic->ressources.fsMainMenuBuffer) {
        allegro_message("Erreur de création du buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->ressources.scoreBuffer = create_bitmap(WIDTH, HEIGHT);

    if (!graphic->ressources.scoreBuffer) {
        allegro_message("Erreur de création du buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->ressources.fsScoreBuffer = create_bitmap(game->graphic.fs_width, game->graphic.fs_height);

    if (!graphic->ressources.fsScoreBuffer) {
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

    graphic->textures.settings = load_bitmap("./res/img/fond_menu_settings.bmp", NULL);

    if (!graphic->textures.settings) {
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

    graphic->textures.piece = load_bitmap("./res/img/piece.bmp", NULL);

    if (!graphic->textures.piece) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.laitue = load_bitmap("./res/img/Laitue.bmp", NULL);

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

    graphic->textures.oeuf = load_bitmap("./res/img/Oeuf.bmp", NULL);

    if (!graphic->textures.oeuf) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graphic->textures.pain = load_bitmap("./res/img/Pain.bmp", NULL);

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

    graphic->textures.steakCuit = load_bitmap("./res/img/Steak.bmp", NULL);

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

    graphic->textures.salade = load_bitmap("./res/img/Salade.bmp", NULL);

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

    graphic->textures.void_texture = create_bitmap(getCorrectCaseSize(game), getCorrectCaseSize(game));

    if (!graphic->textures.void_texture) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    clear_to_color(graphic->textures.void_texture, makecol(255, 0, 255));

    game->sons[INTRO].son = load_sample("./res/song/intro.wav");

    if (!game->sons[INTRO].son) {
        allegro_message("Erreur de chargement du son");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->sons[INTRO].volume = 75;
    game->sons[INTRO].pan = 100;
    game->sons[INTRO].pitch = 1000;
    game->sons[INTRO].loop = 1;

    game->sons[PAS].son = load_sample("./res/song/Pas1.wav");

    if (!game->sons[PAS].son) {
        allegro_message("Erreur de chargement du son");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->sons[PAS].volume = 100;
    game->sons[PAS].pan = 100;
    game->sons[PAS].pitch = 1000;
    game->sons[PAS].loop = 0;

    game->sons[SON_ASSIETTE].son = load_sample("./res/song/Assiette.wav");

    if (!game->sons[SON_ASSIETTE].son) {
        allegro_message("Erreur de chargement du son");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->sons[SON_ASSIETTE].volume = 100;
    game->sons[SON_ASSIETTE].pan = 100;
    game->sons[SON_ASSIETTE].pitch = 1000;
    game->sons[SON_ASSIETTE].loop = 0;

    game->sons[SON_DEFAITE].son = load_sample("./res/song/Wihlem.wav");

    if (!game->sons[SON_DEFAITE].son) {
        allegro_message("Erreur de chargement du son");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->sons[SON_DEFAITE].volume = 100;
    game->sons[SON_DEFAITE].pan = 100;
    game->sons[SON_DEFAITE].pitch = 1000;
    game->sons[SON_DEFAITE].loop = 0;

    game->sons[SON_POUBELLE].son = load_sample("./res/song/Poubelle.wav");

    if (!game->sons[SON_POUBELLE].son) {
        allegro_message("Erreur de chargement du son");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->sons[SON_POUBELLE].volume = 100;
    game->sons[SON_POUBELLE].pan = 100;
    game->sons[SON_POUBELLE].pitch = 1000;
    game->sons[SON_POUBELLE].loop = 0;

    game->sons[SON_COMMANDE].son = load_sample("./res/song/Sonnette.wav");

    if (!game->sons[SON_COMMANDE].son) {
        allegro_message("Erreur de chargement du son");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->sons[SON_COMMANDE].volume = 100;
    game->sons[SON_COMMANDE].pan = 100;
    game->sons[SON_COMMANDE].pitch = 1000;
    game->sons[SON_COMMANDE].loop = 0;

    game->sons[SON_CUISSON].son = load_sample("./res/song/Cuisson.wav");

    if (!game->sons[SON_CUISSON].son) {
        allegro_message("Erreur de chargement du son");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->sons[SON_CUISSON].volume = 100;
    game->sons[SON_CUISSON].pan = 100;
    game->sons[SON_CUISSON].pitch = 1000;
    game->sons[SON_CUISSON].loop = 0;

    game->sons[SON_DECOUPE].son = load_sample("./res/song/Decoupage.wav");

    if (!game->sons[SON_DECOUPE].son) {
        allegro_message("Erreur de chargement du son");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->sons[SON_DECOUPE].volume = 100;
    game->sons[SON_DECOUPE].pan = 100;
    game->sons[SON_DECOUPE].pitch = 1000;
    game->sons[SON_DECOUPE].loop = 0;

    for (int i = 0; i < NUM_SONS; i++) {
        game->sons[i].voice = -1;
    }

    game->settings.music = 1;

    game->nbRecettes = 0;
    game->etatJeu = LOADING;

    srand(time(NULL));

    initialisePlayers(game);
    set_close_button_callback(&toQuit);
    set_mouse_speed(20, 20);
    loadRecipes(game);
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

void reinitialiserPartie(s_game *game) {
    for (int i = 0; i < NB_COMMANDES_MAX; i++) {
        game->commandes[i].recette.nbIngredients = 0;
        game->commandes[i].duration = 0;
        game->commandes[i].debut = 0;
    }
    game->nbCommandes = 0;
    game->score = 0;
}

void hc_finish(s_game *game) {
    free(game);
    allegro_exit();
    exit(EXIT_SUCCESS);
}

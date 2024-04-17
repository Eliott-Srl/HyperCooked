#include "backend/backend.h"
#include <dirent.h>

int main() {
    int width = 800;
    int height = 600;
    allegro_init();
    set_window_title("The best game ever");

    install_mouse();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,width, height, 0, 0) != 0) {
        allegro_message("Pb de mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // écran de chargement ici
    s_graphic *graphic = (s_graphic *) malloc(sizeof(s_graphic));
    set_graphic(graphic);
    get_graphic()->width = width;
    get_graphic()->height = height;

    BITMAP *loading_screen = load_bitmap("./res/img/loading_screen.bmp", NULL);

    if (!loading_screen) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    blit(loading_screen, screen, 0, 0, 0, 0, width, height);

    textprintf_centre_ex(screen, font, width/2, height/2, makecol(255, 255, 255), -1, "Loading");

    get_graphic()->cursor = load_bitmap("./res/img/cursor.bmp", NULL);

    if (!get_graphic()->cursor) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    get_graphic()->pointer = load_bitmap("./res/img/pointer.bmp", NULL);

    if (!get_graphic()->pointer) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    char* maps[10];
    int map_index = 0;

    // Récupération des maps
    struct dirent *dir;
    DIR *d = opendir("./maps/");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
            if (startsWith(dir->d_name, "map") && endsWith(dir->d_name, ".txt")) {
                maps[map_index] = dir->d_name;
                map_index++;
            }
        }
        closedir(d);
    }

    s_game *game = (s_game *) malloc(sizeof(s_game));

    if (!game) {
        allegro_message("Erreur d'allocation");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    game->nb_recettes = 0;
    loadRecipes(game);

    rest(1000);

    for (int i = 0; i < map_index + 1; i++) {
        char input;
        int timeBegin = 0;
        int timeSinceLastRecette = 0;
        int timeSinceBegin = 0;
        char filename[STRMAX];

        game->partie.score = 0;
        game->partie.temps = 0;

        sprintf(filename, "/maps/%s", maps[i]);

        initialiserMatrice(game->matrice, filename); // créer un fichier ou les meubles apparais

        clear(screen);
        // Fin de l'écran de chargement

        afficherMatrice(game->matrice); // afficher la matrice

        // Créer les joueurs

        // Gérer le timer
        timeBegin = timeSinceLastRecette = time(0);
        do {
            timeSinceBegin = time(0);

            // Toutes les 20 secondes, il y a une nouvelle recette qui est rendu disponible
            if (timeSinceBegin - timeSinceLastRecette > 20) {
                newRecette(game);
                timeSinceLastRecette = time(0);
            }

            deplacerPersonnages(game);
            // afficherMatrice(game->matrice);

            // printf("Il reste %d \n", 90 - (timeSinceBegin - timeBegin));
        } while (timeSinceBegin - timeBegin <= 90);
    }

    return 0;
} END_OF_MAIN()

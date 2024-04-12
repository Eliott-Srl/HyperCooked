#include "backend/backend.h"
#include <conio.h>
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

    get_graphic()->cursor = load_bitmap("cursor.bmp", NULL);

    if (!get_graphic()->cursor) {
        allegro_message("Erreur de chargement de l'image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    get_graphic()->pointer = load_bitmap("pointer.bmp", NULL);

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
                strcpy(maps[map_index], dir->d_name);
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

    game->nb_partie = 0;
    game->nb_recettes = 0;
    // Fin de l'écran de chargement

    for (int i = 0; i < map_index + 1; i++) {
        int dx = 0;
        int dy = 0;
        char input;
        int eltiempo = 0;
        int tempsDuJeux = 0;
        int perso = 0;
        char filename[STRMAX];

        s_partie *partie = realloc(game->partie, game->nb_partie + 1);

        if (!partie) {
            allegro_message("Erreur d'allocation");
            allegro_exit();
            exit(EXIT_FAILURE);
        }

        partie->score = 0;
        partie->temps = 0;
        game->partie[game->nb_partie] = *partie;
        game->nb_partie++;

        sprintf(filename, "/maps/%s", maps[i]);
        initialiserMatrice(game->matrice, filename); // créer un fichier ou les meubles apparais
        afficherMatrice(game->matrice); // afficher la matrice

        // Créer les joueurs
        loadRecipes(game);

        // Gérer le timer
        tempsDuJeux = timer();
        while (tempsDuJeux <= 90) {
            if(tempsDuJeux - eltiempo > 20){
                crearecettes(game); // crée une recette depuis la structure
                eltiempo = tempsDuJeux; //
            }

            input = getch();

            switch (input) {
                case 'z' :
                    dy++;
                    perso = 0;
                    break;
                case 's' :
                    dy--;
                    perso = 0;
                    break;
                case 'q' :
                    dx--;
                    perso = 0;
                    break;
                case 'd' :
                    dx++;
                    perso = 0;
                    break;
                case 75 :// Flèche gauche
                    dx--;
                    perso = 1;
                    break;
                case 77 :// Flèche droite
                    dx++;
                    perso = 1;
                    break;
                case 72 :// Flèche haut
                    dy++;
                    perso = 1;
                    break;
                case 80 :// Flèche bas
                    dy--;
                    perso = 1;
                    break;
            }



            deplacerPersonnage(game, &game->joueurs[perso], dx, dy);
            afficherMatrice(game->matrice);
            printf("Il reste %d \n", 90 - tempsDuJeux);
        }

        printf("Vous avez perdu, looooooseerrrr !!!");
    }

    return 0;
} END_OF_MAIN()

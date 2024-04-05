#include "allezgros/Allezgros.h"
#include <conio.h>
#include <dirent.h>

int main() {
    allegro_init();

    // écran de chargement ici

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

    // Initialisation des ressources


    // Fin de l'écran de chargement

    for (int i = 0; i < map_index + 1; i++) {
        int dx = 0;
        int dy = 0;
        char input;
        int eltiempo = 0;
        int tempsDuJeux = 0;
        int perso = 0;
        char filename[STRMAX];

        s_game *game = (s_game *) calloc(1, sizeof(s_game));

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

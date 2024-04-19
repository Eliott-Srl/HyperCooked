#include "backend/backend.h"
#include <dirent.h>

int main() {
    hc_init();

    char* maps[NB_MAPS_MAX];
    int nbMaps = loadingMaps(maps);

    rest(1000);

    for (int i = 0; i < nbMaps + 1; i++) {
        reinitialiserPartie();

        char filename[STRMAX];
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

                    elapsedTime = timeSinceBegin - timeBegin;
                }
            } while (elapsedTime <= 90 || (etatJeu != DANS_MENU_JEU && etatJeu != PLAYING));
        } else if (etatJeu == LOADING) {
            hc_blit(graphic->loading_screen);
        }
    }

    return 0;
} END_OF_MAIN()

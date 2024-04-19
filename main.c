#include "backend/backend.h"

int main() {
    hc_init();

    char* maps[NB_MAPS_MAX];
    int nbMaps = loadingMaps(maps);

    rest(1000);

    for (int i = 0; i < nbMaps + 1; i++) {
        reinitialiserPartie();

        char filename[STRMAX];
        sprintf(filename, "/maps/%s", maps[i]);

        initialiserMatrice(getGame()->matrice, filename); // créer un fichier ou les meubles apparais

        getGame()->etatJeu = DANS_MENU;

        clear(screen);
        // Fin de l'écran de chargement

        getGame()->etatJeu = PLAYING;
        if (getGame()->etatJeu == DANS_MENU) {
            // Créer les joueurs
        } else if (getGame()->etatJeu == PLAYING) {
            jeu(i + 1);
        } else if (getGame()->etatJeu == LOADING) {
            hc_blit(getGraphic()->loadingScreen);
        }
    }

    return 0;
} END_OF_MAIN()

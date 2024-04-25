#include "backend/backend.h"

int main() {
    hc_init();

    char* maps[NB_MAPS_MAX];
    int nbMaps = loadingMaps(maps);

    rest(10000);

    for (int i = 0; i < nbMaps + 1; i++) {
        reinitialiserPartie();

        char filename[STRMAX];
        sprintf(filename, "/maps/%s", maps[i]);

        initialiserMatrice(filename); // créer un fichier ou les meubles apparais

        getGame()->etatJeu = PLAYING;
        // Fin de l'écran de chargement

        s_color j1 = {255, 0, 0}, j2 = {0,0, 255};
        initialisePlayers(j1, "Stephane", j2, "Bernard");

        if (getGame()->etatJeu == DANS_MENU) {
            // Créer les joueurs
            getGame()->etatJeu = PLAYING;
        } else if (getGame()->etatJeu == PLAYING) {
            jeu(i + 1);
        } else if (getGame()->etatJeu == LOADING) {
            hc_blit(getGraphic()->ressources.loadingScreen);
        }
    }

    return 0;
} END_OF_MAIN()

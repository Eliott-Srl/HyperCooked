#include "Progress.h"

int getBestScoreByNiveau(int niveau) {
    char ligne[128];
    FILE *fichier = fopen("data/score.txt", "r");
    int niveauLu = 0, scoreLu;

    if (fichier == NULL) {
        allegro_message("Erreur lors de l'ouverture du fichier\n");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    while (fgets(ligne, 128, fichier) != NULL && niveauLu < niveau) {
        scoreLu = strtol(ligne, NULL, 10);
        niveauLu++;
    }

    fclose(fichier);

    if (niveauLu == niveau) {
        return scoreLu;
    } else {
        return 0;
    }
}

// à revoir pas sûr que ça marche
void writeBestScoreByNiveau(int niveau, int score) {
    int scores[NB_MAPS_MAX];
    for (int i = 0; i < NB_MAPS_MAX; i++) {
        if (i + 1 == niveau) {
            scores[i] = score;
        } else {
            scores[i] = getBestScoreByNiveau(i + 1);
        }
    }

    FILE *fichier = fopen("data/score.txt", "w");

    if (fichier == NULL) {
        allegro_message("Erreur lors de l'ouverture du fichier\n");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NB_MAPS_MAX; i++) {
        if (scores[i] != 0) {
            fprintf(fichier, (i + 1 == NB_MAPS_MAX ? "%d" : "%d\n"), scores[i]);
        } else {
            fprintf(fichier, (i + 1 == NB_MAPS_MAX ? "" : "\n"));
        }
    }

    fclose(fichier);
}

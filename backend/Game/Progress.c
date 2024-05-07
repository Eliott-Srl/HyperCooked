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
        return -1;
    }
}

// à revoir pas sûr que ça marche
void writeBestScoreByNiveau(int niveau, int score) {
    char ligne[128];
    FILE *fichier = fopen("data/score.txt", "w");
    int niveauLu = 0, scoreLu;

    if (fichier == NULL) {
        allegro_message("Erreur lors de l'ouverture du fichier\n");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    while (fgets(ligne, 128, fichier) != NULL && niveauLu < niveau) {
        niveauLu++;
    }

    if (niveauLu == niveau) {
        fprintf(fichier, "%d\n", score);
    } else {
        for (int i = 0; i < niveau - niveauLu; i++) {
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "%d\n", score);
    }

    fclose(fichier);
}

void resetProgression(s_game *game) {
    FILE *fichier = fopen("data/score.txt", "w");
    fclose(fichier);
}

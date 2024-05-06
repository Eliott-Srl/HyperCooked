#include "song.h"
#include "allegro.h"

// Fonction pour charger les échantillons sonores
void chargeSound(s_game *game, s_leson *leson) {
    leson->sons[0].son = load_wav("Pas.wav");
    if (!leson->sons[0].son) {
        allegro_message("Erreur lors du chargement du son 0");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    leson->sons[0].volume = 255;
    leson->sons[0].pan = 128;
    leson->sons[0].pitch = 1000;
    leson->sons[0].loop = 0;
}

// Fonction pour jouer un son spécifique
void playSound(s_game *game, s_leson *leson, int index) {
    if (index < 0 || index >= NUM_SONS) {
        // Gérer l'erreur si l'index est hors limites
        return;
    }

    play_sample(leson->sons[index].son, leson->sons[index].volume, leson->sons[index].pan, leson->sons[index].pitch, leson->sons[index].loop);
}

// Fonction pour libérer la mémoire des échantillons sonores
void freeSound(s_game *game, s_leson *leson) {
    int i;
    for (i = 0; i < NUM_SONS; i++) {
        destroy_sample(leson->sons[i].son);
    }
}

int charge_Sound(s_game *game, int choix) {
    // Initialisation Allegro
    if (allegro_init() != 0) {
        allegro_message("Erreur d'initialisation d'Allegro.");
        return -1;
    }

    // Initialiser les échantillons sonores
    s_leson leson;

    chargeSound(game, &leson);

    // Jouer un exemple de son (le premier dans cet exemple)
    playSound(game, &leson, 0);

    return 0;
}
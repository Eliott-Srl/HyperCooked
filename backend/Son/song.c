#include "song.h"
#include "allegro.h"

// Fonction pour charger les échantillons sonores
    void chargeSound(s_leson *leson) {
    leson->sons[0].son = load_sample("./res/res song/Pas.wav");
    leson->sons[0].volume = 255;
    leson->sons[0].pan = 128;
    leson->sons[0].pitch = 1000;
    leson->sons[0].loop = 10;

   leson->sons[1].son = load_sample("./res/res song/Cuisson.wav");
   leson->sons[1].volume = 255;
   leson->sons[1].pan = 128;
   leson->sons[1].pitch = 1000;
   leson->sons[1].loop = 0;

    leson->sons[2].son = load_sample("./res/res song/Découpage.wav");
    leson->sons[2].volume = 255;
    leson->sons[2].pan = 128;
    leson->sons[2].pitch = 1000;
    leson->sons[2].loop = 0;

    leson->sons[3].son = load_sample("./res/res song/Poubelle.wav");
    leson->sons[3].volume = 255;
    leson->sons[3].pan = 128;
    leson->sons[3].pitch = 1000;
    leson->sons[3].loop = 0;

    leson->sons[4].son = load_sample("./res/res song/Sonette.wav");
    leson->sons[4].volume = 255;
    leson->sons[4].pan = 128;
    leson->sons[4].pitch = 1000;
    leson->sons[4].loop = 0;

    leson->sons[5].son = load_sample("./res/res song/Cri Wihlem.wav");
    leson->sons[5].volume = 255;
    leson->sons[5].pan = 128;
    leson->sons[5].pitch = 1000;
    leson->sons[5].loop = 0;

    leson->sons[6].son = load_sample("./res/res song/Assiette.wav");
    leson->sons[6].volume = 255;
    leson->sons[6].pan = 128;
    leson->sons[6].pitch = 1000;
    leson->sons[6].loop = 0;

    leson->sons[7].son = load_sample("son8.wav");
    leson->sons[7].volume = 255;
    leson->sons[7].pan = 128;
    leson->sons[7].pitch = 1000;
    leson->sons[7].loop = 0;

}

// Fonction pour jouer un son spécifique
    void playSound(s_leson *leson, int index) {

        if (index < 0 || index >= NUM_SONS) {
            // Gérer l'erreur si l'index est hors limites
            return;
        }

        play_sample(leson->sons[index].son, leson->sons[index].volume, leson->sons[index].pan, leson->sons[index].pitch, leson->sons[index].loop);
    }

// Fonction pour libérer la mémoire des échantillons sonores
    void freeSound(s_leson *leson) {
        int i;
        for (i = 0; i < NUM_SONS; i++) {
            destroy_sample(leson->sons[i].son);
        }
    }

int charge_Sound(int choix) {
    // Initialisation Allegro
    if (allegro_init() != 0) {
        allegro_message("Erreur d'initialisation d'Allegro.");
        return -1;
    }

    // Initialisation du système audio
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
        allegro_message("Erreur d'initialisation du système audio.");
        return -1;
    }

    // Initialiser les échantillons sonores
        s_leson leson;

    chargeSound(&leson);

    // Jouer un exemple de son (le premier dans cet exemple)
    playSound(&leson, 0);

    // Attendre avant de fermer la fenêtre
    rest(2000);

    // Libérer la mémoire
    freeSound(&leson);

    return 0;
}
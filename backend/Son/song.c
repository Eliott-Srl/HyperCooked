#include "song.h"
#include "allegro.h"

// Fonction pour charger les échantillons sonores
    void chargeSound(s_sound sons[NUM_SONS]) {
    sons[0].son = load_sample("./res/res song/Pas.wav");
    sons[0].volume = 255;
    sons[0].pan = 128;
    sons[0].pitch = 1000;
    sons[0].loop = 10;

    sons[1].son = load_sample("./res/res song/Cuisson.wav");
    sons[1].volume = 255;
    sons[1].pan = 128;
    sons[1].pitch = 1000;
    sons[1].loop = 0;

    sons[2].son = load_sample("./res/res song/Découpage.wav");
    sons[2].volume = 255;
    sons[2].pan = 128;
    sons[2].pitch = 1000;
    sons[2].loop = 0;

    sons[3].son = load_sample("./res/res song/Poubelle.wav");
    sons[3].volume = 255;
    sons[3].pan = 128;
    sons[3].pitch = 1000;
    sons[3].loop = 0;

    sons[4].son = load_sample("./res/res song/Sonette.wav");
    sons[4].volume = 255;
    sons[4].pan = 128;
    sons[4].pitch = 1000;
    sons[4].loop = 0;

    sons[5].son = load_sample("./res/res song/Cri Wihlem.wav");
    sons[5].volume = 255;
    sons[5].pan = 128;
    sons[5].pitch = 1000;
    sons[5].loop = 0;

    sons[6].son = load_sample("./res/res song/Assiette.wav");
    sons[6].volume = 255;
    sons[6].pan = 128;
    sons[6].pitch = 1000;
    sons[6].loop = 0;

    sons[7].son = load_sample("son8.wav");
    sons[7].volume = 255;
    sons[7].pan = 128;
    sons[7].pitch = 1000;
    sons[7].loop = 0;

}

// Fonction pour jouer un son spécifique
    void playSound(s_sound sons[NUM_SONS], int index) {
        if (index < 0 || index >= NUM_SONS) {
            // Gérer l'erreur si l'index est hors limites
            return;
        }

        play_sample(sons[index].son, sons[index].volume, sons[index].pan, sons[index].pitch, sons[index].loop);
    }

// Fonction pour libérer la mémoire des échantillons sonores
    void freeSound(s_sound sound[NUM_SONS]) {
        int i;
        for (i = 0; i < NUM_SONS; i++) {
            destroy_sample(sound[i].son);
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
    s_sound sons[NUM_SONS];
    chargeSound(sons);

    // Jouer un exemple de son (le premier dans cet exemple)
    playSound(sons, choix);

    // Attendre avant de fermer la fenêtre
    rest(5000);

    // Libérer la mémoire
    freeSound(sons);

    return 0;
}
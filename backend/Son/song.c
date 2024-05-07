#include "song.h"
#include "allegro.h"


SAMPLE *JouerLintro() {
    SAMPLE *intro = load_sample("./res/song/intro.wav");
    if (!intro) {
        allegro_message("Erreur de chargement de son");
        return 0;
        }else{
    play_sample(intro, 100, 50, 1000, 1);
    return intro;
    }
}

void playScream(){
    SAMPLE *scream = load_sample("./res/song/Pas.wav");
    if(!scream){
        allegro_message("Erreur de chargement de son");
    } else{
        scream->priority = 2;
        int laservoice = allocate_voice(scream);
        voice_set_volume(laservoice, 200);
        voice_set_pan(laservoice, 200);
        voice_set_playmode(laservoice,PLAYMODE_PLAY);

        voice_start(laservoice);
    }
}
#include "Recettes/Recettes.h"
#include "Commandes/Commandes.h"
#include "allegro.h"

int rgbToAllegroColor(s_color color) {
    return makecol(color.r, color.g, color.b);
}

int main() {
    allegro_init();



    return 0;
} END_OF_MAIN()
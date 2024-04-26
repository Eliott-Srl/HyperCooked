#include "meubles.h"

void afficherMatrice() {
    for (int h = 0; h < HAUTEUR; h++) {
        for (int l = 0; l < LARGEUR; l++) {
            printf("%d ", getGame()->matrice[h][l].typeMeuble);
        }
        printf("\n");
    }
}

void initialiserMatrice(const char* file) {
    FILE *fichier;
    char ligne[128];
    s_game *game = getGame();

    // Ouvrir le fichier en mode lecture
    fichier = fopen(file, "r");

    char *base = "0123456789";

    int x;
    int y = 0;
    // Parcourir le fichier caractère par caractère
    while (fgets(ligne, 128, fichier) != NULL) {
        char *p = ligne;
        int a = 0;
        x = 0;
        char nombre[128] = "";
        while(*p != '\n' && *p != '\0') {
            if (strchr(base, *p) != NULL) {
                strncat(nombre, p, 1);
            } else if (*p == ' ') {
                game->matrice[y][x].typeMeuble = strtol(nombre, NULL, 10);
                game->matrice[y][x].objet.type = NONE;
                game->matrice[y][x].objet.nbStockes = 0;
                game->matrice[y][x].objet.stockageMax = 0;
                a = 1;
                nombre[0] = '\0';
            } else if (*p == ';') {
                if (a == 0) {
                    game->matrice[y][x].typeMeuble = strtol(nombre, NULL, 10);
                    game->matrice[y][x].objet.type = NONE;
                    game->matrice[y][x].objet.nbStockes = 0;
                    game->matrice[y][x].objet.stockageMax = 0;
                } else {
                    game->matrice[y][x].objet.type = strtol(nombre, NULL, 10);

                    if(strtol(nombre, NULL, 10) == POELE || strtol(nombre, NULL, 10) == ASSIETTE) {
                        game->matrice[y][x].objet.stockageMax = 1;
                    } else if(strtol(nombre, NULL, 10) == MARMITE) {
                        game->matrice[y][x].objet.stockageMax = 3;
                    } else {
                        game->matrice[y][x].objet.stockageMax = 0;
                    }

                    a = 0;
                }
                nombre[0] = '\0';
                x++;
            } else {
                exit(-1);
            }
            p++;
        }
        y++;
    }

    afficherMatrice();

    fclose(fichier);  // Fermer le fichier après avoir trouvé un espace
}



void hc_afficher_matrice() {
    // TODO: Charles tu vas bosser ici
    for(int h = 0; h < HAUTEUR; h++) {
        for(int l = 0; l < LARGEUR; l++) {
            if (getGame()->matrice[h][l].typeMeuble == SOL) {
                draw_sprite(getCorrectBuffer(), getGraphic()->textures.SOL, h*getCorrectCaseSize(), l*getCorrectCaseSize());
            }
            if (getGame()->matrice[h][l].typeMeuble == COMPTOIR) {
                getGraphic()->textures.COMPTOIR;
                //draw_sprite();
            }
            if (getGame()->matrice[h][l].typeMeuble == SOL) {
                getGraphic()->textures.COFFFRE;
            }
            if (getGame()->matrice[h][l].typeMeuble == SOL) {
                getGraphic()->textures.POUBELLE;
            }
        }
    }
    getGame()->matrice[0][0].typeMeuble == SOL;

    //getCorrectCaseSize();
}

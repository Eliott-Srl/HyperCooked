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
    char nombre[128] = "";

    int x;
    int y = 0;
    // Parcourir le fichier caractère par caractère
    while (fgets(ligne, 128, fichier) != NULL) {
        char *p = ligne;
        int a = 0;
        x = 0;
        char nombre[128] = "";

        while(*p != '\n' && *p != '\0') {
            if (strchr(base, *p) == NULL) {
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
                stretch_sprite(getCorrectBuffer(), getGraphic()->textures.SOL, (getCorrectWidth()-LARGEUR*getCorrectCaseSize())/2+l*getCorrectCaseSize(), (getCorrectHeight()-HAUTEUR*getCorrectCaseSize())/2+h*getCorrectCaseSize(), getCorrectCaseSize(), getCorrectCaseSize());
            }
            if (getGame()->matrice[h][l].typeMeuble == COMPTOIR) {
                stretch_sprite(getCorrectBuffer(), getGraphic()->textures.COMPTOIR, (getCorrectWidth()-LARGEUR*getCorrectCaseSize())/2+l*getCorrectCaseSize(), (getCorrectHeight()-HAUTEUR*getCorrectCaseSize())/2+h*getCorrectCaseSize(), getCorrectCaseSize(), getCorrectCaseSize());
            }
            if (getGame()->matrice[h][l].typeMeuble == COFFRE) {
                stretch_sprite(getCorrectBuffer(), getGraphic()->textures.COFFFRE, (getCorrectWidth()-LARGEUR*getCorrectCaseSize())/2+l*getCorrectCaseSize(), (getCorrectHeight()-HAUTEUR*getCorrectCaseSize())/2+h*getCorrectCaseSize(), getCorrectCaseSize(), getCorrectCaseSize());
            }
            if (getGame()->matrice[h][l].typeMeuble == POUBELLE) {
                stretch_sprite(getCorrectBuffer(), getGraphic()->textures.POUBELLE, (getCorrectWidth()-LARGEUR*getCorrectCaseSize())/2+l*getCorrectCaseSize(), (getCorrectHeight()-HAUTEUR*getCorrectCaseSize())/2+h*getCorrectCaseSize(), getCorrectCaseSize(), getCorrectCaseSize());
            }
            if (getGame()->matrice[h][l].typeMeuble == PLAN_DE_TRAVAIL) {
                stretch_sprite(getCorrectBuffer(), getGraphic()->textures.PLAN_DE_TRAVAIL, (getCorrectWidth()-LARGEUR*getCorrectCaseSize())/2+l*getCorrectCaseSize(), (getCorrectHeight()-HAUTEUR*getCorrectCaseSize())/2+h*getCorrectCaseSize(), getCorrectCaseSize(), getCorrectCaseSize());
            }
            if (getGame()->matrice[h][l].typeMeuble == PLANCHE_A_DECOUPER) {
                stretch_sprite(getCorrectBuffer(), getGraphic()->textures.PLANCHE_A_DECOUPER, (getCorrectWidth()-LARGEUR*getCorrectCaseSize())/2+l*getCorrectCaseSize(), (getCorrectHeight()-HAUTEUR*getCorrectCaseSize())/2+h*getCorrectCaseSize(), getCorrectCaseSize(), getCorrectCaseSize());
            }
            if (getGame()->matrice[h][l].typeMeuble == PLAQUE_A_CUISSON) {
                stretch_sprite(getCorrectBuffer(), getGraphic()->textures.PLAQUE_A_CUISSON, (getCorrectWidth()-LARGEUR*getCorrectCaseSize())/2+l*getCorrectCaseSize(), (getCorrectHeight()-HAUTEUR*getCorrectCaseSize())/2+h*getCorrectCaseSize(), getCorrectCaseSize(), getCorrectCaseSize());
            }
        }
    }
    getGame()->matrice[0][0].typeMeuble == SOL;

    //getCorrectCaseSize();
}

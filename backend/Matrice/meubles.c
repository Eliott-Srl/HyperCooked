#include "meubles.h"

void afficherMatrice(s_meuble matrice[HAUTEUR][LARGEUR]) {
    for (int h = 0; h < HAUTEUR; h++) {
        for (int l = 0; l < LARGEUR; l++) {
            printf("%d ", matrice[h][l].type_meuble);
        }
        printf("\n");
    }
}

void initialiserMatrice(s_meuble matrice_dynamique[HAUTEUR][LARGEUR], const char* file) {
    FILE *fichier;
    char ligne[128];

    // Ouvrir le fichier en mode lecture
    fichier = fopen(file, "r");

    char *base = "0123456789";

    int x = 0;
    int y = 0;
    // Parcourir le fichier caractère par caractère
    while (fgets(ligne, 128, fichier) != NULL) {
        char *p = ligne;
        int a = 0;
        x=0;
        char nombre[128] = "";
        while(*p != '\n' && *p != '\0') {
            if (strchr(base, *p) != NULL) {
                strncat(nombre, p, 1);
            } else if (*p == ' ') {
                matrice_dynamique[y][x].type_meuble = atoi(nombre);
                matrice_dynamique[y][x].objet.type = NONE;
                matrice_dynamique[y][x].objet.nbStockes = 0;
                matrice_dynamique[y][x].objet.stockageMax = 0;
                a = 1;
                nombre[0] = '\0';
            } else if (*p == ';') {
                if (a == 0) {
                    matrice_dynamique[y][x].type_meuble = atoi(nombre);
                    matrice_dynamique[y][x].objet.type = NONE;
                    matrice_dynamique[y][x].objet.nbStockes = 0;
                    matrice_dynamique[y][x].objet.stockageMax = 0;
                } else {
                    matrice_dynamique[y][x].objet.type = atoi(nombre);

                    if(atoi(nombre) == POELE || atoi(nombre) == ASSIETTE) {
                        matrice_dynamique[y][x].objet.stockageMax = 1;
                    } else if(atoi(nombre) == MARMITE) {
                        matrice_dynamique[y][x].objet.stockageMax = 3;
                    } else {
                        matrice_dynamique[y][x].objet.stockageMax = 0;
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

    fclose(fichier);  // Fermer le fichier après avoir trouvé un espace
}


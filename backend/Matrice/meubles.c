#include "meubles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficherMatrice(s_matrice *tab) {
    for (int h = 0; h < HAUTEUR; h++) {
        for (int l = 0; l < LARGEUR; l++) {
            printf("%d ", tab->matrice[h][l].type_objet);
        }
        printf("\n");
    }
}

void initialiserMatrice(s_meuble matrice_dynamique[12][20]) {
    FILE *fichier;
    char ligne[128];

    // Ouvrir le fichier en mode lecture
    fichier = fopen("map1.txt", "r");

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
                matrice_dynamique->matrice[y][x].type_meuble = atoi(nombre);
                matrice_dynamique->matrice[y][x].type_objet = NONE;
                a = 1;
                nombre[0] = '\0';
            } else if (*p == ';') {
                if (a == 0) {
                    matrice_dynamique->matrice[y][x].type_meuble = atoi(nombre);
                    matrice_dynamique->matrice[y][x].type_objet = NONE;
                } else {
                    matrice_dynamique->matrice[y][x].type_objet = atoi(nombre);
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


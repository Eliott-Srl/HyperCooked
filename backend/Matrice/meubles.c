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

    if (fichier == NULL) {
        allegro_message("Erreur lors de l'ouverture du fichier\n");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

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
                for (int i = 0; i < NB_INGREDIENTS_MAX; ++i) {
                    game->matrice[y][x].objet.nourriture[i].nom = PAS_D_INGREDIENT;
                }

                if (a == 0) {
                    game->matrice[y][x].typeMeuble = strtol(nombre, NULL, 10);
                    game->matrice[y][x].objet.type = NONE;
                    game->matrice[y][x].objet.nbStockes = 1;
                    game->matrice[y][x].objet.stockageMax = 1;
                } else {
                    int elm = strtol(nombre, NULL, 10);
                    if (game->matrice[y][x].typeMeuble == COFFRE) {
                        game->matrice[y][x].objet.type = STOCKEUR;
                        game->matrice[y][x].objet.nbStockes = 1;
                        game->matrice[y][x].objet.stockageMax = 1;
                        game->matrice[y][x].objet.nourriture[0].nom = elm;
                        game->matrice[y][x].objet.nourriture[0].coupable = coupableByIngredient(elm);
                        game->matrice[y][x].objet.nourriture[0].cuisson = cuissonByIngredient(elm);
                    } else {
                        game->matrice[y][x].objet.type = elm;

                        if (game->matrice[y][x].objet.type == POELE || game->matrice[y][x].objet.type == ASSIETTE) {
                            game->matrice[y][x].objet.stockageMax = 1;
                        } else if (game->matrice[y][x].objet.type == MARMITE) {
                            game->matrice[y][x].objet.stockageMax = 3;
                        } else {
                            game->matrice[y][x].objet.stockageMax = 0;
                        }

                    }
                    a = 0;
                }

                nombre[0] = '\0';
                switch (game->matrice[y][x].typeMeuble) {
                    case SOL:
                        game->matrice[y][x].action = &neFaitRien;
                        break;
                    case PLAN_DE_TRAVAIL:
                        game->matrice[y][x].action = &planDeTravail;
                        break;
                    case PLANCHE_A_DECOUPER:
                        game->matrice[y][x].action = &plancheADecouper;
                        break;
                    case COMPTOIR:
                        game->matrice[y][x].action = &comptoir;
                        break;
                    case COFFRE:
                        game->matrice[y][x].action = &coffre;
                        break;
                    case PLAQUE_A_CUISSON:
                        game->matrice[y][x].action = &plaqueDeCuisson;
                        break;
                    case POUBELLE:
                        game->matrice[y][x].action = &poubelle;
                        break;
                    default:
                        break;
                }
                if (game->matrice[y][x].typeMeuble == COFFRE && game->matrice[y][x].objet.type != STOCKEUR) {
                    allegro_message("Bad format");
                    allegro_exit();
                    exit(EXIT_FAILURE);
                }

                x++;
            } else {
                exit(-1);
            }
            p++;
        }
        y++;
    }

    // afficherMatrice();

    fclose(fichier);
}

void hc_afficher_matrice() {
    for(int h = 0; h < HAUTEUR; h++) {
        for(int l = 0; l < LARGEUR; l++) {
            int x = getOffsetX() + l * getCorrectCaseSize();
            int y = getOffsetY() + h * getCorrectCaseSize();

            BITMAP *meuble = getTextureByFurnitureName(getGame()->matrice[h][l].typeMeuble);
            if (meuble) {
                stretch_sprite(getCorrectBuffer(), meuble, x, y, getCorrectCaseSize(), getCorrectCaseSize());
            }

            BITMAP *objet = getTextureByObjectName(getGame()->matrice[h][l].objet.type);
            if (objet) {
                stretch_sprite(getCorrectBuffer(), objet, x, y, getCorrectCaseSize(), getCorrectCaseSize());
            }

            if (getGame()->matrice[h][l].objet.type == STOCKEUR) {
                BITMAP *nourriture = getTextureByIngredientName(getGame()->matrice[h][l].objet.nourriture[0].nom);
                if (nourriture) {
                    stretch_sprite(getCorrectBuffer(), nourriture, x, y, getCorrectCaseSize(), getCorrectCaseSize());
                }
            }
        }
    }
}

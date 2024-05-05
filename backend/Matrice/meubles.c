#include "meubles.h"

BITMAP * getTextureByFurnitureName(e_meubles meuble) {
    switch (meuble) {
        case SOL:
            return getGraphic()->textures.sol;
        case PLAN_DE_TRAVAIL:
            return getGraphic()->textures.planDeTravail;
        case PLANCHE_A_DECOUPER:
            return getGraphic()->textures.plancheADecouper;
            case COMPTOIR:
                return getGraphic()->textures.comptoir;
            /*
            case COFFRE:
                return getGraphic()->textures.coffre;
            */
        case PLAQUE_DE_CUISSON:
            return getGraphic()->textures.plaqueDeCuisson;
        case POUBELLE:
            return getGraphic()->textures.poubelle;
        default:
            return getGraphic()->textures.invalidTexture;
    }
}

void *getActionByFurnitureName(e_meubles meuble) {
    switch (meuble) {
        case SOL:
            return &neFaitRien;
        case PLAN_DE_TRAVAIL:
            return &planDeTravail;
        case PLANCHE_A_DECOUPER:
            return &plancheADecouper;
        case COMPTOIR:
            return &comptoir;
        case COFFRE:
            return &coffre;
        case PLAQUE_DE_CUISSON:
            return &plaqueDeCuisson;
        case POUBELLE:
            return &poubelle;
        default:
            return &neFaitRien;
    }
}

int getSupposedTimerByFurnitures(e_meubles meuble) {
    switch (meuble) {
        case PLANCHE_A_DECOUPER:
            return 5000;
        case PLAQUE_DE_CUISSON:
            return 10000;
        default:
            return -1;
    }
}

int getSlotsByObject(e_objet objet) {
    switch (objet) {
        case MARMITE:
            return TROIS_SLOTS;
        default:
            return UN_SLOT;
    }
}

void afficherProgression(int x, int y, int timer, int timerTotale, int color) {
    int time = getTime();
    int dTime = time - timer;

    double progression = ((double) dTime / (double) timerTotale);
    if (progression > 1) {
        progression = 1;
    }
    rect(getCorrectBuffer(), x, y - 2, x + getCorrectCaseSize(), y + (int) (3 * getCorrectRatio()) + 2, color);
    if (progression > 0) {
        rectfill(getCorrectBuffer(), x + 2, y, x + (int) (progression * ((double) getCorrectCaseSize() - 2.0)), y + (int) (3 * getCorrectRatio()), color);
    }
}

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
    int joueur = 0;
    int ligneActuelle = 0;

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
        if (ligne[0] == '#') {
            continue;
        }

        if (ligneActuelle == 0) {
            int i = 0;
            char *a = strtok(ligne, ";");
            while (a != NULL) {
                game->recetteAvailable[i] = strtol(a, NULL, 10);
                i++;
                a = strtok(NULL, ";");
            }
            game->nbRecettesAvailable = i + 1;
            ligneActuelle++;
        } else if (ligneActuelle == 1) {
            game->duration = strtol(ligne, NULL, 10);
            ligneActuelle++;
        } else {
            char *p = ligne;
            int a = 0;
            x = 0;
            char nombre[128] = "";

            while(*p != '\n' && *p != '\0') {
                game->matrice[y][x].timer = -1;
                game->matrice[y][x].objet.nbStockes = 0;
                game->matrice[y][x].objet.stockageMax = getSlotsByObject(NONE);
                if (strchr(base, *p) != NULL) {
                    strncat(nombre, p, 1);
                } else if (*p == ' ') {
                    game->matrice[y][x].typeMeuble = strtol(nombre, NULL, 10);
                    game->matrice[y][x].objet.type = NONE;
                    a = 1;
                    nombre[0] = '\0';
                } else if (*p == ';') {
                    for (int i = 0; i < NB_INGREDIENTS_MAX; ++i) {
                        game->matrice[y][x].objet.nourriture[i].nom = PAS_D_INGREDIENT;
                    }

                    if (a == 0) {
                        if (strtol(nombre, NULL, 10) == POSITION_JOUEUR) {
                            game->matrice[y][x].typeMeuble = SOL;
                            game->matrice[y][x].objet.type = NONE;
                            if (joueur < 2) {
                                game->joueurs[joueur].x = (float) x * (float) getCorrectCaseSize() + getCorrectOffsetX();
                                game->joueurs[joueur].y = (float) y * (float) getCorrectCaseSize() + getCorrectOffsetY();
                                joueur++;
                            }
                        } else {
                            game->matrice[y][x].typeMeuble = strtol(nombre, NULL, 10);
                            game->matrice[y][x].objet.type = NONE;
                        }
                    } else {
                        int elm = strtol(nombre, NULL, 10);
                        if (game->matrice[y][x].typeMeuble == COFFRE) {
                            game->matrice[y][x].objet.type = STOCKEUR;
                            game->matrice[y][x].objet.nbStockes = 1;
                            game->matrice[y][x].objet.stockageMax = 0;
                            game->matrice[y][x].objet.nourriture[0].nom = elm;
                            /* ça peut être dérangeant de mettre
                             * le nom de l'ingrédient dans le nom de l'objet mais ça simplifie le bazar
                             */
                            game->matrice[y][x].objet.nourriture[0].coupable = (getIngredientAfterCutting(elm) != PAS_D_INGREDIENT);
                            game->matrice[y][x].objet.nourriture[0].cuisson = getCuissonByIngredient(elm);
                        } else {
                            game->matrice[y][x].objet.type = elm;
                            game->matrice[y][x].objet.stockageMax = getSlotsByObject(elm);
                        }
                        a = 0;
                    }

                    nombre[0] = '\0';
                    game->matrice[y][x].action = getActionByFurnitureName(game->matrice[y][x].typeMeuble);
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
    }

    // afficherMatrice();

    fclose(fichier);
}

void hc_afficher_matrice() {
    BITMAP *plandetravail = getTextureByFurnitureName(PLAN_DE_TRAVAIL);
    if (!plandetravail) {
        allegro_message("Erreur lors du chargement de la texture du sol");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    float coosX[3] = {(float) 1/2, (float) 3/4, (float) 1/4};
    float coosY[3] = {(float) 1/4, (float) 3/4, (float) 3/4};

    for(int h = 0; h < HAUTEUR; h++) {
        for(int l = 0; l < LARGEUR; l++) {
            int x = (int) (getCorrectOffsetX() + (float) l * (float) getCorrectCaseSize());
            int y = (int) (getCorrectOffsetY() + (float) h * (float) getCorrectCaseSize());

            if (getGame()->matrice[h][l].typeMeuble != SOL && getGame()->matrice[h][l].typeMeuble != COFFRE && getGame()->matrice[h][l].typeMeuble != COMPTOIR && getGame()->matrice[h][l].typeMeuble != POUBELLE) {
                stretch_sprite(getCorrectBuffer(), plandetravail, x, y, getCorrectCaseSize(), getCorrectCaseSize());
            }

            if (getGame()->matrice[h][l].typeMeuble == COFFRE) {
                rectfill(getCorrectBuffer(), x, y, x + getCorrectCaseSize(), y + getCorrectCaseSize(), makecol(255, 255, 255));
            } else {
                stretch_sprite(getCorrectBuffer(), getTextureByFurnitureName(getGame()->matrice[h][l].typeMeuble), x, y, getCorrectCaseSize(), getCorrectCaseSize());
            }

            if (getGame()->matrice[h][l].objet.type == STOCKEUR) {
                stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getGame()->matrice[h][l].objet.nourriture[0].nom), x, y, getCorrectCaseSize(), getCorrectCaseSize());
            } else if (getGame()->matrice[h][l].typeMeuble == PLANCHE_A_DECOUPER) {
                if (getGame()->matrice[h][l].timer != -1 && getTime() - getGame()->matrice[h][l].timer < getSupposedTimerByFurnitures(getGame()->matrice[h][l].typeMeuble)) {
                    stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getGame()->matrice[h][l].objet.nourriture[0].nom), x, y, getCorrectCaseSize(), getCorrectCaseSize());
                } else if (getGame()->matrice[h][l].timer != -1 && getGame()->matrice[h][l].objet.nbStockes > 0) {
                    stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getIngredientAfterCutting(getGame()->matrice[h][l].objet.nourriture[0].nom)), x, y, getCorrectCaseSize(), getCorrectCaseSize());
                }
            } else if (getGame()->matrice[h][l].typeMeuble == PLAQUE_DE_CUISSON) {
                if (getGame()->matrice[h][l].objet.type != NONE) {
                    stretch_sprite(getCorrectBuffer(), getTextureByObjectName(getGame()->matrice[h][l].objet.type), x, y, getCorrectCaseSize(), getCorrectCaseSize());
                }

                if (getGame()->matrice[h][l].objet.type != NONE
                 && getGame()->matrice[h][l].objet.nbStockes > 0
                 && getGame()->matrice[h][l].objet.stockageMax == 1
                 && (getGame()->matrice[h][l].timer == -1 || getTime() - getGame()->matrice[h][l].timer < getSupposedTimerByFurnitures(getGame()->matrice[h][l].typeMeuble))) {
                    stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getGame()->matrice[h][l].objet.nourriture[0].nom), x, y, getCorrectCaseSize(), getCorrectCaseSize());
                } else if (getGame()->matrice[h][l].objet.type != NONE
                        && getGame()->matrice[h][l].objet.nbStockes > 0
                        && getGame()->matrice[h][l].objet.stockageMax == 3
                        && (getGame()->matrice[h][l].timer == -1 || getTime() - getGame()->matrice[h][l].timer < getSupposedTimerByFurnitures(getGame()->matrice[h][l].typeMeuble))) {
                    for (int i = 0; i < getGame()->matrice[h][l].objet.nbStockes; i++) {
                        stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getGame()->matrice[h][l].objet.nourriture[i].nom), x + (int) (coosX[i] * (float) getCorrectCaseSize()), y + (int) (coosY[i] * (float) getCorrectCaseSize()), getCorrectCaseSize() / 2, getCorrectCaseSize() / 2);
                    }
                } else if (getGame()->matrice[h][l].timer != -1 && getTime() - getGame()->matrice[h][l].timer > getSupposedTimerByFurnitures(getGame()->matrice[h][l].typeMeuble)) {
                    stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getIngredientAfterCooking(getGame()->matrice[h][l].objet.nourriture[0].nom)), x, y, getCorrectCaseSize(), getCorrectCaseSize());
                }
            } else if (getGame()->matrice[h][l].objet.type != NONE) {
                stretch_sprite(getCorrectBuffer(), getTextureByObjectName(getGame()->matrice[h][l].objet.type), x, y,
                               getCorrectCaseSize(), getCorrectCaseSize());
                if (getGame()->matrice[h][l].objet.type != NONE
                    && getGame()->matrice[h][l].objet.nbStockes > 0
                    && getGame()->matrice[h][l].objet.stockageMax == 1) {
                    stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getGame()->matrice[h][l].objet.nourriture[0].nom), x, y, getCorrectCaseSize(), getCorrectCaseSize());
                }
            }

            if (getGame()->matrice[h][l].timer != -1 && getTime() - getGame()->matrice[h][l].timer <
                                                                getSupposedTimerByFurnitures(getGame()->matrice[h][l].typeMeuble)) {
                afficherProgression(x, y + (int) (4 * getCorrectRatio()), getGame()->matrice[h][l].timer,
                         getSupposedTimerByFurnitures(getGame()->matrice[h][l].typeMeuble),
                              makecol(255, 0, 0));
            }
        }
    }
}

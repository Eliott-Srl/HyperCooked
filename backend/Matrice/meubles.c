#include "meubles.h"

BITMAP *getTextureByFurnitureName(s_game *game, e_meubles meuble) {
    switch (meuble) {
        case SOL:
            return game->graphic.textures.sol;
        case PLAN_DE_TRAVAIL:
            return game->graphic.textures.planDeTravail;
        case PLANCHE_A_DECOUPER:
            return game->graphic.textures.plancheADecouper;
            case COMPTOIR:
                return game->graphic.textures.comptoir;
        /*
        case COFFRE:
            return game->graphic.textures.coffre;
        */
        case VOID:
            return game->graphic.textures.void_texture;
        case PLAQUE_DE_CUISSON:
            return game->graphic.textures.plaqueDeCuisson;
        case POUBELLE:
            return game->graphic.textures.poubelle;
        default:
            return game->graphic.textures.invalidTexture;
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
        case GENERATEUR_ASSIETTE:
            return &generateurAssiette;
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
        case ASSIETTE:
            return RECETTE;
        case MARMITE:
            return TROIS_SLOTS;
        default:
            return UN_SLOT;
    }
}

void afficherProgression(s_game *game, int x, int y, int timer, int timerTotale, int color) {
    int time = getTime(game);
    int dTime = time - timer;

    double progression = ((double) dTime / (double) timerTotale);
    if (progression > 1) {
        progression = 1;
    }

    rect(getCorrectBuffer(game), x, y - 2, x + getCorrectCaseSize(game), y + (int) (3 * getCorrectRatio(game)) + 2, color);
    if (progression > 0) {
        rectfill(getCorrectBuffer(game), x + 2, y, x + (int) (progression * ((double) getCorrectCaseSize(game) - 2.0)), y + (int) (3 * getCorrectRatio(game)), color);
    }
}


void afficherMatrice(s_game *game) {
    for (int h = 0; h < HAUTEUR; h++) {
        for (int l = 0; l < LARGEUR; l++) {
            printf("%d ", game->matrice[h][l].typeMeuble);
        }
        printf("\n");
    }
}

void initialiserMatrice(s_game *game, const char* file) {
    FILE *fichier;
    char ligne[128];
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
            for (int i = 0; i < NB_RECETTES_MAX; i++) {
                game->recetteAvailable[i] = -1;
            }

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
            char *a = strtok(ligne, ";");
            game->duration = strtol(a, NULL, 10);
            a = strtok(NULL, ";");
            game->timeBtCommandes = strtol(a, NULL, 10);
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
                                game->joueurs[joueur].x = (float) x * (float) getCorrectCaseSize(game) + getCorrectOffsetX(game) + (float) getCorrectCaseSize(game) / 2;
                                game->joueurs[joueur].y = (float) y * (float) getCorrectCaseSize(game) + getCorrectOffsetY(game) + (float) getCorrectCaseSize(game) / 2;
                                joueur++;
                            }
                        } else {
                            game->matrice[y][x].typeMeuble = strtol(nombre, NULL, 10);
                            game->matrice[y][x].objet.type = NONE;
                        }

                        if (game->matrice[y][x].typeMeuble == GENERATEUR_ASSIETTE) {
                            game->matrice[y][x].objet.type = ASSIETTE;
                            game->matrice[y][x].objet.nbStockes = 0;
                            game->matrice[y][x].objet.stockageMax = RECETTE;
                        }
                    } else {
                        int elm = strtol(nombre, NULL, 10);
                        if (game->matrice[y][x].typeMeuble == COFFRE) {
                            game->matrice[y][x].objet.type = STOCKEUR;
                            game->matrice[y][x].objet.nbStockes = 1;
                            game->matrice[y][x].objet.stockageMax = SANS;
                            game->matrice[y][x].objet.nourriture[0].nom = elm;
                            /* ça peut être dérangeant de mettre
                             * le nom de l'ingrédient dans le nom de l'objet mais ça simplifie le bazar
                             */
                            game->matrice[y][x].objet.nourriture[0].coupable = (getIngredientAfterCutting(elm) !=
                                                                                PAS_D_INGREDIENT);
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

void afficherPlancheDecouper(s_game *game, int h, int l) {
    int x = (int) (getCorrectOffsetX(game) + (float) l * (float) getCorrectCaseSize(game));
    int y = (int) (getCorrectOffsetY(game) + (float) h * (float) getCorrectCaseSize(game));
    int offSetIngredient = (int) ((float) getCorrectCaseSize(game) / 4);

    stretch_sprite(getCorrectBuffer(game), getTextureByFurnitureName(game, game->matrice[h][l].typeMeuble), x, y, getCorrectCaseSize(game), getCorrectCaseSize(game));

    if (game->matrice[h][l].timer != -1 && getTime(game) - game->matrice[h][l].timer < getSupposedTimerByFurnitures(game->matrice[h][l].typeMeuble)) {
        stretch_sprite(getCorrectBuffer(game), getTextureByIngredientName(game, game->matrice[h][l].objet.nourriture[0].nom), x + offSetIngredient, y + offSetIngredient, (int) ((float) getCorrectCaseSize(game) / 2), (int) ((float) getCorrectCaseSize(game) / 2));
    } else if (game->matrice[h][l].timer != -1 && game->matrice[h][l].objet.nbStockes > 0) {
        stretch_sprite(getCorrectBuffer(game), getTextureByIngredientName(game, getIngredientAfterCutting(game->matrice[h][l].objet.nourriture[0].nom)), x + offSetIngredient, y + offSetIngredient, (int) ((float) getCorrectCaseSize(game) / 2), (int) ((float) getCorrectCaseSize(game) / 2));
    }
}

void hc_afficher_matrice(s_game *game) {
    BITMAP *plandetravail = getTextureByFurnitureName(game, PLAN_DE_TRAVAIL);
    if (!plandetravail) {
        allegro_message("Erreur lors du chargement de la texture du sol");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    for(int h = 0; h < HAUTEUR; h++) {
        for(int l = 0; l < LARGEUR; l++) {
            int x = (int) (getCorrectOffsetX(game) + (float) l * (float) getCorrectCaseSize(game));
            int y = (int) (getCorrectOffsetY(game) + (float) h * (float) getCorrectCaseSize(game));

            if (game->matrice[h][l].typeMeuble != SOL
             && game->matrice[h][l].typeMeuble != COFFRE
             && game->matrice[h][l].typeMeuble != COMPTOIR
             && game->matrice[h][l].typeMeuble != POUBELLE
             && game->matrice[h][l].typeMeuble != VOID) {
                stretch_sprite(getCorrectBuffer(game), plandetravail, x, y, getCorrectCaseSize(game), getCorrectCaseSize(game));
            }

            if (game->matrice[h][l].typeMeuble == COFFRE || game->matrice[h][l].typeMeuble == GENERATEUR_ASSIETTE) {
                rectfill(getCorrectBuffer(game), x, y, x + getCorrectCaseSize(game), y + getCorrectCaseSize(game),
                         makecol(255, 255, 255));
            } else if (game->matrice[h][l].typeMeuble == PLANCHE_A_DECOUPER) {
                afficherPlancheDecouper(game, h, l);
            } else {
                stretch_sprite(getCorrectBuffer(game), getTextureByFurnitureName(game, game->matrice[h][l].typeMeuble), x, y, getCorrectCaseSize(game), getCorrectCaseSize(game));
            }

            if (game->matrice[h][l].objet.type == STOCKEUR && game->matrice[h][l].typeMeuble != GENERATEUR_ASSIETTE && game->matrice[h][l].objet.nbStockes > 0) {
                stretch_sprite(getCorrectBuffer(game),
                               getTextureByIngredientName(game, game->matrice[h][l].objet.nourriture[0].nom), x, y,
                               getCorrectCaseSize(game), getCorrectCaseSize(game));
            } else if (game->matrice[h][l].typeMeuble == GENERATEUR_ASSIETTE) {
                stretch_sprite(getCorrectBuffer(game), getTextureByObjectName(game, ASSIETTE), x, y, getCorrectCaseSize(game), getCorrectCaseSize(game));
            } else if (game->matrice[h][l].objet.type == ASSIETTE && game->matrice[h][l].typeMeuble != GENERATEUR_ASSIETTE) {
                afficherAssietteOnFurniture(game, h, l);
            } else if (game->matrice[h][l].objet.type == POELE) {
                afficherPoeleOnFurniture(game, h, l);
            }

            if (game->matrice[h][l].timer != -1 && getTime(game) - game->matrice[h][l].timer <
                                                                getSupposedTimerByFurnitures(game->matrice[h][l].typeMeuble)) {
                afficherProgression(game, x, y + (int) (4 * getCorrectRatio(game)), game->matrice[h][l].timer,
                         getSupposedTimerByFurnitures(game->matrice[h][l].typeMeuble),
                              makecol(255, 0, 0));
                playBruitage(game, getSoundByFurniture(game, game->matrice[h][l].typeMeuble));
            }

            if (game->matrice[h][l].objet.nbStockes > 0 && game->graphic.debug) {
                circlefill(getCorrectBuffer(game), x + 5, y + 5, 5, makecol(255, 0, 0));
            }
        }
    }
}

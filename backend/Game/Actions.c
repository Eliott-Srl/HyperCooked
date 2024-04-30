#include "Actions.h"

void executeFunctionForEveryBlockReachable(s_joueur *joueur, void (*fonction)(s_joueur*, int, int)) {
    s_game *game = getGame();
    for (int k = 0; k < HAUTEUR; k++) {
        for (int s = 0; s < LARGEUR; s++) {
            if (hypotSq((int) joueur->x, (int) joueur->y, getOffsetX() + s * getCorrectCaseSize() + getCorrectCaseSize() / 2, getOffsetY() + k * getCorrectCaseSize() + getCorrectCaseSize() / 2, 4 * getCorrectCaseSize() / 6)) {
                fonction(joueur, k, s);
            }
        }
    }
}

void meuble(s_joueur *joueur, int k, int s) {
    if (getGame()->matrice[k][s].typeMeuble == SOL) {
        return;
    }

    char filename[STRMAX];
    sprintf(filename, "[%s] pour intéragir", strcmp(getGame()->joueurs[0].nom, joueur->nom) == 0 ? "SHIFT" : "0");
    textout_centre_ex(getCorrectBuffer(), font, filename, getOffsetX() + (int) ((float) s * (float) getCorrectCaseSize() + (float) getCorrectCaseSize() / 2), getOffsetY() + (int) ((float) k * (float) getCorrectCaseSize() + (float) getCorrectCaseSize() / 2), makecol(255, 255, 255), -1);
}

void deplacerPersonnage(s_joueur* joueur, double veloX, double veloY) {
    if (veloX < 0.01 && veloX > -0.01 && veloY < 0.01 && veloY > -0.01) {
        return;
    }

    s_game *game = getGame();
    // Nouvelles positions potentielles
    float newX = joueur->x + (float) veloX * (float) (getGraphic()->fs ? SPEED * getGraphic()->ratio * 3.0 : SPEED);
    float newY = joueur->y + (float) veloY * (float) (getGraphic()->fs ? SPEED * getGraphic()->ratio * 3.0 : SPEED);

    if (newX < 0 || newX > (float) getCorrectWidth() || newY < 0 || newY > (float) getCorrectHeight()) {
        return;
    }

    // Vérifier les collisions avec les meubles
    int i = (int) ((newX - (float) getOffsetX()) / (float) getCorrectCaseSize());
    int j = (int) ((newY - (float) getOffsetY()) / (float) getCorrectCaseSize());
    if (collisionsBtRectanglesAndCircles(getOffsetX() + i * getCorrectCaseSize(), getOffsetY() + j * getCorrectCaseSize(),
                                         getCorrectCaseSize(), getCorrectCaseSize(), (int) newX, (int) newY,
                                         getCorrectRayon())
        && game->matrice[j][i].typeMeuble != SOL) {
        // Il y a une collision, ne pas bouger
        return;
    }

    s_joueur *autre_joueur;
    // Vérifier les collisions avec les autres personnages
    if (game->joueurs[0].couleur.r == joueur->couleur.r
     && game->joueurs[0].couleur.g == joueur->couleur.g
     && game->joueurs[0].couleur.b == joueur->couleur.b) {
        autre_joueur = &game->joueurs[1];
    } else {
        autre_joueur = &game->joueurs[0];
    }

    if (collisionsBtCircles((int) newX, (int) newY, getCorrectRayon(), (int) autre_joueur->x, (int) autre_joueur->y,
                            getCorrectRayon())) {
        // Il y a une collision avec un autre personnage, ne pas bouger
        return;
    }

    // Déplacer et tourner le personnage aux nouvelles positions
    if (veloX * veloY != 0) {
        joueur->angle = fixatan(ftofix((float) veloY / (float) veloX)) - itofix(64);

        if (veloX > 0) {
            joueur->angle += itofix(128);
        }
    }  else {
        joueur->angle = ftofix((float) (((veloX + 1)*90 + (veloY)*90) * 256) / (float) 360);

        if (veloX != 0) {
            joueur->angle -= itofix(64);
        }
    }

    /* It was a try to fix the angle of the player
    fixed angle = fixcos(ftofix(veloX));

    if (fixsin(ftofix(veloY)) < 0) {
        angle = -angle;
    }

    joueur->angle = angle;
     */

    joueur->x = newX;
    joueur->y = newY;
}

BITMAP *getTextureByObjectName(e_objet objet) {
    switch (objet) {
        /*
        case POELE:
            return getGraphic()->textures.poele;
        case MARMITE:
            return getGraphic()->textures.marmite;
        case ASSIETTE:
            return getGraphic()->textures.assiette;
        case EXTINCTEUR:
            return getGraphic()->textures.extincteur;
        */
        default:
            return NULL;
    }
}

BITMAP *getTextureByFurnitureName(e_meubles meuble) {
    switch (meuble) {
        case SOL:
            return getGraphic()->textures.sol;
        case PLAN_DE_TRAVAIL:
            return getGraphic()->textures.planDeTravail;
        case PLANCHE_A_DECOUPER:
            return getGraphic()->textures.plancheADecouper;
        /*
        case COMPTOIR:
            return getGraphic()->textures.comptoir;
        case COFFRE:
            return getGraphic()->textures.coffre;
        */
        case PLAQUE_A_CUISSON:
            return getGraphic()->textures.plaqueDeCuisson;
        default:
            return NULL;
    }
}

BITMAP *getTextureByIngredientName(e_ingredients ingredients) {
    switch (ingredients) {
        case SALADE:
            return getGraphic()->textures.Laitue;
        case TOMATE:
            return getGraphic()->textures.tomate;
        case PAIN:
            return getGraphic()->textures.Pain;
        case STEAK:
            return getGraphic()->textures.steak;
        case POTATO:
            return getGraphic()->textures.PommeDeTerre;
        case OEUF:
            return getGraphic()->textures.Oeuf;
        default:
            return NULL;
    }
}

void afficherPersonnages() {
    for (int i = 0; i < 2; i++) {
        int dims = getCorrectCaseSize();
        float x = getGame()->joueurs[i].x - (float) dims / 2;
        float y = getGame()->joueurs[i].y - (float) dims / 2;
        float offsetX = (float) cos(fixtof(getGame()->joueurs[i].angle)) * (float) dims / 2;
        float offsetY = (float) sin(fixtof(getGame()->joueurs[i].angle)) * (float) dims / 2;


        if (getGame()->joueurs[i].en_main == OBJET) {
            if (getTextureByObjectName(getGame()->joueurs[i].handObjet.type) != NONE) {
                rotate_scaled_sprite(getCorrectBuffer(), getTextureByObjectName(getGame()->joueurs[i].handObjet.type),
                                     (int) (x + (float) offsetX), (int) (y + (float) offsetY),
                                     getGame()->joueurs[i].angle, ftofix((float) getCorrectCaseSize() /
                                                                         (float) getTextureByIngredientName(
                                                                                 getGame()->joueurs[i].handIngredient.nom)->w));
            }
        } else if (getGame()->joueurs[i].en_main == INGREDIENT) {
            if (getTextureByIngredientName(getGame()->joueurs[i].handIngredient.nom) != PAS_D_INGREDIENT) {
                rotate_scaled_sprite(getCorrectBuffer(), getTextureByIngredientName(getGame()->joueurs[i].handIngredient.nom), (int)(x + (float) offsetX), (int)(y + (float) offsetY), getGame()->joueurs[i].angle, ftofix((float) getCorrectCaseSize() / (float) getTextureByIngredientName(getGame()->joueurs[i].handIngredient.nom)->w));
            }
        }

        rotate_scaled_sprite(getCorrectBuffer(), getGraphic()->textures.player, (int) x, (int) y, getGame()->joueurs[i].angle, ftofix((float) dims / (float) getGraphic()->textures.player->w));
        circlefill(getCorrectBuffer(), (int) getGame()->joueurs[i].x, (int) getGame()->joueurs[i].y, dims/5,
                   rgbToAllegroColor(getGame()->joueurs[i].couleur));

        executeFunctionForEveryBlockReachable(getGame()->joueurs + i, &meuble);
    }
}

void deplacerPersonnagesClavier() {
    s_coo velo_perso1 = {0, 0};
    s_coo velo_perso2 = {0, 0};
    int sound = 0;

    if (key[KEY_W]) {
//      charge_Sound(sound);
        velo_perso1.y--;
    }
    if (key[KEY_S]) {
        velo_perso1.y++;
    }
    if (key[KEY_A]) {
        velo_perso1.x--;
    }
    if (key[KEY_D]) {
        velo_perso1.x++;
    }
    if (key[KEY_UP]) {
        velo_perso2.y--;
    }
    if (key[KEY_DOWN]) {
        velo_perso2.y++;
    }
    if (key[KEY_LEFT]) {
        velo_perso2.x--;
    }
    if (key[KEY_RIGHT]) {
        velo_perso2.x++;
    }

    deplacerPersonnage(&getGame()->joueurs[0], velo_perso1.x, velo_perso1.y);
    deplacerPersonnage(&getGame()->joueurs[1], velo_perso2.x, velo_perso2.y);
}

void deplacerPersonnageJoystick() {
    for (int i = 0; i < 2; i++) {
        if (joy[i].flags & JOYFLAG_ANALOG && joy[i].flags & JOYFLAG_SIGNED) {
            double x = (double) joy[i].stick[0].axis[0].pos / 128.0;
            double y = (double) joy[i].stick[0].axis[1].pos / 128.0;

            deplacerPersonnage(&getGame()->joueurs[i], x, y);
        } else if (joy[i].flags & JOYFLAG_CALIB_DIGITAL) {

        } else {
            s_coo velo_perso = {0, 0};

            if (joy[i].stick[0].axis[0].d1) {
                velo_perso.x--;
            }
            if (joy[i].stick[0].axis[0].d2) {
                velo_perso.x++;
            }
            if (joy[i].stick[0].axis[1].d1) {
                velo_perso.y--;
            }
            if (joy[i].stick[0].axis[1].d2) {
                velo_perso.y++;
            }

            deplacerPersonnage(&getGame()->joueurs[i], velo_perso.x, velo_perso.y);
        }
    }
}

void deplacerPersonnages() {
    deplacerPersonnagesClavier();
    deplacerPersonnageJoystick();

    afficherPersonnages();
}

int coupableByIngredient(e_ingredients ingredient) {
    switch (ingredient) {
        case POTATO:
        case TOMATE:
        case PAIN:
        case SALADE:
            return 1;
        default:
            return 0;
    }
}

int cuissonByIngredient(e_ingredients ingredient) {
    switch (ingredient) {
        case STEAK:
            return A_LA_POELE;
        default:
            return NON;
    }
}

void neFaitRien(s_joueur* joueur, int i, int j) {
    // Ne rien faire
}

void planDeTravail(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET && getGame()->matrice[i][j].objet.type == NONE) {
        getGame()->matrice[i][j].objet = joueur->handObjet;
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == INGREDIENT && getGame()->matrice[i][j].objet.nourriture[0].nom == PAS_D_INGREDIENT) {
        getGame()->matrice[i][j].objet.type = STOCKEUR;
        getGame()->matrice[i][j].objet.nourriture[0] = joueur->handIngredient;
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == NOTHING) {
        if (getGame()->matrice[i][j].objet.type == STOCKEUR) {
            joueur->handIngredient = getGame()->matrice[i][j].objet.nourriture[0];
            joueur->en_main = INGREDIENT;
            getGame()->matrice[i][j].objet.nourriture[0].nom = PAS_D_INGREDIENT;
            getGame()->matrice[i][j].objet.type = NONE;
        } else if (getGame()->matrice[i][j].objet.type != NONE) {
            joueur->handObjet = getGame()->matrice[i][j].objet;
            joueur->en_main = OBJET;
            getGame()->matrice[i][j].objet.type = NONE;
        }
    }
}

void plancheADecouper(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        getGame()->matrice[i][j].objet.nourriture[0] = joueur->handIngredient;
        joueur->en_main = NOTHING;
    }
}

void comptoir(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET) {
        s_commande commandFind;
        int good = verificationDeLaRecette(&joueur->handObjet, &commandFind);
        joueur->en_main = NOTHING;
        if (good) {
            // TODO: Calculate score
        } else {
            printf("La commande n'était pas bonne");
        }
    }
}

void coffre(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == NOTHING) {
        joueur->en_main = INGREDIENT;
        joueur->handIngredient.cuit = NON;
        joueur->handIngredient.coupe = 0;
        joueur->handIngredient.nom = getGame()->matrice[i][j].objet.nourriture[0].nom;
        joueur->handIngredient.coupable = getGame()->matrice[i][j].objet.nourriture[0].coupable;
        joueur->handIngredient.cuisson = getGame()->matrice[i][j].objet.nourriture[0].cuisson;
    }
}

void plaqueDeCuisson(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT
    && ((getGame()->matrice[i][j].objet.type == MARMITE
      && getGame()->matrice[i][j].objet.nbStockes < getGame()->matrice[i][j].objet.stockageMax)
     || (getGame()->matrice[i][j].objet.type == POELE
      && getGame()->matrice[i][j].objet.nbStockes < 1))) {
        getGame()->matrice[i][j].objet.nourriture[getGame()->matrice[i][j].objet.nbStockes] = joueur->handIngredient;
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == OBJET && getGame()->matrice[i][j].objet.type == NONE) {
        getGame()->matrice[i][j].objet = joueur->handObjet;
        joueur->en_main = NOTHING;
    }
}

void poubelle(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        joueur->en_main = NOTHING;
    } else if (joueur->en_main == OBJET) {
        joueur->handObjet.nbStockes = 0;
        joueur->en_main = NOTHING;
    }
}

void interact(s_joueur* joueur, int i, int j) {
    getGame()->matrice[i][j].action(joueur, i, j);
}

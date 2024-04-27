#include "Actions.h"

void deplacerPersonnageClavier(s_joueur* joueur, int veloX, int veloY) {
    if (veloX == 0 && veloY == 0) {
        return;
    }

    s_game *game = getGame();
    // Nouvelles positions potentielles
    float newX = joueur->x + (float) veloX * (float) SPEED;
    float newY = joueur->y + (float) veloY * (float) SPEED;

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

    joueur->x = newX;
    joueur->y = newY;
}

void afficherPersonnages() {
    for (int i = 0; i < 2; i++) {
        int dims = getCorrectCaseSize();
        float x = getGame()->joueurs[i].x - (float) dims / 2;
        float y = getGame()->joueurs[i].y - (float) dims / 2;
        rotate_scaled_sprite(getCorrectBuffer(), getGraphic()->textures.player, (int) x, (int) y, getGame()->joueurs[i].angle, ftofix((float) dims / (float) getGraphic()->textures.player->w));
        circlefill(getCorrectBuffer(), (int) getGame()->joueurs[i].x, (int) getGame()->joueurs[i].y, dims/5,
                   rgbToAllegroColor(getGame()->joueurs[i].couleur));
    }
}

void deplacerPersonnagesClavier() {
    s_coo velo_perso1 = {0, 0};
    s_coo velo_perso2 = {0, 0};

    if (key[KEY_W]) {
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

    deplacerPersonnageClavier(&getGame()->joueurs[0], velo_perso1.x, velo_perso1.y);
    deplacerPersonnageClavier(&getGame()->joueurs[1], velo_perso2.x, velo_perso2.y);
}

void deplacerPersonnageJoystick() {
    s_coo velo_perso1 = {0, 0};
    s_coo velo_perso2 = {0, 0};

    if (joy[0].stick[0].axis[0].d1) {
        velo_perso1.x--;
    }
    if (joy[0].stick[0].axis[0].d2) {
        velo_perso1.x++;
    }
    if (joy[0].stick[0].axis[1].d1) {
        velo_perso1.y--;
    }
    if (joy[0].stick[0].axis[1].d2) {
        velo_perso1.y++;
    }

    if (joy[1].stick[0].axis[0].d1) {
        velo_perso2.x--;
    }
    if (joy[1].stick[0].axis[0].d2) {
        velo_perso2.x++;
    }
    if (joy[1].stick[0].axis[1].d1) {
        velo_perso2.y--;
    }
    if (joy[1].stick[0].axis[1].d2) {
        velo_perso2.y++;
    }

    deplacerPersonnageClavier(&getGame()->joueurs[0], velo_perso1.x, velo_perso1.y);
    deplacerPersonnageClavier(&getGame()->joueurs[1], velo_perso2.x, velo_perso2.y);
}

void deplacerPersonnages() {
    deplacerPersonnagesClavier();
    deplacerPersonnageJoystick();

    afficherPersonnages();
}

void neFaitRien(s_joueur* joueur) {
    // Ne rien faire
}

void planDeTravail(s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET) {
        getGame()->matrice[i][j].objet = joueur->handObjet;
        joueur->en_main = NOTHING;
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

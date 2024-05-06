#include "Players.h"

char noms[NB_PRENOMS][STRMAX] = {"Stéphane", "Eliott", "Jean-Kevin", "Bernard", "Michel", "Pierre-Alexandre", "Papou"};

void changeNomJ1(s_game *game) {
    strcpy(game->joueurs[0].nom, noms[rand() % NB_PRENOMS]);
}

void changeColorJ1(s_game *game) {
    game->joueurs[0].couleur.r = rand() % 256;
    game->joueurs[0].couleur.g = rand() % 256;
    game->joueurs[0].couleur.b = rand() % 256;
}

void changeNomJ2(s_game *game) {
    strcpy(game->joueurs[1].nom, noms[rand() % NB_PRENOMS]);
}

void changeColorJ2(s_game *game) {
    game->joueurs[1].couleur.r = rand() % 256;
    game->joueurs[1].couleur.g = rand() % 256;
    game->joueurs[1].couleur.b = rand() % 256;
}

void reinitialiserPlayers(s_game *game) {
    for (int i = 0; i < 2; i++) {
        // game->joueurs[i].x = (float) WIDTH / 2 + (float) ((i * 2 - 1) * getCorrectCaseSize());
        // game->joueurs[i].y = (float) HEIGHT / 2;
        game->joueurs[i].en_main = NOTHING;
        game->joueurs[i].score = 0;
    }
}

void initialisePlayers(s_game *game) {
    reinitialiserPlayers(game);
    changeNomJ1(game);
    game->joueurs[0].couleur.r = 255;
    game->joueurs[0].couleur.g = 0;
    game->joueurs[0].couleur.b = 0;
    changeNomJ2(game);
    game->joueurs[1].couleur.r = 0;
    game->joueurs[1].couleur.g = 0;
    game->joueurs[1].couleur.b = 255;
}

void deplacerPersonnage(s_game *game, s_joueur* joueur, double veloX, double veloY) {
    if (veloX < 0.01 && veloX > -0.01 && veloY < 0.01 && veloY > -0.01) {
        return;
    }

    // Nouvelles positions potentielles
    float newX = joueur->x + (float) veloX * (float) getCorrectRatio(game) * (float) getCorrectRatio(game) * (float) SPEED;
    float newY = joueur->y + (float) veloY * (float) getCorrectRatio(game) * (float) getCorrectRatio(game) * (float) SPEED;

    if (newX < 0 || newX > (float) getCorrectWidth(game) || newY < 0 || newY > (float) getCorrectHeight(game)) {
        return;
    }

    // Vérifier les collisions avec les meubles
    int i = (int) ((newX - getCorrectOffsetX(game)) / (float) getCorrectCaseSize(game));
    int j = (int) ((newY - getCorrectOffsetY(game)) / (float) getCorrectCaseSize(game));
    if (collisionsBtRectanglesAndCircles((int) (getCorrectOffsetX(game) + (float) i * (float) getCorrectCaseSize(game)),
                                         (int) (getCorrectOffsetY(game) + (float) j * (float) getCorrectCaseSize(game)),
                                         getCorrectCaseSize(game), getCorrectCaseSize(game), (int) newX, (int) newY,
                                         getCorrectRayon(game))
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

    if (collisionsBtCircles((int) newX, (int) newY, getCorrectRayon(game), (int) autre_joueur->x, (int) autre_joueur->y,
                            getCorrectRayon(game))) {
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


void afficherPersonnages(s_game *game) {
    for (int i = 0; i < 2; i++) {
        int dims = getCorrectCaseSize(game);
        BITMAP *player = create_bitmap(dims, dims * 3);
        clear_to_color(player, makecol(255, 0, 255));

        float x = game->joueurs[i].x - (float) dims / 2;
        float y = game->joueurs[i].y - (float) dims / 2;
        float offsetYElements = (float) dims / 2;
        float offsetXElements = (float) ((float) dims - ((float) 3 * (float) dims / 4)) / 2;

        if (game->joueurs[i].en_main == OBJET && game->joueurs[i].handObjet.type == POELE) {
            afficherPoeleInHands(game, player, game->joueurs + i);
        } else if (game->joueurs[i].en_main == OBJET && game->joueurs[i].handObjet.type == ASSIETTE) {
            afficherAssietteInHands(game, player, game->joueurs + i);
        } else if (game->joueurs[i].en_main == OBJET) {
            stretch_sprite(player, getTextureByObjectName(game, game->joueurs[i].handObjet.type), (int) offsetXElements, (int) offsetYElements, 3 * dims / 4, 3 * dims / 4);
        } else if (game->joueurs[i].en_main == INGREDIENT) {
            if (game->joueurs[i].handIngredient.nom != PAS_D_INGREDIENT) {
                stretch_sprite(player, getTextureByIngredientName(game, game->joueurs[i].handIngredient.nom), (int) offsetXElements, (int) offsetYElements, 3 * dims / 4, 3 * dims / 4);
            }
        }

        stretch_sprite(player, game->graphic.textures.player, 0, dims, dims, dims);
        rotate_scaled_sprite(getCorrectBuffer(game), player, (int) x, (int) y - dims, game->joueurs[i].angle, ftofix((float) dims / (float) player->w));
        destroy_bitmap(player);

        circlefill(getCorrectBuffer(game), (int) game->joueurs[i].x, (int) game->joueurs[i].y, dims/5,
                   rgbToAllegroColor(game->joueurs[i].couleur));

        textprintf_centre_ex(getCorrectBuffer(game), font, (int) game->joueurs[i].x, (int) game->joueurs[i].y, makecol(255, 255, 255), -1, "%s", game->joueurs[i].nom);

        executeFunctionForEveryBlockReachable(game, game->joueurs + i, &showInteractions);
    }
}

void deplacerPersonnagesClavier(s_game *game) {
    s_coo velo_perso1 = {0, 0};
    s_coo velo_perso2 = {0, 0};
    /*
    int nb=0;
    s_leson leson;
    */

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
        // charge_Sound(nb);
    }
    if (key[KEY_UP]) {
        velo_perso2.y--;
        // charge_Sound(nb);
    }
    if (key[KEY_DOWN]) {
        velo_perso2.y++;
        // playSound(sons, 0);
    }
    if (key[KEY_LEFT]) {
        velo_perso2.x--;
        // playSound(sons, 0);
    }
    if (key[KEY_RIGHT]) {
        velo_perso2.x++;
        // playSound(sons, 0);
    }

    deplacerPersonnage(game, &game->joueurs[0], velo_perso1.x, velo_perso1.y);
    deplacerPersonnage(game, &game->joueurs[1], velo_perso2.x, velo_perso2.y);
}

void deplacerPersonnageJoystick(s_game *game) {
    for (int i = 0; i < 2; i++) {
        if (joy[i].flags & JOYFLAG_ANALOG && joy[i].flags & JOYFLAG_SIGNED) {
            double x = (double) joy[i].stick[0].axis[0].pos / 128.0;
            double y = (double) joy[i].stick[0].axis[1].pos / 128.0;

            deplacerPersonnage(game, &game->joueurs[i], x, y);
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

            deplacerPersonnage(game, &game->joueurs[i], velo_perso.x, velo_perso.y);
        }
    }
}

void deplacerPersonnages(s_game *game) {
    deplacerPersonnagesClavier(game);
    deplacerPersonnageJoystick(game);

    afficherPersonnages(game);
}

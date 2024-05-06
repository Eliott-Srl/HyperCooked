#include "Commandes.h"

int recetteAvailable(s_game *game, int choix) {
    for (int i = 0; i < game->nbRecettes; i++) {
        if (game->recetteAvailable[i] == choix) {
            return 1;
        }
    }
    return 0;
}

void afficherTimer(s_game *game, s_commande *commande, int i) {
    int time = getTime(game);
    int dTime = time - commande->debut;

    double progression = ((double) dTime / (double) (commande->duration * 1000));
    if (progression > 1) {
        progression = 1;
    }

    int offsetX = (i + 1) * getCorrectCaseSize(game)/4 + i * (getCorrectCaseSize(game) * 3);

    rect(getCorrectBuffer(game),
           offsetX,
          getCorrectHeight(game) - (getCorrectCaseSize(game) * 3) - 10,
           (int) ((float) offsetX + (float) getCorrectCaseSize(game) * 3),
           getCorrectHeight(game) - (getCorrectCaseSize(game) * 3) + 10,
         (progression < 0.8 ? makecol(0, 255, 0) : makecol(255, 0, 0)));
    if (progression > 0) {
        rectfill(getCorrectBuffer(game),
                   offsetX + 2,
                  getCorrectHeight(game) - (getCorrectCaseSize(game) * 3) - 8,
                   (int) ((float) offsetX + progression * ((float) getCorrectCaseSize(game) * 3 - 2.0)),
                   getCorrectHeight(game) - (getCorrectCaseSize(game) * 3) + 8,
                 (progression < 0.8 ? makecol(0, 255, 0) : makecol(255, 0, 0)));
    }
}

void newCommande(s_game *game) {
    if (game->nbCommandes >= NB_COMMANDES_MAX) {
        return;
    }

    int choix;
    do {
        choix = (rand() % (game->nbRecettesAvailable));
    } while (!recetteAvailable(game, choix));

    for (int i = 0; i < game->recettes[choix].nbIngredients; i++) {
        game->commandes[game->nbCommandes].recette.ingredients[i] = game->recettes[choix].ingredients[i];
    }
    game->commandes[game->nbCommandes].recette.nbIngredients = game->recettes[choix].nbIngredients;
    game->commandes[game->nbCommandes].recette.nom = game->recettes[choix].nom;

    game->commandes[game->nbCommandes].duration = ((rand() % 2) + 1) * 5 + 45;
    game->commandes[game->nbCommandes].debut = getTime(game);
    game->nbCommandes++;
    game->commandes[game->nbCommandes].angle = ftofix((float) (rand() % 200 - 100) / 10);
}

void AfficherCommande(s_game *game) {
    if (getQuitting()) {
        return;
    }

    int width = game->graphic.textures.piece->w * getCorrectCaseSize(game) / game->graphic.textures.piece->h;

    stretch_sprite(getCorrectBuffer(game), game->graphic.textures.piece, getCorrectWidth(game) / 2 - width / 2, 0, width, getCorrectCaseSize(game));
    textprintf_centre_ex(getCorrectBuffer(game), font, getCorrectWidth(game) / 2, (getCorrectCaseSize(game) * game->graphic.textures.piece->h / game->graphic.textures.piece->w) / 2, makecol(255, 255, 255), -1, "%d", game->score);

    int EspaceHorizontalEntreLesRectangle = 30;
    int LargeurRectangle;

    if (game->graphic.fs) {
        LargeurRectangle = 150;
    } else {
        LargeurRectangle = 90;
    }

    stretch_sprite(getCorrectBuffer(game), game->graphic.textures.bar, 0,(int) (game->graphic.fs ? (float) getCorrectHeight(game) - 205 : (float) getCorrectHeight(game) - 100),getCorrectWidth(game), 40);
    stretch_sprite(getCorrectBuffer(game), game->graphic.textures.plancheH, 0,(int) (game->graphic.fs ? (float) getCorrectHeight(game) - 173 : (float) getCorrectHeight(game) - 70),getCorrectWidth(game),   (int) (game->graphic.fs ? 140 * getCorrectRatio(game) : (float) 140));

    for (int i = 0; i < game->nbCommandes; i++) {
        int xLogo = 10 + (i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle));

        set_clip_rect(getCorrectBuffer(game), 0, (int) (game->graphic.fs ? 1005 : (float) 375), getCorrectWidth(game),getCorrectHeight(game));
        rotate_scaled_sprite(getCorrectBuffer(game), game->graphic.textures.ticket, xLogo,(int) (game->graphic.fs ? 980 : (float) 340),
                             game->commandes[i].angle,ftofix((float) 110 / (float) game->graphic.textures.ticket->w));
        set_clip_rect(getCorrectBuffer(game), 0, 0, getCorrectWidth(game), getCorrectHeight(game));

        stretch_sprite(getCorrectBuffer(game), getTextureByRecette(game, game->commandes[i].recette.nom), 37 + xLogo, (int) (game->graphic.fs ? 870 : (float) 408), (int) (game->graphic.fs ? 38 * getCorrectRatio(game) : (float) 38), (int) (game->graphic.fs ? 38 * getCorrectRatio(game) : (float) 38));

        int coosX[4] = {25, 90};
        int coosY[4] = {400, 435};
        int coosY2[4] = {972, 1004};

        for (int j = 0; j < game->commandes[i].recette.nbIngredients; j++) {
            BITMAP *ingredient = getTextureByIngredientName(game, game->commandes[i].recette.ingredients[j].nom);

            if (ingredient != NULL) {
                stretch_sprite(getCorrectBuffer(game),
                               getTextureByIngredientName(game, game->commandes[i].recette.ingredients[j].nom),
                               coosX[(int) j/2] + i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle), (int) (game->graphic.fs ? (float) coosY2[j%2]: (float) coosY[j%2]), (int) ((float)18 * (float) getCorrectRatio(game)), (int) ((float)18 * (float) getCorrectRatio(game)));
            }
        }

        afficherTimer(game, &game->commandes[i], i);
    }
}

void actualiserCommandes(s_game *game) {
    for (int i = 0; i < game->nbCommandes; i++) {
        if (game->commandes[i].duration * 1000 < getTime(game) - game->commandes[i].debut) {
            enleverCommande(game, &game->commandes[i]);
            game->score -= 10;
        }
    }
}

void enleverCommande(s_game *game, s_commande *commande) {
    for (int i = 0; i < game->nbCommandes; i++) {
        if (game->commandes[i].recette.nom == commande->recette.nom) {
            for (int j = i; j < game->nbCommandes - 1; j++) {
                game->commandes[j] = game->commandes[j + 1];
            }
            game->nbCommandes--;
            break;
        }
    }
}

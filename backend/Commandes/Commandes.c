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
    int EspaceHorizontalEntreLesRectangle = (int) (30.0 * getCorrectRatio(game));
    int LargeurRectangle = (int) (90.0 * getCorrectRatio(game));

    int xLogo = 10 + (i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle));

    int time = getTime(game);
    int dTime = time - commande->debut;

    double progression = ((double) dTime / (double) (commande->duration * 1000));
    if (progression > 1) {
        progression = 1;
    }

    rect(getCorrectBuffer(game),
         xLogo,
         (int) ((float) getCorrectHeight(game) - (float) (getCorrectCaseSize(game) * 3.75) - (float) 6.0 * getCorrectRatio(game)),
           (int) ((float) xLogo + (float) getCorrectCaseSize(game) * 3.2),
         (int) ((float) getCorrectHeight(game) - (float) (getCorrectCaseSize(game) * 3.75) + (float) 6.0 * getCorrectRatio(game)),
         (progression < 0.8 ? makecol(0, 255, 0) : makecol(255, 0, 0)));
    if (progression > 0) {
        rectfill(getCorrectBuffer(game),
                 xLogo + 2,
                 (int) ((float) getCorrectHeight(game) - (float) (getCorrectCaseSize(game) * 3.75) - (float) 4.0 * getCorrectRatio(game)),
                   (int) ((float) xLogo + progression * ((float) getCorrectCaseSize(game) * 3.2 - 2.0)),
                 (int) ((float) getCorrectHeight(game) - (float) (getCorrectCaseSize(game) * 3.75) + (float) 4.0 * getCorrectRatio(game)),
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
    game->commandes[game->nbCommandes].angle = ftofix((float) ((rand() % 20) - 10));
}

void AfficherCommande(s_game *game) {
    if (getQuitting()) {
        return;
    }

    int width = game->graphic.textures.piece->w * getCorrectCaseSize(game) / game->graphic.textures.piece->h;

    stretch_sprite(getCorrectBuffer(game), game->graphic.textures.piece, getCorrectWidth(game) / 2 - width / 2, 0, width, getCorrectCaseSize(game));
    textprintf_centre_ex(getCorrectBuffer(game), font, getCorrectWidth(game) / 2, (getCorrectCaseSize(game) * game->graphic.textures.piece->h / game->graphic.textures.piece->w) / 2, makecol(255, 255, 255), -1, "%d", game->score);

    int EspaceHorizontalEntreLesRectangle = (int) (30.0 * getCorrectRatio(game));
    int LargeurRectangle = (int) (90.0 * getCorrectRatio(game));

    stretch_sprite(getCorrectBuffer(game), game->graphic.textures.bar, 0,(int) ((float) getCorrectHeight(game) - (float) getCorrectCaseSize(game) * 4.2),getCorrectWidth(game), (int) ((float)40 *
                                                                                                                                                                                       (float) getCorrectRatio(game)));
    stretch_sprite(getCorrectBuffer(game), game->graphic.textures.plancheH, 0,(int) ((float) getCorrectHeight(game) - (float) getCorrectCaseSize(game) * 2.9),getCorrectWidth(game), (int) ((float)140 *
            (float) getCorrectRatio(game)));

    BITMAP *card = create_bitmap(game->graphic.textures.ticket->w, game->graphic.textures.ticket->h);
    for (int i = 0; i < game->nbCommandes; i++) {
        clear_to_color(card, makecol(255, 0, 255));

        int xLogo = 10 + (i * (LargeurRectangle + EspaceHorizontalEntreLesRectangle));

        draw_sprite(card, game->graphic.textures.ticket, 0,0);

        int widthA  = game->graphic.textures.ticket->w / 2;
        int offset = 150;
        BITMAP *recette = getTextureByRecette(game, game->commandes[i].recette.nom);
        stretch_sprite(card, getTextureByRecette(game, game->commandes[i].recette.nom),
                       widthA - widthA/2,
                       ((recette->h * widthA) / recette->w) - ((recette->h * widthA) / recette->w)/2 + offset,
                       widthA, ((recette->h * widthA) / recette->w));

        float coos[2] = {(float) 1 / 8, (float) 5 / 8};

        for (int j = 0; j < game->commandes[i].recette.nbIngredients; j++) {
            stretch_sprite(card,
                           getTextureByIngredientName(game, game->commandes[i].recette.ingredients[j].nom),
                           (int) (coos[j % 2] * (float) widthA * 2.0), (int) ((float) offset + coos[(int) j/2] * (float) widthA * 2.0),
                           90, 90);
        }

        set_clip_rect(getCorrectBuffer(game), 0, (int) ((float) getCorrectHeight(game) - (float) getCorrectCaseSize(game) * 3.15), getCorrectWidth(game), getCorrectHeight(game));
        rotate_scaled_sprite(getCorrectBuffer(game), card, xLogo, (int) ((float) getCorrectCaseSize(game) * 14.5),
                             game->commandes[i].angle, ftofix((float) getCorrectCaseSize(game) / 110.0));
        set_clip_rect(getCorrectBuffer(game), 0, 0,getCorrectWidth(game), getCorrectHeight(game));

        afficherTimer(game, &game->commandes[i], i);
    }
    destroy_bitmap(card);
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

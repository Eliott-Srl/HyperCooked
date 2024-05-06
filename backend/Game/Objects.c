#include "Objects.h"

void afficherPoeleOnFurniture(s_game *game, int h, int l) {
    int x = (int) (getCorrectOffsetX(game) + (float) l * (float) getCorrectCaseSize(game));
    int offsetXIngredient = (int) ((float) getCorrectCaseSize(game) / 5);
    int y = (int) (getCorrectOffsetY(game) + (float) h * (float) getCorrectCaseSize(game));
    int offSetYIngredient = (int) ((float) getCorrectCaseSize(game) / 4);

    stretch_sprite(getCorrectBuffer(game), getTextureByObjectName(game,POELE), x, y, getCorrectCaseSize(game), getCorrectCaseSize(game));
    if (game->matrice[h][l].objet.nbStockes == 0) {
        return;
    }
    if ((game->matrice[h][l].timer == -1 || getTime(game) - game->matrice[h][l].timer < getSupposedTimerByFurnitures(game->matrice[h][l].typeMeuble))) {
        stretch_sprite(getCorrectBuffer(game), getTextureByIngredientName(game, game->matrice[h][l].objet.nourriture[0].nom), x + offsetXIngredient, y + offSetYIngredient, getCorrectCaseSize(game)/2, getCorrectCaseSize(game)/2);
    } else {
        stretch_sprite(getCorrectBuffer(game), getTextureByIngredientName(game, getIngredientAfterCooking(game->matrice[h][l].objet.nourriture[0].nom)), x + offsetXIngredient, y + offSetYIngredient, getCorrectCaseSize(game)/2, getCorrectCaseSize(game)/2);
    }
}

void afficherPoeleInHands(s_game *game, BITMAP *bmp, s_joueur *joueur) {
    int dims = getCorrectCaseSize(game);
    float offsetYElements = (float) dims / 2;
    float offsetXElements = (float) ((float) dims - ((float) 3 * (float) dims / 4)) / 2;

    stretch_sprite(bmp, getTextureByObjectName(game, POELE), (int) offsetXElements, (int) offsetYElements, 3*dims/4, 3*dims/4);

    if (joueur->handObjet.nbStockes == 0) {
        return;
    }

    stretch_sprite(bmp, getTextureByIngredientName(game, joueur->handObjet.nourriture[0].nom), (int) offsetXElements, (int) offsetYElements, dims / 2, dims / 2);
}

void afficherAssietteOnFurniture(s_game *game, int h, int l) {
    int x = (int) (getCorrectOffsetX(game) + (float) l * (float) getCorrectCaseSize(game));
    int y = (int) (getCorrectOffsetY(game) + (float) h * (float) getCorrectCaseSize(game));

    stretch_sprite(getCorrectBuffer(game), getTextureByObjectName(game, ASSIETTE), x, y, getCorrectCaseSize(game), getCorrectCaseSize(game));
    for (int i = 0; i < game->matrice[h][l].objet.nbStockes; i++) {
        stretch_sprite(getCorrectBuffer(game), getTextureByIngredientName(game, game->matrice[h][l].objet.nourriture[i].nom),
                       x + (int) ((i % 2) * getCorrectCaseSize(game) / 2),
                       y + (int) (((int) (i/2) % 2) * getCorrectCaseSize(game) / 2),
                       getCorrectCaseSize(game) / 2,
                       getCorrectCaseSize(game) / 2);
    }
}

void afficherAssietteInHands(s_game *game, BITMAP *bmp, s_joueur *joueur) {
    int dims = getCorrectCaseSize(game);
    float offsetYElements = (float) dims / 2;
    float offsetXElements = (float) ((float) dims - ((float) 3 * (float) dims / 4)) / 2;

    stretch_sprite(bmp, getTextureByObjectName(game, ASSIETTE), (int) offsetXElements, (int) offsetYElements, 3*dims/4, 3*dims/4);

    for (int i = 0; i < joueur->handObjet.nbStockes; i++) {
        stretch_sprite(bmp, getTextureByIngredientName(game, joueur->handObjet.nourriture[i].nom),
                       (int) ((i % 2) * 3 * dims / 8) + (int) offsetXElements,
                       (int) (((int) (i/2) % 2) * 3 * getCorrectCaseSize(game) / 8) + (int) offsetYElements,
                       3 * getCorrectCaseSize(game) / 8,
                       3 * getCorrectCaseSize(game) / 8);
    }
}

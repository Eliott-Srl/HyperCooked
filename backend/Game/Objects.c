#include "Objects.h"

void afficherPoeleOnFurniture(int h, int l) {
    int x = (int) (getCorrectOffsetX() + (float) l * (float) getCorrectCaseSize());
    int offsetXIngredient = (int) ((float) getCorrectCaseSize() / 5);
    int y = (int) (getCorrectOffsetY() + (float) h * (float) getCorrectCaseSize());
    int offSetYIngredient = (int) ((float) getCorrectCaseSize() / 4);

    stretch_sprite(getCorrectBuffer(), getTextureByObjectName(POELE), x, y, getCorrectCaseSize(), getCorrectCaseSize());
    if (getGame()->matrice[h][l].objet.nbStockes == 0) {
        return;
    }
    if ((getGame()->matrice[h][l].timer == -1 || getTime() - getGame()->matrice[h][l].timer < getSupposedTimerByFurnitures(getGame()->matrice[h][l].typeMeuble))) {
        stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getGame()->matrice[h][l].objet.nourriture[0].nom), x + offsetXIngredient, y + offSetYIngredient, getCorrectCaseSize()/2, getCorrectCaseSize()/2);
    } else {
        stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getIngredientAfterCooking(getGame()->matrice[h][l].objet.nourriture[0].nom)), x + offsetXIngredient, y + offSetYIngredient, getCorrectCaseSize()/2, getCorrectCaseSize()/2);
    }
}

void afficherPoeleInHands(BITMAP *bmp, s_joueur *joueur) {
    int dims = getCorrectCaseSize();
    float offsetYElements = (float) dims / 2;
    float offsetXElements = (float) ((float) dims - ((float) 3 * (float) dims / 4)) / 2;

    stretch_sprite(bmp, getTextureByObjectName(POELE), (int) offsetXElements, (int) offsetYElements, 3*dims/4, 3*dims/4);

    if (joueur->handObjet.nbStockes == 0) {
        return;
    }

    stretch_sprite(bmp, getTextureByIngredientName(joueur->handObjet.nourriture[0].nom), (int) offsetXElements, (int) offsetYElements, dims / 2, dims / 2);
}

void afficherAssietteOnFurniture(int h, int l) {
    int x = (int) (getCorrectOffsetX() + (float) l * (float) getCorrectCaseSize());
    int y = (int) (getCorrectOffsetY() + (float) h * (float) getCorrectCaseSize());

    stretch_sprite(getCorrectBuffer(), getTextureByObjectName(ASSIETTE), x, y, getCorrectCaseSize(), getCorrectCaseSize());
    for (int i = 0; i < getGame()->matrice[h][l].objet.nbStockes; i++) {
        stretch_sprite(getCorrectBuffer(), getTextureByIngredientName(getGame()->matrice[h][l].objet.nourriture[i].nom),
                       x + (int) ((i % 2) * getCorrectCaseSize() / 2),
                       y + (int) (((int) (i/2) % 2) * getCorrectCaseSize() / 2),
                       getCorrectCaseSize() / 2,
                       getCorrectCaseSize() / 2);
    }
}

void afficherAssietteInHands(BITMAP *bmp, s_joueur *joueur) {
    int dims = getCorrectCaseSize();
    float offsetYElements = (float) dims / 2;
    float offsetXElements = (float) ((float) dims - ((float) 3 * (float) dims / 4)) / 2;

    stretch_sprite(bmp, getTextureByObjectName(ASSIETTE), (int) offsetXElements, (int) offsetYElements, 3*dims/4, 3*dims/4);

    for (int i = 0; i < joueur->handObjet.nbStockes; i++) {
        stretch_sprite(bmp, getTextureByIngredientName(joueur->handObjet.nourriture[i].nom),
                       (int) ((i % 2) * 3 * dims / 8) + (int) offsetXElements,
                       (int) (((int) (i/2) % 2) * 3 * getCorrectCaseSize() / 8) + (int) offsetYElements,
                       3 * getCorrectCaseSize() / 8,
                       3 * getCorrectCaseSize() / 8);
    }
}

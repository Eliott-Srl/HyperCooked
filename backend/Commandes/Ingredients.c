#include "Ingredients.h"

BITMAP *getTextureByIngredientName(e_ingredients ingredients) {
    switch (ingredients) {
        case SALADE:
            return getGraphic()->textures.laitue;
        case SALADE_COUPEE:
            return getGraphic()->textures.laitueCoupee;
        case TOMATE:
            return getGraphic()->textures.tomate;
        case TOMATES_COUPEES:
            return getGraphic()->textures.tomateCoupee;
        case PAIN:
            return getGraphic()->textures.pain;
        case STEAK:
            return getGraphic()->textures.steak;
        case STEAK_CUIT:
            return getGraphic()->textures.steakCuit;
        case POTATO:
            return getGraphic()->textures.pommeDeTerre;
        case OEUF:
            return getGraphic()->textures.oeuf;
        case FROMAGE:
            return getGraphic()->textures.fromage;
        default:
            return getGraphic()->textures.invalidTexture;
    }
}

int getCuissonByIngredient(e_ingredients ingredient) {
    switch (ingredient) {
        case STEAK:
            return A_LA_POELE;
        default:
            return NON;
    }
}

int getIngredientAfterCooking(e_ingredients ingredient) {
    switch (ingredient) {
        case STEAK:
            return STEAK_CUIT;
        default:
            return PAS_D_INGREDIENT;
    }
}


int getFurnitureByCooking(e_cuisson cuisson) {
    switch (cuisson) {
        case A_LA_POELE:
            return POELE;
        case A_LA_MARMITE:
            return MARMITE;
        default:
            return NONE;
    }
}

int getIngredientAfterCutting(e_ingredients ingredient) {
    switch (ingredient) {
        case TOMATE:
            return TOMATES_COUPEES;
        case SALADE:
            return SALADE_COUPEE;
        default:
            return PAS_D_INGREDIENT;
    }
}

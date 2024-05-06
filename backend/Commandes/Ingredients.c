#include "Ingredients.h"

BITMAP *getTextureByIngredientName(s_game *game, e_ingredients ingredients) {
    switch (ingredients) {
        case SALADE:
            return game->graphic.textures.laitue;
        case SALADE_COUPEE:
            return game->graphic.textures.laitueCoupee;
        case TOMATE:
            return game->graphic.textures.tomate;
        case TOMATES_COUPEES:
            return game->graphic.textures.tomateCoupee;
        case PAIN:
            return game->graphic.textures.pain;
        case STEAK:
            return game->graphic.textures.steak;
        case STEAK_CUIT:
            return game->graphic.textures.steakCuit;
        case POTATO:
            return game->graphic.textures.pommeDeTerre;
        case OEUF:
            return game->graphic.textures.oeuf;
        case FROMAGE:
            return game->graphic.textures.fromage;
        default:
            return game->graphic.textures.invalidTexture;
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

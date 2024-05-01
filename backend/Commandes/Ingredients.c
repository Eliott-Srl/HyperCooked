#include "Ingredients.h"

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

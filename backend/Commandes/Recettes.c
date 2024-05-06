#include "Recettes.h"

BITMAP *getTextureByRecette(s_game *game, e_recettes recette) {
    switch (recette) {
        case BURGER:
            return game->graphic.textures.burger;
        case P_SALADE:
            return game->graphic.textures.salade;
        case PIZZA:
            return game->graphic.textures.pizza;
        default:
            return game->graphic.textures.invalidTexture;
    }
}

void loadRecipes(s_game *game) {
    int nbRecettes = 0;
    char ligne[STRMAX], *p, *d, *g, *end;
    FILE *fp = NULL;

    fp = fopen("recettes.txt", "r");

    if (!fp) {
        perror("recettes.txt");
        abort();
    }

    while (fgets(ligne, STRMAX, fp) != NULL && nbRecettes < NB_RECETTES_MAX) {
        if (ligne[0] == '#') {
            continue;
        }

        int nbIngredients = 0;

        p = strtok(ligne, ";");
        game->recettes[nbRecettes].nom = strtol(p, NULL, 10);

        p = strtok(NULL, ";");

        d = strtok_r(p, ",", &end);
        while (d != NULL) {
            g = strtok(d, " ");
            game->recettes[nbRecettes].ingredients[nbIngredients].nom = strtol(g, NULL, 10);
            g = strtok(NULL, " ");
            game->recettes[nbRecettes].ingredients[nbIngredients].cuisson = strtol(g, NULL, 10);
            g = strtok(NULL, " ");
            game->recettes[nbRecettes].ingredients[nbIngredients].coupable = strtol(g, NULL, 10);
            nbIngredients++;
            d = strtok_r(NULL, ",", &end);
        }
        game->recettes[nbRecettes].nbIngredients = nbIngredients;
        nbRecettes++;
    }
    game->nbRecettes = nbRecettes;
    fclose(fp);
}

int verificationIngredient(s_ingredient ingredient, s_commande *commande) {
    for (int i = 0; i < commande->recette.nbIngredients; i++) {
        if (ingredient.nom == commande->recette.ingredients[i].nom) {
            return 1;
        }
    }
    return 0;
}

int verificationDeLaRecette(s_game *game, s_objet* plat, s_commande* commandeFind) {
    int ingredientCorresponds;
    if (plat->type != ASSIETTE) {
        return 0;
    }

    for (int commande = 0; commande < game->nbCommandes; commande++) {
        *commandeFind = game->commandes[commande];
        if (commandeFind->recette.nbIngredients == plat->nbStockes) {
            ingredientCorresponds = 0;
            for (int ingredient = 0; ingredient < plat->nbStockes; ingredient++) {
                if (verificationIngredient(plat->nourriture[ingredient], commandeFind)) {
                    ingredientCorresponds++;
                }
            }

            if (ingredientCorresponds == plat->nbStockes) {
                return 1;
            }
        }
    }
    return 0;
}

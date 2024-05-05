#include "Recettes.h"

BITMAP *getTextureByRecette(e_recettes recette) {
    switch (recette) {
        case BURGER:
            return getGraphic()->textures.burger;
        case P_SALADE:
            return getGraphic()->textures.salade;
        case PIZZA:
            return getGraphic()->textures.pizza;
        default:
            return getGraphic()->textures.invalidTexture;
    }
}

void loadRecipes() {
    s_game *game = getGame();

    int nbRecettes = 0;
    char ligne[STRMAX], *p, *d, *g, *end;
    FILE *fp = NULL;

    char *base = "0123456789";
    char nombre[128] = "";

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
        game->recettes[nbRecettes].nbIngredients = nbIngredients; //
        nbRecettes++;
    }
    getGame()->nbRecettes = nbRecettes;
    fclose(fp);
}

int verificationDeLaRecette(s_objet* plat, s_commande* commandeFind) {
    int a;
    for (int i = 0; i < getGame()->nbCommandes; i++) {
        *commandeFind = getGame()->commandes[i];
        if (commandeFind->recette.nbIngredients == plat->nbStockes) {
            a = 0;
            for (int j = 0; j < plat->nbStockes; j++) {
                if(plat->nourriture[j].nom == commandeFind->recette.ingredients[a].nom
                   && plat->nourriture[j].coupe == commandeFind->recette.ingredients[a].coupe
                   && plat->nourriture[j].cuit == commandeFind->recette.ingredients[a].cuit) {
                    a++;
                } else {
                    break;
                }
            }

            if (a == plat->nbStockes) {
                return 1;
            }
        }
    }
    return 0;
}

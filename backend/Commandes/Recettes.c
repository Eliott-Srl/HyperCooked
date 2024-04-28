#include "Recettes.h"

void loadRecipes() {
    s_game *game = getGame();

    int nbRecettes = 0, nbIngredients = 0;
    char ligne[STRMAX], *p, *d, *g, *end;
    FILE *fp = NULL;

    fp = fopen("recettes.txt", "r");

    if (!fp) {
        perror("recettes.txt");
        abort();
    }

    while (fgets(ligne, STRMAX, fp) != NULL || nbRecettes < NB_RECETTES_MAX) {
        p = strtok(ligne, ";");
        strcpy(game->recettes[nbRecettes].nom, p);

        p = strtok(NULL, ";");

        d = strtok_r(p, ",", &end);
        while (d != NULL) {
            g = strtok(d, " ");
            game->recettes[nbRecettes].ingredients[game->recettes[nbRecettes].nbIngredients].nom = atoi(g);
            g = strtok(NULL, " ");
            game->recettes[nbRecettes].ingredients[game->recettes[nbRecettes].nbIngredients].cuisson = atoi(g);
            g = strtok(NULL, " ");
            game->recettes[nbRecettes].ingredients[game->recettes[nbRecettes].nbIngredients].coupable = atoi(g);
            nbIngredients++;
            game->recettes[nbRecettes].nbIngredients = nbIngredients;
            d = strtok_r(NULL, ",", &end);
        }
        nbRecettes++;
    }
    getGame()->nbRecettes = nbRecettes;
    fclose(fp);
}

void freeRecettes(s_recette *recettes) {
    free(recettes);
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

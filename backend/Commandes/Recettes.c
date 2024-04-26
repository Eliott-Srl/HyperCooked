#include "Recettes.h"

void loadRecipes() {
    s_game *game = getGame();

    int nbRecettes = 0;
    char ligne[STRMAX], *p, ingredients[STRMAX], *end, *s;
    s_recette *pRecette = NULL;
    FILE *fp = NULL;

    char *base = "0123456789";

    fp = fopen("../recettes.txt", "r");
    if (!fp) {
        perror("../recettes.txt");
        abort();
    }

    while (fgets(ligne, STRMAX, fp) != NULL || nbRecettes < NB_RECETTES_MAX) {
        p = strtok(ligne, ";");
        strcpy(game->recettes[nbRecettes].nom, p);

        p = strtok(ligne, ";");

        for(int i = 1; i <= 3; i++){
            p = strtok(p, ",");
            for(int j = 1; j <= 3; j++){
                p = strtok(p, " ");
                switch (j) {
                    case 1:
                        game->recettes[nbRecettes].ingredients[NB_INGREDIENTS_MAX].nom = strtol(ligne, &end, 10);
                        break;
                    case 2:
                        game->recettes[nbRecettes].ingredients[NB_INGREDIENTS_MAX].cuit = strtol(ligne, &end, 10);
                        break;
                    case 3:
                        game->recettes[nbRecettes].ingredients[NB_INGREDIENTS_MAX].coupable = strtol(ligne, &end, 10);
                        break;
                }
            }
        }
        nbRecettes++;
    }
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

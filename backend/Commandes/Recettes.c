#include "Recettes.h"

void loadRecipes() {
    s_game *game = getGame();
    /*
    int type = 0, nbRecettes = 0;
    char ligne[STRMAX], *p, ingredients[STRMAX], *i, *end, *j;
    s_recette *pRecette = NULL, *recettes = NULL, stckrecette[NB_RECETTES_MAX];
    FILE *fp = NULL;

    char *base = "0123456789";

    fp = fopen("../recettes.txt", "r");
    if (!fp) {
        perror("../recettes.txt");
        abort();
    }

    recettes = (s_recette *) malloc(sizeof(s_recette) * NB_RECETTES_MAX);

    if (!recettes) {
        fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(s_recette)*NB_RECETTES_MAX);
        abort();
    }

    while (fgets(ligne, STRMAX, fp) != NULL || nbRecettes < NB_RECETTES_MAX) {
        if (strchr(base, *p) != NULL) {
            strncat(stckrecette, p, 1);
        }

        p = strtok(ligne, ";");
        strcpy(stckrecette[nbRecettes].nom, p);

        p = strtok(NULL, ";");
        strcpy(stckrecette[nbRecettes].ingredients, p);

        i = strtok("ingredients", ",");
        while(i) {
            j = strtok("caractéristiques", " ");
            while (j){
                stckrecette[nbRecettes].ingredients[type].nom = strtol(j, &end, 10);
                stckrecette[nbRecettes].ingredients[type].cuisson = strtol(j, &end, 10);
                stckrecette[nbRecettes].ingredients[type].coupable = strtol(j, &end, 10);
            }
            type++;
        }
        nbRecettes++;
    }
    fclose(fp);

    return stckrecette;
     */
}

void freeRecettes(s_recette *recettes) {
    free(recettes);
}

void newRecette(s_graphic* graphic) {
    int choix = rand() % (getGame()->nbRecettes - 1);
    getGame()->commandes[getGame()->nbCommandes].recette = getGame()->recettes[choix];
    printf("Nouvelle recette: %s\n", getGame()->commandes[getGame()->nbCommandes].recette.nom);
    getGame()->nbCommandes++;
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

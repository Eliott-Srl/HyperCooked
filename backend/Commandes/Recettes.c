#include "Recettes.h"

s_recette *load() {
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
}

int compareIngredients(s_ingredient *ingredient1, s_ingredient_physique *ingredient2) {
    if (ingredient1->nom == ingredient2->type.nom) {
        return 1;
    }
    return 0;
}

void freeRecettes(s_recette *recettes) {
    free(recettes);
}

void crearecettes(s_game *game) {
    int j,  choix = rand()%game->nb_recettes;
    s_recette recettes[NB_RECETTES_MAX];
    e_ingredients ingredients[NB_INGREDIENTS_MAX];

    printf("la recette est %s ", recettes[choix].nom);

    for(int i = 0 ; i < NB_INGREDIENTS_MAX ; i++){
        switch (ingredients[i]) {
            case SALADE:
                printf("Salade \n");
            case PAIN:
                printf("Pain \n");
            case STEAK:
                printf("Steak \n");
            case TOMATE:
                printf("Tomate \n");
            case OEUF:
                printf("Oeuf \n");
            case POTATO:
                printf("Pomme de terre \n");
        }
    }
}

int verificationDeLaRecette(s_game* game, s_objet* plat, s_commande* commandeFind) {
    int a;
    for (int i = 0; i < game->nbCommandes; i++) {
        *commandeFind = game->commandes[i];
        if (commandeFind->recette.nbIngredients == plat->nbStockes) {
            a = 0;
            for (int j = 0; j < plat->nbStockes; j++) {
                if(plat->nourriture[j].nom == commandeFind->recette.ingredients[0].nom
                   && plat->nourriture[j].coupe == commandeFind->recette.ingredients[0].coupe
                   && plat->nourriture[j].cuit == commandeFind->recette.ingredients[0].cuit) {
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
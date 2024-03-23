#include "Recettes.h"

s_recette *load() {
    int type = 0, nbRecettes = 0;
    char ligne[STRMAX], *p, ingredients[STRMAX], *i, *end, *j;
    s_recette *pRecette = NULL, *recettes = NULL;
    FILE *fp = NULL;

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
        p = strtok(ligne, ";");
        strcpy(recettes[nbRecettes].nom, p);

        p = strtok(NULL, ";");
        strcpy(ingredients, p);

        i = strtok("ingredients", ",");
        while(i) {
            j = strtok("ingredients", " ");
            while (j){
                recettes[nbRecettes].ingredients[type].nom = strtol(j, &end, 10);
                recettes[nbRecettes].ingredients[type].cuisson = strtol(j, &end, 10);
                recettes[nbRecettes].ingredients[type].coupable = strtol(j, &end, 10);
            }
            type++;
        }

        nbRecettes++;
    }
    fclose(fp);

    return recettes;
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
    int j,  choix = rand()%game->nbRecettes;
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

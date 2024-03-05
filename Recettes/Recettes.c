#include "Recettes.h"

s_recette *load() {
    int type = 0, nbRecettes = 0;
    char ligne[STRMAX], *p, ingredients[STRMAX], *i, *end;
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

        i = strtok("ingredients", " ");
        while(i) {
            recettes[nbRecettes].ingredients[type] = strtol(i, &end, 10);
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

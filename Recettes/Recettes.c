#include "Recettes.h"

void load() {
    int type = 0, nbRecettes = 0;
    char ligne[STRMAX], *p, ingredients[STRMAX], *i, *end;
    s_recette *recette = NULL;
    FILE *fp = NULL;

    fp = fopen("../recettes.txt", "r");
    if (fp == NULL) {
        return;
    }

    s_game *game = (s_game *) malloc(sizeof(s_game));

    while (fgets(ligne, STRMAX, fp) != NULL || game < NB_RECETTES_MAX) {
        recette = (s_recette *) malloc(sizeof(s_recette));

        p = strtok(ligne, ";");
        strcpy(recette->nom, p);

        p = strtok(NULL, ";");
        strcpy(ingredients, p);

        i = strtok("ingredients", " ");
        while(i) {
            recette->ingredients[type] = strtol(i, &end, 10);
            type++;
        }

        nbRecettes++;
    }

    free(game);
}
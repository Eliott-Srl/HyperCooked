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

    while (fgets(ligne, STRMAX, fp) != NULL || nbRecettes < NB_RECETTES_MAX) {
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
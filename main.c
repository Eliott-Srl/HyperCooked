#include "allezgros/Allezgros.h"
#include <conio.h>

int main() {
    allegro_init();

    int dx = 0;
    int dy = 0;
    char input;
    int eltiempo = 0;
    int tempsDuJeux = 0;
    int perso = 0;

    s_game *game = (s_game *) calloc(1, sizeof(s_game));

    initialiserMatrice(game->matrice); // créer un fichier ou les meubles apparais
    afficherMatrice(game->matrice); // afficher la matrice

    // Créer les joueurs

    load();

    // Gérer le timer
    tempsDuJeux = timer();
    while (tempsDuJeux <= 90) {
        if(tempsDuJeux - eltiempo > 20){
            crearecettes(game); // crée une recette depuis la structure
            eltiempo = tempsDuJeux; //
        }

        input = getch();

        switch (input) {
            case 'z' :
                dy++;
                perso = 0;
                break;
            case 's' :
                dy--;
                perso = 0;
                break;
            case 'q' :
                dx--;
                perso = 0;
                break;
            case 'd' :
                dx++;
                perso = 0;
                break;
            case 75 :// Flèche gauche
                dx--;
                perso = 1;
                break;
            case 77 :// Flèche droite
                dx++;
                perso = 1;
                break;
            case 72 :// Flèche haut
                dy++;
                perso = 1;
                break;
            case 80 :// Flèche bas
                dy--;
                perso = 1;
                break;
        }

        deplacerPersonnage(game, game->joueurs[perso], dx, dy);
        afficherMatrice(game->matrice);
        printf("Il reste %d \n", 90 - tempsDuJeux);
    }

    printf("Vous avez perdu, looooooseerrrr !!!");

    return 0;
} END_OF_MAIN()
#include "Game.h"
#include <time.h>
#include "../Matrice/meubles.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void creationJoueurs() {

        char nom[50];
        char couleur[20];

        printf("Veuillez entrer le nom de votre personnage : ");
        scanf("%49s", nom); // %49s limite la saisie à 49 caractères pour éviter le dépassement de mémoire


        printf("Veuillez entrer la couleur de votre personnage : ");
        scanf("%19s", couleur); // %19s limite la saisie à 19 caractères pour éviter le dépassement de mémoire

        printf("Vous avez créé un personnage nommé %s avec la couleur %s.\n", nom, couleur);


}

void timer(){
        int seconde = 90;
        int score = 0;

        // Obtenir le temps actuel
        time_t start_time = time(NULL);
        time_t current_time = 0;
        int elapsed_time = 0, deplacement = 0;

        while (elapsed_time <= 90 && score < 150) {
            deplacement = 0;

            afficherMatrice(int *tab);

            // Obtenir le temps actuel
            current_time = time(NULL);

            // Calculer le temps écoulé en secondes
            elapsed_time = difftime(current_time, start_time);
            printf("Il reste %d \n", 90 - elapsed_time);
        }

}





// Fonction pour détecter les collisions entre deux objets
int collisions(int x1, int y1, int l1, int h1, int x2, int y2, int l2, int h2) {
    return (x1 < x2 + l2 &&
            x1 + l1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2);
    }

// Fonction pour déplacer un personnage tout en évitant les collisions avec les meubles
void deplacerPersonnage(Personnage *personnage, int dx, int dy, Meuble meubles[], int nbMeubles, Personnage autresPersonnages[], int nbAutresPersonnages) {
    // Nouvelles positions potentielles
    int newX = personnage->x + dx;
    int newY = personnage->y + dy;

    // Vérifier les collisions avec les meubles
    for (int i = 0; i < nbMeubles; i++) {
        if (collisions(newX, newY, personnage->largeur, personnage->hauteur, meubles[i].x, meubles[i].y, meubles[i].largeur, meubles[i].hauteur)) {
            // Il y a une collision, ne pas bouger
            return;
        }
    }

    // Vérifier les collisions avec les autres personnages
    for (int i = 0; i < nbAutresPersonnages; i++) {
        if (collisions(newX, newY, personnage->largeur, personnage->hauteur, autresPersonnages[i].x, autresPersonnages[i].y, autresPersonnages[i].largeur, autresPersonnages[i].hauteur)) {
            // Il y a une collision avec un autre personnage, ne pas bouger
            return;
        }
    }

    // Déplacer le personnage aux nouvelles positions
    personnage->x = newX;
    personnage->y = newY;
}

void Collision () {

    // Exemple de deux personnages et quelques meubles
    Personnage joueur1 = {10, 10, 20, 20};
    Personnage joueur2 = {30, 30, 20, 20};
    Meuble meubles[] = {
            {PLAN_DE_TRAVAIL, 25, 25, 30, 5},
            {COFFRE, 40, 15, 10, 10},
            {COMPTOIR, 60, 20, 5, 15},
            {POUBELLE, 10, 50, 8, 8}
    };
    int nbMeubles = sizeof(*meubles) / sizeof(meubles[0]);

    // Déplacer joueur1
    deplacerPersonnage(&joueur1, 5, 5, meubles, nbMeubles, &joueur2, 1);

    // Déplacer joueur2
    deplacerPersonnage(&joueur2, -5, -5, meubles, nbMeubles, &joueur1, 1);

    // Afficher les positions des joueurs après déplacement
    printf("Position joueur1 : (%d, %d)\n", joueur1.x, joueur1.y);
    printf("Position joueur2 : (%d, %d)\n", joueur2.x, joueur2.y);

}




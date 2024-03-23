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
                }
            }

            if (a == plat->nbStockes) {
                return 1;
            }
        }
    }
    return 0;
}

void neFaitRien(s_game* game, s_joueur* joueur) {
    return;
}

void planDeTravail(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET) {
        game->matrice[i][j].objet = joueur->hand_objet;
        joueur->en_main = NOTHING;
    }
}

void plancheADecouper(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        game->matrice[i][j].objet.nourriture[0] = joueur->hand_ingredient.type;
        joueur->en_main = NOTHING;
    }
}

void comptoir(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == OBJET) {
        s_commande commandFind;
        int good = verificationDeLaRecette(game, &joueur->hand_objet, &commandFind);
        joueur->en_main = NOTHING;
        if (good) {
            // TODO: Calculate score
        } else {
            printf("La commande n'était pas bonne");
        }
    }
}

void coffre(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == NOTHING) {
        joueur->en_main = INGREDIENT;
        joueur->hand_ingredient.en_main = 1;
        joueur->hand_ingredient.type.cuit = NON;
        joueur->hand_ingredient.type.coupe = 0;
        joueur->hand_ingredient.type.nom = game->matrice[i][j].objet.nourriture[0].nom;
        joueur->hand_ingredient.type.coupable = game->matrice[i][j].objet.nourriture[0].coupable;
        joueur->hand_ingredient.type.cuisson = game->matrice[i][j].objet.nourriture[0].cuisson;
    }
}

void plaqueDeCuisson(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        if (game->matrice[i][j].objet.type == MARMITE && game->matrice[i][j].objet.nbStockes < game->matrice[i][j].objet.stockageMax) {
            game->matrice[i][j].objet.nourriture[game->matrice[i][j].objet.nbStockes] = joueur->hand_ingredient.type;
            joueur->en_main = NONE;
        } else if (game->matrice[i][j].objet.type == POELE && game->matrice[i][j].objet.nbStockes < 1) {
            game->matrice[i][j].objet.nourriture[game->matrice[i][j].objet.nbStockes] = joueur->hand_ingredient.type;
            joueur->en_main = NONE;
        }
    } else if (joueur->en_main == OBJET) {
        if (game->matrice[i][j].objet.type == NONE) {
            game->matrice[i][j].objet = joueur->hand_objet;
            joueur->en_main = NONE;
        }
    }
}

void poubelle(s_game* game, s_joueur* joueur, int i, int j) {
    if (joueur->en_main == INGREDIENT) {
        joueur->en_main = NONE;
    } else if (joueur->en_main == OBJET) {
        joueur->hand_objet.nbStockes = 0;
        joueur->en_main = NONE;
    }
}
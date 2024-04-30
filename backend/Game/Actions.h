#ifndef HYPERCOOKED_ACTIONS_H
#define HYPERCOOKED_ACTIONS_H

#include "../backend.h"
#include <Math.h>

void executeFunctionForEveryBlockReachable(s_joueur *joueur, void (*fonction)(s_joueur*, int, int));
void meuble(s_joueur *joueur, int k, int s);
// Fonction pour gérer les entrées joystick et déplacer les deux joueurs
void deplacerPersonnageJoystick();
void deplacerPersonnage(s_joueur* joueur, double veloX, double veloY);
BITMAP *getTextureByObjectName(e_objet objet);
BITMAP *getTextureByFurnitureName(e_meubles meuble);
BITMAP *getTextureByIngredientName(e_ingredients ingredients);
void deplacerPersonnages();
int coupableByIngredient(e_ingredients ingredient);
int cuissonByIngredient(e_ingredients ingredient);
void interact(s_joueur* joueur, int i, int j);
void neFaitRien(s_joueur* joueur, int i, int j);
void planDeTravail(s_joueur* joueur, int i, int j);
void plancheADecouper(s_joueur* joueur, int i, int j);
void comptoir(s_joueur* joueur, int i, int j);
void coffre(s_joueur* joueur, int i, int j);
void plaqueDeCuisson(s_joueur* joueur, int i, int j);
void poubelle(s_joueur* joueur, int i, int j);

#endif //HYPERCOOKED_ACTIONS_H

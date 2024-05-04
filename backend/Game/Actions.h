#ifndef HYPERCOOKED_ACTIONS_H
#define HYPERCOOKED_ACTIONS_H

#include "../backend.h"
#include <Math.h>

void executeFunctionForEveryBlockReachable(s_joueur *joueur, void (*fonction)(s_joueur*, int, int));
void showInteractions(s_joueur *joueur, int k, int s);
BITMAP *getTextureByObjectName(e_objet objet);
void interact(s_joueur* joueur, int i, int j);
void neFaitRien(s_joueur* joueur, int i, int j);
void planDeTravail(s_joueur* joueur, int i, int j);
void plancheADecouper(s_joueur* joueur, int i, int j);
void comptoir(s_joueur* joueur, int i, int j);
void coffre(s_joueur* joueur, int i, int j);
void plaqueDeCuisson(s_joueur* joueur, int i, int j);
void poubelle(s_joueur* joueur, int i, int j);

#endif //HYPERCOOKED_ACTIONS_H

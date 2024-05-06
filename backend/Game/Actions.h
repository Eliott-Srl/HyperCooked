#ifndef HYPERCOOKED_ACTIONS_H
#define HYPERCOOKED_ACTIONS_H

#include "../backend.h"
#include <Math.h>

void executeFunctionForEveryBlockReachable(s_game *game, s_joueur *joueur, void (*fonction)(s_game*, s_joueur*, int, int));
void showInteractions(s_game *game, s_joueur *joueur, int k, int s);
BITMAP *getTextureByObjectName(s_game *game, e_objet objet);
void interact(s_game *game, s_joueur* joueur, int i, int j);
void neFaitRien(s_game *game, s_joueur* joueur, int i, int j);
void planDeTravail(s_game *game, s_joueur* joueur, int i, int j);
void plancheADecouper(s_game *game, s_joueur* joueur, int i, int j);
void comptoir(s_game *game, s_joueur* joueur, int i, int j);
void coffre(s_game *game, s_joueur* joueur, int i, int j);
void plaqueDeCuisson(s_game *game, s_joueur* joueur, int i, int j);
void generateurAssiette(s_game *game, s_joueur *joueur, int i, int j);
void poubelle(s_game *game, s_joueur* joueur, int i, int j);

#endif //HYPERCOOKED_ACTIONS_H

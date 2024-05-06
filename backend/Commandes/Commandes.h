#ifndef HYPERCOOKED_COMMANDES_H
#define HYPERCOOKED_COMMANDES_H

#include "../backend.h"
#include <stdlib.h>
#include <stdio.h>
#include "time.h"

void newCommande(s_game *game);
void AfficherCommande(s_game *game);
void actualiserCommandes(s_game *game);
void enleverCommande(s_game *game, s_commande *commande);

#endif //HYPERCOOKED_COMMANDES_H

//
// Created by LuucM on 28-04-2023.
//

#ifndef YUKONGAMEDTU_LOGIC_H
#define YUKONGAMEDTU_LOGIC_H

#include "stdlib.h"
#include "stdbool.h"
#include "card.h"

bool checkMoveC(Card** fromPile, Card** toPile, int from);
bool checkMoveF(Card** fromPile, Card** toPile, int from);

bool moveCards(Card **fromPile, Card **toPile, int from, bool endPile, char *messages);
void checkForValidInputMove(char* usrInput);
void splitShuffle(Card** firstCard, Card** lastCard, int split);
void shuffle(Card** firstCard, Card** lastCard);
void placeCard(Card** newPile, Card** oldPile);

#endif //YUKONGAMEDTU_LOGIC_H

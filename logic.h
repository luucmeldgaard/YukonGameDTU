//
// Created by LuucM on 28-04-2023.
//

#ifndef YUKONGAMEDTU_LOGIC_H
#define YUKONGAMEDTU_LOGIC_H

#include "stdlib.h"
#include "stdbool.h"
#include "card.h"

bool checkLegalMove(Card** fromPile, Card** toPile, int from);
bool checkLegalMove2(Card** fromPile, Card** toPile, int from);
bool moveCards(Card** fromPile, Card** toPile, int from, bool endPile);
void checkForValidInputMove(char* usrInput);
void splitShuffle(Card** firstCard, Card** lastCard, int split);
void shuffle(Card** firstCard, Card** lastCard);
void placeCard(Card** newPile, Card** oldPile);

#endif //YUKONGAMEDTU_LOGIC_H

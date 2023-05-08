//
// Created by emils on 29/04/2023.
//

#ifndef YUKONGAMEDTU_UNDOREDO_H
#define YUKONGAMEDTU_UNDOREDO_H

#include "card.h"
#include <stdio.h>

char *saveCurrentGame(Card** c1, Card** c2, Card** c3, Card** c4, Card** c5, Card** c6, Card** c7, Card** f1, Card** f2, Card** f3, Card** f4);

char *saveMove(char* move);

#endif //YUKONGAMEDTU_UNDOREDO_H

#ifndef YUKONGAMEDTU_CARD_H
#define YUKONGAMEDTU_CARD_H

#include <stdbool.h>

// Each card represent a Node in the linked list
typedef struct Card{
    // Clubs, diamonds, Hearts, Spades
    char cardType;
    // Ace, numbers, jacks, queens, kings
    char cardValue;
    // Loads the next and previous memory location for sorrounding cards
    struct Card *next;
    struct Card *previous;
    bool flipped;
} Card;

#endif //YUKONGAMEDTU_CARD_H

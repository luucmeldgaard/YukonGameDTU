//
// Created by LuucM on 28-04-2023.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "card.h"
#include "logic.h"
#include "inputChecks.h"



// Assignment

bool moveCards(Card **fromPile, Card **toPile, int from, bool endPile, char *messages) {

    if (redo == true) {
        printf("true");
    }

    if (*fromPile == NULL){
        strcpy(messages, "The chosen selected column does not have card");
        printf("CRASHAND DIE");
        return false;
    }


    Card* tempFrom = *fromPile;
    Card* tempTo = *toPile;


    if (from == -1) {
        while ((*fromPile)->next != NULL) {
            (*fromPile) = (*fromPile)->next;
        }
    }
    for (int i = 0; i < from; i ++) {
        (*fromPile) = (*fromPile)->next;
    }
    if ((*toPile) != NULL) {
        while ((*toPile)->next != NULL) {
            (*toPile) = (*toPile)->next;
        }
    }


    if ((*fromPile)->flipped == true){
        *fromPile = tempFrom;
        *toPile = tempTo;
        strcpy(messages, "Card is still flipped upside down");
        return false;
    }

    if (!endPile) {
        if (!checkMoveC(fromPile, toPile)) {
            strcpy(messages, "Illegal move");
            printf("\nIllegal move to main board!\n");
            *fromPile = tempFrom;
            *toPile = tempTo;
            return false;
        }
    } else{
        if (!checkMoveF(fromPile, toPile)) {
            strcpy(messages, "Illegal move!");
            printf("\nIllegal move to end pile!\n");
            *fromPile = tempFrom;
            *toPile = tempTo;
            return false;
        }
    }


    // Makes moves from C1-C7 to F1-F4 available - (First card only)
    if ((*fromPile)->previous == NULL && (*toPile == NULL)){
        (*toPile) = (*fromPile);
        *fromPile = NULL;
        strcpy(messages, "Movement successful!");
        return true;
    }
    Card* oldPile = *fromPile;
    Card* newPile = *toPile;

    // Make moves for kings to empty space available
    if (newPile == NULL){
        newPile = oldPile;
        oldPile = oldPile->previous;
        oldPile->next = NULL;
        newPile->previous = NULL;
        while (oldPile->previous != NULL){
            oldPile = oldPile->previous;
        }
        (*fromPile) = oldPile;
        (*toPile) = newPile;
        strcpy(messages, "Movement successful!");
        return true;
    }

    printf("\n\n%c%c <<<\n\n", (*toPile)->cardValue, (*toPile)->cardType);
    printf("\n\n%c%c <<<\n\n", (*fromPile)->cardValue, (*fromPile)->cardType);

    Card* cardToMove = oldPile;
    ////////////////////////////////////////
    // Wrong pile is moved, fix me ////////////////
    //////////////////////////////////////////////
    oldPile = oldPile->previous;
    oldPile->flipped = false;
    oldPile->next = NULL;

    newPile->next = cardToMove;



    *fromPile = tempFrom;
    *toPile = tempTo;
    strcpy(messages, "Movement successful!");


    return true;
}


// Splitshuffle according to assignemnet. Lots of pointer stuff -_-
void splitShuffle(Card** firstCard, Card** lastCard, int split){
    Card* currentCard = *firstCard;
    int randomNumber = split;
    // Creates a random number. rand() in c must be provided a seed, otherwise the same random sequence will happen everytime, and as such very quickly become predictable
    // Using the current time as seed.
    if (randomNumber == 0) {
        time_t currentTime = time(NULL);
        srand(currentTime);
        randomNumber = rand() % (52 - 1 + 1) + 1;
    }


    for (int i = 1; i < randomNumber; i++) {
        currentCard = currentCard->next;
    }
    // Creates the piles
    Card* pile1 = *firstCard;
    Card* pile2 = currentCard->next;
    Card* pile3 = NULL;

    // splits the list into 2
    currentCard->next->previous = NULL;
    currentCard->next = NULL;
    currentCard = NULL; // Reset should not be necessary but done just to be sure...
    while(pile1 != NULL && pile2 != NULL){
        if (pile1 != NULL){
            if (pile1->previous != NULL){
                currentCard = pile1->next;
                pile1->next = pile3;
                pile3 = pile1;
                pile1 = currentCard;
            } else if (pile1->previous == NULL) {
                currentCard = pile1->next;
                pile1->next = NULL;
                pile3 = pile1;
                pile1 = currentCard;
            }
        }
        if (pile2 != NULL){
            if (pile2 != NULL) {
                currentCard = pile2->next;
                pile2->next = pile3;
                pile3 = pile2;
                pile2 = currentCard;
            }
        }
    }

    pile3 -> previous = NULL;
    *firstCard = pile3;

    while (pile3->next != NULL){
        pile3 = pile3->next;
    }

    if ((randomNumber) > 26){
        while (pile1 != NULL){
            pile3->next = pile1;
            pile3 = pile3->next;
            pile1 = pile1->next;
        }
        pile3->next = NULL;
        *lastCard = pile3;
    } else {
        while (pile2 != NULL) {
            pile3->next = pile2;
            pile3 = pile3->next;
            pile2 = pile2->next;
        }
        pile3->next = NULL;
        *lastCard = pile3;
    }

    currentCard = *firstCard;
    Card* prevCard = currentCard;
    currentCard = currentCard->next;
    while (currentCard != NULL){
        currentCard->previous = prevCard;
        currentCard = currentCard->next;
        prevCard = prevCard->next;
    }

    currentCard = *firstCard;

    printf("\n\n Doing what u think im doing");
    while (currentCard != NULL){
        printf("\n%c%c\n", currentCard->cardValue, currentCard->cardType);
        currentCard = currentCard->next;
    }
}

void shuffle(Card** firstCard, Card** lastCard){
    Card* pile1 = *firstCard;
    Card* pile2;
    Card* currentCard = pile1;
    int cardsInPile2 = 1; // first card gets used before the loop
    Card* prevCard;
    Card* temp; // Can be removed, but makes life easier
    // First card is a special case and would just complicate things in the loop
    pile2 = pile1;
    pile1 = pile1->next;
    pile2->next = NULL;
    pile2->previous = NULL;
    time_t currentTime = time(NULL);
    srand(currentTime);
    int randomNumber = rand() % cardsInPile2;
    //int randomNumber = 1;
    while (pile1 != NULL){
        // Randomizes where the next card should be put in the pile.
        cardsInPile2++;
        randomNumber = rand() % cardsInPile2;

        // 0 is taken as a special case to make things easier
        if (randomNumber == 0){
            prevCard = pile2->previous;
            currentCard = pile2;
        } else {
            // All other positions in pile2 is treated equally
            for (int i = 0; i < randomNumber; i++) {
                prevCard = pile2;
                currentCard = pile2->next;
            }
        }
        // Pointer stuff.
        // If currentCard is null, it must be the very last card in the deck
        if (currentCard == NULL){
            prevCard->next = pile1;
            pile1 = pile1->next;
            currentCard = prevCard->next;
            currentCard->previous = prevCard;
            currentCard->next = NULL;
            // If currecCard->previous is NULL, it must be the very first card in the deck
        } else if (currentCard->previous == NULL){
            currentCard->previous = pile1;
            pile1 = pile1->next;
            prevCard = currentCard->previous;
            prevCard->next = pile2;
            prevCard->previous = NULL;
            pile2 = prevCard;
            // If it is not the first and neither the last card, it must be a normal card in the deck sorrounded by other cards
        } else {
            prevCard->next = pile1;
            currentCard->previous = pile1;
            temp = pile1;
            pile1 = pile1->next;
            temp->next = currentCard;
            temp->previous = prevCard;

        }
        currentCard = pile2;
    }
    // Updates the pointers in main()
    *firstCard = pile2;
    while (pile2->next != NULL){
        pile2 = pile2->next;
    }
    *lastCard = pile2;
    printf("noise");


}


/**
 * This is a helper function.
 * The function places a card drawn from the deck into the board
 * ***** THIS FUNCTION CAN NOT AND SHOULD NOT BE USED TO MOVE CARDS WHEN PLAYING THE GAME!!!!*******
 * @param piledToAdd The pile which a card should be added to
 * @param tempCard current card from the old pile
 */
void placeCard(Card** newPile, Card** oldPile) {
    Card *cardToMove = *oldPile;
    Card *memoryToFree = *oldPile;


    // Remove the card from the old pile

    (*oldPile) = (*oldPile)->next;
    if (*oldPile != NULL){
        (*oldPile)->previous = NULL;
    }

    cardToMove->next = NULL;
    cardToMove->previous = NULL;

    // Place the card in the new pile
    if (*newPile == NULL){
        *newPile = cardToMove;
    } else {
        Card *temp = *newPile;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = cardToMove;
        cardToMove->previous = temp;
    }


// Old code - not tested
/*
    Card *newPile1 = *newPile;
    Card *newPile2;
    Card *oldPile1 = oldPile;
    Card *oldPile2;
        // No cards in pile
    if (*newPile == NULL){
        newPile1 = oldPile1; // useless
        oldPile1 = oldPile1->next;
        oldPile1->previous = NULL;
        newPile1->next = NULL;
        newPile1->previous = NULL;
        // First card in the pile
    } else if ((*newPile)->previous == NULL) {
        oldPile2 = oldPile1->next;
        newPile1->previous = oldPile1;
        newPile2 = newPile1;
        newPile1 = newPile1->previous;
        newPile1->previous = NULL;
        newPile1->next = newPile2;
        oldPile2-> previous = NULL;
    } else if ((*newPile)->next == NULL){
        oldPile2 = oldPile1->next;
        newPile1->next = oldPile1;
        newPile2 = newPile1->next;
        oldPile2->previous = NULL;
        newPile2->next = NULL;
        newPile2->previous = newPile1;
    } else {
        oldPile2 = oldPile1->next;
        newPile2 = newPile1->next;
        newPile1->next = oldPile1;

        oldPile1 = oldPile1->previous;
        oldPile1->next = oldPile2;
        oldPile2->previous = oldPile1;

        newPile1 = newPile1->next;
        newPile1->next = newPile2;
        newPile2->previous = newPile1;



    }
    */
}
//
// Created by emils on 29/04/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include "card.h"

bool checkCardValue(Card** fromPile, Card** toPile){
    printf("\nSo, SO SOSOOOO truev3\n");
    Card* firstCard = *fromPile;
    Card* secondCard = *toPile;
    if (firstCard->cardValue >= '1' && firstCard->cardValue <= '9') {
        if (secondCard->cardValue >= '1' && secondCard->cardValue <= '9') {
            printf("\nSo, SO SOSOOOO truev4\n");
            printf("\n%d\n", (char) (firstCard->cardValue + 1));
            printf("\n%c%c card values\n", firstCard->cardValue, secondCard->cardValue);
            if ((char) (firstCard->cardValue - 1) == secondCard->cardValue) {
                printf("\nSo, SO SOSOOOO truev6\n");
                return true;
            }
        }
    }

    printf("\nSo, SO SOSOOOO truev7\n");
    if (secondCard->cardValue == 'A' && firstCard->cardValue == '2' ||
            secondCard->cardValue == '9' && firstCard->cardValue == 'T' ||
            secondCard->cardValue == 'T' && firstCard->cardValue == 'J' ||
            secondCard->cardValue == 'J' && firstCard->cardValue == 'Q' ||
            secondCard->cardValue == 'Q' && firstCard->cardValue == 'K') {
        return true;
    }

    return false;

}


bool checkMoveC(Card **fromPile, Card **toPile) {



    if (*toPile == NULL){
        if ((*fromPile)->cardValue == 'K'){
            return true;
        }
        return false;
    }
    printf("\n%c%c <<", (*fromPile)->cardValue, (*fromPile)->cardType);
    printf("\n%c%c <<\n", (*toPile)->cardValue, (*toPile)->cardType);

    Card* firstCard = *fromPile;
    Card* secondCard = *toPile;

    printf("\nSo, SO SOSOOOO truev1\n");

    printf("\n\n%c%c\n", firstCard->cardValue, firstCard->cardType);
    printf("%c%c\n\n", secondCard->cardValue, secondCard->cardType);

    printf("\nSo, SO SOSOOOO truev2\n");




    if (firstCard->cardType == 'C' || firstCard->cardType == 'S') {
        if (secondCard->cardType == 'D' || secondCard->cardType == 'H' || secondCard == NULL) {
            //return true;
        }
    } else if (firstCard->cardType == 'D' || firstCard->cardType == 'H') {
        if (secondCard->cardType == 'C' || secondCard->cardType == 'S' || secondCard == NULL) {
            //return true;
        }
    } else {
        return false;
    }



    printf("\nSo, SO SOSOOOO truev3 \n");




    if (firstCard->cardValue >= '1' && firstCard->cardValue <= '9') {
        if (secondCard->cardValue >= '1' && secondCard->cardValue <= '9') {
            printf("\nSo, SO SOSOOOO truev4\n");
            printf("\n%d\n", (char) (firstCard->cardValue + 1));
            if ((char) (firstCard->cardValue + 1) == secondCard->cardValue) {
                printf("\nSo, SO SOSOOOO truev6\n");
                return true;
            }
        }
    }

    if (firstCard->cardValue == 'A' && secondCard->cardValue == '2' ||
            firstCard->cardValue == '9' && secondCard->cardValue == 'T' ||
            firstCard->cardValue == 'T' && secondCard->cardValue == 'J' ||
            firstCard->cardValue == 'J' && secondCard->cardValue == 'Q' ||
            firstCard->cardValue == 'Q' && secondCard->cardValue == 'K') {
        return true;
    }

    printf("\nillegalv3");



    return false;


}


bool checkMoveF(Card **fromPile, Card **toPile) {

    if (*toPile == NULL){
        if ((*fromPile)->cardValue == 'A'){
            return true;
        }
        return false;
    }

    Card* firstCard = *fromPile;
    Card* secondCard = *toPile;


    printf("\n\n%c%c\n", firstCard->cardValue, firstCard->cardType);
    printf("%c%c\n\n", secondCard->cardValue, secondCard->cardType);


    if (checkCardValue(&firstCard, &secondCard) == true && firstCard->cardType == secondCard->cardType){
        return true;
    }

    return false;

}



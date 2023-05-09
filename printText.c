//
// Created by emils on 28/04/2023.
//


#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "card.h"
// Just a simple print method. No fancy stuff except for some conversions to get propper card type visuals:
void showCards(Card* firstCard){
    // upper row
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    Card* currentCard = firstCard;

    int counter = 0;
    // Prints all da cards
    while (currentCard != NULL){
        if (counter%7 == 0){
            if (counter != 0){
                printf("\n");
            }

        }
        // Prints the value of the card. Cards get converted to another char value for visuals
        /*
         * ♣ (Club) - 0x05 (5 in decimal)
         * ♠ (Spade) - 0x06 (6 in decimal)
         * ♥ (Heart) - 0x03 (3 in decimal)
         * ♦ (Diamond) - 0x04 (4 in decimal)
         */
        if (currentCard->cardType == 'C'){
            printf("%c%c\t", currentCard->cardValue, (char) 5);
        } else if (currentCard->cardType == 'S'){
            printf("%c%c\t", currentCard->cardValue, (char) 6);
        } else if (currentCard->cardType == 'H'){
            printf("%c%c\t", currentCard->cardValue, (char) 3);
        } else if (currentCard->cardType == 'D'){
            printf("%c%c\t", currentCard->cardValue, (char) 4);
        }


        //printf("%c%c\t", currentCard->cardValue, currentCard->cardType);
        // At the end of the every 2. line F# is added
        if (counter == 6 ){
            printf("\t[]\tF1");
        } else if (counter == 20){
            printf("\t[]\tF2");
        } else if (counter == 34){
            printf("\t[]\tF3");
        } else if (counter == 48){
            printf("\t[]\tF4");
        }
        // Next card and increases counter
        currentCard = currentCard->next;
        counter++;
    }
}

/*
 * Prints the current board. Not much to be explained, just a bunch of if statements printing stuff.
 */
void printCurrentBoard(Card* c1, Card* c2, Card* c3, Card* c4, Card* c5, Card* c6, Card* c7, Card* f1, Card* f2, Card* f3, Card* f4, char* userInput, char* message){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    int lineCounter = 0;


    // Prints the value of the card. Cards get converted to another char value for visuals
    /*
     * ♣ (Club) - 0x05 (5 in decimal)
     * ♠ (Spade) - 0x06 (6 in decimal)
     * ♥ (Heart) - 0x03 (3 in decimal)
     * ♦ (Diamond) - 0x04 (4 in decimal)
     */

    while (c1 != NULL || c2 != NULL || c3 != NULL || c4 != NULL || c5 != NULL || c6 != NULL || c7 != NULL){
        if (c1 != NULL){
            if (c1->flipped == true){
                printf("[]\t");
            } else {
                //printf("%c%c\t", c1->cardValue, c1->cardType == 'C' ? (char) 5 : c1->cardType == 'S' ? (char) 6 : c1->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\t", c1->cardValue, c1->cardType);
            }
            c1 = c1->next;
        } else {
            printf("\t");
        }
        if (c2 != NULL){
            if (c2->flipped == true){
                printf("[]\t");
            } else {
                //printf("%c%c\t", c2->cardValue, c2->cardType == 'C' ? (char) 5 : c2->cardType == 'S' ? (char) 6 : c2->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\t", c2->cardValue, c2->cardType);
            }
            c2 = c2->next;
        }else {
            printf("\t");
        }
        if (c3 != NULL){
            if (c3->flipped == true){
                printf("[]\t");
            } else {
                printf("%c%c\t", c3->cardValue, c3->cardType);
                //printf("%c%c\t", c3->cardValue, c3->cardType == 'C' ? (char) 5 : c3->cardType == 'S' ? (char) 6 : c3->cardType == 'H' ? (char) 3 : (char) 4);
            }
            c3 = c3->next;
        }else {
            printf("\t");
        }
        if (c4 != NULL){
            if (c4->flipped == true){
                printf("[]\t");
            } else {
                //printf("%c%c\t", c4->cardValue, c4->cardType == 'C' ? (char) 5 : c4->cardType == 'S' ? (char) 6 : c4->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\t", c4->cardValue, c4->cardType);
            }
            c4 = c4->next;
        }else {
            printf("\t");
        }
        if (c5 != NULL){
            if (c5->flipped == true){
                printf("[]\t");
            } else {
                //printf("%c%c\t", c5->cardValue, c5->cardType == 'C' ? (char) 5 : c5->cardType == 'S' ? (char) 6 : c5->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\t", c5->cardValue, c5->cardType);
            }
            c5 = c5->next;
        }else {
            printf("\t");
        }
        if (c6 != NULL){
            if (c6->flipped == true){
                printf("[]\t");
            } else {
                //printf("%c%c\t", c6->cardValue, c6->cardType == 'C' ? (char) 5 : c6->cardType == 'S' ? (char) 6 : c6->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\t", c6->cardValue, c6->cardType);
            }
            c6 = c6->next;
        }else {
            printf("\t");
        }
        if (c7 != NULL){
            if (c7->flipped == true){
                printf("[]\t");
            } else {
                //printf("%c%c\t", c7->cardValue, c7->cardType == 'C' ? (char) 5 : c7->cardType == 'S' ? (char) 6 : c7->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\t", c7->cardValue, c7->cardType);
            }
            c7 = c7->next;
        }else {
            printf("\t");
        }

        if (lineCounter == 0){
            if (f1 == NULL){
                printf("[]\tF1");
            } else {
                while (f1->next != NULL){
                    f1 = f1->next;
                }
                //printf("%c%c\t", f1->cardValue, f1->cardType == 'C' ? (char) 5 : f1->cardType == 'S' ? (char) 6 : f1->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\tF1", f1->cardValue, f1->cardType);
            }
        } else if (lineCounter == 2){
            if(f2 == NULL){
                printf("[]\tF2");
            } else {
                while (f2->next != NULL){
                    f2 = f2->next;
                }
                //printf("%c%c\t", f2->cardValue, f2->cardType == 'C' ? (char) 5 : f2->cardType == 'S' ? (char) 6 : f2->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\tF2", f2->cardValue, f2->cardType);
            }
        } else if (lineCounter == 4){
            if (f3 == NULL){
                printf("[]\tF3");
            } else {
                while (f3->next != NULL){
                    f3 = f3->next;
                }
                //printf("%c%c\t", f3->cardValue, f3->cardType == 'C' ? (char) 5 : f3->cardType == 'S' ? (char) 6 : f3->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\tF3", f3->cardValue, f3->cardType);
            }
        } else if (lineCounter == 6){
            if (f4 == NULL){
                printf("[]\tF4");
            } else {
                while (f4->next != NULL){
                    f4 = f4->next;
                }
                //printf("%c%c\t", f4->cardValue, f4->cardType == 'C' ? (char) 5 : f4->cardType == 'S' ? (char) 6 : f4->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\tF4", f4->cardValue, f4->cardType);
            }


        }

        //printf("\n%d\n", lineCounter);
        printf("\n");
        lineCounter += 1;
    }

    //printf("\nDone with counting lines at %d :\n", lineCounter);



    if (lineCounter == 0) {
        while (f1->next != NULL){
            f1 = f1->next;
        }

        printf("\t\t\t\t\t\t\t%c%c\tF1\n", f1->cardValue, f1->cardType);
        printf("\n");
        printf("\t\t\t\t\t\t\t%c%c\tF2\n", f2->cardValue, f2->cardType);
        printf("\n");
        printf("\t\t\t\t\t\t\t%c%c\tF3\n", f3->cardValue, f3->cardType);
        printf("\n");
        printf("\t\t\t\t\t\t\t%c%c\tF4\n", f4->cardValue, f4->cardType);
    }

    else if (lineCounter <= 2){
        while (f2->next != NULL){
            f2 = f2->next;
        }
        while (f3->next != NULL){
            f3 = f3->next;
        }
        while (f4->next != NULL){
            f4 = f4->next;
        }
        if (lineCounter == 1){
            printf("\n");
        }
        printf("\t\t\t\t\t\t\t%c%c\tF2\n", f2->cardValue, f2->cardType);
        printf("\n");
        printf("\t\t\t\t\t\t\t%c%c\tF3\n", f3->cardValue, f3->cardType);
        printf("\n");
        printf("\t\t\t\t\t\t\t%c%c\tF4\n", f4->cardValue, f4->cardType);
    } else if (lineCounter <= 4){
        if (lineCounter == 3){
            printf("\n");
        }
        while (f3->next != NULL){
            f3 = f3->next;
        }
        while (f4->next != NULL){
            f4 = f4->next;
        }
        printf("\t\t\t\t\t\t\t%c%c\tF3\n", f3->cardValue, f3->cardType);
        printf("\n");
        printf("\t\t\t\t\t\t\t%c%c\tF4\n", f4->cardValue, f4->cardType);
    } else if (lineCounter <= 6){

        if (lineCounter == 5){
            printf("\n");
        }
        while (f4->next != NULL){
            f4 = f4->next;
        }
        printf("\t\t\t\t\t\t\t%c%c\tF4\n", f4->cardValue, f4->cardType);
    }

    //Prints the userinput
    printf("%s", "Last command: ");
    int i = 0;
    while(true){
        printf("%c",userInput[i]);
        i = i + 1;
        if(userInput[i] == '\0'){
            break;
        }
    }
    printf("%c",'\n');

    printf("Status message: %s\n", message);
    printf("Input: ");
}


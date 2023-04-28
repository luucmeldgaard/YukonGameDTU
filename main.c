#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

// Creates 52 nodes in a double linked list containing the values given in the assignment if no file is given...
// Was created to avoid writing 52 cards by hand... 10/10 time sink!
// Double pointer as we want to change the content outside the function
void createDeck(Card** firstCard, Card** lastCard){
    // Will create a deck with 52 cards, startng
    for (int i = 1; i <= 4; i++){
        for(int j = 1; j <= 13; j++){
            // *** The following is just an explanation for allocating memory ***
            /* *card represents the memory location we want to allocate
             * (Card*) is a type cast. This will convert the pointer from 'void*' to 'Card*'
             * malloc() allocates a specified amount of bytes.
             * In our case the amount of bytes we wish to reserve is equal to or a little more than the struct Card()
             * An estimate of the actual size of Card would be 6 bytes on a 32 bit system and 10 bytes on a 64 bit system.
             * The two chars each takes up one byte. The pointers size depends on the system. Addresses for 32 bit is 4 bytes and 64 bit is 8 bytes.
             * Card might be expanded to a double linked list at which point its size increase to 10 or 16 bytes.
             */
            Card* newCard = (Card*)malloc(sizeof(Card));
            newCard->flipped = false; // Might be bad
            // Assign the type, C/D/H/S
            if (i == 1){
                newCard->cardType = (char) (67);
            } else if (i == 2){
                newCard->cardType = (char) (68);
            } else if (i == 3){
                newCard->cardType = (char) (72);
            } else if (i == 4){
                newCard->cardType = (char) (83);
            }
            // Assigns the value from ACE to K
            if (j == 1){
                newCard -> cardValue = 'A';
            } else if(j < 10){
                // Converts ASCII int value to char
                newCard -> cardValue = (char) (j + 48);
            } else if(j == 10){
                newCard -> cardValue = 'T';
            }else if(j == 11){
                newCard -> cardValue = 'J';
            } else if(j == 12){
                newCard -> cardValue = 'Q';
            } else if(j == 13){
                newCard -> cardValue = 'K';
            }
            // Saves the pointer to the previous card
            newCard->previous = *lastCard;
            // As this is now the last card in the deck, the next card is NULL
            newCard->next = NULL;
            // The first card of an empty deck is always NULL.
            if (*firstCard == NULL){
                // sets the pointer of the first card to point at the new card
                *firstCard = newCard;
            }
                // If not the first entry in the deck
            else {
                // Links the new node to the end of the list by modifying the previous cards next pointer to the current card
                (*lastCard)->next = newCard;
            }
            // Updates the lastCard pointer to the card which has been added last
            *lastCard = newCard;
        }
    }
}
/*
 * controlDeck is used to test if a given card is valid, and if it is a duplicate, and if the list is too short
 * A known validated deck is used to test if an unknown deck is also correct.
 * If the unkown deck contains all the values of a validated deck, it must be correct.
 * The validated deck is searched for a given card of the unknown deck. If the card matches a card in the validated deck, the card will be removed from the validated deck to prevent doubles
 * If the card does not match a value in the validated deck, it must be an invalid value
 */
bool controlDeck(Card** firstCardTemp, Card** lastCardTemp, Card* currentCardTemp, const char *temp){
    // Loop going transversing the validated deck
    while (currentCardTemp != NULL){
        // Checks if the card is in the validated deck. Temp contains the values of a card from the unknown deck whilst currentCardTemp contains the current value of a card from the validated deck.
        if (temp[0] == currentCardTemp->cardValue && temp[1] == currentCardTemp->cardType){
            // If only one card is left in the deck, both the previous and next pointer must be NULL, and we will just free up the last memory
            if (currentCardTemp->previous == NULL && currentCardTemp->next == NULL){
                free(currentCardTemp);
                return true;
            }
                // If the card is the first card in the validated deck ("AC" by default), the firstCard pointer must move to the 2. node ("2C" by default)
            else if (currentCardTemp->previous == NULL){
                // Move the pointer pointing to the start of the validated deck from first card to second card
                // (*firstCardTemp) dereferences the pointer such the content in the address can be accessed
                *firstCardTemp = (*firstCardTemp)->next;
                // Sets the previous pointer of the second card to be null
                (*firstCardTemp)->previous = NULL;
                // Frees the allocated memory from the unlinked card
                free(currentCardTemp);
                return true;
            }
                // If the card is the last card, the second last card must become the last card.
                // Exactly same method as previous else-if statement just reversed.
            else if (currentCardTemp->next == NULL){
                *lastCardTemp = (*lastCardTemp)->previous;
                (*lastCardTemp)->next = NULL;
                free(currentCardTemp);
                return true;
            }
                // If it is not the first card, last card or only card in the validated deck, the pointers in the surrounding cards is moved such they are now linked, and the current card gets deleted.
            else {
                (currentCardTemp->next)->previous = currentCardTemp->previous;
                (currentCardTemp->previous)->next = currentCardTemp->next;
                free(currentCardTemp);
                return true;
            }
        }
        // Goes to the next card in the validated deck if no match is found
        currentCardTemp = currentCardTemp->next;
    }return false;

}

void removeDeck(Card** firstCard){
    Card *temp = *firstCard;
    Card* temp2 = *firstCard;
    while (temp != NULL){
        temp = (*firstCard)->next;
        free(*firstCard);
        printf("im also doing this");
        (*firstCard) = temp;
    }
}

/*
 * loadDeck is used to load a deck from a txt file. Uses ControlDeck to validate the loaded deck.
 */
char *loadDeck(Card** firstCard, Card** lastCard, const char *fileName, char *textbuf){
    printf("%c", (*firstCard)->cardType);
    // Checks if input is empty
    if (fileName == NULL || strcmp(fileName, "") == 0 || strcmp(fileName, "\0") == 0){
        // Clears previous deck if exists
        if ((*firstCard) != NULL){
            removeDeck(firstCard);
        }
        createDeck(firstCard, lastCard);
        return "OK, deck created";
    }
    // Opens a file if a filename is given
    FILE* file = fopen(fileName, "r");
    if (file == NULL){
        return "Invalid file path";
    }
    // Clears the previous deck if one exists
    if ((*firstCard) != NULL){
        printf("im running");
        removeDeck(firstCard);
    }

    printf("File not NULL");
    // Creates a linked list containing all 52 cards. Is used to check against the imported card deck.
    Card* firstCardTemp = NULL;
    Card* lastCardTemp = NULL;
    createDeck(&firstCardTemp, &lastCardTemp);
    // Temp is created for fgets. Contains details of one card.
    // Should be made into a while statement..... lazy.
    char temp[4];
    for (int i = 1; i <= 52; i++){

        printf("\n\ncrashing\n\n");
        // fgets reads a line from a txt file and saves it in temp. The int defines the max-count of chars on a line. Is set to 4 as it also includes \n
        fgets(temp, 4, file);
        // Resets the currentCardTemp to start at the fron every loop
        Card* currentCardTemp = firstCardTemp;

        // Tests if a given card is valid. Also checks for doubles and if the txt file contains less than 52 cards
        // if the txt file contains more than 52 cards, no error will be given if the first 52 data entries is legit
        if (controlDeck(&firstCardTemp, &lastCardTemp, currentCardTemp, temp) == false){
            //snprintf is used to append the line of error to the string.
            // textbuf is saved in main to eliminate memory issues
            snprintf(textbuf, 100, "Error at line: %d", i);
            return textbuf;
        }

        Card* newCard = (Card*)malloc(sizeof(Card));
        newCard->flipped = false; // Might be bad
        // Stores the loaded data in a newly created Card;
        newCard->cardValue = temp[0];
        newCard->cardType = temp[1];
        // Saves the pointer to the previous card
        newCard->previous = *lastCard;
        // As this is now the last card in the deck, the next card is NULL
        newCard->next = NULL;
        // The first card of an empty deck is always NULL.
        if (*firstCard == NULL){
            // sets the pointer of the first card to point at the new card
            *firstCard = newCard;
        }
            // If not the first entry in the deck
        else {
            // Links the new node to the end of the list by modifying the previous cards next pointer to the current card
            (*lastCard)->next = newCard;
        }
        // Updates the lastCard pointer to the card which has been added last
        *lastCard = newCard;
    }

    fclose(file);
    return "OK, file loaded";
}

// Reads the current deck and saves it
// As we only want to read the content from the linked list we point to the content of Card
// savedDeck returns messages to make it easier to incoporate in a gui...
char *saveDeck(Card* firstCard, const char *savedDeckName){
    // If the users has not given an input default name cards.txt will be given in accordance with the specification
    if (savedDeckName == NULL || strcmp(savedDeckName, "") == 0){
        savedDeckName = "cards.txt";
    }
    // Creates a new file with the given filename. "w" indicate the file will be created if none exists. If file with same name exists, it will be formatted.
    FILE* file = fopen(savedDeckName, "w");
    // If file could not be created, print an error message
    if (file == NULL) {
        // 48 chars used
        return "Error: Unable to create the file. check filepath";
    }
    // temporary pointer currentCard made to not traverse the actual deck
    Card* currentCard = firstCard;
    // If the current card is null, the linked list must be at the very end
    while (currentCard != NULL){



        // Prints the card values to the file
        fprintf(file, "%c%c\n", currentCard->cardValue, currentCard->cardType);
        // sets current card to the next card
        currentCard = currentCard->next;
    }
    // Closes the file
    fclose(file);
    return "Success! File saved.";
}
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
    printf("\nMessage:\nInput:");
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

/*
 * Prints the current board. Not much to be explained, just a bunch of if statements printing stuff.
 */
void printCurrentBoard(Card* c1, Card* c2, Card* c3, Card* c4, Card* c5, Card* c6, Card* c7, Card* f1, Card* f2, Card* f3, Card* f4, char* message){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
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
                //printf("%c%c\t", f1->cardValue, f1->cardType == 'C' ? (char) 5 : f1->cardType == 'S' ? (char) 6 : f1->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\tF1", f1->cardValue, f1->cardType);
            }
        } else if (lineCounter == 2){
            if(f2 == NULL){
                printf("[]\tF2");
            } else {
                //printf("%c%c\t", f2->cardValue, f2->cardType == 'C' ? (char) 5 : f2->cardType == 'S' ? (char) 6 : f2->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\tF2", f2->cardValue, f2->cardType);
            }
        } else if (lineCounter == 4){
            if (f3 == NULL){
                printf("[]\tF3");
            } else {
                //printf("%c%c\t", f3->cardValue, f3->cardType == 'C' ? (char) 5 : f3->cardType == 'S' ? (char) 6 : f3->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\tF3", f3->cardValue, f3->cardType);
            }
        } else if (lineCounter == 6){
            if (f4 == NULL){
                printf("[]\tF4");
            } else {
                //printf("%c%c\t", f4->cardValue, f4->cardType == 'C' ? (char) 5 : f4->cardType == 'S' ? (char) 6 : f4->cardType == 'H' ? (char) 3 : (char) 4);
                printf("%c%c\tF4", f4->cardValue, f4->cardType);
            }


        }

        printf("\n");
        lineCounter += 1;
    }
    if (lineCounter < 2){
        if (lineCounter == 1){
            printf("\n");
        }
        printf("\t\t\t\t\t\t\tF2\n");
        printf("\t\t\t\t\t\t\tF3\n");
        printf("\t\t\t\t\t\t\tF4\n");
    } else if (lineCounter < 4){
        if (lineCounter == 2){
            printf("\n");
        }
        printf("\t\t\t\t\t\t\tF3\n");
        printf("\t\t\t\t\t\t\tF4\n");
    } else if (lineCounter < 6){
        if (lineCounter == 4){
            printf("\n");
        }
        printf("\t\t\t\t\t\t\tF4\n");
    }

    printf("\n");
    printf("Status message: %s\n", message);
    printf("Input: ");
}


/**
 * Function for playing the game. This function tak
 * @param firstCard
 * @param lastCard
 */
void play(Card** firstCard, Card** lastCard, Card** c1, Card** c2, Card** c3, Card** c4, Card** c5, Card** c6, Card** c7){


    printf("%c%c\n", (*firstCard)->cardValue, (*firstCard)->cardType);

    int cardsPlaced[] = {0,0,0,0,0,0,0};

    //createPlayGame(c1, c2, c3, c4, c5, c6, c7, firstCard);



    while (*firstCard != NULL) {

        if (cardsPlaced[0] == 0) {
            placeCard(c1, firstCard);
            cardsPlaced[0] += 1;
            printf("c1 placed\n");
        }
        if (cardsPlaced[1] < 6) {
            if (cardsPlaced[1] == 0){
                (*firstCard)->flipped = true;
            }
            placeCard(c2, firstCard);
            cardsPlaced[1] += 1;
            printf("c2 placed\n");
        }
        if (cardsPlaced[2] < 7) {
            if (cardsPlaced[2] < 2) {
                (*firstCard)->flipped = true;
            }
            placeCard(c3, firstCard);
            cardsPlaced[2] += 1;
        }
        if (cardsPlaced[3] < 8) {
            if (cardsPlaced[3] < 3){
                (*firstCard)->flipped = true;
            }
            placeCard(c4, firstCard);
            cardsPlaced[3] += 1;
        }
        if (cardsPlaced[4] < 9) {
            if ((*firstCard) == NULL){ return;}
            if (cardsPlaced[4] < 4){
                (*firstCard)->flipped = true;
            }
            placeCard(c5, firstCard);
            cardsPlaced[4] += 1;
        }
        if (cardsPlaced[5] < 10) {
            if (cardsPlaced[5] < 5){
                (*firstCard)->flipped = true;
            }
            placeCard(c6, firstCard);
            cardsPlaced[5] += 1;
        }
        if (cardsPlaced[6] < 11) {
            if (cardsPlaced[6] < 6){
                (*firstCard)->flipped = true;
            }
            placeCard(c7, firstCard);
            cardsPlaced[6] += 1;
        }
    }
}


bool checkLegalMove(Card** fromPile, Card** toPile, int from) {

    Card* firstCard = fromPile[0];
    Card* secondCard = toPile[0];


    printf("\n\n%c%c\n", firstCard->cardValue, firstCard->cardType);
    printf("%c%c\n\n", secondCard->cardValue, secondCard->cardType);

    if (firstCard->cardType == 'C' || firstCard->cardType == 'S') {
        if (secondCard->cardType == 'D' || secondCard->cardType == 'H' || secondCard == NULL) {
            return true;
        }
        return false;
    }

    if (firstCard->cardType == 'D' || firstCard->cardType == 'H') {
        if (secondCard->cardType == 'C' || secondCard->cardType == 'S' || secondCard == NULL) {
            return true;
        }
        return false;
    }
}

bool checkLegalMove2(Card** fromPile, Card** toPile, int from){

    if ((*toPile) == NULL){
        return true;
    }

    Card* firstCard = fromPile[0];
    Card* secondCard = toPile[0];


    printf("\n\n%c%c\n", firstCard->cardValue, firstCard->cardType);
    printf("%c%c\n\n", secondCard->cardValue, secondCard->cardType);

    if (firstCard->cardType == secondCard->cardType) {
        return true;
    }

    return false;

}


// Assignment

bool moveCards(Card** fromPile, Card** toPile, int from, bool endPile){
    printf("%d", from);
    Card* temp = *fromPile;
    Card* temp2 = *toPile;
    printf("\n\n%c%c <<<\n\n", temp->cardValue, temp->cardType);
    printf("Crash1");
    while ((*fromPile)->next != NULL) {
        printf("Crash1.1");
        (*fromPile) = (*fromPile)->next;
    }
    printf("mamma im doing good\n");
    for (int i = 0; i < from; i ++) {
        printf("Crash1.2");
        (*fromPile) = (*fromPile)->previous;
    }
    printf("mamma im doing goodv2\n");
    if ((*toPile) != NULL) {
        while ((*toPile)->next != NULL) {
            printf("Crash1.3");
            (*toPile) = (*toPile)->next;
        }
    }


    printf("mamma im doing goodv3\n");


    if (*fromPile == NULL){
        printf("mamma im doing goodv3.5\n");
        *fromPile = temp;
        *toPile = temp2;
        printf("CRASHAND DIE");
        return false;
    }

    printf("mamma im doing goodv4\n");

    if ((*fromPile)->flipped == true){
        *fromPile = temp;
        *toPile = temp2;
        return false;
    }

    printf("mamma im doing goodv5\n");
    if ((*toPile) == NULL){

        if ((*fromPile)->previous ==NULL){

        }

        if (checkLegalMove2(fromPile, toPile, from) == true){
            printf("mamma im doing goodv6\n");
            *toPile = *fromPile;
            (*fromPile) = (*fromPile)->previous;
            (*fromPile)->next = NULL;
            printf("mamma im doing goodv7\n");
            (*toPile)->next = NULL;
            (*toPile)->previous = NULL;
            printf("mamma im doing goodv8\n");
            printf("all done");
            return true;
        }
    }


    if (!endPile) {
        if (!checkLegalMove(fromPile, toPile, from)) {
            printf("\nIllegal move!\n");
            *fromPile = temp;
            *toPile = temp2;
            return false;
        }
    } else{
        if (!checkLegalMove2(fromPile, toPile, from)) {
            printf("\nIllegal move!\n");
            *fromPile = temp;
            *toPile = temp2;
            return false;
        }
    }


    Card* oldPile = *fromPile;
    Card* newPile = *toPile;

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



    *fromPile = temp;
    *toPile = temp2;

    return true;
}

void checkForValidInputMove(char* usrInput){

}

void playGame(Card** c1, Card** c2, Card** c3, Card** c4, Card** c5, Card** c6, Card** c7, Card** f1, Card** f2, Card** f3, Card** f4){
    printCurrentBoard(*c1, *c2, *c3, *c4, *c5, *c6, *c7, NULL, NULL, NULL, NULL, "Welcome!");
    char usrInput[256];
    bool moveByColumn;
    Card **chosenDeck1;
    Card **chosenDeck2;
    char messages[256];
    while (true) {
        while (true) {

            fflush(stdin); // Clears input buffer
            memset(usrInput, '\0', 256); // Clears the input array
            scanf("%s", &usrInput[0]);

            if (usrInput[0] == 'Q'){
                return;
            }

            if (usrInput[2] == ':' && usrInput[5] == '-' && usrInput[6] == '>') {
                printf("\nAt first line\n");
                if (!(usrInput[0] == 'C' || usrInput[0] == 'F')) {
                    printf("no good input1: %c", usrInput[0]);
                    memset(usrInput, '\0', 256); // Resets the array

                } else if (!(usrInput[1] >= '1' && usrInput[1] <= '7')) {
                    printf("no good input2: ");
                    memset(usrInput, '\0', 256);

                } else if (!(usrInput[3] >= '1' && usrInput[3] <= '9') || usrInput[3] == 'A' || usrInput[3] == 'J' ||
                           usrInput[3] == 'Q' || usrInput[3] == 'K') {
                    printf("no good input3: ");
                    memset(usrInput, '\0', 256);

                } else if (!(usrInput[4] == 'C' || usrInput[4] == 'S' || usrInput[4] == 'H' || usrInput[4] == 'D')){
                    printf("no good input4: ");
                    memset(usrInput, '\0', 256);
                } else if (!(usrInput[0] == 'C' || usrInput[0] == 'F')){
                    printf("no good input5: ");
                    memset(usrInput, '\0', 256);
                } else if(!(usrInput[1] >= '1' && usrInput[1] <= '7')){
                    printf("no good input6: ");
                    memset(usrInput, '\0', 256);
                }
                else {
                    printf("BREAK1");
                    moveByColumn = false;
                    break;
                }
            }
            else if (usrInput[2] == '-' && usrInput[3] == '>'){
                printf("\nAt second line\n");
                if (!(usrInput[0] == 'C' || usrInput[0] == 'F')) {
                    printf("no good input7: %c", usrInput[0]);
                    memset(usrInput, '\0', 256); // Resets the array

                } else if (!(usrInput[1] >= '1' && usrInput[1] <= '7')) {
                    printf("no good input8: ");
                    memset(usrInput, '\0', 256);

                } else if (!(usrInput[4] == 'C' || usrInput[4] == 'F')){
                    printf("no good input9: ");
                    memset(usrInput, '\0', 256);
                } else if(!(usrInput[5] >= '1' && usrInput[5] <= '7')){
                    printf("no good input10: ");
                    memset(usrInput, '\0', 256);
                }
                else {
                    moveByColumn = true;
                    printf("BREAK2");
                    break;
                }
            }
        }

        //////// Start of checks for mving columns aka moveByColumn == true /////////////
        if (moveByColumn == true) {
            if (usrInput[0] == 'C') {
                if (usrInput[1] == '1') {
                    chosenDeck1 = c1;
                } else if (usrInput[1] == '2') {
                    chosenDeck1 = c2;
                } else if (usrInput[1] == '3') {
                    chosenDeck1 = c3;
                } else if (usrInput[1] == '4') {
                    chosenDeck1 = c4;
                } else if (usrInput[1] == '5') {
                    chosenDeck1 = c5;
                } else if (usrInput[1] == '6') {
                    chosenDeck1 = c6;
                } else if (usrInput[1] == '7') {
                    chosenDeck1 = c7;
                }
            }

            if (usrInput[0] == 'C') {
                if (usrInput[8] == '1') {
                    chosenDeck2 = c1;
                } else if (usrInput[5] == '1') {
                    chosenDeck2 = c1;
                } else if (usrInput[5] == '2') {
                    chosenDeck2 = c2;
                } else if (usrInput[5] == '3') {
                    chosenDeck2 = c3;
                } else if (usrInput[5] == '4') {
                    chosenDeck2 = c4;
                } else if (usrInput[5] == '5') {
                    chosenDeck2 = c5;
                } else if (usrInput[5] == '6') {
                    chosenDeck2 = c6;
                } else if (usrInput[5] == '7') {
                    chosenDeck2 = c7;
                }
            }

            if (usrInput[0] == 'F') {
                if (usrInput[1] == '1') {
                    chosenDeck2 = f1;
                } else if (usrInput[1] == '2') {
                    chosenDeck2 = f2;
                } else if (usrInput[1] == '3') {
                    chosenDeck2 = f3;
                } else if (usrInput[1] == '4') {
                    chosenDeck2 = f4;
                }
            }

            if (usrInput[4] == 'F') {
                if (usrInput[5] == '1') {
                    chosenDeck2 = f1;
                } else if (usrInput[5] == '2') {
                    chosenDeck2 = f2;
                } else if (usrInput[5] == '3') {
                    chosenDeck2 = f3;
                } else if (usrInput[5] == '4') {
                    chosenDeck2 = f4;
                }
            }
            moveCards(chosenDeck1, chosenDeck2, 0, false);
        }
            //////// End of checks for moving columns /////////////

            //////// Start of checks for moving card at x row ////////
        else {
            if (usrInput[0] == 'C') {
                if (usrInput[1] == '1') {
                    chosenDeck1 = c1;
                } else if (usrInput[1] == '2') {
                    chosenDeck1 = c2;
                } else if (usrInput[1] == '3') {
                    chosenDeck1 = c3;
                } else if (usrInput[1] == '4') {
                    chosenDeck1 = c4;
                } else if (usrInput[1] == '5') {
                    chosenDeck1 = c5;
                } else if (usrInput[1] == '6') {
                    chosenDeck1 = c6;
                } else if (usrInput[1] == '7') {
                    chosenDeck1 = c7;
                }
            }

            if (usrInput[7] == 'C') {
                if (usrInput[8] == '1') {
                    chosenDeck2 = c1;
                } else if (usrInput[8] == '2') {
                    chosenDeck2 = c2;
                } else if (usrInput[8] == '3') {
                    chosenDeck2 = c3;
                } else if (usrInput[8] == '4') {
                    chosenDeck2 = c4;
                } else if (usrInput[8] == '5') {
                    chosenDeck2 = c5;
                } else if (usrInput[8] == '6') {
                    chosenDeck2 = c6;
                } else if (usrInput[8] == '7') {
                    chosenDeck2 = c7;
                }
            }

            if (usrInput[0] == 'F') {
                if (usrInput[1] == '1') {
                    chosenDeck2 = f1;
                } else if (usrInput[1] == '2') {
                    chosenDeck2 = f2;
                } else if (usrInput[1] == '3') {
                    chosenDeck2 = f3;
                } else if (usrInput[1] == '4') {
                    chosenDeck2 = f4;
                }
            }

            if (usrInput[7] == 'F') {
                if (usrInput[8] == '1') {
                    chosenDeck2 = f1;
                } else if (usrInput[8] == '2') {
                    chosenDeck2 = f2;
                } else if (usrInput[8] == '3') {
                    chosenDeck2 = f3;
                } else if (usrInput[8] == '4') {
                    chosenDeck2 = f4;
                }
            }

            Card* temp = *chosenDeck1;
            int height = 0;
            bool cardInColumn = false;
            while (*chosenDeck1 != NULL){

                if ((*chosenDeck1)->cardValue == usrInput[3] && (*chosenDeck1)->cardType == usrInput[4]){
                    strcpy(messages, "Movement succesful!");
                    *chosenDeck1 = temp;
                    cardInColumn = true;
                    if(moveCards(chosenDeck1, chosenDeck2, height, false) == true) {
                        break;
                    } else {
                        strcpy(messages, "No cards in pile or invalid move");
                    }
                }
                (*chosenDeck1) = (*chosenDeck1)->next;
                if (*chosenDeck1 == NULL){
                    strcpy(messages, "Card does not exists");
                    printf("Card does not exists ");
                }
                height++;
            }
        }

        printf("\n\n%c%c\n\n", (*chosenDeck1)->cardValue, (*chosenDeck2)->cardValue);
        printCurrentBoard(*c1, *c2, *c3, *c4, *c5, *c6, *c7, NULL, NULL, NULL, NULL, messages);



        memset(usrInput, '\0', 256); // Resets the array
        printf("Input is great§!");
    }

}


void startMenu(Card** firstCard, Card** lastCard, char* textBuf){
    // The card is split into 7 columns
    Card* c1 = NULL; Card* c2 = NULL; Card* c3 = NULL; Card* c4 = NULL; Card* c5 = NULL; Card* c6 = NULL; Card* c7 = NULL;
    // 4 additional lists is made for finished cards
    Card* f1 = NULL; Card* f2 = NULL; Card* f3 = NULL; Card* f4 = NULL;
    ///// Program breaks if more than 128 chars is inputted. It will override memory.
    char input[128]; //Allocates the space fo the string
    char filename[128];
    char usrInput;
    char saveChar;

    while (true){
        int i = 0;
        printf("What would you like to do? \nLD <filename> \nSW \nSI<split> \nSR \nSD <filepath> \nP \nQQ (quit)\n");
        // --- Can break the
        scanf("%s", &input[0]); // Scanf leaves behind a newline in the buffer, as it stops reading when it reaches a new line
        // handles Load
        if ((strcmp(input, "LD")) == 0) {
            printf("Input file path (leave empty if you want to start a new game): ");
            getchar(); // Consume the new line character left in the buffer by scanf
            usrInput = ' '; // Initialize usrInput to a non-newline char
            while (usrInput != '\n' && i < sizeof(filename) - 1) {
                usrInput = (char)getchar();
                filename[i++] = usrInput;

            }
            printf("\n");

            if (i > 0 && filename[i - 1] == '\n') {
                filename[i - 1] = '\0'; // Remove newline character from the filename
            } else {
                filename[i] = '\0';
            }
            printf("\n");
            printf("%s", filename);
            printf("%s", loadDeck(firstCard, lastCard, filename, textBuf));

            printf("\n");

        }
            // show cards
        else if ((strcmp(input,"SW")) == 0){ //strcmp returns 0 if theyre the same.
            showCards(*firstCard);
        }
            // splitshuffle
        else if ((strcmp(input,"SI")) == 0){ //strcmp returns 0 if theyre the same.
            printf("Please enter a number between 0 and 52. Leave empty or enter any letter to pick a random number: ");
            signed int chosenCard = 0;

            while (true) {
                scanf("%3d", &chosenCard);
                getchar();
                if (chosenCard >= 0 && chosenCard <= 52){
                    break;
                } else {
                    printf("Failure, please only numbers between 0 and 52: ");
                    continue;
                }
            }

            printf("%d", chosenCard);

            printf("Do i do this?");

            splitShuffle(firstCard, lastCard, chosenCard);
            printf("s");
        }
            // Shuffle
        else if ((strcmp(input,"SR")) == 0){ //strcmp returns 0 if theyre the same.
            shuffle(firstCard,lastCard); //Should work..?
        }
            // Save current deck
        else if ((strcmp(input,"SD")) == 0){ //strcmp returns 0 if theyre the same.
            printf("Input desired file name: ");
            char saveFileName[128];
            getchar();
            while ((saveChar =(char) getchar()) != '\n' && i < sizeof(saveFileName) - 1){
                saveFileName[i++] = saveChar;
                printf("%usrInput", saveChar);
            }
            saveDeck(*firstCard,saveFileName); //Tjek lige om det der pointer noget fungerer
        }
            // "Play" - starts the game
        else if ((strcmp(input,"P")) == 0){ //strcmp returns 0 if theyre the same.
            play(firstCard, lastCard, &c1, &c2, &c3, &c4, &c5, &c6, &c7);
            playGame(&c1, &c2, &c3, &c4, &c5, &c6, &c7, &f1, &f2, &f3, &f4);
            printf("s");
        }
        else if ((strcmp(input,"QQ")) == 0){ //strcmp returns 0 if theyre the same.
            printf("s");
            exit(0);
        }
        else{
            printf("Wrong command");
        }
    }

}

/*
 * ******** IGNORE ALL TEXT IN THIS CLASS, IT IS (probably) NOT VALID! ********************
 */
/*
 * Global values and game initiation.
 */

int closeSDLWindow(SDL_Window* window) {

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

}

/*
 * ******** IGNORE ALL TEXT IN THIS CLASS, IT IS (probably) NOT VALID! ********************
 */
/*
 * Global values and game initiation.
 */
int main(int argc, char* args[]){

    /*
    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SLD_ERROR: %s\n", SDL_GetError());
    }
    else {
        // Create window
        window = SDL_CreateWindow("Yukon Machine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface -> format, 0xff, 0xff, 0xff));

            // Update the surface
            SDL_UpdateWindowSurface(window);

            // Get window to stay visible
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }

    }
     */


    /*
 * Essentially we are creating an object of type Card and do stuff with it
 */
    int j = 0;
    char chars = '2';
    chars = (char) ((j+97));
    printf("%c", chars);

    printf("\n\n");

    char errorMessages[100];

    // Time test.. should be deleted
    /*
    time_t currentTime = time(NULL);
    srand(currentTime);
    int tempint = rand() % 52;
    printf("\n\n%d\n\n", tempint);
     */


    /**
     * All global data is saved here. Global data is seen as the card deck and their available spots on the board
     */
    Card* firstCard = NULL;
    Card* lastCard = NULL;

    // Gives the address to createDeck. firstCard will change accordingly and will no longer be empty
    createDeck(&firstCard, &lastCard);
    //printf("%s", loadDeck(&firstCard, &lastCard, "savedDeck.txt", errorMessages));
    Card* current = firstCard;

    //shuffle(&firstCard, &lastCard);

    // Prints, for testing
    //char *str = saveDeck(firstCard, "");
    //printf("%s\n", str);

    // just for testing.. Prints the current deck
/*
    printf("\n");
    if (current != NULL){
        while (current != NULL){
            printf("%c%c\n", current->cardValue, current->cardType);
            current = current->next;
        }
    }
    */

/*
    printf("\n\n");
    //splitShuffle(&firstCard, &lastCard);
    showCards(firstCard);
    play(&firstCard, &lastCard, &c1, &c2, &c3, &c4, &c5, &c6, &c7);
    //showCards(firstCard);

    printf("\n The board below is the current card deck: \n");
    printCurrentBoard(c1, c2, c3, c4, c5, c6, c7);

    moveCards(&c4, &c5, 2, false);



    printCurrentBoard(c1, c2, c3, c4, c5, c6, c7);
*/
    //printf("%s", loadDeck(&firstCard,&lastCard,"",errorMessages));
    startMenu(&firstCard, &lastCard, errorMessages);
    printf("\nCode finished succesfully(maybe not succesfully, it did finish though..)");
    return 1;

}

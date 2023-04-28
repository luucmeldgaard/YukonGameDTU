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
                newCard->cardType = 'C';
            } else if (i == 2){
                newCard->cardType = 'D';
            } else if (i == 3){
                newCard->cardType = 'H';
            } else if (i == 4){
                newCard->cardType = 'S';
            }
            // Assigns the value from ACE to K
            if (j == 1){
                newCard -> cardValue = 'A';
            } else if(j < 10){
                // Converts ASCII int value to char
                newCard -> cardValue = j + '0';
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
/*
 * loadDeck is used to load a deck from a txt file. Uses ControlDeck to validate the loaded deck.
 */
char *loadDeck(Card** firstCard, Card** lastCard, const char *fileName, char *textbuf){
    if (fileName == NULL || fileName == "" || strcmp(fileName, "\0") == 0){
        createDeck(firstCard, lastCard);
        return "OK, deck created";
    }
    FILE* file = fopen(fileName, "r");
    if (file == NULL){
        return "Invalid file path";
    }
    // Creates a linked list containing all 52 cards. Is used to check against the imported card deck.
    Card* firstCardTemp = NULL;
    Card* lastCardTemp = NULL;
    createDeck(&firstCardTemp, &lastCardTemp);

    // Temp is created for fgets. Contains details of one card.
    // Should be made into a while statement..... lazy.
    char temp[2];
    for (int i = 1; i <= 52; i++){
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
    if (savedDeckName == NULL || savedDeckName == ""){
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
// Just a simple print method. No fancy stuff.
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
        // Prints the value of the card
        printf("%c%c\t", currentCard->cardValue, currentCard->cardType);
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
void splitShuffle(Card** firstCard, Card** lastCard){
    Card* currentCard = *firstCard;
    // Creates a random number. rand() in c must be provided a seed, otherwise the same random sequence will happen everytime, and as such very quickly become predictable
    // Using the current time as seed.
    time_t currentTime = time(NULL);
    srand(currentTime);
    int randomNumber = rand() % (52 - 1 + 1) + 1;
    randomNumber = 13;
    for (int i = 1; i <= randomNumber; i++){
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

/*
 * Prints the current board. Not much to be explained, just a bunch of if statements printing stuff.
 */
void printCurrentBoard(Card* c1, Card* c2, Card* c3, Card* c4, Card* c5, Card* c6, Card* c7){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    int lineCounter = 0;
    while (c1 != NULL || c2 != NULL || c3 != NULL || c4 != NULL || c5 != NULL || c6 != NULL || c7 != NULL){
        if (c1 != NULL){
            if (c1->flipped == true){
                printf("[]\t");
            } else {
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
            }
            c3 = c3->next;
        }else {
            printf("\t");
        }
        if (c4 != NULL){
            if (c4->flipped == true){
                printf("[]\t");
            } else {
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
                printf("%c%c\t", c7->cardValue, c7->cardType);
            }
            c7 = c7->next;
        }else {
            printf("\t");
        }
        if (lineCounter == 0){
            printf("\tF1");
        } else if (lineCounter == 2){
            printf("\tF2");
        } else if (lineCounter == 4){
            printf("\tF3");
        } else if (lineCounter == 6){
            printf("\tF4");
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
    printf("Status message: \n");
    printf("Input: \n");
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
    Card* temp = *fromPile;
    Card* temp2 = *toPile;
    for (int i = 0; i < from; i ++) {
        (*fromPile) = (*fromPile)->next;
    }
    while ((*toPile)->next != NULL) {
        (*toPile) = (*toPile)->next;
    }

    if (*fromPile == NULL || *toPile == NULL){
        *fromPile = temp;
        *toPile = temp2;
        return false;
    }

    if ((*fromPile)->flipped){
        *fromPile = temp;
        *toPile = temp2;
        return false;
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

    printf("\n\n%c%c\n\n", (*toPile)->cardValue, (*toPile)->cardType);

    Card* cardToMove = oldPile;

    oldPile = oldPile->previous;
    oldPile->next = NULL;

    newPile->next = cardToMove;

    *fromPile = temp;
    *toPile = temp2;


    return true;
}


void startMenu(Card** firstCard, Card** lastCard,char* textBuf){
    char input[4]; //Allocates the space fo the string
    char filename[128];
    char c;
    int i = 0;

    while (true){
        printf("What would you like to do? \nLD <filename> \nSW \nSI<split> \nSR \nSD <filepath> \nP \nQQ (quit)\n");
        scanf("%c%c", &input[0], &input[1]);

        if ((strcmp(input,"LD")) == 0){ //strcmp returns 0 if theyre the same.
            printf("Input file path: (leave empty if you want to start a new game)");
            getchar();
            while ((c = getchar()) != '\n' && i < sizeof(filename) - 1){
                filename[i++] = c;
                printf("%c", c);
            }
            printf("\n");
            printf("%s", loadDeck(firstCard, lastCard, filename, textBuf));

            printf("\n");

        }
        else if ((strcmp(input,"SW")) == 0){ //strcmp returns 0 if theyre the same.
            showCards(*firstCard);
        }
        else if ((strcmp(input,"SI")) == 0){ //strcmp returns 0 if theyre the same.
            printf("s");
        }
        else if ((strcmp(input,"SR")) == 0){ //strcmp returns 0 if theyre the same.
            printf("s");
        }
        else if ((strcmp(input,"SD")) == 0){ //strcmp returns 0 if theyre the same.
            printf("s");
        }
        else if ((strcmp(input,"P")) == 0){ //strcmp returns 0 if theyre the same.
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


    /*
     * Essentially we are creating an object of type Card and do stuff with it
     */

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
    // The card is split into 7 columns
    Card* c1 = NULL; Card* c2 = NULL; Card* c3 = NULL; Card* c4 = NULL; Card* c5 = NULL; Card* c6 = NULL; Card* c7 = NULL;
    // 4 additional lists is made for finished cards
    Card* f1, f2, f3, f4;
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

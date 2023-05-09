//
// Created by LuucM on 28-04-2023.
//

#include "card.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        //printf("im also doing this"); //Removed because it doesnt do anything besides make the gui messy
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL.h>
#include "card.h"
#include "logic.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

// PLACE BACK HERE IF NO WORKING

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

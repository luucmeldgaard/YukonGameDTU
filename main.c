#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include "card.h"
#include "logic.h"
#include <SDL_image.h>
#include <SDL_timer.h>
#include "printText.h"
#include "undoRedo.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* win;



typedef struct currentGame{
    char* move;
    struct currentGame *next;
    struct currentGame *prev;
} currentGame;

currentGame* moves = NULL;

/**
 * Function for playing the game. This function tak
 * @param firstCard
 * @param lastCard
 */
void movePileToBoard(Card** firstCard, Card** lastCard, Card** c1, Card** c2, Card** c3, Card** c4, Card** c5, Card** c6, Card** c7){



    printf("%c%c\n", (*firstCard)->cardValue, (*firstCard)->cardType);

    int cardsPlaced[] = {0,0,0,0,0,0,0};

    while (*firstCard != NULL) {

        if (cardsPlaced[0] == 0) {
            placeCard(c1, firstCard);
            cardsPlaced[0] += 1;
        }
        if (cardsPlaced[1] < 6) {
            if (cardsPlaced[1] == 0){
                (*firstCard)->flipped = true;
            }
            placeCard(c2, firstCard);
            cardsPlaced[1] += 1;
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
    printf("\n\n ---------------------- FINISHED ----------------------\n\n");
}


void freeBoardPiles(Card** c1, Card** c2, Card** c3, Card** c4, Card** c5, Card** c6, Card** c7, Card** f1, Card** f2, Card** f3, Card** f4) {
    Card* tempCard;
    Card* piles[] = {*c1, *c2, *c3, *c4, *c5, *c6, *c7, *f1, *f2, *f3, *f4};



    for (int i = 0; i < 11; i++) {
        Card* currentPile = piles[i];

        while (currentPile != NULL) {
            tempCard = currentPile;
            currentPile = currentPile->next;
            free(tempCard);
        }

        piles[i] = NULL;
    }
}


void nextMove(char* usrInput, currentGame** chain){
    currentGame* move = (currentGame*)(malloc(sizeof(currentGame)));
    move->move = strdup(usrInput);
    move->next = NULL;
    move->prev = NULL;

    if (*chain == NULL){
        *chain = move;
        return;
    }

    currentGame* temp = *chain;
    while (temp->next != NULL){
        temp = temp->next;
    }
    move->prev = temp;
    temp->next = move;
}

char* undo() {

    currentGame* currentMove = moves;

    while (currentMove->next != NULL) {
        currentMove = currentMove->next;
    }

    if (currentMove->prev == NULL) {
        return "0";
    }

    char *firstCard = malloc(8*sizeof(char));
    char *secondCard = malloc(8*sizeof(char));
    *firstCard = '\0';
    *secondCard = '\0';
    bool nextCard = false;


    char* move = currentMove->move;

    int size = strlen(move);

    for (int i = 0; i < size; i++) {
        if (move[i] == '-' || move[i] == '>') {
            nextCard = true;
        }
        else if (nextCard == true) {
            strncat(secondCard, &move[i], 1);
        }
        else {
            strncat(firstCard, &move[i], 1);
        }
    }

    printf("move reversed: %s -> %s\n", secondCard, firstCard);
    char *result = malloc(8*sizeof(char));
    *result = '\0';

    strcat(result, secondCard);
    strcat(result, "->");
    strcat(result, firstCard);




    if (currentMove->prev == NULL) {
        currentMove = NULL;
        return result;
    }

    currentMove = currentMove->prev;
    currentMove->next = NULL;

    return result;

}

void playGame(Card** firstCard, Card** lastCard, Card** c1, Card** c2, Card** c3, Card** c4, Card** c5, Card** c6, Card** c7, Card** f1, Card** f2, Card** f3, Card** f4){
    printCurrentBoard(*c1, *c2, *c3, *c4, *c5, *c6, *c7, *f1, *f2, *f3, *f4,"P", "Welcome!"); //P is hardcoded here, but could be passed as an arg to playgame(), doesn't really matter
    char usrInput[256];
    bool moveByColumn;
    bool endPile;
    Card **chosenDeck1;
    Card **chosenDeck2;
    char messages[256];
    bool redo = false;

    while (true) {
        while (true) {
            currentGame* temp = moves;
            while (temp != NULL){
                temp = temp->next;
            }


            endPile = false;
            memset(usrInput, '\0', 256); // Clears the input array
            fflush(stdin); // Clears input buffer
            scanf("%s", &usrInput[0]);



            if (usrInput[0] == 'Q'){
                freeBoardPiles(c1, c2, c3, c4, c5, c6, c7, f1, f2, f3, f4);
                return;
            }

            if (usrInput[0] == 'U') {
                memset(usrInput, '\0', 256); // Clears the input array
                fflush(stdin); // Clears input buffer
                if (moves != NULL){
                    printf("You're being naughty naughty");
                    char *result = undo();
                    redo = true;
                    int resultLength  = strlen(result);
                    char resultArray[resultLength + 1];
                    strcpy(resultArray, result);
                    strcpy(usrInput, resultArray);
                }


                if (usrInput[0] == '0') { //TODO: THIS DOESNT PRINT CORRECTLY. Hardcode or fix?
                    printCurrentBoard(*c1, *c2, *c3, *c4, *c5, *c6, *c7, *f1, *f2, *f3, *f4,"U0", "Nothing to undo! (Or less than one move made) ");
                    continue;
                }
            }

            if (!(usrInput[2] == ':' && usrInput[5] == '-' && usrInput[6] == '>' || usrInput[2] == '-' && usrInput[3] == '>')){
                printf("Incorrect user input detected. Please check your input and try again\nInput: ");
                continue;
            }


            if (usrInput[2] == ':' && usrInput[5] == '-' && usrInput[6] == '>') {

                if (usrInput[1] == usrInput[8] && usrInput[0] == usrInput[7]){
                    printf("Incorrect user input detected. Please check your input and try again\nInput: ");
                    continue;
                }


                printf("\nAt first line\n");
                if (!(usrInput[0] == 'C' || usrInput[0] == 'F')) {
                    printf("no good input: %c", usrInput[0]);
                    continue;

                } else if (!(usrInput[1] >= '1' && usrInput[1] <= '7')) {
                    printf("no good input: ");
                    continue;

                } else if (!(usrInput[3] >= '1' && usrInput[3] <= '9') && usrInput[3] != 'T' && usrInput[3] != 'A' && usrInput[3] != 'J' &&
                           usrInput[3] != 'Q' && usrInput[3] != 'K') {
                    printf("no good input: ");
                    continue;

                } else if (!(usrInput[4] == 'C' || usrInput[4] == 'S' || usrInput[4] == 'H' || usrInput[4] == 'D')){
                    printf("no good input: ");
                    continue;
                } else if (!(usrInput[0] == 'C' || usrInput[0] == 'F')){
                    printf("no good input: ");
                    continue;
                } else if(!(usrInput[1] >= '1' && usrInput[1] <= '7')){
                    printf("no good input: ");
                    continue;
                }
                else {
                    moveByColumn = false;
                    break;
                }
            }
            else if (usrInput[2] == '-' && usrInput[3] == '>'){
                if (usrInput[1] == usrInput[5] && usrInput[0] == usrInput[4]){
                    printf("im a good boy");
                    continue;
                }
                printf("\nAt second line\n");
                if (!(usrInput[0] == 'C' || usrInput[0] == 'F')) {
                    printf("no good input: %c", usrInput[0]);
                    continue;

                } else if (!(usrInput[1] >= '1' && usrInput[1] <= '7')) {
                    printf("no good input: ");
                    continue;

                } else if (!(usrInput[4] == 'C' || usrInput[4] == 'F')){
                    printf("no good input: ");
                    continue;
                } else if(!(usrInput[5] >= '1' && usrInput[5] <= '7')){
                    printf("no good input: ");
                    continue;
                }
                else {
                    moveByColumn = true;
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

            if (usrInput[4] == 'C') {
                if (usrInput[5] == '1') {
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
                    chosenDeck1 = f1;
                } else if (usrInput[1] == '2') {
                    chosenDeck1 = f2;
                } else if (usrInput[1] == '3') {
                    chosenDeck1 = f3;
                } else if (usrInput[1] == '4') {
                    chosenDeck1 = f4;
                }
            }

            if (usrInput[4] == 'F') {
                endPile = true;
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
            if (moveCards(chosenDeck1, chosenDeck2, -1, endPile, messages, redo) == true){
            } else {
            }
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
                endPile = true;
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
                    *chosenDeck1 = temp;
                    cardInColumn = true;
                    if(moveCards(chosenDeck1, chosenDeck2, height, endPile, messages, redo) == true) {
                        break;
                    } else {
                        break;
                    }
                }
                if (*chosenDeck1 == NULL){
                    strcpy(messages, "Card does not exists in column");
                }
                (*chosenDeck1) = (*chosenDeck1)->next;
                height++;
            }
        }

        if (*f1 != NULL && *f2 != NULL && *f3 != NULL && *f4 != NULL) {

            printf("\n\nAm actually at all heree am i not actually here?\n");

            Card* tempf1 = *f1;
            Card* tempf2 = *f2;
            Card* tempf3 = *f3;
            Card* tempf4 = *f4;

            while (tempf1->next != NULL){
                tempf1 = tempf1->next;
            }
            while (tempf2->next != NULL){
                tempf2 = tempf2->next;
            }
            while (tempf3->next != NULL){
                tempf3 = tempf3->next;
            }
            while (tempf4->next != NULL){
                tempf4 = tempf4->next;
            }


            printf("\n\n%c%c\n", tempf1->cardValue, tempf1->cardType);
            printf("\n\n%c%c\n", tempf2->cardValue, tempf2->cardType);
            printf("\n\n%c%c\n", tempf3->cardValue, tempf3->cardType);
            printf("\n\n%c%c\n", tempf4->cardValue, tempf4->cardType);

            if ((tempf1)->cardValue == 'K' && (tempf2)->cardValue == 'K' && (tempf3)->cardValue == 'K' &&
                (tempf4)->cardValue == 'K') {

                printf("\n-------------------------------------------------\n");
                printf("\n|            Congrats, you won!!!!              |\n");
                printf("\n-------------------------------------------------\n");
                printf("\n press any button to return to main menu: ");
                getchar();
                getchar();

                return;
            }
        }

        printCurrentBoard(*c1, *c2, *c3, *c4, *c5, *c6, *c7, *f1, *f2, *f3, *f4, usrInput,messages);
        if (!redo){
            nextMove(usrInput, &moves);
        }
    }
}

Card* copyLinkedList(Card* toCopy){
    if (toCopy == NULL) {
        return NULL;
    }

    Card* newPile = NULL;
    Card* temp = toCopy;
    Card* newCard = NULL;
    Card* prevCard = NULL;

    while (temp != NULL) {
        newCard = (Card*) malloc(sizeof(Card));
        newCard->cardValue = temp->cardValue;
        newCard->cardType = temp->cardType;
        newCard->next = NULL;
        newCard->flipped = false;

        if (prevCard != NULL) {
            prevCard->next = newCard;
            newCard->previous = prevCard;
        } else {
            newCard->previous = NULL;
            newPile = newCard;
        }

        prevCard = newCard;
        temp = temp->next;
    }
    return newPile;
}

void startMenu(Card** firstCard, Card** lastCard, char* textBuf){

    // The card is split into 7 columns
    Card* c1 = NULL; Card* c2 = NULL; Card* c3 = NULL; Card* c4 = NULL; Card* c5 = NULL; Card* c6 = NULL; Card* c7 = NULL;
    // 4 additional lists is made for finished cards
    Card* f1 = NULL; Card* f2 = NULL; Card* f3 = NULL; Card* f4 = NULL;

// Creating a deck in a very weird way... Dont ask... We fucked up pointers so long ago it's a wonder it still works :)
    Card* copyList;
    Card** currentCard = &copyList;
    Card** currentLastCard;
    Card* temp = *currentCard;


    ///// Program breaks if more than 128 chars is inputted. It will override memory.
    char input[256]; //Allocates the space fo the string
    char filename[256];
    char usrInput;
    char saveChar;

    while (true){
        int i = 0;
        printf("\nWhat would you like to do? \nLD <filename> \nSW \nSI<split> \nSR \nSD <filepath> \nP \nQQ (quit)\n");
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
        else if ((strcmp(input, "SI")) == 0) {
            printf("Please enter a number between 0 and 52. Leave empty or enter any letter to pick a random number: ");
            char consumeNewLine;
            while ((consumeNewLine = getchar()) != '\n' && consumeNewLine != EOF) {}
            signed int chosenCard = 0;
            while (true) {
                char tempUsrInput[5];
                fgets(tempUsrInput, sizeof(tempUsrInput), stdin);

                // Check if there are extra characters in the input stream
                if (strchr(tempUsrInput, '\n') == NULL) {
                    // Clear input buffer
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}
                }

                int result = sscanf(tempUsrInput, "%3d", &chosenCard);

                if (result == 1 && chosenCard >= 0 && chosenCard <= 52) {
                    break;
                } else if (tempUsrInput[0] == '\n'){
                    break;
                }
                else {
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
                printf("%c", saveChar);
            }
            saveFileName[i++] = '\0';
            printf("%s","\n");
            saveDeck(*firstCard,saveFileName); //Tjek lige om det der pointer noget fungerer
        }
            // "Play" - starts the game
        else if ((strcmp(input,"P")) == 0){ //strcmp returns 0 if theyre the same.
            // The card is split into 7 columns
            c1 = NULL; c2 = NULL; c3 = NULL; c4 = NULL; c5 = NULL; c6 = NULL; c7 = NULL;
            // 4 additional lists is made for finished cards
            f1 = NULL; f2 = NULL; f3 = NULL; f4 = NULL;
            copyList = copyLinkedList(*firstCard);
            currentCard = &copyList;
            temp = *currentCard;
            printf("\n -----------------------------------------------\n");
            while (temp != NULL){
                currentLastCard = &temp;
                printf("\n%c%c\n", (*currentLastCard)->cardValue, (*currentLastCard)->cardType);
                temp = temp->next;
            }
            printf("\n -----------------------------------------------\n");


            if ((*currentCard) != NULL){
                movePileToBoard(currentCard, currentLastCard, &c1, &c2, &c3, &c4, &c5, &c6, &c7);
            }
            playGame(currentCard, currentLastCard, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &f1, &f2, &f3, &f4);
            printf("s");
        }
        else if ((strcmp(input,"QQ")) == 0){ //strcmp returns 0 if theyre the same.
            printf("s");
            exit(0);
        } else if ((strcmp(input, "test")) == 0) { //This shouldnt actually run, and is only used for debugging in future versions
            printf("test");
            saveCurrentGame(&c1, &c2, &c3, &c4, &c5, &c6, &c7, &f1, &f2, &f3, &f4);
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

bool init() {

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    win = SDL_CreateWindow("Yukon Game", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       500, 500, 0);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    // creates a surface to load an image into the main memory
    SDL_Surface* surface;
    SDL_Surface* surface2;

    surface = IMG_Load("libs/images/title.png");
    surface2 = IMG_Load("libs/images/start.png");

    // loads image to our graphics hardware memory.
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_Texture* tex2 = SDL_CreateTextureFromSurface(rend, surface2);

    // clears main-memory
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);


    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;
    SDL_Rect dest2;

    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    SDL_QueryTexture(tex2, NULL, NULL, &dest2.w, &dest2.h);

    // adjust height and width of title
    dest.w = 200;
    dest.h = 200;

    // sets initial x-position of title
    dest.x = (500 - dest.w) / 2;

    // sets initial y-position of title
    dest.y = (500 - dest.h) / 2;
    dest.y -= 200;


    // adjust height and width of start
    dest2.w = 150;
    dest2.h = 80;

    // sets initial x-position of start
    dest2.x = (500 - dest2.w) / 2;

    // sets initial y-position of start
    dest2.y = (500 - dest2.h) / 2;



    // controls animation loop
    int close = 0;

    int speed = 5;

    // animation loop
    while (!close) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    // handling of close button
                    close = 1;
                    break;

                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_ENTER)
                    {
                        //printf("YOU ARE WITHIN THE WINDOW FRAME");
                    }
                    else if (event.window.event == SDL_WINDOWEVENT_LEAVE)
                    {
                        //printf("YOU ARE NO LONGER WITHIN THE WINDOW FRAME");
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        int x = event.button.x;
                        int y = event.button.y;
                        // Handle the left mouse button down event at (x,y)
                        //printf("x = %d\ny = %d", x, y);
                        if (x >= dest2.x && x<= dest2.x + dest2.w) {
                            if (y >= dest2.y && y <= dest2.y + dest2.h) {
                                close = 1;
                            }
                        }
                    }
                    break;
            }
        }

        // right boundary
        if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;

        // upper boundary
        if (dest.y < 0)
            dest.y = 0;

        // clears the screen
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_RenderCopy(rend, tex2, NULL, &dest2);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // destroy texture
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(tex2);

    // destroy renderer
    SDL_DestroyRenderer(rend);

    // destroy window
    SDL_DestroyWindow(win);

    // close SDL
    SDL_Quit();

    return 0;

}

bool loadMedia(SDL_Window* window, SDL_Surface** screenSurface) {

    // Media loading flag
    bool success = true;

    //The surface contained by the window
    SDL_Surface* image = NULL;

    // Load image
    image = SDL_LoadBMP( "background.bmp" );
    if( image == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "background.bmp", SDL_GetError() );
        success = false;
    }
    else {
        //Apply the image
        SDL_BlitSurface( image, NULL, *screenSurface, NULL );

        // Update the window surface
        SDL_UpdateWindowSurface(window);
    }

    return success;
}

int main(int argc, char* argv[]){

    // Initialize SDL and start window
    init();



    /*
 * Essentially we are creating an object of type Card and do stuff with it
 */
    int j = 0;
    char chars = '2';
    chars = (char) ((j+97));
    printf("%c", chars);

    printf("\n\n");

    char errorMessages[256];


    /**
     * All global data is saved here. Global data is seen as the card deck and their available spots on the board
     */
    Card* firstCard = NULL;
    Card* lastCard = NULL;

    // Gives the address to createDeck. firstCard will change accordingly and will no longer be empty
    createDeck(&firstCard, &lastCard);
    Card* current = firstCard;
    startMenu(&firstCard, &lastCard, errorMessages);
    printf("\nCode finished succesfully(maybe not succesfully, it did finish though..)");
    return 1;

}

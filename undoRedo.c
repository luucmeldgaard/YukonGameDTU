//
// Created by emils on 29/04/2023.
//
#include "card.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int movesUndone = 0;
char* fileName = "logs.txt";

void resetMovesUndoneCounter(){
    movesUndone = 0;
}

void writeReversedData(FILE *file, Card **card_list) {
    // Count the number of cards in the list
    Card *temp = *card_list;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    // Write the card values and types in reverse order
    for (int i = count - 1; i >= 0; i--) {
        temp = *card_list;

        // Move to the i-th card in the list
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }

        // Write the card value and type to the file
        fprintf(file, "%c%c", temp->cardValue, temp->cardType);
    }
}

char *saveCurrentGame(Card** c1, Card** c2, Card** c3, Card** c4, Card** c5, Card** c6, Card** c7, Card** f1, Card** f2, Card** f3, Card** f4){
    printf("\nAm i runnning?\n");
    FILE* file = fopen(fileName, "w");

    writeReversedData(file, c1);
    fprintf(file, "\n");

    writeReversedData(file, c2);
    fprintf(file, "\n");

    writeReversedData(file, c3);
    fprintf(file, "\n");

    writeReversedData(file, c4);
    fprintf(file, "\n");

    writeReversedData(file, c5);
    fprintf(file, "\n");

    writeReversedData(file, c6);
    fprintf(file, "\n");

    writeReversedData(file, c7);
    fprintf(file, "\n");

    writeReversedData(file, f1);
    fprintf(file, "\n");

    writeReversedData(file, f2);
    fprintf(file, "\n");

    writeReversedData(file, f3);
    fprintf(file, "\n");

    writeReversedData(file, f4);
    fprintf(file, "\n");

    fclose(file);

    return "Success!";
}

char *loadGame(){

}


char *undoMoves(Card** c1,Card** c2,Card** c3,Card** c4,Card** c5,Card** c6,Card** c7,Card** f1,Card** f2,Card** f3,Card** f4){
    char buffer;
    movesUndone += 1;
    Card* Temp;

    FILE* file = fopen(fileName, "r+");

    if (file == NULL){
        return "No moves made";
    }

    while (1){
        fscanf(file, "%c%c", &((*c1)->cardValue), &((*c1)->cardType));

        int ch = fgetc(file);


        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file); // Put the character back in the file stream
        }
        (*c1) = (*c1)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c2)->cardValue), &((*c2)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c2) = (*c2)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c3)->cardValue), &((*c3)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c3) = (*c3)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c4)->cardValue), &((*c4)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c4) = (*c4)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c5)->cardValue), &((*c5)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c5) = (*c5)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c6)->cardValue), &((*c6)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c6) = (*c6)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c7)->cardValue), &((*c7)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c7) = (*c7)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*f1)->cardValue), &((*f1)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*f1) = (*f1)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*f2)->cardValue), &((*f2)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*f2) = (*f2)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*f3)->cardValue), &((*f3)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*f3) = (*f3)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*f4)->cardValue), &((*f4)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*f1) = (*f4)->next;
    }


    fclose(file);
    return "Success!";

}


char *redoMoves(Card** c1,Card** c2,Card** c3,Card** c4,Card** c5,Card** c6,Card** c7,Card** f1,Card** f2,Card** f3,Card** f4){
    char buffer;
    FILE* file = fopen(fileName, "r+");
    if (file == NULL){
        return "No moves made";
    }




    for (int i = 0; i < movesUndone; i++){
        for (int j = 0; j < 11; j++) {
            fseek(file, 0, SEEK_SET);
        }
    }

    while (1){
        fscanf(file, "%c%c", &((*c1)->cardValue), &((*c1)->cardType));

        int ch = fgetc(file);


        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file); // Put the character back in the file stream
        }
        (*c1) = (*c1)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c2)->cardValue), &((*c2)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c2) = (*c2)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c3)->cardValue), &((*c3)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c3) = (*c3)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c4)->cardValue), &((*c4)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c4) = (*c4)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c5)->cardValue), &((*c5)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c5) = (*c5)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c6)->cardValue), &((*c6)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c6) = (*c6)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*c7)->cardValue), &((*c7)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*c7) = (*c7)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*f1)->cardValue), &((*f1)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*f1) = (*f1)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*f2)->cardValue), &((*f2)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*f2) = (*f2)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*f3)->cardValue), &((*f3)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*f3) = (*f3)->next;
    }
    while (1){

        fscanf(file, "%c%c", &((*f4)->cardValue), &((*f4)->cardType));

        int ch = fgetc(file);

        if (ch == '\n' || ch == EOF) {
            break;
        } else {
            ungetc(ch, file);
        }
        (*f1) = (*f4)->next;
    }


    fclose(file);
    return "Succes!";




}
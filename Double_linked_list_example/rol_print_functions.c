// rol_print_functions.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rol_print_functions.h"
#include "person_node.h"



// ANSI color codes
#define RESET   "\033[0m"
#define BOLDRED "\033[1;31m"
#define BOLDGRN "\033[1;32m"
#define BOLDBLU "\033[1;34m"
#define BOLDYEL "\033[1;33m"
#define BORDER  "\033[1;37m"  // White for borders
#define REDONYEL "\033[1;31;43m"

void print_hello_world(int numTimes) {
    printf("\nHello World\n");
}


// ***** Function to add padding for right alignment
void addPadding(int totalLength, int currentLength) {
    int padding = totalLength - currentLength;
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
}

// ****** Function to print the diagram of the doubly linked list with borders and two-way arrows
void printListDiagramVerticalPadding(struct PersonNode* head, struct PersonNode* tail) {
    struct PersonNode* current = head;
    const int boxWidth = 25;  // Set a fixed width for the box
    
    printf("\n");
    printf(REDONYEL"Head: %s", head->name);
    printf(RESET"\n");

    // Iterate through the list and print each node's details
    while (current != NULL) {
        // Top border
        printf(BORDER"+------------------------+\n" RESET);

        // Print node information with color formatting inside borders
        printf(BORDER"| " RESET);
        printf(BOLDGRN"Name: %s" RESET, current->name);
        addPadding(boxWidth - 9, strlen(current->name));  // 9 accounts for "Name: " and spaces
        printf(BORDER" |\n" RESET);

        printf(BORDER"| " RESET);
        printf(BOLDYEL"Age: %d" RESET, current->age);
        addPadding(boxWidth - 8, snprintf(NULL, 0, "%d", current->age));  // 8 accounts for "Age: " and spaces
        printf(BORDER" |\n" RESET);

        // Print whether there's a previous node
        printf(BORDER"| " RESET);
        if (current->prev != NULL) {
            printf(BOLDBLU"Prev: %s" RESET, current->prev->name);
            addPadding(boxWidth - 9, strlen(current->prev->name));  // 10 accounts for "Prev: " and spaces
        } else {
            printf(BOLDBLU"Prev: NULL" RESET);
            addPadding(boxWidth - 9, 4);  // 4 for "NULL"
        }
        printf(BORDER" |\n" RESET);

        // Print whether there's a next node
        printf(BORDER"| " RESET);
        if (current->next != NULL) {
            printf(BOLDBLU"Next: %s" RESET, current->next->name);
            addPadding(boxWidth - 9, strlen(current->next->name));  // 10 accounts for "Next: " and spaces
        } else {
            printf(BOLDBLU"Next: NULL" RESET);
            addPadding(boxWidth - 9, 4);  // 4 for "NULL"
        }
        printf(BORDER" |\n" RESET);

        // Bottom border
        printf(BORDER"+------------------------+\n" RESET);

        // Move to the next node
        current = current->next;

        // If there's a next node, print the two-way arrow with color
        if (current != NULL) {
            printf(BOLDRED"   ↓↑   \n" RESET);  // Two-way arrow for bidirectional links
        }
    }
  
    printf(REDONYEL"Tail: %s", tail->name);
    printf(RESET"\n");
}


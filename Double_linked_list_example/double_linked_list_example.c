
// To compile, link, run:
//     gcc -o ll_prog double_linked_list_example.c rol_print_functions.c  // compiles and links the program
//     ./ll_prog    // executes the program
//
//     or create a task or makefile that VS code uses
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "person_node.h"
#include "rol_print_functions.h"


bool DEBUG = false;  //set to true to print debug messages

void debugPrint(char* msg) {
    if (DEBUG == true) { printf("\nDEBUG: %s", msg); }
}


// Insert a node at the beginning of the list
void insertAtBeginning(struct PersonNode** head, struct PersonNode** tail,  int newAge, char* newName) {
    struct PersonNode* newNode = (struct PersonNode*)malloc(sizeof(struct PersonNode));
    struct PersonNode *tNode = *head;

    newNode->name = malloc(strlen(newName) + 1);
    strcpy(newNode->name, newName); 
    newNode->age = newAge;

    newNode->next = (*head);
    newNode->prev = NULL;

    // if this is the first node, set tail to this new node
     if (tNode == NULL) {
        (*tail) = newNode;
        debugPrint("first node created and linked to beginning\n");
    }

    // if this is not the first node, then set the prev link of the existing first node to the new first node
     if (tNode != NULL) {
        (*head)->prev = newNode;
        debugPrint("additional node created and linked to beginning\n");
    }

    // set head to be the new node since we are adding to the front of the list
    (*head) = newNode;
}

// Insert a node at the end of the list
void insertAtEnd(struct PersonNode** head, struct PersonNode** tail, int newAge, char* newName) {
    struct PersonNode* newNode = (struct PersonNode*)malloc(sizeof(struct PersonNode));
    struct PersonNode* last = *head;
    struct PersonNode *tNode = *tail;

    newNode->name = malloc(strlen(newName) + 1);
    strcpy(newNode->name, newName); //newNode->name = newName; - this results in the new name just being a pointer so all names the same as latest
    newNode->age = newAge;
    newNode->next = NULL; 

    // check if this is the first node being added and if so, set head and tail to the new node
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
        newNode->prev = NULL;
        debugPrint("first node created and linked to end\n");
        return;
    }
    
    //at least one node exists, so link the new node to the end of the list
    newNode->prev = (*tail); 
    tNode->next = newNode;
    *tail = newNode;

    debugPrint("Additional node created and linked to end\n");
}

// Delete a node in the list that matches the given age - only the first match is deleted
void deleteNode(struct PersonNode** head, struct PersonNode** tail, int key) {
    struct PersonNode *temp = *head, *prev;

    //check if the first node is the match and delete it
    if (temp != NULL && temp->age == key) {
        debugPrint("matched first node for deletion by age\n");
        *head = temp->next;
        //check if this is the only node in the list and if so then make the prev ptr NULL
        if (temp->next != NULL) {
            debugPrint("more than one node in the list when delete");
            temp->next->prev = NULL; 
        }  else {
            debugPrint("only one node in list when delete");
            //update tail since no nodes left in list
            *tail = NULL;
        }
        free(temp);
        debugPrint("removed first node in list by age\n");
        return;
    }

    //go through list and search for matching key
    while (temp != NULL && temp->age != key) {
        prev = temp;
        temp = temp->next;
    }
    
    //if no match was found, let the user know
    if (temp == NULL) { printf ("Delete: No matching age entry\n"); return;}

    //unlink the node and free the memory
    //handle the case where the last node is the match
    if (prev->next->next == NULL) {
        debugPrint("removing the last node\n");
        printf("%s", prev->next->name);
        *tail = prev;
        prev->next = NULL;
        free(prev->next);
        debugPrint("removed last node");
        return;
    }

    //it's NOT the last node that we are deleting
    debugPrint("removing a middle node\n");
    prev->next = temp->next;
    temp->next->prev = prev;
    free(temp);
}

// Delete a node in the list that matches the given name - only the first match is deleted
void deleteNodebyName(struct PersonNode** head, struct PersonNode** tail, char* key) {
    struct PersonNode *temp = *head, *prev;

    //check if the first node is the match and delete it
    if (temp != NULL && (strcmp(temp->name,key)==0)) {
        debugPrint("matched first node for deletion by name\n");
        *head = temp->next;
        //check if this is the only node in the list and if so then make the prev ptr NULL
        if (temp->next != NULL) {
            debugPrint("more than one node in the list when delete");
            temp->next->prev = NULL; 
        }  else {
            debugPrint("only one node in list when delete");
            //update tail since no nodes left in list
            *tail = NULL;
        }
        free(temp);
        debugPrint("removed first node in list by name\n");
        return;
    }

    //go through list and search for matching key
    while (temp != NULL && (strcmp(temp->name,key)!=0)) {
        prev = temp;
        temp = temp->next;
    }
    
    //if no match was found, let the user know
    if (temp == NULL) { printf ("Delete: No matching name entry\n"); return;}

    //unlink the node and free the memory
    //handle the case where the last node is the match
    if (prev->next->next == NULL) {
        debugPrint("removing the last node\n");
        printf("%s", prev->next->name);
        *tail = prev;
        prev->next = NULL;
        free(prev->next);
        debugPrint("removed last node");
        return;
    }
    //it's NOT the last node that we are deleting
    debugPrint("removing a middle node\n");
    prev->next = temp->next;
    temp->next->prev = prev;
    free(temp);
}

// Display the list starting at the first node
void displayList(struct PersonNode* node) {
    printf ("\nhere is the list: \n");

    while (node != NULL) {
        printf("%s, %d -> ", node->name, node->age);
        node = node->next;
    }
    printf("NULL\n");
}

// Display the list starting at the last node
//students - do i need this function? why or why not?
void displayListReverse(struct PersonNode* node) {
    printf ("\nhere is the list in reverse: \n");
    while (node != NULL) {
        printf("%s, %d -> ", node->name, node->age);
        node = node->prev;
    }
    printf("NULL\n");
}



// *****************************************
// ************** Main *********************
// ******************************************
 int main() {

    int myNum;
    char name[20]= "";
    struct PersonNode* head = NULL;
    struct PersonNode* tail = NULL;

    printf("Hi, Welcome to Linked List Example in C with ints and strings in a Linked List!\n");
    printf("Enter 'exit' for the name when done.\n");

    // loop and get names and ages until the user enters "exit" for the name
    while (1) {
        // Ask the user to type a string
        printf("\nType a name: ");
        scanf("%s", &name);

        if (strcmp(name,"exit") == 0) { break; }

        // Ask the user to type a number
        printf("Enter their age: ");
        scanf("%d", &myNum);

        insertAtEnd(&head, &tail, myNum, name);
        printListDiagramColor(head);
        //displayListReverse(tail);

                // other ways to insert into the list
                //insertAtEnd(&head, 1, "name1");
                //insertAtBeginning(&head, 2, "name2");

    }

    // test a few deletions
    //deleteNode(&head, &tail, 2);
    //deleteNodebyName(&head, &tail, "roland");

    //displayList(head);
    //displayListReverse(tail);
    printListDiagramColor(head);
    printListDiagramVerticalPadding(head, tail);

    return 0;
}

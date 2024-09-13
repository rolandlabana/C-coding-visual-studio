#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define our node to hold a name and an age
struct PersonNode {
    char *name;
    int age;
    struct PersonNode* next;
};

// Insert a node at the beginning of the list
void insertAtBeginning(struct PersonNode** head, int newAge, char* newName) {
    struct PersonNode* newNode = (struct PersonNode*)malloc(sizeof(struct PersonNode));
    newNode->name = newName;
    newNode->age = newAge;
    newNode->next = (*head);
    (*head) = newNode;

    // debug - 
    //printf("added node: %d,"  "%s\n",newNode->age, newNode->name);
}

// Insert a node at the end of the list
void insertAtEnd(struct PersonNode** head, int newAge, char* newName) {
    struct PersonNode* newNode = (struct PersonNode*)malloc(sizeof(struct PersonNode));
    struct PersonNode* last = *head;

    newNode->name = malloc(strlen(newName) + 1);
    strcpy(newNode->name, newName); 
    //newNode->name = newName;   // this results in the new name just being a pointer so all names the same as latest
    newNode->age = newAge;
    newNode->next = NULL;

    // debug - 
    //printf("added node: %d,"  "%s\n",newNode->age, newNode->name);

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

// Delete a node in the list that matches the given age - only the first match is deleted
void deleteNode(struct PersonNode** head, int key) {
    struct PersonNode *temp = *head, *prev;
    if (temp != NULL && temp->age == key) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->age != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) { printf ("Delete: No matching age entry"); return;}
    prev->next = temp->next;
    free(temp);
}

// Delete a node in the list that matches the given age - only the first match is deleted
void deleteNodebyName(struct PersonNode** head, char* key) {
    struct PersonNode *temp = *head, *prev;
    if (temp != NULL && (strcmp(temp->name,key)==0)) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && (strcmp(temp->name,key)!=0)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) { printf ("Delete: No matching name entry"); return;}
    prev->next = temp->next;
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

// ************** Main *********************
 int main() {

    // Create an integer variable that will store the number we get from the user
    int myNum;
    char name[20]= "";
    struct PersonNode* head = NULL;

    printf("Hi, Welcome to Linked List Example in C with ints and strings in a Linked List!\n");
    printf("Enter 'exit' for the name when done.\n");

    // loop and get names and ages until the user enters "exit" for the name
    while (1) {
        // Ask the user to type a string
        printf("Type a name: ");
        // Get and save the number the user type
        scanf("%s", &name);

        if (strcmp(name,"exit") == 0) { break; }
        // Output the name the user typed
        //printf("Your name is: %s\n", name);

        // Ask the user to type a number
        printf("Enter their age: ");
        // Get and save the number the user types
        scanf("%d", &myNum);
        // Output the number the user typed
        //printf("Your number is: %d\n", myNum);

        insertAtEnd(&head, myNum, name);
        displayList(head);

        // other ways to insert into the list
        //insertAtEnd(&head, 1, "name1");
        //insertAtBeginning(&head, 2, "name2");

    }

    // test a few deletions
    deleteNode(&head, 2);
    deleteNodebyName(&head, "roland");

    displayList(head);

    return 0;
}

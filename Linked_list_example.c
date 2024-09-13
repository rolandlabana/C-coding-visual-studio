#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *name;
    int data;
    struct Node* next;
};

void insertAtBeginning(struct Node** head, int newData, char* newName) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->name = newName;
    newNode->data = newData;
    newNode->next = (*head);
    (*head) = newNode;
}

void insertAtEnd(struct Node** head, int newData, char* newName) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head;

    newNode->name = malloc(strlen(newName) + 1);
    strcpy(newNode->name, newName); 
    //newNode->name = newName;   // this results in the new name just being a pointer so all names the same as latest
    newNode->data = newData;
    newNode->next = NULL;

    // debug - 
    //printf("added node: %d,"  "%s\n",newNode->data, newNode->name);

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}


void deleteNode(struct Node** head, int key) {
    struct Node *temp = *head, *prev;
    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

void deleteNodebyName(struct Node** head, char* key) {
    struct Node *temp = *head, *prev;
    if (temp != NULL && (strcmp(temp->name,key)==0)) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && (strcmp(temp->name,key)!=0)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

void displayList(struct Node* node) {
    printf ("\nhere is the list: \n");
    while (node != NULL) {
        printf("%s, %d -> ", node->name, node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// *********************************************************************
 int main() {

// Create an integer variable that will store the number we get from the user
    int myNum;
    char name[20]= "";
    struct Node* head = NULL;

    printf("Hi, Welcome to Linked List Example in C with ints and strings in a Linked List!\n");
    printf("Enter 'exit' for the name when done.\n");

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
    //insertAtEnd(&head, 1, "name1");
    //insertAtBeginning(&head, 2, "name2");
    displayList(head);

}

    // test a few deletions
    deleteNode(&head, 2);
    deleteNodebyName(&head, "roland");

    displayList(head);

    return 0;
}

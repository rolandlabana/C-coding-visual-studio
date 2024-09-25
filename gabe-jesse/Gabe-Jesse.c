#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ppl {
    int id;
    int age;
    int gender; 
    struct ppl* next;
    struct ppl* prev;
};

struct fnt_pointer { //makes pointers to the beginning and end of the list
    struct ppl* first_;
    struct ppl* tail_;
};

struct fnt_pointer* initializer(struct ppl** first, struct ppl** tail, struct fnt_pointer* returner) {
    // a function that intializes a small list for the user
    struct ppl* creator = NULL;
    int N = 1;
    int rand_age = 0;
    int rand_gender = 0;
    int rand_id = 0;
    struct ppl* previous = NULL;
    for (int i=0; i<10; i++) {
        creator = malloc (sizeof(struct ppl));
        if (previous != NULL) {
            previous->next = creator;
        } else if (previous == NULL) {
            *first = creator;
        }
        
        rand_id = rand() % (N*9999+1);
        rand_age = rand() % (N*100+1);
        rand_gender = rand() % (N+1);
        
        creator->id = rand_id;
        creator->age = rand_age;
        creator->gender = rand_gender;
        creator->next = NULL;
        creator->prev = previous;
        //printf("%d, %d, %d, %p, %p\n", creator->id, rand_age, rand_gender, creator->prev, creator->next);
        previous = creator;
        //free(creator);
        if (i==9){
            *tail = creator;
        }
    };

   // tail = creator;
    
    returner = malloc(sizeof(struct fnt_pointer));
    returner->first_ = *first;
    returner->tail_ = *tail;
    return returner;
};

int access_func(struct ppl* first,int query) {
    int cont = 1;
    int found = 0;
    struct ppl* curr = NULL;
    struct ppl* found_query = NULL;
    while(cont == 1) {
        if (curr == NULL) {
            curr = first;
        }
        if (query == curr->id){
            found = 1;
            found_query = curr;
        } 
        if (curr->next == NULL) {
            cont = 0;
        }
        curr = curr->next;
    }
    if (found == 1) {
        printf("%d, %d, %d, %p, %p\n", found_query->id, found_query->age, found_query->gender, found_query->prev, found_query->next);
    } else {
        printf("Search query not found\n");
    }

    return 0;
}

struct undo_ret {
    struct ppl* tail_;
    struct ppl* affected_;
    struct redo_node* redo_first_;
};

struct redo_node{
    struct ppl* affected_;
    struct redo_node* next;
};

struct redo_node* redo_list_appender(struct redo_node* redo_first, struct ppl* affected){
    struct redo_node* curr = redo_first;
    if (redo_first == NULL){
        redo_first = malloc(sizeof(struct redo_node));
        //printf("unnullified\n");
    };

    struct redo_node* new_node = malloc(sizeof(struct redo_node));
    new_node->affected_ = affected;
    new_node->next = redo_first;

    //printf("new node at %p\n",new_node);
    redo_first = new_node;
    return redo_first;
}

struct undo_ret* undo_function(struct ppl* tail, struct redo_node* redo_first){ 
    struct ppl* penult = tail->prev;  
    struct ppl* affected = tail;
    tail = penult;
    penult->next = NULL;
    struct undo_ret* undo_ret_ = malloc(sizeof(struct undo_ret));
    undo_ret_->tail_ = tail;
    undo_ret_->affected_ = affected;

    redo_first = redo_list_appender(redo_first, affected);
    undo_ret_->redo_first_ = redo_first;
    return undo_ret_; 
}

int redo_list_printer(struct redo_node* redo_first, int cond){
    if (cond == 1){
        if(redo_first != NULL){
            struct redo_node* curr = redo_first;
            if (redo_first->next != NULL){
                while(curr->next!=NULL){
                    printf("%p-%p\n",curr->next,curr->affected_);
                    curr = curr->next;
                }
            } else {
                printf("%p---\n",redo_first->next);
            }
        } else {
            printf("empty list\n");
        }
    }
    return 0;
}

void add_func(struct ppl* inputs, struct ppl** tail) { //passes in a pointer to the tail pointer
    if (*tail != NULL) { // if list is empty
        (*tail)->next = inputs;
        inputs->prev = *tail;
    }
    inputs->next = NULL;
    *tail = inputs; //adds new node to list, updates tail pointer to point to new (final) node
}

struct ppl* database_add_prompt(struct ppl* first, struct ppl** tail) {
    struct ppl* inputs = malloc(sizeof(struct ppl)); //makes new node
    if (inputs == NULL) { 
        printf("Memory allocation failed\n");
        exit(1);//checks if malloc failed
    }
    printf("ID: ");
    scanf("%d", &(inputs->id));
    printf("Age: ");
    scanf("%d", &(inputs->age));
    printf("Gender: ");
    scanf("%d", &(inputs->gender));
    inputs->next = NULL;  
    add_func(inputs, tail);
}

struct redo_node* redo_function(struct redo_node* redo_first,struct ppl* first, struct ppl* tail){
    if (redo_first != NULL){ printf("ran\n");
        struct redo_node* second = redo_first->next;
        tail->next = redo_first->affected_;
        redo_first->affected_->prev = tail;
        redo_first = second;
    } else {
        printf("NO REDOS\n");
    };

    return redo_first;
}

int print_all(struct ppl* first, int cond) { //prints the whole list
    if (cond == 1) {
        int torf = 1;
        struct ppl* curr = NULL;
        while(torf == 1) {
            if (curr == NULL) {
                curr = first;
            }
            printf("%d, %d, %d, %p, %p\n", curr->id, curr->age, curr->gender, (void*)curr->prev, (void*)curr->next);
            if (curr->next == NULL) {
                torf = 0;
            }
            curr = curr->next;
        }
    
    }
    printf("\n");
    return 0;
}

  
int main(void) {
    char restart_answer='l'; //tells whether or not to loop
    char* add="add"; //variables for comparing user input to
    char* access="access";
    char* modify="modify";

    struct ppl* first = NULL;
    struct ppl* tail = NULL;

    struct redo_node* redo_first = NULL;
    struct undo_ret* undo_ret_ = NULL;

    struct fnt_pointer* returner = NULL;
    
    returner = initializer(&first,&tail,returner);
    
    first = returner->first_;
    tail = returner->tail_;

    int cond = 0; 
    print_all(first, 1);
    redo_list_printer(redo_first,cond);

    if (cond == 1) {
        undo_ret_ = undo_function(tail, redo_first); 
        tail = undo_ret_->tail_;
        redo_first = undo_ret_->redo_first_;

        undo_ret_ = undo_function(tail, redo_first); 
        tail = undo_ret_->tail_;
        redo_first = undo_ret_->redo_first_;
    }
    print_all(first,cond); 
    redo_list_printer(redo_first,cond);

    if (cond == 1){
        redo_first = redo_function(redo_first,first,tail);
    }
    print_all(first,cond); 
    redo_list_printer(redo_first,cond);


    printf("Hello!\n Welcome to the Federal Bureau of Investigation Super Duper Top Secret Totally Classified People Database (aka FBI SDTSTCPD.)\n");
    char aachoice[50];
    do{
        printf("Please choose whether you would like to add, modify, or access the database?\n");
        scanf("%49s",aachoice); //49 limits characters to avoid crash
            if(strcmp(aachoice,add)==0){ //if they type "add"
                printf("please add an ID number to the database.\n");
                tail = database_add_prompt(first,&tail);
                restart_answer = 'q'; // Exit loop

            } else if (strcmp(aachoice, access) == 0) { // If user types "access"
                int query;
                printf("Enter the ID to search for: ");
                scanf("%d", &query);
                printf("Accessing the database.\n");
                access_func(first, query);

            } else if (strcmp(aachoice, modify) == 0) { // If user types "modify"
                char modifyInput[50];
                char* undo="undo";
                char* redo="redo";
                do{
                    printf("would you like to undo or redo?\n");
                    scanf("%49s",modifyInput);
                    if (strcmp(modifyInput, undo) == 0){
                        printf("undoing...\n");
                        if (first->next != NULL){
                            undo_ret_ = undo_function(tail,redo_first);
                            tail = undo_ret_->tail_;
                            redo_first = undo_ret_->redo_first_;
                            print_all(first,1);
                        } else {
                            printf("no more undos\n");
                        }
                        break;

                    } else if ((strcmp(modifyInput, redo) == 0)){
                        printf("redoing...\n");
                        redo_function(redo_first,first,tail);
                        print_all(first,1);
                        break;
                    }
                    else{
                        printf("please type undo or redo");
                    }
                }while (modifyInput!=undo && modifyInput!=redo);
            } 
            else{//if they type neither "add" nor "access"
                printf("please input 'modify', 'access' or 'add'.\n");
            }

        printf("Do you want to continue? (y/n): "); //prompt user to continue the loop
        scanf(" %c", &restart_answer); 

    } while (restart_answer=='y');


    print_all(first,cond);

    
    return 0;

}
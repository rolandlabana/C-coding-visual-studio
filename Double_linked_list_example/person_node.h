

#ifndef person_node_H
#define person_node_H

// Define our node to hold a name and an age
struct PersonNode {
    char *name;
    int age;
    struct PersonNode* next;
    struct PersonNode* prev;
};

#endif
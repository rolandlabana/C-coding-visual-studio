
// rol_print_functions.h
#ifndef ROL_PRINT_FUNCTIONS_H
#define ROL_PRINT_FUNCTIONS_H

struct PersonNode;  // this is a forward def of the struct to indicate it's defined elsewhere
                    // omitting this will give an error during build

void print_hello_world(int numTimes);
void printListDiagramVerticalPadding(struct PersonNode* head, struct PersonNode* tail);
void printListDiagram(struct PersonNode* head);
void printListDiagramColor(struct PersonNode* head);
void printListDiagramVertical(struct PersonNode* head);

#endif // ROL_PRINT_FUNCTIONS_H
 



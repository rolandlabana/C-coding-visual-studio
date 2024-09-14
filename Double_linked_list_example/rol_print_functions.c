// rol_print_functions.c
#include <stdio.h>
#include "rol_print_functions.h"

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

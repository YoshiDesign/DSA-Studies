#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 1024

typedef struct Node Node;           // Somewhat more readable
struct Node {

    bool isHouse;
    int  nCandy;
    struct Node *nodes[MAX_NODES];  // Note: cannot contain own type by value.

};

int main(void) {


}
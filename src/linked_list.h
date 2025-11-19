#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "pipe.h"

typedef struct Node {
    Pipe* pipe;
    struct Node* next;
} Node;

void add_end(Node** head, Node** tail, Pipe* pipe);
void remove_first(Node** head, Node** tail);

void apply_function(Node** head, Node** tail, void (*function)(Pipe* pipe));

#endif
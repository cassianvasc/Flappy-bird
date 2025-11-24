#include "linked_list.h"
#include <stdlib.h>

void add_end(Node** head, Node** tail, Pipe* pipe){
    Node* node = malloc(sizeof(Node));
    node->pipe = pipe;
    node->next = NULL;

    if (*tail){
        (*tail)->next = node;
    } else {
        *head = node;
    }   
    *tail = node;
}

void remove_first(Node** head, Node** tail){
    if (*head == NULL) return;
    Node* first = *head;
    *head = first->next;

    if (*head == NULL){
        *tail = NULL;
    }
    Pipe_free(first->pipe);
    free(first);
}

void apply_function(Node** head, Node** tail, void (*function)(Pipe* pipe)){
    Node* cur = *head;
    while (cur != NULL){
        Pipe* pipe = cur->pipe;
        function(pipe);
        cur = cur->next;
    }
}
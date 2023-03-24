//
// Created by Oguzhan TUNCER on 23.03.2023.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"

ListNode* head = NULL;

void add(char* key, int value) {
    ListNode* node = malloc(sizeof(ListNode));
    node -> key = key;
    node -> value = value;

    if (head == NULL) {
        head = node;
    }
    else {
        node -> next = head;
        head = node;
    }
}

int get(char* key) {
    ListNode* temp = head;

    while (temp -> next != NULL) {
        if (strcmp(temp -> key, key) == 0) {
            return temp -> value;
        }
        temp = temp -> next;
    }
    return -1; // If key is not found
}
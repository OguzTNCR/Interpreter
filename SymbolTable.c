//
// Created by Oguzhan TUNCER on 23.03.2023.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SymbolTable.h"

ListNode* head = NULL;

void add(char* key, long long value) {
    if (!does_exist(key)) {
        ListNode *node = malloc(sizeof(ListNode));
        node->key = key;
        node->value = value;

        if (head == NULL) {
            head = node;
        } else {
            node->next = head;
            head = node;
        }
    }
    else {
        ListNode* temp = head;
        while (temp != NULL) {
            if (strcmp(temp -> key, key) == 0) {
                temp -> value = value;
                break;
            }
            temp = temp -> next;
        }
    }
}

bool does_exist(char* key) {
    ListNode* temp = head;

    while (temp != NULL) {
        if (strcmp(temp -> key, key) == 0) {
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

long get(char* key) {
    ListNode* temp = head;

    while (temp != NULL) {
        if (strcmp(temp -> key, key) == 0) {
            return temp -> value;
        }
        temp = temp -> next;
    }
    return 0;
}
//
// Created by Oguzhan TUNCER on 23.03.2023.
//

#ifndef CMPE230_SYMBOLTABLE_H
#define CMPE230_SYMBOLTABLE_H

typedef struct ListNode{
    char* key;
    int value;
    struct ListNode* next;
}ListNode;

void add(char* key, int value);
int get(char* key);
bool does_exist(char* key);


#endif //CMPE230_SYMBOLTABLE_H

//
// Created by Oguzhan TUNCER on 23.03.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <string.h>
#include "interpreter.h"
#include "SymbolTable.h"
#include <stdbool.h>


long long interpret(ParserNode* node, bool* is_assignment) {
    if (node == NULL) {
        return 0LL;
    }

    long long left = interpret(node -> left, is_assignment);
    long long right = interpret(node -> right, is_assignment);

    if (node -> type == PARSER_STATEMENT) {
        return left;
    }
    else if (node -> token -> type == TOKEN_ASSIGN) {
        add(node -> left -> token -> value, right);
        *is_assignment = true;
        return right;
    }
    else if (node -> token -> type == TOKEN_IDENTIFIER) {
        if (does_exist(node -> token -> value)) {
            return get(node -> token -> value);
        }
        return 0;
    }
    else if (node -> token -> type == TOKEN_NUMBER) {
        return atoll(node -> token -> value);
    }
    else if (strcmp(node -> token -> value,  "+") == 0) {
        return left + right;
    }
    else if (strcmp(node -> token -> value, "-") == 0) {
        return left - right;
    }
    else if (strcmp(node -> token -> value, "*") == 0) {
        return left * right;
    }
    else if (strcmp(node -> token -> value, "&") == 0) {
        return left & right;
    }
    else if (strcmp(node -> token -> value, "|") == 0) {
        return left | right;
    }
    else if (strcmp(node -> token -> value, "xor") == 0) {
        return left ^ right;
    }
    else if (strcmp(node -> token -> value, "ls") == 0) {
        return left << right;
    }
    else if (strcmp(node -> token -> value, "rs") == 0) {
        return left >> right;
    }
    else if (strcmp(node -> token -> value, "lr") == 0) {
        return (left << right) | (left >> (64 - right));
    }
    else if (strcmp(node -> token -> value, "ls") == 0) {
        return (left >> right) | (left << (64 - right));
    }
    else if (strcmp(node -> token -> value, "not") == 0) {
        return ~left;
    }
    return 0;

}
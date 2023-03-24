//
// Created by Oguzhan TUNCER on 23.03.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <string.h>
#include "interpreter.h"

int interpret(ParserNode* node) {
    if (node == NULL) {
        return 0;
    }

    int left = interpret(node -> left);
    int right = interpret(node -> right);

    if (node -> type == PARSER_STATEMENT) {
        return left;
    }
    else if (node -> token -> type == TOKEN_NUMBER) {
        return atoi(node -> token -> value);
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
        return ~right;
    }


    return 0;
}
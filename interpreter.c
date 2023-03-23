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

    if (node -> token -> type == TOKEN_NUMBER) {
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


}
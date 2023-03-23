#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "parser.h"

int TOKEN_INDEX = 0;
bool is_not_function = false;

ParserNode* parser_statement(Token* tokens) {
    if (tokens[TOKEN_INDEX].type == TOKEN_EOL) {
        return NULL;
    }
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_STATEMENT;
    node -> left = parser_expr(tokens);
    node -> right = NULL;
    return node;
}

ParserNode* parser_expr(Token* tokens) {
    ParserNode* node = parser_term(tokens);
    if (tokens[TOKEN_INDEX].type == TOKEN_EOL) {
        return NULL;
    }
//    printf("Expr: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);
    while (tokens[TOKEN_INDEX].type == TOKEN_PLUS || tokens[TOKEN_INDEX].type == TOKEN_MINUS) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_EXPR;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_term(tokens);
        node = new_node;
    }
    return node;
}

ParserNode* parser_term(Token* tokens) {
    ParserNode* node = parser_factor(tokens);
    if (tokens[TOKEN_INDEX].type == TOKEN_EOL) {
        return NULL;
    }
//    printf("Term: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);
    while (tokens[TOKEN_INDEX].type == TOKEN_MULTIPLY) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_TERM;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_factor(tokens);
        node = new_node;
    }
    return node;
}

ParserNode* parser_factor(Token* tokens) {
    ParserNode* node = NULL;
    if (tokens[TOKEN_INDEX].type == TOKEN_EOL) {
        return NULL;
    }
//    printf("Factor: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);
    if (tokens[TOKEN_INDEX].type == TOKEN_NUMBER) {
        node = parser_number(tokens);
    } else if (tokens[TOKEN_INDEX].type == TOKEN_OPEN_PAREN) {
        TOKEN_INDEX++;
        node = parser_expr(tokens);

        if (tokens[TOKEN_INDEX].type == TOKEN_COMMA) {
            if (is_not_function) {
                printf("Error!\n");
                reset_is_not_function();
                exit(1);
            }
            TOKEN_INDEX++;
            node -> right = parser_expr(tokens);
        } else {
            node -> right = NULL;
        }
        if (tokens[TOKEN_INDEX].type == TOKEN_CLOSE_PAREN) {
            TOKEN_INDEX++;
        } else {
            printf("Error: Expected ')'\n");
        }
    } else if (tokens[TOKEN_INDEX].type == TOKEN_XOR ||
    tokens[TOKEN_INDEX].type == TOKEN_NOT ||
    tokens[TOKEN_INDEX].type == TOKEN_LS ||
    tokens[TOKEN_INDEX].type == TOKEN_RS ||
    tokens[TOKEN_INDEX].type == TOKEN_BITWISE_AND ||
    tokens[TOKEN_INDEX].type == TOKEN_BITWISE_OR ||
    tokens[TOKEN_INDEX].type == TOKEN_LR ||
    tokens[TOKEN_INDEX].type == TOKEN_RR) {
        if (tokens[TOKEN_INDEX].type == TOKEN_NOT){
            is_not_function = true;
        }
        TOKEN_INDEX++;
        node = parser_factor(tokens);
        node -> type = PARSER_FUNC;
        node -> token = &tokens[TOKEN_INDEX];
    } else {
        printf("Error!\n");
    }
    return node;
}



ParserNode* parser_number(Token* tokens) {
    ParserNode* node = malloc(sizeof(ParserNode));
//    printf("Number: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);
    node -> type = PARSER_NUMBER;
    node -> token = &tokens[TOKEN_INDEX];
    TOKEN_INDEX++;
    return node;
}

void reset_token_index() {
    TOKEN_INDEX = 0;
}

void reset_is_not_function() {
    is_not_function = false;
}



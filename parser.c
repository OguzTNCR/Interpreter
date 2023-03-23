#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "parser.h"

int TOKEN_INDEX = 0;
bool is_not_function = false;
bool is_function = false;

ParserNode* parser_statement(Token* tokens) {
    if (&tokens[TOKEN_INDEX] == TOKEN_EOL) {
        return NULL;
    }
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_STATEMENT;

    if (tokens[TOKEN_INDEX].type == TOKEN_IDENTIFIER) {
        node -> left = parser_assign_expr(tokens);
    }
    else {
        node -> left = parser_expr(tokens);
    }
    return node;
}

ParserNode* parser_assign_expr(Token* tokens) {
    printf("assign expr: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);
    ParserNode* node = parser_identifier(tokens);
    if (tokens[TOKEN_INDEX].type == TOKEN_ASSIGN) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_ASSIGN;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_expr(tokens);
        node = new_node;
    }
    return node;
}

ParserNode* parser_expr(Token* tokens) {
    if (&tokens[TOKEN_INDEX] == TOKEN_EOL) {
        return NULL;
    }
    ParserNode* node = parser_term(tokens);
    printf("Expr: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);
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
    if (&tokens[TOKEN_INDEX] == TOKEN_EOL) {
        return NULL;
    }
    ParserNode* node = parser_factor(tokens);
    printf("Term: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);
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
    if (&tokens[TOKEN_INDEX] == TOKEN_EOL) {
        return NULL;
    }
    ParserNode* node = NULL;
    printf("Factor: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);
    if (tokens[TOKEN_INDEX].type == TOKEN_NUMBER) {
        node = parser_number(tokens);
    } else if (tokens[TOKEN_INDEX].type == TOKEN_OPEN_PAREN) {
        TOKEN_INDEX++;
        node = parser_expr(tokens);

        if (is_function) {
            if (tokens[TOKEN_INDEX].type == TOKEN_COMMA) {
                if (is_not_function) {
                    printf("Error!\n");
                    reset_is_not_function();
                    exit(1);
                }
                TOKEN_INDEX++;
                node -> right = parser_expr(tokens);
            }
            reset_is_function();
        }

        if (tokens[TOKEN_INDEX].type == TOKEN_CLOSE_PAREN) {
            TOKEN_INDEX++;
        } else {
            printf("Error!\n");
        }
    } else if (tokens[TOKEN_INDEX].type == TOKEN_XOR ||
    tokens[TOKEN_INDEX].type == TOKEN_NOT ||
    tokens[TOKEN_INDEX].type == TOKEN_LS ||
    tokens[TOKEN_INDEX].type == TOKEN_RS ||
    tokens[TOKEN_INDEX].type == TOKEN_BITWISE_AND ||
    tokens[TOKEN_INDEX].type == TOKEN_BITWISE_OR ||
    tokens[TOKEN_INDEX].type == TOKEN_LR ||
    tokens[TOKEN_INDEX].type == TOKEN_RR) {
        is_function = true;
        if (tokens[TOKEN_INDEX].type == TOKEN_NOT){
            is_not_function = true;
        }
        TOKEN_INDEX++;
        node = parser_expr(tokens);
        node -> type = PARSER_FUNC;
        node -> token = &tokens[TOKEN_INDEX];
    }else {
        printf("Error!\n");
    }
    return node;
}

ParserNode* parser_identifier(Token* tokens) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_IDENTIFIER;
    node -> token = &tokens[TOKEN_INDEX];
    TOKEN_INDEX++;
    return node;
}

ParserNode* parser_number(Token* tokens) {
    ParserNode* node = malloc(sizeof(ParserNode));
    printf("Number: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);
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

void reset_is_function() {
    is_function = false;
}



#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "parser.h"

int TOKEN_INDEX = 0;
bool is_not_function = false;
bool is_function = false;
bool check_token = false;

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

ParserNode* parser_expr(Token* tokens) {
    ParserNode* node = parser_bitwise_or_expr(tokens);
    while(tokens[TOKEN_INDEX].type == TOKEN_BITWISE_OR) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_BITWISE_OR;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_bitwise_or_expr(tokens);
        node = new_node;
    }
    return node;
}

ParserNode* parser_bitwise_or_expr(Token* tokens) {
    ParserNode* node = parser_bitwise_and_expr(tokens);
    while(tokens[TOKEN_INDEX].type == TOKEN_BITWISE_AND) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_BITWISE_AND;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_bitwise_and_expr(tokens);
        node = new_node;
    }
    return node;
}

ParserNode* parser_bitwise_and_expr(Token* tokens) {
    ParserNode* node = parser_add_expr(tokens);
    while(tokens[TOKEN_INDEX].type == TOKEN_PLUS || tokens[TOKEN_INDEX].type == TOKEN_MINUS) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_ADD_EXPR;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_add_expr(tokens);
        node = new_node;
    }
    return node;
}

ParserNode* parser_add_expr(Token* tokens) {
    ParserNode* node = parser_multiply_expr(tokens);
    while(tokens[TOKEN_INDEX].type == TOKEN_MULTIPLY) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_MULTIPLY_EXPR;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_multiply_expr(tokens);
        node = new_node;
    }
    return node;
}

ParserNode* parser_multiply_expr(Token* tokens) {
    ParserNode* node = parser_func_expr(tokens);
    while(tokens[TOKEN_INDEX].type == TOKEN_MULTIPLY) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_FUNC_EXPR;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_func_expr(tokens);
        node = new_node;
    }
    return node;
}

ParserNode* parser_func_expr(Token* tokens) {
    ParserNode* node = parser_factor(tokens);

    while(
            tokens[TOKEN_INDEX].type == TOKEN_XOR ||
            tokens[TOKEN_INDEX].type == TOKEN_LS ||
            tokens[TOKEN_INDEX].type == TOKEN_RS ||
            tokens[TOKEN_INDEX].type == TOKEN_LR ||
            tokens[TOKEN_INDEX].type == TOKEN_RR ||
            tokens[TOKEN_INDEX].type == TOKEN_NOT
            ) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];


        switch (tokens[TOKEN_INDEX].type) {
            case TOKEN_XOR:
            case TOKEN_LS:
            case TOKEN_RS:
            case TOKEN_LR:
            case TOKEN_RR:
                new_node -> type = PARSER_FUNC_EXPR;
                TOKEN_INDEX++;
                token_checker(tokens, TOKEN_OPEN_PAREN);
                new_node -> right = parser_expr(tokens);
                token_checker(tokens, TOKEN_COMMA);
                new_node -> extra = parser_expr(tokens);
                token_checker(tokens, TOKEN_CLOSE_PAREN);
                break;
            case TOKEN_NOT:
                new_node -> type = PARSER_FUNC_EXPR;
                TOKEN_INDEX++;
                token_checker(tokens, TOKEN_OPEN_PAREN);
                new_node -> right = parser_expr(tokens);
                token_checker(tokens, TOKEN_CLOSE_PAREN);
                break;
            default:
                printf("Error!\n");
                exit(1);
        }

        node = new_node;
        }

    return node;
    }

ParserNode* parser_factor(Token* tokens) {
    ParserNode* node = NULL;
    switch (tokens[TOKEN_INDEX].type) {
        case TOKEN_NUMBER:
            node = parser_number(tokens);
            break;
        case TOKEN_IDENTIFIER:
            node = parser_identifier(tokens);
            break;
        case TOKEN_OPEN_PAREN:
            TOKEN_INDEX++;
            node = parser_expr(tokens);
            token_checker(tokens, TOKEN_CLOSE_PAREN);
            break;
        default:
            printf("Error!\n");
            exit(1);
    }
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

ParserNode* parser_identifier(Token* tokens) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_IDENTIFIER;
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

void token_checker(Token* tokens, TokenType token_type) {
    if (tokens[TOKEN_INDEX].type != token_type) {
        printf("Error!");
        exit(1);
    }

    TOKEN_INDEX++;
    check_token = true;
}



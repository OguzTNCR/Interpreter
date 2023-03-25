#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "parser.h"

int TOKEN_INDEX = 0;
bool is_not_function = false;
bool is_function = false;
bool check_token = false;

ParserNode* parser_statement(Token* tokens, bool* is_error) {
    if (&tokens[TOKEN_INDEX] == TOKEN_EOL) {
        return NULL;
    }
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_STATEMENT;

    if (tokens[TOKEN_INDEX].type == TOKEN_IDENTIFIER) {
        node -> left = parser_expr(tokens, is_error);
        if (tokens[TOKEN_INDEX].type == TOKEN_ASSIGN) {
            ParserNode* new_node = malloc(sizeof(ParserNode));
            new_node -> type = PARSER_ASSIGN;
            new_node -> left = node -> left;
            new_node -> token = &tokens[TOKEN_INDEX];
            TOKEN_INDEX++;
            new_node -> right = parser_expr(tokens, is_error);
            node -> left = new_node;
        }
    }
    else {
        node -> left = parser_expr(tokens, is_error);
    }
    return node;
}

ParserNode* parser_expr(Token* tokens, bool* is_error) {
    ParserNode* node = parser_bitwise_or_expr(tokens, is_error);
    while(tokens[TOKEN_INDEX].type == TOKEN_BITWISE_OR) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_BITWISE_OR;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_bitwise_or_expr(tokens, is_error);
        node = new_node;
    }
    return node;
}

ParserNode* parser_bitwise_or_expr(Token* tokens, bool* is_error) {
    ParserNode* node = parser_bitwise_and_expr(tokens, is_error);
    while(tokens[TOKEN_INDEX].type == TOKEN_BITWISE_AND) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_BITWISE_AND;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_bitwise_and_expr(tokens, is_error);
        node = new_node;
    }
    return node;
}

ParserNode* parser_bitwise_and_expr(Token* tokens, bool* is_error) {
    ParserNode* node = parser_add_expr(tokens, is_error);
    while(tokens[TOKEN_INDEX].type == TOKEN_PLUS || tokens[TOKEN_INDEX].type == TOKEN_MINUS) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_ADD_EXPR;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_add_expr(tokens, is_error);
        node = new_node;
    }
    return node;
}

ParserNode* parser_add_expr(Token* tokens, bool* is_error) {
    ParserNode* node = parser_multiply_expr(tokens, is_error);
    while(tokens[TOKEN_INDEX].type == TOKEN_MULTIPLY) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_MULTIPLY_EXPR;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_multiply_expr(tokens, is_error);
        node = new_node;
    }
    return node;
}

ParserNode* parser_multiply_expr(Token* tokens, bool* is_error) {
    ParserNode* node = parser_func_expr(tokens, is_error);
    while(tokens[TOKEN_INDEX].type == TOKEN_MULTIPLY) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> type = PARSER_MULTIPLY_EXPR;
        new_node -> left = node;
        new_node -> token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        new_node -> right = parser_func_expr(tokens, is_error);
        node = new_node;
    }
    return node;
}

ParserNode* parser_func_expr(Token* tokens, bool* is_error) {
    ParserNode* node = NULL;
    if(
            tokens[TOKEN_INDEX].type == TOKEN_XOR ||
            tokens[TOKEN_INDEX].type == TOKEN_LS ||
            tokens[TOKEN_INDEX].type == TOKEN_RS ||
            tokens[TOKEN_INDEX].type == TOKEN_LR ||
            tokens[TOKEN_INDEX].type == TOKEN_RR ||
            tokens[TOKEN_INDEX].type == TOKEN_NOT
            ) {
        ParserNode* new_node = malloc(sizeof(ParserNode));
        new_node -> token = &tokens[TOKEN_INDEX];
        new_node -> type = PARSER_FUNC_EXPR;


        switch (tokens[TOKEN_INDEX].type) {
            case TOKEN_XOR:
            case TOKEN_LS:
            case TOKEN_RS:
            case TOKEN_LR:
            case TOKEN_RR:
                new_node -> type = PARSER_FUNC_EXPR;
                TOKEN_INDEX++;
                token_checker(tokens, TOKEN_OPEN_PAREN, is_error);
                new_node -> left = parser_expr(tokens, is_error);
                token_checker(tokens, TOKEN_COMMA, is_error);
                new_node -> right = parser_expr(tokens, is_error);
                token_checker(tokens, TOKEN_CLOSE_PAREN, is_error);
                break;
            case TOKEN_NOT:
                new_node -> type = PARSER_FUNC_EXPR;
                TOKEN_INDEX++;
                token_checker(tokens, TOKEN_OPEN_PAREN, is_error);
                new_node -> left = parser_expr(tokens, is_error);
                token_checker(tokens, TOKEN_CLOSE_PAREN, is_error);
                break;
            default:
                *is_error = true;
                break;
        }

        node = new_node;
        } else {
            node = parser_factor(tokens, is_error);
        }

    return node;
    }

ParserNode* parser_factor(Token* tokens, bool* is_error) {
    ParserNode* node = NULL;
    switch (tokens[TOKEN_INDEX].type) {
        case TOKEN_NUMBER:
            node = parser_number(tokens, is_error);
            break;
        case TOKEN_IDENTIFIER:
            node = parser_identifier(tokens, is_error);
            break;
        case TOKEN_OPEN_PAREN:
            TOKEN_INDEX++;
            node = parser_expr(tokens, is_error);
            token_checker(tokens, TOKEN_CLOSE_PAREN, is_error);
            break;
        default:
            *is_error = true;
            break;
    }
    return node;
}

ParserNode* parser_number(Token* tokens, bool* is_error) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_NUMBER;
    node -> token = &tokens[TOKEN_INDEX];
    TOKEN_INDEX++;
    return node;
}

ParserNode* parser_identifier(Token* tokens, bool* is_error) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_IDENTIFIER;
    node -> token = &tokens[TOKEN_INDEX];
    TOKEN_INDEX++;
    return node;
}

//ParserNode* parser_assign_expr(Token* tokens, bool* is_error) {
//    ParserNode* node = parser_identifier(tokens, is_error);
//    if (tokens[TOKEN_INDEX].type == TOKEN_ASSIGN) {
//        ParserNode* new_node = malloc(sizeof(ParserNode));
//        new_node -> type = PARSER_ASSIGN;
//        new_node -> left = node;
//        new_node -> token = &tokens[TOKEN_INDEX];
//        TOKEN_INDEX++;
//        new_node -> right = parser_expr(tokens, is_error);
//        node = new_node;
//    }
//    return node;
//}

void reset_token_index() {
    TOKEN_INDEX = 0;
}

void token_checker(Token* tokens, TokenType token_type, bool* is_error) {
    if (tokens[TOKEN_INDEX].type != token_type) {
        *is_error = true;
    }

    TOKEN_INDEX++;
    check_token = true;
}



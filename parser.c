#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "parser.h"

// Global variables
int TOKEN_INDEX = 0;
bool is_not_function = false;
bool is_function = false;
bool check_token = false;

// Parser functions

// Statement parser
ParserNode* parser_statement(Token* tokens, bool* is_error) {
    if (&tokens[TOKEN_INDEX] == TOKEN_EOL) {
        return NULL;
    }
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_STATEMENT;

    // Check if the statement is an identifier
    if (tokens[TOKEN_INDEX].type == TOKEN_IDENTIFIER) {
        node -> left = parser_expr(tokens, is_error);

        // Check if there are consecutive identifiers
        if (tokens[TOKEN_INDEX].type == TOKEN_IDENTIFIER && tokens[TOKEN_INDEX - 1].type == TOKEN_IDENTIFIER) {
            *is_error = true;
        }
        // Check if the statement is an assignment
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

// Expression parser
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

// Bitwise or parser
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

// Bitwise and parser
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

// Add parser
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

// Multiply parser
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

// Function parser
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

// Factor parser
ParserNode* parser_factor(Token* tokens, bool* is_error) {
    ParserNode* node = NULL;
    switch (tokens[TOKEN_INDEX].type) {
        case TOKEN_NUMBER:
            node = parser_number(tokens, is_error);
            break;
        case TOKEN_IDENTIFIER:
            node = parser_identifier(tokens, is_error);

            // Check if there are consecutive identifiers
            if (tokens[TOKEN_INDEX].type == TOKEN_IDENTIFIER && tokens[TOKEN_INDEX - 1].type == TOKEN_IDENTIFIER) {
                *is_error = true;
            }
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

// Number parser
ParserNode* parser_number(Token* tokens, bool* is_error) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_NUMBER;
    node -> token = &tokens[TOKEN_INDEX];
    TOKEN_INDEX++;
    return node;
}

// Identifier parser
ParserNode* parser_identifier(Token* tokens, bool* is_error) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_IDENTIFIER;
    node -> token = &tokens[TOKEN_INDEX];
    TOKEN_INDEX++;
    return node;
}

// Reset token index
void reset_token_index() {
    TOKEN_INDEX = 0;
}

// Token checker
void token_checker(Token* tokens, TokenType token_type, bool* is_error) {
    if (tokens[TOKEN_INDEX].type != token_type) {
        *is_error = true;
    }

    TOKEN_INDEX++;
    check_token = true;
}



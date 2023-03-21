#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "parser.h"

int TOKEN_INDEX = 0;

ParserNode* parser_statement(Token* tokens) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_STATEMENT;
    node -> left = parser_expr(tokens);
    TOKEN_INDEX++;
    node -> right = parser_expr(tokens);
    return node;
}

ParserNode* parser_expr(Token* tokens) {
    printf("token_index: %d, token_type: %d, token_value: %s\n", TOKEN_INDEX, tokens[TOKEN_INDEX].type, tokens[TOKEN_INDEX].value);
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_EXPR;
    node -> left = parser_term(tokens);
    node -> token = &tokens[TOKEN_INDEX];
    while (tokens[TOKEN_INDEX].type == TOKEN_PLUS || tokens[TOKEN_INDEX].type == TOKEN_MINUS) {
        TOKEN_INDEX++;
        node -> right = parser_term(tokens);
    }
    return node;
}

ParserNode* parser_term(Token* tokens) {
    printf("token_index: %d, token_type: %d, token_value: %s\n", TOKEN_INDEX, tokens[TOKEN_INDEX].type, tokens[TOKEN_INDEX].value);
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_TERM;
    node -> left = parser_factor(tokens);
    node -> token = &tokens[TOKEN_INDEX];
    while (tokens[TOKEN_INDEX].type == TOKEN_MULTIPLY) {
        TOKEN_INDEX++;
        node -> right = parser_factor(tokens);
    }
    return node;
}

ParserNode* parser_factor(Token* tokens) {
    printf("token_index: %d, token_type: %d, token_value: %s\n", TOKEN_INDEX, tokens[TOKEN_INDEX].type, tokens[TOKEN_INDEX].value);
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_FACTOR;
    node -> token = &tokens[TOKEN_INDEX];
    if (tokens[TOKEN_INDEX].type == TOKEN_NUMBER) {
        TOKEN_INDEX++;
        node -> left = parser_number(tokens);
    }
    return node;
}

ParserNode* parser_number(Token* tokens) {
    printf("token_index: %d, token_type: %d, token_value: %s\n", TOKEN_INDEX, tokens[TOKEN_INDEX].type, tokens[TOKEN_INDEX].value);
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_NUMBER;
    node -> token = &tokens[TOKEN_INDEX];
    TOKEN_INDEX++;
    return node;
}




#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "parser.h"

ParserNode* parser_statement(Token* tokens, int* token_index) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_STATEMENT;
    node -> left = parser_expr(tokens, token_index);
    *token_index += 1;
    node -> right = parser_expr(tokens, token_index);
    return node;
}

ParserNode* parser_expr(Token* tokens, int* token_index) {
    printf("token_index: %d, token_type: %d, token_value: %s", *token_index, tokens[*token_index].type, tokens[*token_index].value);
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_EXPR;
    node -> left = parser_term(tokens, token_index);
    node -> token = &tokens[*token_index];
    while (tokens[*token_index].type == TOKEN_PLUS || tokens[*token_index].type == TOKEN_MINUS) {
        *token_index += 1;
        node -> right = parser_term(tokens, token_index);
    }
    return node;
}

ParserNode* parser_term(Token* tokens, int* token_index) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_TERM;
    node -> left = parser_factor(tokens, token_index);
    node -> token = &tokens[*token_index];
    while (tokens[*token_index].type == TOKEN_MULTIPLY) {
        *token_index += 1;
        node -> right = parser_factor(tokens, token_index);
    }
    return node;
}

ParserNode* parser_factor(Token* tokens, int* token_index) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_FACTOR;
    node -> token = &tokens[*token_index];
    if (tokens[*token_index].type == TOKEN_NUMBER) {
        *token_index += 1;
        node -> left = parser_number(tokens, token_index);
    }
    return node;
}

ParserNode* parser_number(Token* tokens, int* token_index) {
    ParserNode* node = malloc(sizeof(ParserNode));
    node -> type = PARSER_NUMBER;
    node -> token = &tokens[*token_index];
    *token_index += 1;
    return node;
}




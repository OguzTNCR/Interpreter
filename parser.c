#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "parser.h"

int TOKEN_INDEX = 0;

ParserNode* parser_statement(Token* tokens) {
    ParserNode* node = malloc(sizeof(ParserNode));
    printf("statement: %s\n", tokens[TOKEN_INDEX].value);
    node -> type = PARSER_STATEMENT;
    node -> left = parser_expr(tokens);
    node -> right = NULL;
    return node;
}

ParserNode* parser_expr(Token* tokens) {
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
    ParserNode* node = NULL;
    printf("Factor: %s, %s\n" , token_type_names[tokens[TOKEN_INDEX].type], tokens[TOKEN_INDEX].value);

    if (tokens[TOKEN_INDEX].type == TOKEN_NUMBER) {
        node = parser_number(tokens);

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

void reset_token_index() {
    TOKEN_INDEX = 0;
}



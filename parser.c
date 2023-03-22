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
    ParserNode* left = parser_term(tokens);
    while (tokens[TOKEN_INDEX].type == TOKEN_PLUS || tokens[TOKEN_INDEX].type == TOKEN_MINUS) {
        Token* op_token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        ParserNode *right = parser_term(tokens);
        left -> left = left;
        left -> right = right;
        left -> token = op_token;
        left -> type = PARSER_EXPR;
    }
    return left;
}

ParserNode* parser_term(Token* tokens) {
//    printf("token_index: %d, token_type: %d, token_value: %s\n", TOKEN_INDEX, tokens[TOKEN_INDEX].type, tokens[TOKEN_INDEX].value);
    ParserNode* left = parser_number(tokens);
    while (tokens[TOKEN_INDEX].type == TOKEN_MULTIPLY) {
        Token* op_token = &tokens[TOKEN_INDEX];
        TOKEN_INDEX++;
        ParserNode *right = parser_number(tokens);
        left -> left = left;
        left -> right = right;
        left -> token = op_token;
        left -> type = PARSER_TERM;
    }
    return left;
}

ParserNode* parser_factor(Token* tokens) {
//    printf("token_index: %d, token_type: %d, token_value: %s\n", TOKEN_INDEX, tokens[TOKEN_INDEX].type, tokens[TOKEN_INDEX].value);
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
    Token* token = &tokens[TOKEN_INDEX];
    TOKEN_INDEX++;
    ParserNode *node = malloc(sizeof(ParserNode));
    node -> type = PARSER_NUMBER;
    node -> token = token;
    return node;
}

void print_node(ParserNode* node) {
    if (node == NULL) {
        return;
    }
    printf("node_type: %d, node_token: %s\n", node -> type, node -> token -> value);
    print_node(node -> left);
    print_node(node -> right);
}




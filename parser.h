//
// Created by Samet Alan on 20.03.2023.
//

#ifndef CMPE230_PARSER_H
#define CMPE230_PARSER_H

#include "token.h"

// Parser types
typedef enum {
    PARSER_STATEMENT, // statement
    PARSER_NUMBER, // number
    PARSER_IDENTIFIER, // identifier
    PARSER_FUNC, // function
    PARSER_ASSIGN, // assignment
    PARSER_EXPR, // expression
    PARSER_TERM, // term
    PARSER_FACTOR, // factor
} ParserType;

// Parser node
typedef struct ParserNode{
    ParserType type; // type of the node
    Token* token; // token of the node
    struct ParserNode* left; // left child
    struct ParserNode* right; // right child
} ParserNode;

static const char* parser_type_names[] = {
        "PARSER_STATEMENT",
        "PARSER_NUMBER",
        "PARSER_IDENTIFIER",
        "PARSER_FUNC",
        "PARSER_ASSIGN",
        "PARSER_EXPR",
        "PARSER_TERM",
        "PARSER_FACTOR"
};

// Parser functions
ParserNode* parser_statement(Token* tokens);
ParserNode* parser_assign_expr(Token* tokens, int* token_index);
ParserNode* parser_expr(Token* tokens);
ParserNode* parser_term(Token* tokens);
ParserNode* parser_factor(Token* tokens);
ParserNode* parser_number(Token* tokens);
ParserNode* parser_identifier(Token* tokens, int* token_index);
ParserNode* parser_func(Token* tokens, int* token_index);
ParserNode* parser_add_expr(Token* tokens, int* token_index);
ParserNode* parser_mul_expr(Token* tokens, int* token_index);
void reset_token_index();

#endif //CMPE230_PARSER_H
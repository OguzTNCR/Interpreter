//
// Created by Samet Alan on 20.03.2023.
//

#ifndef CMPE230_PARSER_H
#define CMPE230_PARSER_H

#include "token.h"
#include "stdbool.h"

// Parser types
typedef enum {
    PARSER_STATEMENT, // statement
    PARSER_NUMBER, // number
    PARSER_IDENTIFIER, // identifier
    PARSER_FUNC_EXPR, // function expression
    PARSER_ASSIGN, // assignment
    PARSER_EXPR, // expression
    PARSER_FACTOR, // factor
    PARSER_BITWISE_AND, // bitwise and
    PARSER_BITWISE_OR, // bitwise or
    PARSER_ADD_EXPR, // add expression
    PARSER_MULTIPLY_EXPR, // multiply expression
} ParserType;

// Parser node
typedef struct ParserNode{
    ParserType type; // type of the node
    Token* token; // token of the node
    struct ParserNode* left; // left child
    struct ParserNode* right; // right child
    struct ParserNode* extra; // extra child
} ParserNode;

static const char* parser_type_names[] = {
        "PARSER_STATEMENT",
        "PARSER_NUMBER",
        "PARSER_IDENTIFIER",
        "PARSER_FUNC_EXPR",
        "PARSER_ASSIGN",
        "PARSER_EXPR",
        "PARSER_FACTOR",
        "PARSER_BITWISE_AND",
        "PARSER_BITWISE_OR",
        "PARSER_ADD_EXPR",
        "PARSER_MULTIPLY_EXPR"
};

// Parser functions
ParserNode* parser_statement(Token* tokens, bool* is_error);
//ParserNode* parser_assign_expr(Token* tokens, bool* is_error);
ParserNode* parser_identifier(Token* tokens, bool* is_error);
ParserNode* parser_expr(Token* tokens, bool* is_error);
ParserNode* parser_bitwise_or_expr(Token* tokens, bool* is_error);
ParserNode* parser_bitwise_and_expr(Token* tokens, bool* is_error);
ParserNode* parser_add_expr(Token* tokens, bool* is_error);
ParserNode* parser_multiply_expr(Token* tokens, bool* is_error);
ParserNode* parser_func_expr(Token* tokens, bool* is_error);
ParserNode* parser_factor(Token* tokens, bool* is_error);
ParserNode* parser_number(Token* tokens, bool* is_error);

void reset_token_index();
void token_checker(Token* tokens,TokenType type, bool* is_error);

#endif //CMPE230_PARSER_H
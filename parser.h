//
// Created by Samet Alan on 20.03.2023.
//

#ifndef CMPE230_PARSER_H
#define CMPE230_PARSER_H

#include "token.h"

typedef enum {
    PARSER_INTEGER,
    PARSER_IDENTIFIER,
    PARSER_BINARY,
    PARSER_UNARY,
    PARSER_FUNC
} ParserType;

typedef struct ParserNode{
    ParserType type;
    Token* token;
    struct ParserNode* left;
    struct ParserNode* right;
    struct ParserNode* operation;
    struct ParserNode* parameters;
} ParserNode;

ParserNode *parser_primary()

#endif //CMPE230_PARSER_H

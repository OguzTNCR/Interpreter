//
// Created by Oguzhan TUNCER on 18.03.2023.
//

#ifndef CMPE230_TOKEN_H
#define CMPE230_TOKEN_H

// Token types
typedef enum {
    TOKEN_EOL,
    TOKEN_ASSIGN,
    TOKEN_ERROR,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_BITWISE_AND,
    TOKEN_BITWISE_OR,
    TOKEN_XOR,
    TOKEN_LS,
    TOKEN_RS,
    TOKEN_LR,
    TOKEN_RR,
    TOKEN_NOT,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_COMMENT,
    TOKEN_COMMA
} TokenType;

// Token struct
typedef struct Token {
    TokenType type;
    char* value;
}Token;

static const char* token_type_names[] = {
        "TOKEN_EOL",
        "TOKEN_ASSIGN",
        "TOKEN_ERROR",
        "TOKEN_NUMBER",
        "TOKEN_IDENTIFIER",
        "TOKEN_PLUS",
        "TOKEN_MINUS",
        "TOKEN_MULTIPLY",
        "TOKEN_BITWISE_AND",
        "TOKEN_BITWISE_OR",
        "TOKEN_XOR",
        "TOKEN_LS",
        "TOKEN_RS",
        "TOKEN_LR",
        "TOKEN_RR",
        "TOKEN_NOT",
        "TOKEN_OPEN_PAREN",
        "TOKEN_CLOSE_PAREN",
        "TOKEN_COMMENT",
        "TOKEN_COMMA"
};

#endif //CMPE230_TOKEN_H

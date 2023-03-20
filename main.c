#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"



void create_token(TokenType type, char* value, int token_count, Token* tokens) {
    Token* token = malloc(sizeof(Token));
    token -> type = type;

    // token_count++
    // line++   // Add last
//    tokens = realloc(tokens, sizeof(Token) * (token_count + 1));
//    tokens[token_count] = *token;

    if (type == TOKEN_EOL) {
        token -> value = NULL;
    }
    if (type == TOKEN_PLUS || type == TOKEN_MINUS || type == TOKEN_MULTIPLY
    || type == TOKEN_OPEN_PAREN || type == TOKEN_CLOSE_PAREN || type == TOKEN_COMMA || type == TOKEN_COMMENT) {
        token -> value = malloc(2);
        token -> value[0] = *value;
        token -> value[1] = '\0';

    }
    if (type == TOKEN_NUMBER) {
        token -> value = malloc(256);
        int i = 0;
        while (isdigit(*value)) {
            token -> value[i] = *value;
            value++;
            i++;
        }
        token -> value[i] = '\0';
    }
    if (type == TOKEN_IDENTIFIER) {
        token -> value = malloc(256);
        int i = 0;
        while (isalpha(*value)) {
            token -> value[i] = *value;
            value++;
            i++;
        }
        token -> value[i] = '\0';
    }
    if (type == TOKEN_BITWISE_AND || type == TOKEN_BITWISE_OR) {
        token -> value = malloc(2);
        token -> value[0] = *value;
        token -> value[1] = '\0';
    }
    if (type == TOKEN_XOR || type == TOKEN_NOT) {
        token -> value = malloc(4);
        for (int i = 0; i < 3; i++) {
            token -> value[i] = *value;
            value++;
        }
        token -> value[1] = '\0';
    }
    if (type == TOKEN_RR || type == TOKEN_LR || type == TOKEN_LS || type == TOKEN_RS) {
        token -> value = malloc(3);
        for (int i = 0; i < 2; i++) {
            token -> value[i] = *value;
            value++;
        }
        token -> value[1] = '\0';
    }
    token_count++;
    tokens = realloc(tokens, sizeof(Token) * (token_count + 1));
    token[token_count] = *token;

}



Token* tokenize(char* line) {
    Token* tokens = NULL;
    int token_count = 0;
    while (*line != '\0') {
        while (*line == ' ') {
            line++;
        }
        if (*line == '\n') {
            Token* token = malloc(sizeof(Token));
            token -> type = TOKEN_EOL;
            line++;
            tokens = realloc(tokens, sizeof(Token) * (token_count + 1));
            tokens[token_count] = *token;
            token_count++;
            break;
        }
        if (*line == '+') {
            Token* token = malloc(sizeof(Token));
            token -> type = TOKEN_PLUS;
            token -> value = malloc(2);
            token -> value[0] = '+';
            token -> value[1] = '\0';
            line++;
            tokens = realloc(tokens, sizeof(Token) * (token_count + 1));
            tokens[token_count] = *token;
            token_count++;
        }
        else if (isdigit(*line)) {
            Token* token = malloc(sizeof(Token));
            token -> type = TOKEN_NUMBER;
            token -> value = malloc(256);
            int i = 0;
            while (isdigit(*line)) {
                token -> value[i] = *line;
                line++;
                i++;
            }
            token -> value[i] = '\0';
            tokens = realloc(tokens, sizeof(Token) * (token_count + 1));
            tokens[token_count] = *token;
            token_count++;
        }

    }
    return tokens;
}




int main() {


    while (1) {
        char line[256];
        printf(">");
        fgets(line, 256, stdin);
        Token* tokens = tokenize(line);
        for (int i = 0; tokens[i].type != 0; i++) {
            printf("type: %d, value: %s\n", tokens[i].type, tokens[i].value);
        }

    }
}

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"







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

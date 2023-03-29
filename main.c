#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "parser.h"
#include "token.h"
#include "interpreter.h"

// Global variables
int unclosed_open_paranthesis = 0;
bool is_error = false;
bool is_assignment = false;

int token_count = 0;

Token* tokenize(char* line) {
    Token* tokens = malloc(sizeof(Token));
//    int token_count = 0;
    while (*line != '\0') {
        while (*line == ' ') {
            line++;
        }
        Token* token = malloc(sizeof(Token));
        if (*line == '\n') {
            token -> type = TOKEN_EOL;
            break;
        }
        if (*line == '+') {
            token -> type = TOKEN_PLUS;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            line++;
        }
        else if (*line == '*') {
            token -> type = TOKEN_MULTIPLY;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            line++;
        }
        else if (*line == '-') {
            token -> type = TOKEN_MINUS;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            line++;
        }
        else if (*line == '|') {
            token -> type = TOKEN_BITWISE_OR;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            line++;
        }
        else if (*line == '&') {
            token -> type = TOKEN_BITWISE_AND;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            line++;
        }
        else if (*line == '=') {
            token -> type = TOKEN_ASSIGN;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            line++;
        }
        else if (isdigit(*line)) {
            token -> type = TOKEN_NUMBER;
            token -> value = malloc(256);
            int i = 0;
            while (isdigit(*line)) {
                token -> value[i] = *line;
                line++;
                i++;
            }
            token -> value[i] = '\0';
        }
        else if (*line == ',') {
            token -> type = TOKEN_COMMA;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            line++;
        }
        else if (*line == '%') {
            token -> type = TOKEN_COMMENT;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            while (*line != '\n') {
                line++;
            }
        }
        else if (*line == '(') {
            token -> type = TOKEN_OPEN_PAREN;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            unclosed_open_paranthesis++;
            line++;
        }
        else if (*line == ')') {
            if (unclosed_open_paranthesis == 0) {
                printf("Error!\n");
                exit(1);
            }
            token -> type = TOKEN_CLOSE_PAREN;
            unclosed_open_paranthesis--;
            token -> value = malloc(2);
            token -> value[0] = *line;
            token -> value[1] = '\0';
            line++;
        }
        else if (isalpha(*line)) {
            char* start = line;
            while (isalpha(*line)) {
                line++;
            }
            int length = line - start;
            char* string = malloc(length + 1);
            strncpy(string, start, length);
            if (strcmp(string, "xor") == 0) {
                token -> type = TOKEN_XOR;
                token -> value = malloc(4);
                for (int i = 0; i < 3; i++) {
                    token -> value[i] = *start;
                    start++;
                }
                token -> value[3] = '\0';
            }
            else if (strcmp(string, "not") == 0) {
                token -> type = TOKEN_NOT;
                token -> value = malloc(4);
                for (int i = 0; i < 3; i++) {
                    token -> value[i] = *start;
                    start++;
                }
                token -> value[3] = '\0';
            }
            else if (strcmp(string, "ls") == 0) {
                token -> type = TOKEN_LS;
                token -> value = malloc(3);
                for (int i = 0; i < 2; i++) {
                    token -> value[i] = *start;
                    start++;
                }
                token -> value[2] = '\0';
            }
            else if (strcmp(string, "rs") == 0) {
                token -> type = TOKEN_RS;
                token -> value = malloc(3);
                for (int i = 0; i < 2; i++) {
                    token -> value[i] = *start;
                    start++;
                }
                token -> value[2] = '\0';
            }
            else if (strcmp(string, "rr") == 0) {
                token -> type = TOKEN_RR;
                token -> value = malloc(3);
                for (int i = 0; i < 2; i++) {
                    token -> value[i] = *start;
                    start++;
                }
                token -> value[2] = '\0';
            }
            else if (strcmp(string, "lr") == 0) {
                token -> type = TOKEN_LR;
                token -> value = malloc(3);
                for (int i = 0; i < 2; i++) {
                    token -> value[i] = *start;
                    start++;
                }
                token -> value[2] = '\0';
            }
            else {
                token -> type = TOKEN_IDENTIFIER;
                token -> value = malloc(length + 1);
                for (int i = 0; i < length; i++) {
                    token -> value[i] = *start;
                    start++;
                }
                token -> value[length] = '\0';
            }
        }
        else {
            is_error = true;
            break;
        }
        if (token -> type != TOKEN_COMMENT) {
            tokens = realloc(tokens, sizeof(Token) * (token_count + 1));
            tokens[token_count] = *token;
            token_count++;
        }
//        tokens = realloc(tokens, sizeof(Token) * (token_count + 1));
//        tokens[token_count] = *token;
//        token_count++;

    }
    return tokens;
}

void free_tokens(Token* tokens) {
    for (int i = 0; i < token_count; i++) {
        free(tokens[i].value);
    }
    free(tokens);
}
void free_nodes(ParserNode* node) {
    if (node == NULL) {
        return;
    }
    free_nodes(node -> left);
    free_nodes(node -> right);
    free(node);

}

int main() {

    while (1) {
        char line[256];
        printf(">");
        if (fgets(line, 256, stdin) == NULL) {
            break;
        }

        // Tokenize the input
        Token* tokens = tokenize(line);
//        for (int i = 0; i < token_count; i++) {
//            printf("type: %d, value: %s\n", tokens[i].type, tokens[i].value);
//        }

        // Parse the tokens
        ParserNode* node = parser_statement(tokens, &is_error);

        if (token_count == 0) {
            continue;
        }

        if (token_count != get_token_index()) {
            is_error = true;
        }

        if (is_error) {
            // If there was an error, print it
            printf("Error!\n");
        }
        else {
            // Otherwise, interpret the result
            long long result = interpret(node, &is_assignment);
            if (!is_assignment) {
                // If it's not an assignment, print the result
                printf("%lli\n", result);
                free_tokens(tokens);
                free_nodes(node);

            }
        }

        // Reset the token index and flags
        reset_token_index();
        is_error = false;
        is_assignment = false;
        token_count = 0;

    }
}

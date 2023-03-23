#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"
#include "token.h"
#include "interpreter.h"

Token* tokenize(char* line) {
    Token* tokens = malloc(sizeof(Token));
    int token_count = 0;
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
            line++;
        }
        else if (*line == ')') {
            token -> type = TOKEN_CLOSE_PAREN;
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
        tokens = realloc(tokens, sizeof(Token) * (token_count + 1));
        tokens[token_count] = *token;
        token_count++;

    }
    return tokens;
}

typedef struct {
    Token* token;
}NumNode;

typedef struct {
    struct OpNode* left_node;
    struct NumNode* right_node;
    Token* token;
}OpNode;

// Function Node struct needs to be implemented



//NumNode* factor(Token* tokens) {
//    NumNode* node = malloc(sizeof(NumNode));
//    if (tokens[TOKEN_INDEX].type == TOKEN_NUMBER) {
//        node -> token = &tokens[TOKEN_INDEX];
//        TOKEN_INDEX++;
//        return node;
//    }
//}
//
//OpNode* term(Token* tokens) {
//    OpNode* node = malloc(sizeof(OpNode));
//    node -> left_node = factor(&tokens[TOKEN_INDEX]);
//    while (tokens[TOKEN_INDEX].type == TOKEN_MULTIPLY) {
//        node -> token = &tokens[TOKEN_INDEX];
//        node -> right_node = factor(&tokens[TOKEN_INDEX]);
//        TOKEN_INDEX++;
//    }
//    return node;
//}
//
//OpNode* expr(Token* tokens) {
//    OpNode* node = malloc(sizeof(OpNode));
//    node -> left_node = term(tokens);
//    while (tokens[TOKEN_INDEX].type == TOKEN_PLUS || tokens[TOKEN_INDEX].type == TOKEN_MINUS) {
//        node -> token = &tokens[TOKEN_INDEX];
//        node -> right_node = term(&tokens[TOKEN_INDEX]);
//        TOKEN_INDEX++;
//    }
//    return node;
//}




//OpNode* parse_multiple(Token* tokens) {
//    OpNode* node = malloc(sizeof(OpNode));
//    node -> token = &tokens[TOKEN_INDEX];
//    while (tokens[TOKEN_INDEX].type == TOKEN_MULTIPLY) {
//        TOKEN_INDEX++;
//
//        OpNode* right_node = malloc(sizeof(OpNode));
//        right_node -> token = &tokens[TOKEN_INDEX];
//        node -> left_node  = node;
//        node -> right_node = right_node;
//
//    }
//    return node;
//
//}
//OpNode* parse_add(Token* tokens) {
//    OpNode *node = parse_multiple(tokens);
//    while (tokens[TOKEN_INDEX].type == TOKEN_PLUS || tokens[TOKEN_INDEX].type == TOKEN_MINUS) {
//        TOKEN_INDEX++;
//
//        OpNode* right_node = parse_multiple(tokens);
//        node -> left_node  = node;
//        node -> right_node = right_node;
//
//    }
//    return node;
//
//}

//OpNode* create_node(Token* token, OpNode* left_node, OpNode* right_node) {
//    OpNode* node = malloc(sizeof(OpNode));
//    node -> token = token;
//    node -> left_node = left_node;
//    node -> right_node = right_node;
//    return node;
//}

void tree_print(ParserNode* node) {
    if (node == NULL) {
        return;
    }
    printf("%s\n", node -> token -> value);
    tree_print(node -> left);
    tree_print(node -> right);

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

        ParserNode* node = parser_statement(tokens);
//        tree_print(node);
        printf("%d\n", interpret(node));
        reset_token_index();

//        tree_print(node);

    }
}

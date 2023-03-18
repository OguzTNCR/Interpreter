#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct  {
    int type;
    char* value;
}Token;

Token* tokenize(char* line) {
    int type = 0;
    char* start = line;
    while (*line == ' ') {   // skipping whitespaces
        line ++;
        if (*line == '\0') {   // end of line
            return NULL;
        }
    }
    if (*line == '+') {
        type = 2;
        line++;
    }
    else if (isdigit(*line)) {
        type = 1;
        *start = *line;
        while (isdigit(*line)) {
            line++;
        }
    }


    Token* token = malloc(sizeof(Token));
    token -> type = type;
    strncpy(token -> value, start, line - start);
    return token;



}


Token* next_token(char* input) {
    // Skip whitespace
    while (isspace(*input)) {
        input++;
    }

    // Identify token type
    int type = 0;
    char* start = input;
    if (isdigit(*input)) {
        type = 1;
        while (isdigit(*input)) {
            input++;
        }
    }
    else if (*input == '+') {
        type = 2;
        input++;
    }



    // Create token
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->value = strndup(start, input - start);
    return token;
}




int main() {


    while (1) {
        char *line;

        printf(">");
        fgets(line, 256, stdin);
        Token *token;
        while (next_token(line) != NULL) {
            token = next_token(line);
            printf("type=%d, value=%s\n", token->type, token->value);
            line += strlen(token->value);
            free(token->value);
            free(token);
        }

//        Token* token = next_token(line);
//        printf("type: %d, value: %s", token -> type, token -> value);


    }
}

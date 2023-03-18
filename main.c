#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct  {
    int type;
    char value[];
}Token;

Token* tokenize(char* line) {
    int type;
    char* start = line;
    while (*line == ' ') {   // skipping whitespaces
        line ++;
        if (*line == '\0') {   // end of line
            break;
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


int main() {


    while (1) {
        char line[256];

        printf(">");
        fgets(line, 256, stdin);
        Token *token = tokenize(line);
        printf("type = %d : value %s\n", token -> type, token -> value);

    }
}

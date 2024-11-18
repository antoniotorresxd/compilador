#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

int main() {
    FILE *file = fopen("archivo.c", "r");

    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    Token tokens[100];
    int token_count = 0;

    // Tokenizar el archivo
    while (1) {
        Token token = get_next_token(file);
        if (token.type == TOKEN_END) {
            break;
        }
        tokens[token_count++] = token;

        // Imprimir el token para depuración
        printf("Token: %s, Type: %d\n", token.value, token.type);
    }

    fclose(file);

    // Crear el parser
    Parser *parser = create_parser(tokens, token_count);

    // Intentar analizar una declaración
    if (parse_declaration(parser)) {
        printf("Declaration parsed successfully\n");
    } else {
        printf("Error parsing declaration\n");
    }

    // Liberar memoria
    free(parser);
    return 0;
} // MAIN.C


 
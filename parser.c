#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// Crear un parser
Parser *create_parser(Token *tokens, int size) {
    Parser *parser = (Parser *)malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->position = 0;
    parser->size = size;
    return parser;
}

// Obtener el token actual
Token current_token(Parser *parser) {
    if (parser->position < parser->size) {
        return parser->tokens[parser->position];
    }
    Token end_token = {TOKEN_END, ""}; // Token de fin
    return end_token;
}

// Avanzar al siguiente token
void advance(Parser *parser) {
    if (parser->position < parser->size) {
        parser->position++;
    }
}

// Función para analizar declaraciones
int parse_declaration(Parser *parser) {
    Token token = current_token(parser);

    // Imprimir el token actual para depuración
    printf("Parsing token: %s, Type: %d\n", token.value, token.type);

    // Si es una directiva del preprocesador, la saltamos
    if (token.type == TOKEN_KEYWORD && strcmp(token.value, "#include") == 0) {
        advance(parser);  // Consumir '#include'
        return 1;  // Continuar sin procesar la declaración
    }

    // Revisar si la palabra clave es 'int'
    if (token.type == TOKEN_KEYWORD && strcmp(token.value, "int") == 0) {
        advance(parser);  // Consumir 'int'
        printf("After 'int', token: %s, Type: %d\n", current_token(parser).value, current_token(parser).type);

        token = current_token(parser);
        if (token.type == TOKEN_IDENTIFIER) {
            advance(parser);  // Consumir el nombre de la variable
            printf("After identifier, token: %s, Type: %d\n", current_token(parser).value, current_token(parser).type);

            token = current_token(parser);
            if (token.type == TOKEN_OPERATOR && strcmp(token.value, "=") == 0) {
                advance(parser);  // Consumir '='
                printf("After '=', token: %s, Type: %d\n", current_token(parser).value, current_token(parser).type);

                token = current_token(parser);
                if (token.type == TOKEN_NUMBER) {
                    advance(parser);  // Consumir el número
                    printf("After number, token: %s, Type: %d\n", current_token(parser).value, current_token(parser).type);

                    token = current_token(parser);
                    if (token.type == TOKEN_UNKNOWN && strcmp(token.value, ";") == 0) {
                        advance(parser);  // Consumir punto y coma
                        return 1;  // Parseo exitoso
                    } else {
                        printf("Expected ';' but got %s\n", token.value);
                    }
                } else {
                    printf("Expected number but got %s\n", token.value);
                }
            } else {
                printf("Expected '=' but got %s\n", token.value);
            }
        } else {
            printf("Expected identifier but got %s\n", token.value);
        }
    }

    return 0;  // Error en el parseo
} // PARCER.H



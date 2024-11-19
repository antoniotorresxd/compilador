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

// revisar el if
int parse_if_statement(Parser *parser) {
    Token token = current_token(parser);

    if (token.type == TOKEN_KEYWORD && strcmp(token.value, "if") == 0) {
        advance(parser);  // Consumir 'if'
        
        token = current_token(parser);
        if (token.type == TOKEN_LPAREN) {
            advance(parser);  // Consumir '('

            // Aquí debes analizar la expresión dentro del if
            token = current_token(parser);
            if (token.type == TOKEN_IDENTIFIER || token.type == TOKEN_NUMBER) {
                advance(parser);  // Consumir la identificación o número
            } else {
                printf("Error: Se esperaba una expresión válida en 'if'\n");
                return 0;  // Error
            }

            token = current_token(parser);
            if (token.type == TOKEN_RPAREN) {
                advance(parser);  // Consumir ')'
            } else {
                printf("Error: Se esperaba ')' después de la expresión en 'if'\n");
                return 0;  // Error
            }

            token = current_token(parser);
            if (token.type == TOKEN_LBRACE) {  // Verifica que haya una '{'
                advance(parser);  // Consumir '{'
                return 1;  // Parseo exitoso
            } else {
                printf("Error: Se esperaba '{' después de la condición en 'if'\n");
                return 0;  // Error
            }
        } else {
            printf("Error: Se esperaba '(' después de 'if'\n");
            return 0;  // Error
        }
    }
    return 0;  // No es una instrucción if
}

// revisar el for
int parse_for_statement(Parser *parser) {
    Token token = current_token(parser);

    if (token.type == TOKEN_KEYWORD && strcmp(token.value, "for") == 0) {
        advance(parser);  // Consumir 'for'
        
        token = current_token(parser);
        if (token.type == TOKEN_LPAREN) {
            advance(parser);  // Consumir '('

            // Aquí analizamos la inicialización, condición y la actualización
            // Para simplificar, asumimos que hay una expresión simple
            token = current_token(parser);
            if (token.type == TOKEN_IDENTIFIER) { // Ejemplo simplificado
                advance(parser);  // Consumir la identificación
            } else {
                printf("Error: Se esperaba una expresión válida en 'for'\n");
                return 0;  // Error
            }

            // Manejar el siguiente token: condición
            token = current_token(parser);
            if (token.type == TOKEN_SEMICOLON) {
                advance(parser);  // Consumir ';'
                // Manejar expresión de condición aquí (simplificamos)
            }

            // Manejar el siguiente token: actualización
            token = current_token(parser);
            if (token.type == TOKEN_RPAREN) {
                advance(parser);  // Consumir ')'
                return 1;  // Parseo exitoso
            } else {
                printf("Error: Se esperaba ')' después de la expresión en 'for'\n");
                return 0;  // Error
            }
        } else {
            printf("Error: Se esperaba '(' después de 'for'\n");
            return 0;  // Error
        }
    }
    return 0;  // No es una instrucción for
}

int parse_printf_statement(Parser *parser) {
    Token token = current_token(parser);

    if (token.type == TOKEN_IDENTIFIER && strcmp(token.value, "printf") == 0) {
        advance(parser);  // Consumir 'printf'

        token = current_token(parser);
        if (token.type == TOKEN_LPAREN) {
            advance(parser);  // Consumir '('

            token = current_token(parser);
            if (token.type == TOKEN_STRING) { // Validar que el primer argumento sea una cadena
                advance(parser);  // Consumir la cadena
            } else {
                printf("Error: Se esperaba una cadena para printf\n");
                return 0; // Error
            }

            token = current_token(parser);
            if (token.type == TOKEN_RPAREN) {
                advance(parser);  // Consumir ')'
                token = current_token(parser);
                if (token.type == TOKEN_UNKNOWN && strcmp(token.value, ";") == 0) {
                    advance(parser);  // Consumir ';'
                    return 1;  // Parseo exitoso
                } else {
                    printf("Error: Se esperaba ';' después de printf\n");
                    return 0; // Error
                }
            } else {
                printf("Error: Se esperaba ')' en printf\n");
                return 0; // Error
            }
        } else {
            printf("Error: Se esperaba '(' en printf\n");
            return 0; // Error
        }
    }

    return 0; // No es una llamada a printf
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

    // Si es un 'if', llamamos a parse_if_statement
    if (token.type == TOKEN_KEYWORD && strcmp(token.value, "if") == 0) {
        int result = parse_if_statement(parser);
        if (!result) {
            printf("Error: Parsing failed for 'if' statement.\n");
        }
        return result;  // Retorna el resultado del parseo del if
    }

    // Si es un 'for', llamamos a parse_for_statement
    if (token.type == TOKEN_KEYWORD && strcmp(token.value, "for") == 0) {
        return parse_for_statement(parser);
    }

    // Si es una llamada a printf, llamamos a parse_printf_statement
    if (token.type == TOKEN_IDENTIFIER && strcmp(token.value, "printf") == 0) {
        return parse_printf_statement(parser);
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
                        printf("Error: Se esperaba ';' pero se obtuvo %s\n", token.value);
                    }
                } else {
                    printf("Error: Se esperaba un número pero se obtuvo %s\n", token.value);
                }
            } else {
                printf("Error: Se esperaba '=' pero se obtuvo %s\n", token.value);
            }
        } else {
            printf("Error: Se esperaba un identificador pero se obtuvo %s\n", token.value);
        }
    }

    return 0;  // Error en el parseo
} // PARCER.C



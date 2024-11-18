#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Estructura del parser
typedef struct {
    Token *tokens;
    int position;
    int size;
} Parser;

// Crear un parser
Parser *create_parser(Token *tokens, int size);

// Obtener el token actual
Token current_token(Parser *parser);

// Avanzar al siguiente token
void advance(Parser *parser);

// Función para analizar declaraciones
int parse_declaration(Parser *parser);

#endif // PARSER.H

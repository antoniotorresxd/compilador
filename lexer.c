#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

#define NUM_RESERVED_WORDS 20

// Lista de palabras clave
const char *reserved_words[] = {
    "int", "for", "case", "break", "switch", "const", 
    "float", "char", "if", "else", "do", "while", 
    "struct", "typedef", "printf", "return0", "return1", 
    "<stdio.h>", "#include", "main"
};

// Función para verificar si una palabra es una palabra clave
int is_keyword(const char *value) {
    for (int i = 0; i < NUM_RESERVED_WORDS; i++) {
        if (strcmp(value, reserved_words[i]) == 0) {
            return 1; // Es una palabra clave
        }
    }
    return 0; // No es una palabra clave
}

// Función para verificar si un carácter es un operador
int is_operator(char c) {
    return c == '=' || c == '+' || c == '-' || c == '*' || c == '/';
}

// Función para obtener el siguiente token del archivo
Token get_next_token(FILE *file) {
    char c;
    Token token;
    int i = 0;

    token.value[0] = '\0';

    while ((c = fgetc(file)) != EOF && (isspace(c) || c == '\n' || c == '\r')) {
        continue;
    }

    if (c == EOF) {
        token.type = TOKEN_END;
        token.value[0] = '\0';
        return token;
    }

    if (c == '#') {
        // Token para directivas del preprocesador (ej. #include)
        token.type = TOKEN_KEYWORD;
        token.value[i++] = c; // Guardar el '#'
        
        // Leer la siguiente palabra clave (por ejemplo 'include')
        while (isalnum(c = fgetc(file)) || c == '_') {
            token.value[i++] = c;
        }
        token.value[i] = '\0';
        ungetc(c, file);

        // Verificar si es una palabra clave preprocesador (como #include)
        return token;
    }

    if (isdigit(c)) {
        token.type = TOKEN_NUMBER;
        token.value[i++] = c;
        while (isdigit(c = fgetc(file)) || c == '.') {
            token.value[i++] = c;
        }
        token.value[i] = '\0';
        ungetc(c, file);
        return token;
    }

    if (isalpha(c)) {
        token.type = TOKEN_IDENTIFIER;
        token.value[i++] = c;
        while (isalnum(c = fgetc(file)) || c == '_') {
            token.value[i++] = c;
        }
        token.value[i] = '\0';
        ungetc(c, file);

        // Verificamos si es una palabra clave
        if (is_keyword(token.value)) {
            token.type = TOKEN_KEYWORD;
        }
        return token;
    }

    if (is_operator(c)) {
        token.type = TOKEN_OPERATOR;
        token.value[i++] = c;
        token.value[i] = '\0';
        return token;
    }

    if (c == ';') {
        token.type = TOKEN_SEMICOLON;
        token.value[i++] = c;
        token.value[i] = '\0';
        return token;
    }

    if (c == '(') {
        token.type = TOKEN_LPAREN; // Paréntesis izquierdo
        token.value[i++] = c;
        token.value[i] = '\0';
        return token;
    }

    if (c == ')') {
        token.type = TOKEN_RPAREN; // Paréntesis derecho
        token.value[i++] = c;
        token.value[i] = '\0';
        return token;
    }

    token.type = TOKEN_UNKNOWN;
    token.value[i++] = c;
    token.value[i] = '\0';
    return token;
} // LEXER.C


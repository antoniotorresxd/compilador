// ANALIZADOR LEXICO

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100

// Palabras reservadas
const char *reserved_words[] = {
    "int", "for", "case", "break", "switch", "const", 
    "float", "char", "if", "else", "do", "while", 
    "struct", "typedef"
};

// Operadores
const char *operators[] = {
    "+", "=", "-", "*", "/", ">", "<", ">=", "<=", "&&", "||"
};

// Símbolos especiales
const char *symbols[] = {
    "(", ")", ":", ";", ".", ","
};

// Función para verificar si una cadena es una palabra reservada
int is_reserved(const char *token) {
    for (int i = 0; i < sizeof(reserved_words) / sizeof(reserved_words[0]); i++) {
        if (strcmp(token, reserved_words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Función para verificar si una cadena es un operador
int is_operator(const char *token) {
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(token, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Función para verificar si un token es un símbolo especial
int is_symbol(const char *token) {
    for (int i = 0; i < sizeof(symbols) / sizeof(symbols[0]); i++) {
        if (strcmp(token, symbols[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Función para verificar si un token es un número
int is_number(const char *token) {
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i])) {
            return 0; // Solo puede contener dígitos
        }
    }
    return 1;
}

// Función para verificar si un token es un identificador válido
int is_identifier(const char *token) {
    if (!isalpha(token[0]) && token[0] != '_') {
        return 0; // No puede empezar con un número ni ser un símbolo
    }
    for (int i = 1; token[i] != '\0'; i++) {
        if (!isalnum(token[i]) && token[i] != '_') {
            return 0; // Solo puede contener letras, números y guiones bajos
        }
    }
    return 1;
}

// Función para analizar la cadena
void analyze_string(const char *input) {
    char token[MAX_TOKEN_LENGTH];
    int index = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        // Si es un espacio, separamos el token
        if (isspace(input[i])) {
            if (index > 0) {
                token[index] = '\0'; // Terminar el token
                if (is_reserved(token)) {
                    printf("'%s' es una palabra reservada.\n", token);
                } else if (is_identifier(token)) {
                    printf("'%s' es un identificador.\n", token);
                } else if (is_number(token)) {
                    printf("'%s' es un numero.\n", token);
                } else {
                    printf("'%s' es un token no válido.\n", token);
                }
                index = 0; // Reiniciar el índice
            }
            continue;
        }

        // Manejo de operadores y símbolos especiales
        if (strchr("+-*/=><", input[i]) || strchr("();:.,", input[i])) {
            if (index > 0) {
                token[index] = '\0';
                if (is_reserved(token)) {
                    printf("'%s' es una palabra reservada.\n", token);
                } else if (is_identifier(token)) {
                    printf("'%s' es un identificador.\n", token);
                } else if (is_number(token)) {
                    printf("'%s' es un numero.\n", token);
                } else {
                    printf("'%s' es un token no valido.\n", token);
                }
                index = 0; // Reiniciar el índice
            }

            // Si es un operador o símbolo, imprimirlo
            token[index++] = input[i]; // Guardar el operador/símbolo
            token[index] = '\0';

            if (is_operator(token)) {
                printf("'%s' es un operador.\n", token);
            } else if (is_symbol(token)) {
                printf("'%s' es un simbolo especial.\n", token);
            }

            index = 0; // Reiniciar el índice
            continue;
        }

        // Guardar el token
        token[index++] = input[i];
    }

    // Comprobar el último token si existe
    if (index > 0) {
        token[index] = '\0';
        if (is_reserved(token)) {
            printf("'%s' es una palabra reservada.\n", token);
        } else if (is_identifier(token)) {
            printf("'%s' es un identificador.\n", token);
        } else if (is_number(token)) {
            printf("'%s' es un numero.\n", token);
        } else {
            printf("'%s' es un token no valido.\n", token);
        }
    }
}

int main() {
    char input[256] = "+a/bfor-8+b-+/*int8(;9intento)";
    analyze_string(input);
    return 0;
}

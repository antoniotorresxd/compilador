#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_FILE_SIZE 1024

// Palabras reservadas
const char *reserved_words[] = {
    "int", "for", "case", "break", "switch", "const", 
    "float", "char", "if", "else", "do", "while", 
    "struct", "typedef", "printf", "return0", "return1", 
    "<stdio.h>", "#include", "main"
};

// Operadores
const char *operators[] = {
    "+", "=", "-", "*", "/", ">", "<", ">=", "<=", "&&", "||", "==",
};

// Símbolos especiales
const char *symbols[] = {
    "(", ")", ":", ";", ".", ",", "\'", "\"", "{", "}", "[", "]"
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

// Función para analizar la cadena y formatear la salida
void analyze_string(const char *input) {
    char token[MAX_TOKEN_LENGTH];
    int index = 0;
    int in_string = 0; // Indicador para cadenas

    // Imprimir el encabezado de la tabla
    printf("\n%-20s | %-20s\n", "Lexema", "Token");
    printf("--------------------------------------------\n");

    for (int i = 0; input[i] != '\0'; i++) {
        // Manejar cadenas entre comillas dobles y simples
        if (input[i] == '"' || input[i] == '\'') {
            if (in_string) {
                // Si ya estamos dentro de una cadena, la cerramos
                token[index++] = input[i];
                token[index] = '\0';
                printf("%-20s | %-20s\n", token, "Cadena");
                in_string = 0;
                index = 0;
            } else {
                // Si encontramos el inicio de una cadena
                in_string = 1;
                token[index++] = input[i];
            }
            continue;
        }

        // Si estamos dentro de una cadena, seguimos capturando caracteres
        if (in_string) {
            token[index++] = input[i];
            continue;
        }

        // Si es un espacio, separamos el token
        if (isspace(input[i])) {
            if (index > 0) {
                token[index] = '\0'; // Terminar el token
                if (is_reserved(token)) {
                    printf("%-20s | %-20s\n", token, "Palabra Reservada");
                } else if (is_identifier(token)) {
                    printf("%-20s | %-20s\n", token, "Identificador");
                } else if (is_number(token)) {
                    printf("%-20s | %-20s\n", token, "Numero");
                } else {
                    printf("%-20s | %-20s\n", token, "Token no valido");
                }
                index = 0; // Reiniciar el índice
            }
            continue;
        }

        // Manejo de operadores y símbolos especiales
        if (strchr("+-*/=><(){}[]:;.,", input[i])) {
            if (index > 0) {
                token[index] = '\0';
                if (is_reserved(token)) {
                    printf("%-20s | %-20s\n", token, "Palabra Reservada");
                } else if (is_identifier(token)) {
                    printf("%-20s | %-20s\n", token, "Identificador");
                } else if (is_number(token)) {
                    printf("%-20s | %-20s\n", token, "Numero");
                } else {
                    printf("%-20s | %-20s\n", token, "Token no valido");
                }
                index = 0; // Reiniciar el índice
            }

            // Si es un operador o símbolo, imprimirlo
            token[index++] = input[i]; // Guardar el operador/símbolo
            token[index] = '\0';

            if (is_operator(token)) {
                printf("%-20s | %-20s\n", token, "Operador");
            } else if (is_symbol(token)) {
                printf("%-20s | %-20s\n", token, "Simbolo Especial");
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
            printf("%-20s | %-20s\n", token, "Palabra Reservada");
        } else if (is_identifier(token)) {
            printf("%-20s | %-20s\n", token, "Identificador");
        } else if (is_number(token)) {
            printf("%-20s | %-20s\n", token, "Numero");
        } else {
            printf("%-20s | %-20s\n", token, "Token no valido");
        }
    }
}

void clear_file(char input[MAX_FILE_SIZE]){
    FILE *archivo;
    char caracter;
    int index = 0;

    archivo = fopen("archivo.c","r");

    if (archivo == NULL){
        printf("\nError de apertura del archivo. \n\n");
        return;
    }

    while ((caracter = fgetc(archivo)) != EOF && index < MAX_FILE_SIZE - 1) {
        if (!isspace(caracter)) { // Ignorar espacios y tabulaciones
            input[index++] = caracter;
        }
    }
    input[index] = '\0';

    fclose(archivo);

}


int main() {

    char input[MAX_FILE_SIZE] = {0};  
    int opt;

    printf("1.- Analizador con una cadena \n");
    printf("2.- Analizador con archivo .c \n");
    printf("3.- Salir \n");
    printf("Ingresa una opcion: ");
    
    scanf("%i", &opt);

    switch (opt){

        case 1:
            strcpy(input, "+a/for-8+b-+/*int8(intento-9)");
        break;

        case 2:
            clear_file(input);
        break;
    
    default:
        break;
    }
    printf("\nCadena: %s\n", input);

    analyze_string(input);
    return 0;
}

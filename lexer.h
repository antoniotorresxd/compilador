#ifndef LEXER_H
#define LEXER_H

// Definición de los tipos de token
typedef enum {
    TOKEN_END,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_SEMICOLON,
    TOKEN_LPAREN,  
    TOKEN_RPAREN,    
    TOKEN_UNKNOWN,
    TOKEN_STRING,
    TOKEN_DATA_TYPE,
    TOKEN_ASSIGN,
} TokenType;

// Estructura de un token
typedef struct {
    TokenType type;
    char value[100];
} Token;

// Prototipos de funciones
extern const char *reserved_words[];
extern int is_keyword(const char *value);
Token get_next_token(FILE *file);
int is_data_type(const char *str);

#endif // LEXER.H

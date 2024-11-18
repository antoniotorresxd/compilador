
# **C Lexer and Parser**

Este proyecto implementa un analizador léxico (lexer) y un analizador sintáctico (parser) para un lenguaje de programación estilo C. Permite identificar y clasificar tokens en un archivo de código fuente y analizar su validez sintáctica.

## **Características principales**

- **Lexer:**  
  Extrae tokens de un archivo de entrada y clasifica su tipo (identificadores, palabras clave, operadores, etc.).
  
- **Parser:**  
  Verifica la sintaxis del archivo de código fuente utilizando los tokens generados por el lexer.

- **Soporte para palabras clave y tipos de datos:**  
  Reconoce palabras clave comunes del lenguaje C como `int`, `float`, `if`, `return`, entre otras.

## **Requisitos del sistema**

- Compilador C (compatible con C99 o superior).
- Sistema operativo: Linux, macOS, o Windows con herramientas de desarrollo configuradas.
- `Make` (opcional, para compilar el proyecto fácilmente).

## **Estructura del proyecto**

```
.
├── lexer.h        # Declaraciones y tipos para el lexer
├── lexer.c        # Implementación del lexer
├── parser.h       # Declaraciones y tipos para el parser
├── parser.c       # Implementación del parser
├── main.c         # Archivo principal que ejecuta el lexer y parser
└── README.md      # Documentación del proyecto
```

## **Cómo compilar el proyecto**


Esto generará un ejecutable llamado `analyzer`.

### **Manual**
Si prefieres compilar manualmente:

```bash
gcc -o analyzer lexer.c parser.c main.c
```

## **Cómo usarlo**

1. Crea o utiliza un archivo de código fuente en C. Por ejemplo, `archivo.c`:
    ```c
    #include <stdio.h>

    int main() {
        printf("Hola Mundo");
        return 0;
    }
    ```

2. Ejecuta el analizador sobre el archivo:
    ```bash
    ./analyzer archivo.c
    ```

3. El programa mostrará los tokens identificados y verificará la validez de las declaraciones y bloques.

## **Ejemplo de salida**

Para el archivo `archivo.c` proporcionado, el programa podría generar una salida como esta:

```
Token: #include, Type: TOKEN_KEYWORD
Token: <, Type: TOKEN_OPERATOR
Token: stdio, Type: TOKEN_IDENTIFIER
Token: ., Type: TOKEN_OPERATOR
Token: h, Type: TOKEN_IDENTIFIER
Token: >, Type: TOKEN_OPERATOR
Token: int, Type: TOKEN_KEYWORD
Token: main, Type: TOKEN_IDENTIFIER
Token: (, Type: TOKEN_LPAREN
Token: ), Type: TOKEN_RPAREN
Token: {, Type: TOKEN_OPERATOR
Token: printf, Type: TOKEN_IDENTIFIER
Token: (, Type: TOKEN_LPAREN
Token: "Hola Mundo", Type: TOKEN_STRING
Token: ), Type: TOKEN_RPAREN
Token: ;, Type: TOKEN_SEMICOLON
Token: return, Type: TOKEN_KEYWORD
Token: 0, Type: TOKEN_NUMBER
Token: ;, Type: TOKEN_SEMICOLON
Token: }, Type: TOKEN_OPERATOR
Declaration parsed successfully
```

Además, el parser verificará las declaraciones y bloques y generará mensajes de error si encuentra problemas.

## **Problemas comunes**

1. **Error: `conflicting types for 'Token'`:**
   - Asegúrate de que solo se define `Token` en `lexer.h` y que otros archivos simplemente incluyen `lexer.h`.

2. **Error: `invalid initializer`:**
   - Verifica que la función `get_next_token` devuelve correctamente un objeto de tipo `Token`.

3. **Lexer no reconoce palabras clave personalizadas:**
   - Añade las palabras clave necesarias en la lista `reserved_words` en `lexer.c`.

## **Mejoras futuras**

- Implementar análisis semántico.
- Añadir soporte para más operadores y estructuras de control.
- Generar un árbol de sintaxis abstracta (AST) para optimizar el análisis.



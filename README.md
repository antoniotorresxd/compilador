# Analizador Léxico en C

Este proyecto es un analizador léxico simple escrito en C que puede analizar cadenas y archivos de código fuente en C para identificar palabras reservadas, identificadores, números, operadores y símbolos especiales.

## Estructura del Código

El código se divide en varias secciones:

1. **Definiciones y Bibliotecas**
   - Se definen constantes como `MAX_TOKEN_LENGTH` y `MAX_FILE_SIZE`, que determinan el tamaño máximo de los tokens y del archivo que se puede analizar.
   - Se incluyen las bibliotecas necesarias: `stdio.h`, `string.h` y `ctype.h`.

2. **Palabras Reservadas y Tokens**
   - Se definen listas de palabras reservadas, operadores y símbolos especiales que el analizador utilizará para clasificar los tokens en el código.

3. **Funciones de Verificación**
   - **`is_reserved`**: Verifica si un token es una palabra reservada.
   - **`is_operator`**: Verifica si un token es un operador.
   - **`is_symbol`**: Verifica si un token es un símbolo especial.
   - **`is_number`**: Verifica si un token es un número.
   - **`is_identifier`**: Verifica si un token es un identificador válido.

4. **Función Principal**
   - **`analyze_string`**: Analiza la cadena de entrada y clasifica cada token. Imprime una tabla con los tokens y su tipo correspondiente (palabra reservada, identificador, número, operador, símbolo especial).

5. **Lectura de Archivos**
   - **`clear_file`**: Lee un archivo de código fuente en C (`archivo.c`), ignorando espacios y tabulaciones, y almacena el contenido en una cadena.

6. **Función `main`**
   - Permite al usuario elegir entre analizar una cadena predefinida o un archivo de código fuente.
   - Dependiendo de la opción elegida, se llama a `analyze_string` para procesar la cadena o el contenido del archivo.

## Cómo Compilar y Ejecutar

1. **Compilación**
   Usa un compilador de C (como `gcc`) para compilar el código:

   ```bash
   gcc -o analizador analizador.c

## Ejemplo de salida**

    Cadena: +a/for-8+b-+/*int8(intento-9)
    Lexema              | Token               
    --------------------------------------------
    +                   | Operador           
    a                   | Identificador             
    for                 | Palabra Reservada  


### Notas Adicionales
- Asegúrate de crear un archivo llamado `archivo.c` en el mismo directorio donde se ejecuta tu programa si planeas usar la opción 2 para analizar un archivo.
- Puedes personalizar el contenido y el estilo según sea necesario para adaptarlo a tu proyecto.

#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <stdlib.h>

/* ever macro */
#define forever for(;;)

/* Input's buffer size */
#define BUFFER_SIZE 2048

/* Prompt */
#define PROMPT "lisple> "

/* Input's buffer */
/* This buffer is used to store the input string */
/* Static variables are used to avoid memory allocation */
static char buffer[BUFFER_SIZE];

/* Extract sequence to eval */
/* This function extracts the sequence to evaluate */
/* It returns the number of characters extracted */
/* A sequence to evaluate is a sequence of characters surrounded by parentheses containing a symbol and 2 numbers */
/* For example: (+ 1 2) */
int extract_sequence(const char *ast, char *sequence) {
    int i = 0;
    int j = 0;
    // Skip spaces and tabs
    while (' ' == ast[i]  || '\t' == ast[i] ) {
        ++i;
    }
    // Check if the first character is a parenthesis
    if (ast[i] != '(') {
        return -1;
    }
    // Skip the parenthesis
    ++i;

    // Copy the sequence to evaluate and prevent buffer overflow by checking if the buffer ends with a parenthesis
    while (ast[i] != ')' && ast[i] != '\0') {
        sequence[j] = ast[i];
        ++i;
        ++j;
    }

    // Add the null character at the end of the sequence
    sequence[j] = '\0';

    return j;
}


/* Extract symbol */
/* This function extracts the symbol from the sequence to evaluate */
/* It returns the number of characters extracted */
/* A symbol is an operator*/
/* For example: + - * / */
int extract_symbol(const char *sequence, char *symbol) {
    int i = 0;
    int j = 0;
    // Skip spaces and tabs
    while ( ' ' == sequence[i]  || '\t' ==  sequence[i] ) {
        ++i;
    }

    // Detect if the symbol is a valid operator
    if (sequence[i] != '+' && sequence[i] != '-' && sequence[i] != '*' && sequence[i] != '/') {
        return -1;
    }

    // Copy the symbol
    symbol[j] = sequence[i];
    ++j;

    // TODO: Add support for other operators (e.g. ^, %, //, etc.)

    symbol[j] = '\0';

    return j;
}


/* READ function */
char *READ(char prompt[]) {
    char *input = readline(prompt);
    if (!input) return NULL; // EOF

    add_history(input);
    return input;
}

/* EVAL function */
int EVAL(char *ast) {

    char *sequence = malloc(BUFFER_SIZE);
    int len = extract_sequence(ast, sequence);
    // Detect if no sequence is found
    if (-1 == len  || 0 == len) {
        free(sequence);
        return -1;
    }

    char *symbol = malloc(5);
    int len2 = extract_symbol(sequence, symbol);
    // Detect if no symbol is found
    if ( -1 == len2) {
        free(sequence);
        free(symbol);
        return -1;
    }

    strcpy(ast, sequence);
    free(sequence);

    return 0;
}

/* PRINT function */
char *PRINT(char *exp) {
    return exp;
}


int main(int argc, char *argv[]) {
    char *ast;

    /* Print version and exit information */
    puts("Lisple Prince version 0.0.1");
    puts("Press Ctrl+c to Exit");

    /* In a never ending loop */
    /* forever is a macro defined above using K&R suggestions */
    forever {
        /* Add prompt */
        /* snprintf is used to avoid buffer overflow */
        snprintf(buffer, sizeof(buffer), PROMPT);

        /* Read */
        ast = READ(buffer);

        /* If EOF is reached, break from loop */
        if (!ast){
            printf("\n");
            break;
        }

        /* Eval */
        int err = EVAL(ast);
        if (-1 == err) {
            printf("Error: No sequence to evaluate found\n");

            /* Free retrieved input */
            if (ast) {free(ast); ast = NULL;}
            continue;
        }

        /* Print */
        puts(PRINT(ast));

        /* Free retrieved input */
        if (ast) {free(ast); ast = NULL;}

    }

    return 0;
}

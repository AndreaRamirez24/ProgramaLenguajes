/*
Alumno: Ramirez Gonzalez Andrea
Fecha de entrega: 30/Octubre/2024
Fecha de actualizacion: 30/Octubre/2024
Nombre del archivo: Lenguajes*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

// Define nuestros parametros
typedef struct {
    // Tamaño de la pila
    char stack[STACK_SIZE]; 
    // Indice de nuestro inicio
    int top; 
} Stack;

// Funciones para la pila
void inicioStack(Stack *s) {
    s->top = -1;
}

// Función para una pila vacia
int esVacio(Stack *s) {
    return s->top == -1;
}

// Función para el recorrido
void push(Stack *s, char item) {
    if (s->top < STACK_SIZE - 1) {
        s->stack[++s->top] = item;
    }
}

// Función para retirar de la pila
char pop(Stack *s) {
    if (!esVacio(s)) {
        return s->stack[s->top--];
    }
    // Retornar un carácter nulo si la pila está vacía
    return '\0'; 
}

// Función para imprimir el proceso de la pila
void printPila(Stack *s) {
    // Para imprimir un espacio vacio
    if (esVacio(s)) { 
        printf("Pila: (vacía)\n");
        return;
    }
    printf("Pila: ");
    // Imprime es proceso de la Pila
    for (int i = 0; i <= s->top; i++) { 
        printf("%c ", s->stack[i]);
    }
    printf("\n");
}

// Función de transición
void transicion(char *estadoActual, char cadena, Stack *stack) {
    printf("Estado actual: %c, Entrada: %c\n", *estadoActual, cadena);
    
    // Estado q2
    if (*estadoActual == '2') { 
        // Si la cadena es a, se apila A
        if (cadena == 'a') { 
            push(stack, 'A');
            // Si tenemos epsilon, se desapila
        } else if (cadena == 'e') { 
            if (!esVacio(stack)) {
                pop(stack);
            }
        }
        // Estado q1
    } else if (*estadoActual == '1') { 
        // Si la cadena es e, desapila
        if (cadena == 'e') { 
            if (!esVacio(stack)) {
                pop(stack); 
            }
        }
        // Estado q3
    } else if (*estadoActual == '3') { 
        if (cadena == 'a') {
            // Si es vacio, se desapila y se apila B
            if (!esVacio(stack)) { 
                pop(stack);
                push(stack, 'B');
            }
        }
    }

// Imprimir el estado de la pila después de la transición
    printPila(stack); 
}

// Función principal para validar la cadena
int validaCadena(const char *cadena) {
    Stack stack;
    inicioStack(&stack);
    // Estado inicial
    char estadoActual = '2'; 
    // Asegurarse de que hay espacio para el '\0'
    char cadenaFinal[101];  

    // Concatenar el fin de cadena
    snprintf(cadenaFinal, sizeof(cadenaFinal), "%s#", cadena);

// Usamos size_t para seguir un indice
    for (size_t i = 0; i < strlen(cadenaFinal); i++) { 
        char c = cadenaFinal[i]; 

        // Uso de transiciones
        transicion(&estadoActual, c, &stack);
        
        // Cambio de estados
        if (esVacio(&stack) && estadoActual == '2') {
            // Transición a q3 si la pila está vacía
            estadoActual = '3'; 
        }
    }

    // Comprobar si el estado final es aceptado
    return estadoActual == '3' && esVacio(&stack);
}

int main() {
    char cadena[100];

    printf("Ingresa una cadena (solo 'a' y 'e'): ");
    // Limitar la entrada para evitar desbordamiento
    scanf("%99s", cadena); 

    if (validaCadena(cadena)) {
        printf("La cadena es válida.\n");
    } else {
        printf("La cadena no es válida.\n");
    }

    return 0;
}
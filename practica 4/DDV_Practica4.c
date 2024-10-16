#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Estructura de la Pila
struct Pila {
    unsigned capacidad;
    int cima;
    int *arreglo;
};

void fibonacci_iterativo(int n) {
    if (n < 1) {
        printf("Invalid Number of terms\n");
        return;
    }

    int prev1 = 1;
    int prev2 = 0;

    printf("%d ", prev2);

    if (n == 1)
        return;

    printf("%d ", prev1);

    for (int i = 3; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
        printf("%d ", curr);
    }
}

int fibonacci_recursivo(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

// Función para crear una pila con la capacidad dada
struct Pila* crearPila(unsigned capacidad) {
    struct Pila* pila = (struct Pila*) malloc(sizeof(struct Pila));
    pila->capacidad = capacidad;
    pila->cima = -1;
    pila->arreglo = (int*) malloc(pila->capacidad * sizeof(int));
    return pila;
}

// La pila está llena cuando cima es igual al último índice
int estaLlena(struct Pila* pila) {
    return (pila->cima == pila->capacidad - 1);
}

// La pila está vacía cuando cima es igual a -1
int estaVacia(struct Pila* pila) {
    return (pila->cima == -1);
}

// Función para añadir un elemento a la pila
void apilar(struct Pila *pila, int elemento) {
    if (estaLlena(pila))
        return;
    pila->arreglo[++pila->cima] = elemento;
}

// Función para eliminar un elemento de la pila
int desapilar(struct Pila* pila) {
    if (estaVacia(pila))
        return INT_MIN;
    return pila->arreglo[pila->cima--];
}

// Función para mostrar el movimiento de discos
void moverDisco(char desdePoste, char hastaPoste, int disco) {
    printf("Mover el disco %d de '%c' a '%c'\n", disco, desdePoste, hastaPoste);
}

// Función para implementar el movimiento legal entre dos postes
void moverDiscosEntreDosPostes(struct Pila *origen, struct Pila *destino, char o, char d, int *movimientos) {
    int cimaDiscoOrigen = desapilar(origen);
    int cimaDiscoDestino = desapilar(destino);

    if (cimaDiscoOrigen == INT_MIN) {
        apilar(origen, cimaDiscoDestino);
        moverDisco(d, o, cimaDiscoDestino);
    } else if (cimaDiscoDestino == INT_MIN) {
        apilar(destino, cimaDiscoOrigen);
        moverDisco(o, d, cimaDiscoOrigen);
    } else if (cimaDiscoOrigen > cimaDiscoDestino) {
        apilar(origen, cimaDiscoOrigen);
        apilar(origen, cimaDiscoDestino);
        moverDisco(d, o, cimaDiscoDestino);
    } else {
        apilar(destino, cimaDiscoDestino);
        apilar(destino, cimaDiscoOrigen);
        moverDisco(o, d, cimaDiscoOrigen);
    }
    (*movimientos)++; // Incrementar el contador de movimientos
}

// Función para implementar el problema iterativo de la Torre de Hanói
void torrehanoiIterativo(int num_de_discos, struct Pila *origen, struct Pila *auxiliar, struct Pila *destino, int *movimientos) {
    char o = 'A', d = 'C', a = 'B';

    if (num_de_discos % 2 == 0) {
        char temp = d;
        d = a;
        a = temp;
    }

    for (int i = num_de_discos; i >= 1; i--)
        apilar(origen, i);

    int total_movimientos = pow(2, num_de_discos) - 1;

    for (int i = 1; i <= total_movimientos; i++) {
        if (i % 3 == 1)
            moverDiscosEntreDosPostes(origen, destino, o, d, movimientos);
        else if (i % 3 == 2)
            moverDiscosEntreDosPostes(origen, auxiliar, o, a, movimientos);
        else if (i % 3 == 0)
            moverDiscosEntreDosPostes(auxiliar, destino, a, d, movimientos);
    }
}

// Torres de hanoi recursiva
void hanoiRecursivo(int disco, char iniciar, char temp, char final, int *movimientos) {
    if (disco == 1) {
        printf("Mover el disco 1 de '%c' a '%c'\n", iniciar, final);
        (*movimientos)++; // Incrementar el contador de movimientos
        return;
    }
    hanoiRecursivo(disco - 1, iniciar, final, temp, movimientos);
    printf("Mover el disco %d de '%c' a '%c'\n", disco, iniciar, final);
    (*movimientos)++; // Incrementar el contador de movimientos
    hanoiRecursivo(disco - 1, temp, iniciar, final, movimientos);
}
int factorialIterativo(int n) {
    int factorial_result = 1;
    int i;

    // Bucle desde 1 hasta N para calcular el factorial
    for (i = 1; i <= n; i++) {
        factorial_result *= i; // Multiplica cada número
    }

    return factorial_result; // Retorna el resultado
}

int factorialRecursivo(int numero) {
    // Si hemos llegado a 1, detenemos la recursión
    if (numero <= 1)
        return 1;
    return numero * factorialRecursivo(numero - 1); // Llamada recursiva
}

int main() {
    int opcion, n, disco, movimientos_iterativo = 0, movimientos_recursivo = 0;

    do {
        printf("\nMenu de Algoritmos\n");
        printf("1. Fibonacci Iterativo\n");
        printf("2. Fibonacci Recursivo\n");
        printf("3. Factorial Iterativo\n");
        printf("4. Factorial Recursivo\n");
        printf("5. Torres de Hanoi Iterativo\n");
        printf("6. Torres de Hanoi Recursivo\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el numero de terminos para Fibonacci iterativo: ");
                scanf("%d", &n);
                printf("Fibonacci iterativo: ");
                fibonacci_iterativo(n);
                break;

            case 2:
                printf("Ingrese el numero de terminos para Fibonacci recursivo: ");
                scanf("%d", &n);
                printf("Fibonacci recursivo: ");
                for (int i = 0; i < n; i++) {
                    printf("%d ", fibonacci_recursivo(i));
                }
                printf("\n");
                break;

            case 3:
                printf("Ingrese un numero para calcular el factorial iterativo: ");
                scanf("%d", &n);
                printf("Factorial iterativo de %d es %d\n", n, factorialIterativo(n));
                break;

            case 4:
                printf("Ingrese un numero para calcular el factorial recursivo: ");
                scanf("%d", &n);
                printf("Factorial recursivo de %d es %d\n", n, factorialRecursivo(n));
                break;

            case 5:
                printf("Ingrese el número de discos para la Torre de Hanoi iterativa: ");
                scanf("%d", &disco);
                struct Pila *origen = crearPila(disco);
                struct Pila *destino = crearPila(disco);
                struct Pila *auxiliar = crearPila(disco);
                printf("Movimientos (iterativo):\n");
                torrehanoiIterativo(disco, origen, auxiliar, destino, &movimientos_iterativo);
                printf("Total de movimientos (iterativo): %d\n", movimientos_iterativo);
                free(origen->arreglo);
                free(origen);
                free(auxiliar->arreglo);
                free(auxiliar);
                free(destino->arreglo);
                free(destino);
                break;

            case 6:
                printf("Ingrese el nemero de discos para la Torre de Hanoi recursiva: ");
                scanf("%d", &disco);
                printf("Movimientos (recursivo):\n");
                hanoiRecursivo(disco, 'A', 'B', 'C', &movimientos_recursivo);
                printf("Total de movimientos (recursivo): %d\n", movimientos_recursivo);
                break;

            case 0:
                printf("Saliendo\n");
                break;

            default:
                printf("Opcion no válida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
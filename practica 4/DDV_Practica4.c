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

int main() {
    int disco, movimientos_iterativo = 0, movimientos_recursivo = 0;

    printf("Ingrese el número de discos: ");
    scanf("%d", &disco);

    // Para hanoi iterativo
    struct Pila *origen = crearPila(disco);
    struct Pila *destino = crearPila(disco);
    struct Pila *auxiliar = crearPila(disco);

    printf("Movimientos (iterativo):\n");
    torrehanoiIterativo(disco, origen, auxiliar, destino, &movimientos_iterativo);
    printf("Total de movimientos (iterativo): %d\n", movimientos_iterativo);

    printf("\nMovimientos (recursivo):\n");
    hanoiRecursivo(disco, 'A', 'B', 'C', &movimientos_recursivo);
    printf("Total de movimientos (recursivo): %d\n", movimientos_recursivo);

    // Liberar memoria
    free(origen->arreglo);
    free(origen);
    free(auxiliar->arreglo);
    free(auxiliar);
    free(destino->arreglo);
    free(destino);

    return 0;
}

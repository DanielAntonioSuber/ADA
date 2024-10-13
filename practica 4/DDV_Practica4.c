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
    printf("Mueve el disco %d de \'%c\' a \'%c\'\n", disco, desdePoste, hastaPoste);
}

// Función para implementar el movimiento legal entre dos postes
void moverDiscosEntreDosPostes(struct Pila *origen, struct Pila *destino, char o, char d) {
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
}

// Función para implementar el problema iterativo de la Torre de Hanói
void torrehanoiIterativo(int num_de_discos, struct Pila *origen, struct Pila *auxiliar, struct Pila *destino) {
    int i, total_movimientos;
    char o = 'O', d = 'D', a = 'A';

    if (num_de_discos % 2 == 0) {
        char temp = d;
        d = a;
        a = temp;
    }
    total_movimientos = pow(2, num_de_discos) - 1;

    for (i = num_de_discos; i >= 1; i--)
        apilar(origen, i);

    for (i = 1; i <= total_movimientos; i++) {
        if (i % 3 == 1)
            moverDiscosEntreDosPostes(origen, destino, o, d);
        else if (i % 3 == 2)
            moverDiscosEntreDosPostes(origen, auxiliar, o, a);
        else if (i % 3 == 0)
            moverDiscosEntreDosPostes(auxiliar, destino, a, d);
    }
}

// Torres de hanoi recursiva
int num;
void hanoiRecursivo(int disco, char iniciar, char temp, char final) {
    if (disco == 1) {
        printf("\nMueva el disco 1 de la base %c a la base %c", iniciar, final);
        num++;
        return;
    }
    hanoiRecursivo(disco - 1, iniciar, final, temp);
    printf("\nMover el disco %d de la base %c a la base %c", disco, iniciar, final);
    num++;
    hanoiRecursivo(disco - 1, temp, iniciar, final);
}

int main() {
    // para hanoi iterativo
    unsigned num_de_discos = 3;
    struct Pila *origen, *destino, *auxiliar;
    origen = crearPila(num_de_discos);
    auxiliar = crearPila(num_de_discos);
    destino = crearPila(num_de_discos);

    torrehanoiIterativo(num_de_discos, origen, auxiliar, destino);

    // para hanoi recursivo
    int disco;
    printf("Digite el numero de discos: ");
    scanf("%d", &disco);
    printf("Los movimientos para resolver la torre de Hanoi son : ");
    hanoiRecursivo(disco, 'A', 'B', 'C');
    printf("\nTotal de movimientos: %d\n", num);

    // Liberar memoria
    free(origen->arreglo);
    free(origen);
    free(auxiliar->arreglo);
    free(auxiliar);
    free(destino->arreglo);
    free(destino);

    return 0;
}

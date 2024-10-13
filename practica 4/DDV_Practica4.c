#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Estructura de la Pila
struct Pila 
{ 
    unsigned capacidad; 
    int cima; 
    int *arreglo; 
}; 
 
// Función para crear una pila con la capacidad dada
struct Pila* crearPila(unsigned capacidad) 
{ 
    struct Pila* pila = (struct Pila*) malloc(sizeof(struct Pila)); 
    pila->capacidad = capacidad; 
    pila->cima = -1; 
    pila->arreglo = (int*) malloc(pila->capacidad * sizeof(int)); 
    return pila; 
} 
 
// La pila está llena cuando cima es igual al último índice
int estaLlena(struct Pila* pila) 
{ 
    return (pila->cima == pila->capacidad - 1); 
} 
 
// La pila está vacía cuando cima es igual a -1
int estaVacia(struct Pila* pila) 
{ 
    return (pila->cima == -1); 
} 
 
// Función para añadir un elemento a la pila. Aumenta la cima en 1
void apilar(struct Pila *pila, int elemento) 
{ 
    if (estaLlena(pila)) 
        return; 
    pila->arreglo[++pila->cima] = elemento; 
} 
 
// Función para eliminar un elemento de la pila. Disminuye la cima en 1
int desapilar(struct Pila* pila) 
{ 
    if (estaVacia(pila)) 
        return INT_MIN; 
    return pila->arreglo[pila->cima--]; 
} 
 
// Función para mostrar el movimiento de discos
void moverDisco(char desdePoste, char hastaPoste, int disco) 
{ 
    printf("Mueve el disco %d de \'%c\' a \'%c\'\n", disco, desdePoste, hastaPoste); 
}
 
// Función para implementar el movimiento legal entre dos postes
void moverDiscosEntreDosPostes(struct Pila *origen, struct Pila *destino, char o, char d) 
{ 
    int cimaDiscoOrigen = desapilar(origen); 
    int cimaDiscoDestino = desapilar(destino); 
 
    // Cuando el poste de origen está vacío
    if (cimaDiscoOrigen == INT_MIN) 
    { 
        apilar(origen, cimaDiscoDestino); 
        moverDisco(d, o, cimaDiscoDestino); 
    } 
    // Cuando el poste de destino está vacío
    else if (cimaDiscoDestino == INT_MIN) 
    { 
        apilar(destino, cimaDiscoOrigen); 
        moverDisco(o, d, cimaDiscoOrigen); 
    } 
    // Cuando el disco en la cima del origen > disco en la cima del destino
    else if (cimaDiscoOrigen > cimaDiscoDestino) 
    { 
        apilar(origen, cimaDiscoOrigen); 
        apilar(origen, cimaDiscoDestino); 
        moverDisco(d, o, cimaDiscoDestino); 
    } 
    // Cuando el disco en la cima del origen < disco en la cima del destino
    else
    { 
        apilar(destino, cimaDiscoDestino); 
        apilar(destino, cimaDiscoOrigen); 
        moverDisco(o, d, cimaDiscoOrigen); 
    } 
} 
 
// Función para implementar el problema iterativo de la Torre de Hanói
void torrehanoiIterativo(int num_de_discos, struct Pila *origen, struct Pila *auxiliar, struct Pila *destino) 
{ 
    int i, total_movimientos; 
    char o = 'O', d = 'D', a = 'A'; 
 
    // Si el número de discos es par, intercambiar destino y auxiliar
    if (num_de_discos % 2 == 0) 
    { 
        char temp = d; 
        d = a; 
        a = temp; 
    } 
    total_movimientos = pow(2, num_de_discos) - 1; 
 
    // Los discos más grandes se apilan primero
    for (i = num_de_discos; i >= 1; i--) 
        apilar(origen, i); 
 
    for (i = 1; i <= total_movimientos; i++) 
    { 
        if (i % 3 == 1) 
            moverDiscosEntreDosPostes(origen, destino, o, d); 
        else if (i % 3 == 2) 
            moverDiscosEntreDosPostes(origen, auxiliar, o, a); 
        else if (i % 3 == 0) 
            moverDiscosEntreDosPostes(auxiliar, destino, a, d); 
    } 
} 
 
// Función principal
int main() 
{ 
    // Entrada: número de discos
    unsigned num_de_discos = 3; 
 
    struct Pila *origen, *destino, *auxiliar; 
 
    // Crear tres pilas de tamaño 'num_de_discos' para almacenar los discos
    origen = crearPila(num_de_discos); 
    auxiliar = crearPila(num_de_discos); 
    destino = crearPila(num_de_discos); 
 
    torrehanoiIterativo(num_de_discos, origen, auxiliar, destino); 
    return 0; 
}

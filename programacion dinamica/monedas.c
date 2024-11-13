#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int min(int a, int b){ //retornar el min de dos valores
    return (a < b) ? a : b;
}

int cambio(int valor, int monedas[], int n, int NumMinMon[]) {
    int INF = 1000000000; //establecer infinito

    if (valor < 0) {
        return INF;
    }
    if (valor == 0) {
        return 0;
    }

    if (NumMinMon[valor] != -1) { //verifica si se calculo el num min de monedas
        return NumMinMon[valor];
    }

    int respuesta = INF;
    for (int i = 0; i < n; i++) {
        respuesta = min(respuesta, cambio(valor - monedas[i], monedas, n, NumMinMon));
    }

    NumMinMon[valor] = respuesta + 1;
    return NumMinMon[valor];
}

int main() {
    int n; //cantidad de monedas
    int valor; //valor
    int monedas[1000]; //tipos de monedas

    printf("Ingresa el valor: ");
    scanf("%d", &valor);

    printf("Ingresa la cantidad de tipos de monedas: ");
    scanf("%d", &n);

    printf("Ingresa los valores de las monedas:\n");
    for (int i = 0; i < n; i++) {
        printf("Moneda %d: ", i + 1);
        scanf("%d", &monedas[i]);
    }

    int *NumMinMon = (int *)malloc((valor + 1) * sizeof(int)); //asignar memoria a NumMinMon y\e inicializar a -1
    for (int i = 0; i <= valor; i++) {
        NumMinMon[i] = -1;
    }

    int resultado = cambio(valor, monedas, n, NumMinMon);

    if (resultado >= 1000000000) {
        printf("No se puede obtener el cambio.\n");
    } else {
        printf("La cantidad minima de monedas necesaria es: %d\n", resultado);
    }

    free(NumMinMon);
    return 0;
}

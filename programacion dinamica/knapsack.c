#include <stdio.h>

// Función para encontrar el valor máximo entre dos enteros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Función para resolver el problema de la mochila
int knapsack(int capacidad, int pesos[], int valores[], int n) {
    int dp[n + 1][capacidad + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacidad; w++) {
            if (i == 0 || w == 0) {
                // Si no hay elementos o capacidad, el valor es 0
                dp[i][w] = 0;
            } else if (pesos[i - 1] <= w) {
                // Elegimos entre incluir o no incluir el elemento i-1
                dp[i][w] = max(valores[i - 1] + dp[i - 1][w - pesos[i - 1]], dp[i - 1][w]);
            } else {
                // No se incluye el elemento i-1
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // El valor máximo se encuentra en dp[n][capacidad]
    return dp[n][capacidad];
}

int main() {
    int valores[] = {60, 100, 120};  // Valores de los objetos
    int pesos[] = {10, 20, 30};      // Pesos de los objetos
    int capacidad = 50;              // Capacidad de la mochila
    int n = sizeof(valores) / sizeof(valores[0]);  // Número de objetos

    int resultado = knapsack(capacidad, pesos, valores, n);
    printf("El valor máximo que se puede obtener en la mochila es: %d\n", resultado);

    return 0;
}
 
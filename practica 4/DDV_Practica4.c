#include <stdio.h>

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
    int N; // Número del cual calcular el factorial
    
    // Solicitar al usuario el número
    printf("Ingrese el numero para calcular su factorial: ");
    scanf("%d", &N);

    // Factorial iterativo
    printf("Factorial iterativo: ");
    int resultado_factorial_iterativo = factorialIterativo(N); 
    printf("El factorial de %d es %d\n", N, resultado_factorial_iterativo); 

    // Factorial recursivo
    printf("Factorial recursivo: ");
    int resultado_factorial_recursivo = factorialRecursivo(N);
    printf("El factorial de %d es %d\n", N, resultado_factorial_recursivo);

    return 0;
}

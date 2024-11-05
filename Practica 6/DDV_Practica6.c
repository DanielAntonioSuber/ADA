#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Funcion para encontrar el maximo de dos enteros
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Funcion para encontrar el maximo de tres enteros
int max3(int a, int b, int c)
{
    return max(max(a, b), c);
}

// Algoritmo de Kadane para encontrar la suma maxima del subarreglo en O(n)
int maxSubarraySumKadane(int arr[], int size, int *kadane_ops)
{
    int maxSum = arr[0];
    int currSum = arr[0];
    *kadane_ops = 0; // Inicializar el contador

    for (int i = 1; i < size; i++)
    {
        currSum = max(arr[i], currSum + arr[i]);
        maxSum = max(maxSum, currSum);
        *kadane_ops += 3; // Incrementar por la comparacion y dos asignaciones
    }

    return maxSum;
}

// Encuentra la suma maxima cruzando el punto medio en el arreglo
int maxCrossingSum(int arr[], int l, int m, int h, int *cross_ops)
{
    int left_sum = INT_MIN, right_sum = INT_MIN;
    int sum = 0;

    for (int i = m; i >= l; i--)
    {
        sum += arr[i];
        left_sum = max(left_sum, sum);
        *cross_ops += 2; // Una suma y una comparacion
    }

    sum = 0;
    for (int i = m + 1; i <= h; i++)
    {
        sum += arr[i];
        right_sum = max(right_sum, sum);
        *cross_ops += 2; // Otra suma y comparacion
    }

    return left_sum + right_sum;
}

// Funcion recursiva para encontrar la suma maxima de subarreglo usando Divide y Venceras
int maxSubArraySumDivideAndConquer(int arr[], int l, int h, int *divide_ops, int *cross_ops)
{
    if (l == h) // Caso base: solo un elemento
    {
        *divide_ops += 1; // Contar la comparacion
        return arr[l];
    }

    int m = (l + h) / 2;
    *divide_ops += 1; // Contar la operacion de division

    int left_sum = maxSubArraySumDivideAndConquer(arr, l, m, divide_ops, cross_ops);
    int right_sum = maxSubArraySumDivideAndConquer(arr, m + 1, h, divide_ops, cross_ops);
    int cross_sum = maxCrossingSum(arr, l, m, h, cross_ops);

    *divide_ops += 3; // Por las tres llamadas y el calculo final
    return max3(left_sum, right_sum, cross_sum);
}

// Funcion para leer un numero especifico de elementos aleatorios del archivo
int leer_archivo(int numero_elementos, int *arr)
{
    int i = 0;
    long file_size;
    FILE *file = NULL;

    srand(time(NULL));

    printf("\nLeyendo el archivo numeros10millones.txt\n");
    file = fopen("numeros10millones.txt", "r");
    if (file == NULL)
    {
        printf("\nNo se puede abrir el archivo.\n");
        return 0;
    }

    fseek(file, 0L, SEEK_END);
    file_size = ftell(file) / sizeof(int);
    fseek(file, 0L, SEEK_SET);

    if (file_size < numero_elementos)
    {
        printf("\nEl archivo no contiene suficientes elementos para la muestra solicitada.\n");
        fclose(file);
        return 0;
    }

    int indice_aleatorio = rand() % (file_size - numero_elementos);
    fseek(file, indice_aleatorio * sizeof(int), SEEK_SET);

    while (i < numero_elementos && fscanf(file, "%d", &arr[i]) == 1) // Cambiado para verificar lectura
    {
        i++;
    }

    fclose(file);
    return i;
}

// Funcion para mostrar el menu y obtener la opcion del usuario
void mostrar_menu()
{
    printf("\n--- Menu ---\n");
    printf("1. Calcular suma maxima de subarreglo (Kadane)\n");
    printf("2. Calcular suma maxima de subarreglo (Divide y Venceras)\n");
    printf("3. Salir\n");
    printf("Seleccione una opcion: ");
}

int main(int argc, char *argv[])
{
    int opcion = 0; // Inicializar la opción
    int *arr = NULL;
    int numero_elementos = 0;
    int maxSum;

    int kadane_ops = 0, divide_ops = 0, cross_ops = 0; // Declarar contadores

    // Manejar argumentos de línea de comandos
    if (argc > 1)
    {
        // Si se pasa un argumento, se espera que sea el número de elementos
        numero_elementos = atoi(argv[1]);
        arr = (int *)malloc(numero_elementos * sizeof(int));
        if (arr == NULL) // Verificar si la asignación de memoria fue exitosa
        {
            printf("Error al asignar memoria.\n");
            return 1; // Terminar el programa si la asignación falla
        }

        // Leer datos de un archivo o inicializar el arreglo aquí
        numero_elementos = leer_archivo(numero_elementos, arr);
        if (numero_elementos <= 0)
        {
            printf("No se pudo leer el archivo o no contiene suficientes elementos.\n");
            free(arr);
            return 0; // Terminar si no se leen elementos
        }
        printf("Se leyeron %d elementos del archivo con exito.\n", numero_elementos);

        // Si se pasa un segundo argumento, se espera que sea la opción
        if (argc > 2)
        {
            opcion = atoi(argv[2]); // Convertir el segundo argumento a entero
            // Ejecutar la opción directamente
            switch (opcion)
            {
            case 1:
                maxSum = maxSubarraySumKadane(arr, numero_elementos, &kadane_ops);
                printf("Maxima suma de subarreglo (Kadane): %d\n", maxSum);
                printf("Numero de operaciones (Kadane): %d\n", kadane_ops);
                break;

            case 2:
                maxSum = maxSubArraySumDivideAndConquer(arr, 0, numero_elementos - 1, &divide_ops, &cross_ops);
                printf("Maxima suma de subarreglo (Divide y Venceras): %d\n", maxSum);
                printf("Numero de operaciones (Divide y Venceras): %d\n", divide_ops + cross_ops);
                break;

            case 3:
                printf("Saliendo del programa.\n");
                free(arr);
                return 0;

            default:
                printf("Opcion no valida. Se volvera al menu interactivo.\n");
                break;
            }
        }
    }
    else
    {
        // Si no se pasa argumento, solicitar al usuario que ingrese el número de elementos
        printf("\nIngrese el numero de elementos a leer: ");
        scanf("%d", &numero_elementos);

        arr = (int *)malloc(numero_elementos * sizeof(int));
        if (arr == NULL) // Verificar si la asignación de memoria fue exitosa
        {
            printf("Error al asignar memoria.\n");
            return 1; // Terminar el programa si la asignación falla
        }

        // Leer datos del archivo o del usuario
        numero_elementos = leer_archivo(numero_elementos, arr);
        if (numero_elementos <= 0)
        {
            printf("No se pudo leer el archivo o no contiene suficientes elementos.\n");
            free(arr);
            return 0; // Terminar si no se leen elementos
        }
        printf("Se leyeron %d elementos del archivo con exito.\n", numero_elementos);

        // Bucle principal del menú
        while (1)
        {
            mostrar_menu();
            scanf("%d", &opcion);

            switch (opcion)
            {
            case 1:
                if (numero_elementos == 0)
                {
                    printf("\nPrimero debe leer los datos del archivo.\n");
                }
                else
                {
                    maxSum = maxSubarraySumKadane(arr, numero_elementos, &kadane_ops);
                    printf("Maxima suma de subarreglo (Kadane): %d\n", maxSum);
                    printf("Numero de operaciones (Kadane): %d\n", kadane_ops);
                }
                break;

            case 2:
                if (numero_elementos == 0)
                {
                    printf("\nPrimero debe leer los datos del archivo.\n");
                }
                else
                {
                    maxSum = maxSubArraySumDivideAndConquer(arr, 0, numero_elementos - 1, &divide_ops, &cross_ops);
                    printf("Maxima suma de subarreglo (Divide y Venceras): %d\n", maxSum);
                    printf("Numero de operaciones (Divide y Venceras): %d\n", divide_ops + cross_ops);
                }
                break;

            case 3:
                printf("Saliendo del programa.\n");
                free(arr);
                return 0;

            default:
                printf("Opcion no valida. Intente nuevamente.\n");
            }
        }
    }

    free(arr);
    return 0;
}
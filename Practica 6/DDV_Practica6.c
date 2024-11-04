#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Función para encontrar el máximo de dos enteros
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Función para encontrar el máximo de tres enteros
int max3(int a, int b, int c)
{
    return max(max(a, b), c);
}

// Algoritmo de Kadane para encontrar la suma máxima del subarreglo en O(n)
int maxSubarraySumKadane(int arr[], int size)
{
    int maxSum = arr[0];
    int currSum = arr[0];

    for (int i = 1; i < size; i++)
    {
        currSum = max(arr[i], currSum + arr[i]);
        maxSum = max(maxSum, currSum);
    }

    return maxSum;
}

// Encuentra la suma máxima cruzando el punto medio en el arreglo
int maxCrossingSum(int arr[], int l, int m, int h)
{
    int left_sum = INT_MIN, right_sum = INT_MIN;
    int sum = 0;

    for (int i = m; i >= l; i--)
    {
        sum += arr[i];
        left_sum = max(left_sum, sum);
    }

    sum = 0;
    for (int i = m + 1; i <= h; i++)
    {
        sum += arr[i];
        right_sum = max(right_sum, sum);
    }

    return left_sum + right_sum;
}

// Función recursiva para encontrar la suma máxima de subarreglo usando Divide y Vencerás
int maxSubArraySumDivideAndConquer(int arr[], int l, int h)
{
    if (l == h) // Caso base: solo un elemento
        return arr[l];

    int m = (l + h) / 2;

    return max3(
        maxSubArraySumDivideAndConquer(arr, l, m),
        maxSubArraySumDivideAndConquer(arr, m + 1, h),
        maxCrossingSum(arr, l, m, h));
}

// Función para leer un número específico de elementos aleatorios del archivo
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

    while (i < numero_elementos && fscanf(file, "%d", &arr[i]) != EOF)
    {
        i++;
    }

    fclose(file);

    return i;
}

// Función para mostrar el menú y obtener la opción del usuario
void mostrar_menu()
{
    printf("\n--- Menú ---\n");
    printf("1. Calcular suma máxima de subarreglo (Kadane)\n");
    printf("2. Calcular suma máxima de subarreglo (Divide y Vencerás)\n");
    printf("3. Salir\n");
    printf("Seleccione una opción: ");
}

int main()
{
    int opcion;
    int *arr = NULL;
    int numero_elementos = 0;
    int maxSum;

    printf("\nIngrese el número de elementos a leer: ");
    scanf("%d", &numero_elementos);
    arr = (int *)malloc(numero_elementos * sizeof(int));
    numero_elementos = leer_archivo(numero_elementos, arr);

    if (numero_elementos > 0)
    {
        printf("Se leyeron %d elementos del archivo con éxito.\n", numero_elementos);
    }
    else
    {
        printf("No se pudo leer el archivo o no contiene suficientes elementos.\n");
    }

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
                maxSum = maxSubarraySumKadane(arr, numero_elementos);
                printf("Máxima suma de subarreglo (Kadane): %d\n", maxSum);
            }
            break;

        case 2:
            if (numero_elementos == 0)
            {
                printf("\nPrimero debe leer los datos del archivo.\n");
            }
            else
            {
                maxSum = maxSubArraySumDivideAndConquer(arr, 0, numero_elementos - 1);
                printf("Máxima suma de subarreglo (Divide y Vencerás): %d\n", maxSum);
            }
            break;

        case 3:
            printf("Saliendo del programa.\n");
            return 0;

        default:
            printf("Opción no válida. Intente nuevamente.\n");
        }
    }

    return 0;
}

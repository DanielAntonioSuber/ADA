#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maximo_recursivo(int *arr, int n)
{
    if (n == 1)
    {
        return arr[0];
    }
    if (arr[0] < arr[n - 1])
    {
        arr[0] = arr[n - 1];
    }
    n--;
    return maximo_recursivo(arr, n);
}

int minimo_recursivo(int *arr, int n)
{
    if (n == 1)
    {
        return arr[0];
    }
    if (arr[0] > arr[n - 1])
    {
        arr[0] = arr[n - 1];
    }
    n--;
    return minimo_recursivo(arr, n);
}

int maximo_iterativo(int *numeros, int tamano) {
    int mayor = numeros[0];  
    for (int i = 1; i < tamano; ++i) {
        if (numeros[i] > mayor) 
            mayor = numeros[i];
    }
    return mayor;  
}

int minimo_iterativo(int *numeros, int tamano) {
    int menor = numeros[0];  
    for (int i = 1; i < tamano; ++i) {
        if (numeros[i] < menor) 
            menor = numeros[i];
    }
    return menor;  
}

void maximo_minimo_iterativo(int *arr, int n, int *max, int *min) {
    *max = arr[0];
    *min = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > *max) {
            *max = arr[i];
        }
        if (arr[i] < *min) {
            *min = arr[i];
        }
    }
}

void maximo_minimo_recursivo(int *arr, int n, int *max, int *min) {
    if (n == 1) {
        *max = arr[0];
        *min = arr[0];
        return;
    }

    maximo_minimo_recursivo(arr, n - 1, max, min);

    if (arr[n - 1] > *max) {
        *max = arr[n - 1];
    }
    if (arr[n - 1] < *min) {
        *min = arr[n - 1];
    }
}

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

    if (file_size < numero_elementos) {
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

int menu() {
    int opt = 0;
    printf("\n=== Menu de opciones ===\n");
    printf("1. Maximo iterativo\n");
    printf("2. Maximo recursivo\n");
    printf("3. Minimo iterativo\n");
    printf("4. Minimo recursivo\n");
    printf("5. Maximo y Minimo iterativo\n");
    printf("6. Maximo y Minimo recursivo\n");
    printf("7. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opt);

    return opt;
}

int main() {
    int opt = 0;
    int numero_elementos;
    int *arr = NULL;
    int max, min;

    printf("Ingrese la cantidad de elementos a leer del archivo: ");
    scanf("%d", &numero_elementos);

    arr = (int *)malloc(numero_elementos * sizeof(int));
    int elementos_leidos = leer_archivo(numero_elementos, arr);

    if (elementos_leidos == 0) {
        printf("No se pudieron leer los elementos necesarios.\n");
        return 1;
    }

    while (opt != 7) {
        opt = menu();

        switch (opt) {
        case 1:
            printf("\nMaximo (iterativo): %d\n", maximo_iterativo(arr, elementos_leidos));
            break;
        case 2:
            printf("\nMaximo (recursivo): %d\n", maximo_recursivo(arr, elementos_leidos));
            break;
        case 3:
            printf("\nMinimo (iterativo): %d\n", minimo_iterativo(arr, elementos_leidos));
            break;
        case 4:
            printf("\nMinimo (recursivo): %d\n", minimo_recursivo(arr, elementos_leidos));
            break;
        case 5:
            maximo_minimo_iterativo(arr, elementos_leidos, &max, &min);
            printf("\nMaximo y Minimo (iterativo): Max = %d, Min = %d\n", max, min);
            break;
        case 6:
            maximo_minimo_recursivo(arr, elementos_leidos, &max, &min);
            printf("\nMaximo y Minimo (recursivo): Max = %d, Min = %d\n", max, min);
            break;
        case 7:
            printf("\nSaliendo del programa.\n");
            break;
        default:
            printf("\nOpcion incorrecta, por favor intente de nuevo.\n");
            break;
        }
    }

    free(arr);

    return 0;
}
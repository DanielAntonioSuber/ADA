#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int busqueda_lineal(int arr[], int N, int x)
{
	int i; 
    for ( i = 0; i < N; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

int busqueda_binaria(int arr[], int low, int high, int x)
{
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int leer_archivo(int **arr, const char* nombre_archivo)
{
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombre_archivo);
        return -1;
    }

    int capacidad = 1000;
    int i = 0;
    *arr = (int *)malloc(capacidad * sizeof(int));
    if (*arr == NULL) {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return -1;
    }

    while (fscanf(archivo, "%d", &(*arr)[i]) != EOF) {
        i++;
        if (i >= capacidad) {
            capacidad *= 2;
            *arr = (int *)realloc(*arr, capacidad * sizeof(int));
            if (*arr == NULL) {
                printf("Error al reasignar memoria\n");
                fclose(archivo);
                return -1;
            }
        }
    }

    fclose(archivo);
    return i;  // Número de elementos leídos
}

int main()
{
    int *arr = NULL;
    int numero_elementos = leer_archivo(&arr, "numeros.txt");

    if (numero_elementos <= 0) {
        printf("Error al leer los numeros del archivo\n");
        return 1;
    }

    int x, opcion;
    printf("Introduce el numero que quiere buscar: ");
    scanf("%d", &x);

    printf("\nSeleccione el tipo de busqueda que quiere aplicar:\n");
    printf("1. Busqueda lineal\n");
    printf("2. Busqueda binaria\n");
    printf("Ingrese una opcin: ");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1: {
            // Búsqueda lineal
            int resultado_lineal = busqueda_lineal(arr, numero_elementos, x);
            if (resultado_lineal == -1)
                printf("Numero no encontrado \n");
            else
                printf("Numero encontrado en la posicion %d \n", resultado_lineal);
            break;
        }
        case 2: {
            // Búsqueda binaria
            int resultado_binario = busqueda_binaria(arr, 0, numero_elementos - 1, x);
            if (resultado_binario == -1)
                printf("Numero no encontrado \n");
            else
                printf("Numero encontrado en la posicion %d \n", resultado_binario);
            break;
        }
        default:
            printf("Opcion no valida, intente nuevamente \n");
            break;
    }

    free(arr);
    return 0;
}


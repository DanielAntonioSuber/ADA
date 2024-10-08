#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int comparaciones = 0;

int es_numero_entero(const char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (!isdigit(cadena[i]))
        {
            return 0;
        }
    }
    return 1;
}

int busqueda_lineal(int arr[], int N, int x)
{

    for (int i = 0; i < N; i++) {
        comparaciones++;
        if (arr[i] == x)
            return i;
    }
    return -1;
}

int busqueda_binaria(int arr[], int low, int high, int x)
{
    comparaciones++;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        comparaciones++;
        if (arr[mid] == x)
            return mid;

        comparaciones++;
        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int leer_archivo(int numero_elementos, int *arr)
{
    int i = 0;
    long file_size;
    FILE *file = NULL;

    srand(time(NULL));

    printf("\nLeyendo el archivo numeros.txt\n");
    file = fopen("numeros.txt", "r");
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


    while (i < numero_elementos && fscanf(file, "%d", &arr[i]) != EOF)
    {
        i++;
    }

    fclose(file);

    return i;
}

int main(int argc, char *argv[])
{
    int *arr = NULL;
    int numero_elementos = 0;
    int x, opcion;

    if (argc == 4 && es_numero_entero(argv[1]) && es_numero_entero(argv[2]) && es_numero_entero(argv[3]))
    {
        numero_elementos = atoi(argv[1]);
        opcion = atoi(argv[3]);
        x = atoi(argv[2]);

        if (numero_elementos <= 0)
        {
            printf("El numero de elementos debe ser mayor que cero.\n");
            return 1;
        }

        arr = (int *)malloc(numero_elementos * sizeof(int));
        leer_archivo(numero_elementos, arr);

        switch (opcion)
        {
        case 1:
        {
            int resultado_lineal = busqueda_lineal(arr, numero_elementos, x);
            if (resultado_lineal == -1)
                printf("Numero no encontrado \n");
            else
                printf("Numero encontrado en la posicion %d \n", resultado_lineal);
            break;
        }
        case 2:
        {
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
    }
    else
    {
        printf("Ingresa el numero de elementos sobre el cual quieres buscar: ");
        scanf("%d", &numero_elementos);
        if (numero_elementos <= 0)
        {
            printf("Error al leer los numeros del archivo\n");
            return 1;
        }

        arr = (int *)malloc(numero_elementos * sizeof(int));
        leer_archivo(numero_elementos, arr);

        printf("Introduce el numero que quiere buscar: ");
        scanf("%d", &x);

        printf("\nSeleccione el tipo de busqueda que quiere aplicar:\n");
        printf("1. Busqueda lineal\n");
        printf("2. Busqueda binaria\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
        {
            int resultado_lineal = busqueda_lineal(arr, numero_elementos, x);
            if (resultado_lineal == -1)
                printf("Numero no encontrado \n");
            else
                printf("Numero encontrado en la posicion %d \n", resultado_lineal);
            break;
        }
        case 2:
        {
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
    }

    printf("Numero de comparacciones: %d", comparaciones);

    free(arr);
    return 0;
}

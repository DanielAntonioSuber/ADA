#include <stdio.h>

int busqueda_lineal(int arr[], int N, int x)
{
    int i;
    for (i = 0; i < N; i++)
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

int leer_archivo(int numero_elementos, int *arr)
{
    int i = 0;
    long file_size;
    FILE *file = NULL;

    srand(time(NULL));

    printf("\nLeyendo el archivo numeros10millones.txt\n");
    file = fopen("numeros.txt", "r");
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

int main()
{
    int arr[] = { 2, 3, 4, 10, 40 };
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = busqueda_lineal(arr, n, x);
    (result == -1)
        ? printf("Elemento no encontrado\n")
        : printf("Elemento encontrado en la posicion: %d\n", result);
    
   
    int result2 = busqueda_binaria(arr, 0, n - 1, x);
    if(result2 == -1) printf("Elemento no encontrado\n");
    else printf("Elemento encontrado en la posicion:  %d",result2);

    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<ctype.h>

void merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int l, int r);
void quick_sort(int arr[], int low, int high);
int es_numero_entero(const char *cadena);
int leer_archivo(int numero_elementos, int *arr);
int menu(int *numbers, int size);

int comparaciones_merge = 0;
int intercambios_merge = 0;

int comparaciones_quick = 0;
int intercambios_quick = 0;

int main(int argc, char *argv[])
{
    int numero_elementos = 0;
    int *numbers = NULL;
    
    if (argc == 3 && es_numero_entero(argv[1]) && es_numero_entero(argv[2]))
    {
        int opt;
        clock_t inicio, fin;
        double tiempo_ejecucion;
        numero_elementos = atoi(argv[1]);
        opt = atoi(argv[2]);

        if (numero_elementos <= 0)
        {
            printf("El numero de elementos debe ser mayor que cero.\n");
            return 1;
        }

        numbers = (int *)malloc(numero_elementos * sizeof(int));
        if (numbers == NULL)
        {
            printf("Error al asignar memoria.\n");
            return 1;
        }

        int size = leer_archivo(numero_elementos, numbers);
        
        if (size == 0) {
            printf("Error al leer los datos del archivo.\n");
            free(numbers);
            return 1;
        }

        switch (opt)
        {
        case 1:
            printf("\nEjecutando Merge Sort.\n");

            inicio = clock();
            merge_sort(numbers, 0, size - 1);
            fin = clock();

            printf("Merge sort - Intercambios: %d, Comparaciones: %d\n", intercambios_merge, comparaciones_merge);
            break;
        case 2:
            printf("\nEjecutando Merge Sort.\n");

            inicio = clock();
            quick_sort(numbers, 0, size - 1);
            fin = clock();

            printf("Quick sort - Intercambios: %d, Comparaciones: %d\n", intercambios_quick, comparaciones_quick);
            break;
        default:
            printf("Opcion invalida.\n");
            free(numbers);
            return 1;
        }

        tiempo_ejecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("El tiempo de ejecucion del ordenamiento fue: %.6f segundos", tiempo_ejecucion);
    }
    else if (argc == 1)
    {
        printf("Ingresa el numero de elementos que quieras ordenar: ");
        scanf("%d", &numero_elementos);

        if (numero_elementos <= 0)
        {
            printf("El numero de elementos debe ser mayor que cero.\n");
            return 1;
        }

        numbers = (int *)malloc(numero_elementos * sizeof(int));
        if (numbers == NULL)
        {
            printf("Error al asignar memoria.\n");
            return 1;
        }

        int size = leer_archivo(numero_elementos, numbers);
        
        if (size == 0) {
            printf("Error al leer los datos del archivo.\n");
            free(numbers);
            return 1;
        }

        menu(numbers, size);
    }
    else
    {
        printf("Uso: %s <numero_elementos> <opcion_ordenamiento>\n", argv[0]);
    }

    free(numbers);
    return 0;
}

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

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("Error en la asignación de memoria\n");
        exit(1); // Finaliza el programa si no hay suficiente memoria
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        comparaciones_merge++;
        comparaciones_merge++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            intercambios_merge++;
            i++;
        } else {
            arr[k] = R[j];
            j++;
            intercambios_merge++;
        }
        k++;
    }

    comparaciones_merge++;
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        intercambios_merge++;
    }

    comparaciones_merge++;
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        intercambios_merge++;
    }

    free(L);
    free(R);
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
  
    int pivot = arr[high];
  
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        comparaciones_quick++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
            intercambios_quick++;
        }
    }
    
    swap(&arr[i + 1], &arr[high]);
    intercambios_quick ++;
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
  
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int menu(int *numbers, int size)
{
    clock_t inicio, fin;
    double tiempo_ejecucion;
    int opcion;

    printf("\nOpciones de metodos: \n");
    printf("1. Merge sort.\n2. Quick sort.\n");
    printf("\nEscribe el numero de la opcion que deseas usar: ");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        printf("\nEjecutando Merge Sort.\n");
        inicio = clock();
        merge_sort(numbers, 0, size - 1);
        printf("Merge sort - Intercambios: %d, Comparaciones: %d\n", intercambios_merge, comparaciones_merge);
        fin = clock();
        break;
    case 2:
        printf("\nEjecutando Quick Sort.\n");
        inicio = clock();
        quick_sort(numbers, 0, size - 1);
        printf("Quick sort - Intercambios: %d, Comparaciones: %d\n", intercambios_quick, comparaciones_quick);
        fin = clock();
        break;
    default:
        printf("\nOpcion incorrecta.\n");
        return 1;
    }

    tiempo_ejecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("El tiempo de ejecucion del ordenamiento fue: %.6f segundos", tiempo_ejecucion);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

void bubble_sort(int *vector, int size)
{
    int iteracion = 0;
    int permutation = 1;
    int actual;
    long long comp = 0;
    long long inter = 0;

    while (permutation)
    {
        permutation = 0;
        iteracion++;
        for (actual = 0; actual < size - iteracion; actual++)
        {
            comp++;
            if (vector[actual] > vector[actual + 1])
            {
                permutation = 1;
                int temp = vector[actual];
                vector[actual] = vector[actual + 1];
                vector[actual + 1] = temp;
                inter++;
            }
        }
    }

    printf("Bubble Sort - Comparaciones: %lld, Intercambios: %lld\n", comp, inter);
}

void selection_sort(int *vector, int tam)
{
    int actual, mas_pequeno, j, temp;
    long long comp = 0, inter = 0;

    for (actual = 0; actual < tam; actual++)
    {
        mas_pequeno = actual;
        for (j = actual + 1; j < tam; j++)
        {
            comp++;
            if (vector[j] < vector[mas_pequeno])
                mas_pequeno = j;
        }
        if (mas_pequeno != actual)
        {
            temp = vector[actual];
            vector[actual] = vector[mas_pequeno];
            vector[mas_pequeno] = temp;
            inter++;
        }
    }

    printf("Selection Sort - Comparaciones: %lld, Intercambios: %lld\n", comp, inter);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int N, int i, int *comp, int *inter)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N)
    {
        (*comp)++;
        if (arr[left] > arr[largest])
        {
            largest = left;
        }
    }

    if (right < N)
    {
        (*comp)++;
        if (arr[right] > arr[largest])
        {
            largest = right;
        }
    }

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        (*inter)++;
        heapify(arr, N, largest, comp, inter);
    }
}

void heapSort(int arr[], int N)
{
    int i;
    int comp = 0, inter = 0;

    for (i = N / 2 - 1; i >= 0; i--)
    {
        heapify(arr, N, i, &comp, &inter);
    }

    for (i = N - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        inter++;
        heapify(arr, i, 0, &comp, &inter);
    }

    printf("Heap Sort - Comparaciones: %d, Intercambios: %d\n", comp, inter);
}

int menu(int *numbers, int i)
{
    clock_t inicio, fin;
    double tiempo_ejecucion;

    int opcion;
    printf("\nOpciones de metodos: \n");
    printf("1. Bubble Sort.\n2. Selection Sort.\n3. Heap Sort.\n");
    printf("\nEscribe el numero de la opcion que deseas usar: ");
    scanf("%i", &opcion);

    switch (opcion)
    {
    case 1:
        printf("\nEjecutando Bubble Sort.\n");
        inicio = clock();
        bubble_sort(numbers, i);
        fin = clock();
        break;
    case 2:
        printf("\nEjecutando Selection Sort.\n");
        inicio = clock();
        selection_sort(numbers, i);
        fin = clock();
        break;
    case 3:
        printf("\nEjecutando Heap Sort.\n");
        inicio = clock();
        heapSort(numbers, i);
        fin = clock();
        break;
    default:
        printf("\nOpcion incorrrecta");
    }

    tiempo_ejecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("El tiempo de ejecucion del ordenamiento fue: %.6f segundos", tiempo_ejecucion);
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
    int indice_aleatorio;
    long file_size;
    FILE *file = NULL;

    srand(time(NULL));

    printf("\nLeyendo el archivo numero10millones.txt\n");
    file = fopen("numeros10millones.txt", "r");
    if (file == NULL)
    {
        printf("\nNo se puede abrir el archivo.\n");
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    file_size = ftell(file) / sizeof(int);
    fseek(file, 0L, SEEK_SET);

    if (file_size < numero_elementos) {
        printf("\nEl archivo no contiene suficientes elementos para la muestra solicitada.\n");
        fclose(file);
        return 1;
    }

    printf("\nSeleccionando una muestra del numero de elementos deseado (%d) del archivo\n", numero_elementos);
    indice_aleatorio = rand() % (file_size - numero_elementos);
    fseek(file, indice_aleatorio * sizeof(int), SEEK_SET);

    while (i < numero_elementos && fscanf(file, "%d", &arr[i]) != EOF)
    {
        i++;
    }

    fclose(file);
    
    return i;
}

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

        int *numbers = (int *)malloc(numero_elementos * sizeof(int));
        if (numbers == NULL)
        {
            printf("Error al asignar memoria.\n");
            return 1;
        }

        int size = leer_archivo(numero_elementos, numbers);
        printf("ssdf");
        switch (opt)
        {
        case 1:
            inicio = clock();
            bubble_sort(numbers, size);
            fin = clock();

            break;
        case 2:
            inicio = clock();
            selection_sort(numbers, size);
            fin = clock();

            break;
        case 3:
            inicio = clock();
            heapSort(numbers, size);
            fin = clock();

            break;
        default:
            break;
        }

        tiempo_ejecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("El tiempo de ejecucion del ordenamiento fue: %.6f segundos", tiempo_ejecucion);
    }
    else if (argc == 1)
    {
        printf("Ingresa el numero de elementos que quieras ordenar: ");
        scanf("%d", &numero_elementos);

        numbers = (int *)malloc(numero_elementos * sizeof(int));
        if (numbers == NULL)
        {
            printf("Error al asignar memoria.\n");
            return 1;
        }

        int size = leer_archivo(numero_elementos, numbers);

        menu(numbers, size);

    }

    free(numbers);
    return 0;
}
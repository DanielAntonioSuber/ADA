#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    int j; 

    for ( j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main()
{
	int j; 
    FILE *input_file = NULL, *output_file = NULL;
    int i = 0, capacity = 1000000;
    int *arr = NULL;

    arr = (int *)malloc(capacity * sizeof(int));
    if (arr == NULL)
    {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    printf("Leyendo el archivo numeros10millones.txt\n");
    input_file = fopen("numeros10millones.txt", "r");

    if (input_file == NULL)
    {
        printf("\nNo se puede abrir el archivo.\n");
        free(arr);
        return 1;
    }

    while (fscanf(input_file, "%d", &arr[i]) != EOF)
    {
        i++;
        if (i >= capacity)
        {
            capacity *= 2;
            arr = (int *)realloc(arr, capacity * sizeof(int));
            if (arr == NULL)
            {
                printf("Error al reasignar memoria.\n");
                fclose(input_file);
                return 1;
            }
        }
    }
    fclose(input_file);

    printf("Ordenando datos.\n");
    quick_sort(arr, 0, i - 1);

    printf("Guardando archivo numeros.txt\n");
    output_file = fopen("numeros.txt", "w");

    if (output_file == NULL)
    {
        printf("Error al abrir el archivo para escribir.\n");
        free(arr);
        return 1;
    }

    for ( j = 0; j < i - 1; j++) {
        fprintf(output_file, "%d\n", arr[j]);
    }

    fprintf(output_file, "%d", arr[i - 1]);

    fclose(output_file);
    free(arr);
    printf("Numeros escritos correctamente\n");

    return 0;
}

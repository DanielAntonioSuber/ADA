#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include <math.h>

char *strndup(const char *str, size_t n)
{
    size_t len = strnlen(str, n);         // Esto devuelve la longitud del string, pero no más de 'n'
    char *copy = (char *)malloc(len + 1); // Reservamos memoria para la nueva cadena
    if (copy)
    {
        memcpy(copy, str, len); // Copiamos 'len' caracteres
        copy[len] = '\0';       // Aseguramos que la nueva cadena esté terminada en '\0'
    }
    return copy; // Devolvemos la nueva cadena
}

//---------/ Dos puntos /-----------------------------------------------------------------------------//
struct Point
{
    int x, y;
} typedef Point;

/* Following two functions are needed for library function qsort().
   Refer: http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/ */

// Needed to sort array of points according to X coordinate
int compareX(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x - p2->x);
}
// Needed to sort array of points according to Y coordinate
int compareY(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y - p2->y);
}

// A utility function to find the distance between two points
float dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

// A Brute Force method to return the smallest distance between two points
// in P[] of size n
float bruteForce(Point P[], int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

// A utility function to find a minimum of two float values
float min(float x, float y)
{
    return (x < y) ? x : y;
}

float stripClosest(Point strip[], int size, float d)
{
    float min = d; // Initialize the minimum distance as d

    qsort(strip, size, sizeof(Point), compareY);

    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i], strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

// A recursive function to find the smallest distance. The array P contains
// all points sorted according to x coordinate
float closestUtil(Point P[], int n)
{
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(P, n);

    // Find the middle point
    int mid = n / 2;
    Point midPoint = P[mid];

    // Consider the vertical line passing through the middle point
    // calculate the smallest distance dl on left of middle point and
    // dr on right side
    float dl = closestUtil(P, mid);
    float dr = closestUtil(P + mid, n - mid);

    // Find the smaller of two distances
    float d = min(dl, dr);

    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip[j] = P[i], j++;

    // Find the closest points in strip.  Return the minimum of d and closest
    // distance is strip[]
    return min(d, stripClosest(strip, j, d));
}

// The main function that finds the smallest distance
// This method mainly uses closestUtil()
float closest(Point P[], int n)
{
    qsort(P, n, sizeof(Point), compareX);

    // Use recursive function closestUtil() to find the smallest distance
    return closestUtil(P, n);
}

//---------/ Karatsuba /-----------------------------------------------------------------------------//
int makeEqualLength(char **str1, char **str2)
{
    int len1 = strlen(*str1);
    int len2 = strlen(*str2);

    if (len1 < len2)
    {
        *str1 = realloc(*str1, len2 + 1);
        memmove(*str1 + (len2 - len1), *str1, len1 + 1);
        memset(*str1, '0', len2 - len1);
        return len2;
    }
    else if (len1 > len2)
    {
        *str2 = realloc(*str2, len1 + 1);
        memmove(*str2 + (len1 - len2), *str2, len2 + 1);
        memset(*str2, '0', len1 - len2);
    }
    return len1; // If len1 >= len2
}

// Function to add two bit strings and return the result
char *addBitStrings(char *first, char *second)
{
    int length = makeEqualLength(&first, &second);
    char *result = (char *)malloc(length + 2); // +1 for carry, +1 for null-terminator
    result[length + 1] = '\0';

    int carry = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        int firstBit = first[i] - '0';
        int secondBit = second[i] - '0';
        int sum = firstBit ^ secondBit ^ carry;
        result[i + 1] = sum + '0';
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }
    result[0] = carry + '0';

    if (result[0] == '0')
        return result + 1;
    return result;
}

// Utility function to multiply single bits
int multiplyiSingleBit(char *a, char *b)
{
    return (a[0] - '0') * (b[0] - '0');
}

// Recursive function to multiply two bit strings using Karatsuba algorithm
long int multiply(char *X, char *Y)
{
    int n = makeEqualLength(&X, &Y);

    if (n == 0)
        return 0;
    if (n == 1)
        return multiplyiSingleBit(X, Y);

    int fh = n / 2;  // First half
    int sh = n - fh; // Second half

    char *Xl = strndup(X, fh);
    char *Xr = strndup(X + fh, sh);
    char *Yl = strndup(Y, fh);
    char *Yr = strndup(Y + fh, sh);

    long int P1 = multiply(Xl, Yl);
    long int P2 = multiply(Xr, Yr);

    char *XlXr = addBitStrings(Xl, Xr);
    char *YlYr = addBitStrings(Yl, Yr);
    long int P3 = multiply(XlXr, YlYr);

    free(Xl);
    free(Xr);
    free(Yl);
    free(Yr);
    free(XlXr);
    free(YlYr);

    return P1 * (1L << (2 * sh)) + (P3 - P1 - P2) * (1L << sh) + P2;
}

//---------/ Strassen /-----------------------------------------------------------------------------//

int **create_matrix(int n)
{
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free the memory of an n x n matrix
void free_matrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to add two matrices
void add_matrices(int **A, int **B, int **result, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void subtract_matrices(int **A, int **B, int **result, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
}

// Strassen's algorithm
void strassen(int **A, int **B, int **C, int n)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Create submatrices
    int **A11 = create_matrix(k);
    int **A12 = create_matrix(k);
    int **A21 = create_matrix(k);
    int **A22 = create_matrix(k);
    int **B11 = create_matrix(k);
    int **B12 = create_matrix(k);
    int **B21 = create_matrix(k);
    int **B22 = create_matrix(k);
    int **C11 = create_matrix(k);
    int **C12 = create_matrix(k);
    int **C21 = create_matrix(k);
    int **C22 = create_matrix(k);

    // Partition matrices into submatrices
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Allocate space for auxiliary matrices
    int **M1 = create_matrix(k);
    int **M2 = create_matrix(k);
    int **M3 = create_matrix(k);
    int **M4 = create_matrix(k);
    int **M5 = create_matrix(k);
    int **M6 = create_matrix(k);
    int **M7 = create_matrix(k);
    int **temp1 = create_matrix(k);
    int **temp2 = create_matrix(k);

    // Calculate the 7 Strassen products
    add_matrices(A11, A22, temp1, k);
    add_matrices(B11, B22, temp2, k);
    strassen(temp1, temp2, M1, k);

    add_matrices(A21, A22, temp1, k);
    strassen(temp1, B11, M2, k);

    subtract_matrices(B12, B22, temp2, k);
    strassen(A11, temp2, M3, k);

    subtract_matrices(B21, B11, temp2, k);
    strassen(A22, temp2, M4, k);

    add_matrices(A11, A12, temp1, k);
    strassen(temp1, B22, M5, k);

    subtract_matrices(A21, A11, temp1, k);
    add_matrices(B11, B12, temp2, k);
    strassen(temp1, temp2, M6, k);

    subtract_matrices(A12, A22, temp1, k);
    add_matrices(B21, B22, temp2, k);
    strassen(temp1, temp2, M7, k);

    // Calculate the elements of the result matrix C
    add_matrices(M1, M4, temp1, k);
    subtract_matrices(temp1, M5, temp2, k);
    add_matrices(temp2, M7, C11, k);

    add_matrices(M3, M5, C12, k);
    add_matrices(M2, M4, C21, k);

    add_matrices(M1, M3, temp1, k);
    subtract_matrices(temp1, M2, temp2, k);
    add_matrices(temp2, M6, C22, k);

    // Combine submatrices into the final matrix C
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free memory
    free_matrix(A11, k);
    free_matrix(A12, k);
    free_matrix(A21, k);
    free_matrix(A22, k);
    free_matrix(B11, k);
    free_matrix(B12, k);
    free_matrix(B21, k);
    free_matrix(B22, k);
    free_matrix(C11, k);
    free_matrix(C12, k);
    free_matrix(C21, k);
    free_matrix(C22, k);
    free_matrix(M1, k);
    free_matrix(M2, k);
    free_matrix(M3, k);
    free_matrix(M4, k);
    free_matrix(M5, k);
    free_matrix(M6, k);
    free_matrix(M7, k);
    free_matrix(temp1, k);
    free_matrix(temp2, k);
}

//---------/ Otros /-----------------------------------------------------------------------------//

void generateRandomMatrix(int n, int **matrix)
{
    for (int i = 0; i < n; i++)              // Cambié 'size_t' por 'int'
        for (int j = 0; j < n; j++)          // Cambié 'size_t' por 'int'
            matrix[i][j] = rand() % 20 - 10; // Genera números aleatorios en el rango [-10, 9]
}

// Show a matrix
void showMatrix(int n, int **matrix)
{
    for (size_t i = 0; i < n; i++)
    {
        if (i == 0)
        {
            printf(" [ ");
        }
        else
        {
            printf("[ ");
        }
        for (size_t j = 0; j < n; j++)
        {
            printf(" %d ", matrix[i][j]);
        }
        printf(" ]\n ");
    }
}

int menu()
{
    int opcion;
    do
    {
        printf("\n========== Menu de Algoritmos de Divide y Vencerás ==========\n");
        printf("1. Multiplicacion binaria (Karatsuba)\n");
        printf("2. Multiplicacion de matrices (Strassen )\n");
        printf("3. Par de puntos más cercanos\n");
        printf("4. Salir\n");
        printf("===========================================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
        {
            char X[100], Y[100];
            printf("Ingrese el primer numero binario: ");
            scanf("%s", X);
            printf("Ingrese el segundo numero binario: ");
            scanf("%s", Y);
            printf("Resultado: %ld\n", multiply(X, Y));
            break; // Este break debe ir aquí para finalizar el case 1
        }
        case 2:
        {
            int n = 0;
            printf("Ingresa el numero n: ");
            scanf("%d", &n);
            int **A, **B, **C;

            A = (int **)malloc(n * sizeof(int *));
            B = (int **)malloc(n * sizeof(int *));
            C = (int **)malloc(n * sizeof(int *));

            for (int i = 0; i < n; i++)
            {
                A[i] = (int *)malloc(n * sizeof(int));
                B[i] = (int *)malloc(n * sizeof(int));
                C[i] = (int *)malloc(n * sizeof(int));
            }

            generateRandomMatrix(n, A);
            generateRandomMatrix(n, B);

            printf("\tMatrix A:\n");
            showMatrix(n, A);

            printf("\tMatrix B:\n");
            showMatrix(n, B);

            strassen(A, B, C, n);

            printf("\tC\n");
            showMatrix(n, C);

            break; // Este break debe ir aquí para finalizar el case 2
        }
        case 3:
        {
            struct Point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
            int n = sizeof(P) / sizeof(P[0]);
            printf("La distancia minima es: %f\n", closest(P, n));
            break; // Este break debe ir aquí para finalizar el case 3
        }
        case 4:
            printf("Saliendo...\n");
            break; // Este break debe ir aquí para finalizar el case 4
        default:
            break; // Este break es opcional y está bien colocado
        }

    } while (opcion != 4);
}

int main()
{
    menu();

    return 0;
}
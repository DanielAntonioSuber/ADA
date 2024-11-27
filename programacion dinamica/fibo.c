#include <stdio.h>

void fibonacci(int n)
{
    long long int fibo[n + 1];
    int i;
    fibo[0] = 0;
    fibo[1] = 1;

    printf("%lld\n", fibo[0]);
    if (n >= 1)
    {
        printf("%lld\n", fibo[1]);
    }
    for (i = 2; i <= n; i++)
    {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        printf("%lld\n", fibo[i]);
    }
}

int main()
{
    int n;
    printf("Ingrese un numero para calcular la serie Fibonacci hasta ese numero: ");
    scanf("%d", &n);

    fibonacci(n);
    return 0;
}

void fibonacci_iterativo(int n) {
    if (n < 1) {
        printf("Invalid Number of terms\n");
        return;
    }

    int prev1 = 1;
    int prev2 = 0;

    printf("%d ", prev2);

    if (n == 1)
        return;

    printf("%d ", prev1);

    for (int i = 3; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
        printf("%d ", curr);
    }
}

void fibonacci_recursivo(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}


int main() {

}
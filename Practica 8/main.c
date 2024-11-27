#include <stdio.h>

int max(int a, int b) { return (a > b) ? a : b; }

int knapsackTD(int W, int wt[], int val[], int n)
{
    if (n == 0 || W == 0)
        return 0;

    if (wt[n - 1] > W)
        return knapsackTD(W, wt, val, n - 1);

    else
        return max(
            val[n - 1]
                + knapsackTD(W - wt[n - 1], wt, val, n - 1),
            knapsackTD(W, wt, val, n - 1));
}

int knapsackDT(int capacidad, int pesos[], int valores[], int n) {
    int dp[n + 1][capacidad + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacidad; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (pesos[i - 1] <= w) {
                dp[i][w] = max(valores[i - 1] + dp[i - 1][w - pesos[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacidad];
}

// Driver code
int main()
{
    int profit[] = { 60, 100, 120 };
    int weight[] = { 10, 20, 30 };
    int W = 50;
    int n = sizeof(profit) / sizeof(profit[0]);
    printf("%d", knapsackTD(W, weight, profit, n));
    printf("%d", knapsackDT(W, weight, profit, n));
    return 0;
}
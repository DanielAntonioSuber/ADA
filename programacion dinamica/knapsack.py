def knapsack(W, w, v, n):
    # Crear una tabla dp de tamaño (n+1) x (W+1)
    dp = [[0 for _ in range(W + 1)] for _ in range(n + 1)]

    # Llenar la tabla dp
    for i in range(1, n + 1):
        for weight in range(1, W + 1):
            print('Capacidad', w[i - 1], weight)
            if w[i-1] <= weight:
                # Se puede incluir el objeto
                print('Se incluye')
                print(f'[{i-1}][{weight}]: {dp[i-1][weight]}, v[{i - 1}]: {v[i-1]} + dp:[{i-1}][{weight - w[i-1]}]: {dp[i-1][weight - w[i-1]]} = {v[i-1] + dp[i-1][weight - w[i-1]]}')
                dp[i][weight] = max(dp[i-1][weight], v[i-1] + dp[i-1][weight - w[i-1]])
            else:
                # No se puede incluir el objeto
                
                dp[i][weight] = dp[i-1][weight]

    # El valor máximo estará en dp[n][W]
    return dp[n][W]

W = 5
w = [2, 3, 4, 5]  
v = [3, 4, 5, 6]
n = len(w) 


max_value = knapsack(W, w, v, n)

print("El valor máximo que se puede obtener es:", max_value)


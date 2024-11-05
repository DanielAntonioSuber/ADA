import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
import subprocess

def nlogn_model(x, a, b):
    return a * x * np.log(x) + b

numero_elementos = int(input('Escribe el número de elementos del arreglo: '))
print('Menu de algoritmos\n 1. Kadane\n 2. Divide y venceras')
opt_algoritmo = input('Escribe la opción: ')

print('Menu de opciones')
print(' 1. Iterar n veces')
print(' 2. Iterar escalonadamente')
opt_menu = input('Escribe la opcion: ')

operaciones = []

if opt_menu == '1':
    numero_ejecuciones = int(input("Escribe el número de ejecuciones: "))
    
    for i in range(0, numero_ejecuciones):
        proceso = subprocess.Popen(['./practica6.exe', str(numero_elementos), opt_algoritmo], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        salida, error = proceso.communicate()
        n_operaciones = int(salida.split(' ')[-1])
        operaciones.append(n_operaciones)
    operaciones = np.array(operaciones, dtype=np.int64)

    
    x = np.arange(1, operaciones.size+1)
    fig, ax = plt.subplots()
    ax.plot(x, operaciones,'o-', label='Operaciones')
    ax.set_xlabel('Ejecución')
    ax.set_ylabel('Operaciones')
    ax.set_title('Operaciones del algoritmo de ordenamiento')
    ax.legend()
    plt.grid(True)
    plt.show()

    print("El número de operaciones promedio fue: {}".format(operaciones.mean()))
    print("El menor número de operaciones fue: {}".format(operaciones.min()))
    print("El máximo número de operaciones fue: {}".format(operaciones.max()))
    
elif opt_menu == '2':
    for i in range(0, numero_elementos):
        proceso = subprocess.Popen(['./practica6.exe', str(i + 1), opt_algoritmo], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        salida, error = proceso.communicate()
        n_operaciones = int(salida.split(' ')[-1])
        operaciones.append(n_operaciones)
        
    operaciones = np.array(operaciones, dtype=np.int64)
        
    x = np.arange(1, operaciones.size+1)
    params, covariance = curve_fit(nlogn_model, x, operaciones)

    a, b = params
    print(f"Parámetros ajustados: a = {a}, b = {b}")

    y_pred = nlogn_model(x, a, b)
    
    fig, ax = plt.subplots()
    ax.plot(x, operaciones, 'o', label='Número de operaciones')
    ax.plot(x, y_pred, color='red')
    ax.set_xlabel('Ejecución')
    ax.set_ylabel('Operación')
    ax.set_title(f'Operaciones del algoritmo {'Kadane' if  opt_algoritmo == '1'  else 'Divide y venceras'}')
    ax.legend()
    plt.grid(True)
    plt.show()
    
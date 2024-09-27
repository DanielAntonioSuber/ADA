import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
import subprocess

def nlogn_model(x, a, b):
    return a * x * np.log(x) + b

numero_elementos = int(input('Escribe el número de elementos del arreglo: '))
print('Menu de algoritmos\n 1. Mergesort\n 2. Quicksort')
opt_algoritmo = input('Escribe la opción: ')

print('Menu de opciones')
print(' 1. Iterar n veces')
print(' 2. Iterar escalonadamente')
opt_menu = input('Escribe la opcion: ')

comparaciones = []
tiempos = []
intercambios = []

if opt_menu == '1':
    numero_ejecuciones = int(input("Escribe el número de ejecuciones: "))
    
    for i in range(0, numero_ejecuciones):
        proceso = subprocess.Popen(['./practica2.exe', str(numero_elementos), opt_algoritmo], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        salida, error = proceso.communicate()
        print(salida)

        n_intercambios = int(salida.split('\n')[-2].split(' ')[4].replace(',', ''))
        n_comparaciones = int(salida.split('\n')[-2].split(' ')[-1])
        tiempo = salida.split()[-2]
        
        tiempos.append(tiempo)
        comparaciones.append(n_comparaciones)
        intercambios.append(n_intercambios)
        
        print("{}. Tiempo ejecución: {}".format(i+1, tiempo))
        print("Comparaciones: {}, Intercambios: {}\n".format(n_comparaciones, n_intercambios))
            
    tiempos = np.array(tiempos, dtype=np.float64)
    comparaciones = np.array(comparaciones, dtype=np.int64)
    intercambios = np.array(intercambios, dtype=np.int64)
    operaciones = intercambios + comparaciones

    x = np.arange(1, tiempos.size+1)

    fig, ax = plt.subplots()
    ax.plot(x, tiempos,'o-', label='Tiempo de ejecución')
    ax.set_xlabel('Ejecución')
    ax.set_ylabel('Tiempo (s)')
    ax.set_title('Tiempo de Ejecución del algoritmo de ordenamiento')
    ax.legend()
    plt.grid(True)
    plt.show()

    fig, ax = plt.subplots()
    ax.plot(x, comparaciones,'o-', label='Comparaciones')
    ax.set_xlabel('Ejecución')
    ax.set_ylabel('Comparaciones')
    ax.set_title('Comparaciones del algoritmo de ordenamiento')
    ax.legend()
    plt.grid(True)
    plt.show()

    fig, ax = plt.subplots()
    ax.plot(x, intercambios,'o-', label='Intercambios')
    ax.set_xlabel('Ejecución')
    ax.set_ylabel('Intercambios')
    ax.set_title('Itercambios del algoritmo de ordenamiento')
    ax.legend()
    plt.grid(True)
    plt.show()

    fig, ax = plt.subplots()
    ax.plot(x, operaciones,'o-', label='Operaciones')
    ax.set_xlabel('Ejecución')
    ax.set_ylabel('Operaciones')
    ax.set_title('Operaciones del algoritmo de ordenamiento')
    ax.legend()
    plt.grid(True)
    plt.show()

    print("El tiempo promedio de ejecución fue {}".format(tiempos.mean()))
    print("El menor tiempo de ejeución fue: {}".format(tiempos.min()))
    print("El máximo tiempo de ejecución fue: {}\n".format(tiempos.max()))

    print("El número de comparaciones promedio fue: {}".format(comparaciones.mean()))
    print("El menor número de comparaciones fue: {}".format(comparaciones.min()))
    print("El máximo número de compraciones fue: {}\n".format(comparaciones.max()))

    print("El número de intercambios promedio fue: {}".format(comparaciones.mean()))
    print("El menor número de intercambios fue: {}".format(comparaciones.min()))
    print("El máximo número de intercambios fue: {}\n".format(comparaciones.max()))

    print("El número de operaciones promedio fue: {}".format(operaciones.mean()))
    print("El menor número de operaciones fue: {}".format(operaciones.min()))
    print("El máximo número de operaciones fue: {}".format(operaciones.max()))
    
elif opt_menu == '2':
    for i in range(0, numero_elementos):
        proceso = subprocess.Popen(['./practica2.exe', str(i + 1), opt_algoritmo], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        salida, error = proceso.communicate()
        print(salida)

        n_intercambios = int(salida.split('\n')[-2].split(' ')[4].replace(',', ''))
        n_comparaciones = int(salida.split('\n')[-2].split(' ')[-1])
        tiempo = salida.split()[-2]
        
        tiempos.append(tiempo)
        comparaciones.append(n_comparaciones)
        intercambios.append(n_intercambios)
        
        print("{}. Tiempo ejecución: {}".format(i+1, tiempo))
        print("Comparaciones: {}, Intercambios: {}\n".format(n_comparaciones, n_intercambios))
        
    tiempos = np.array(tiempos, dtype=np.float64)
    comparaciones = np.array(comparaciones, dtype=np.int64)
    intercambios = np.array(intercambios, dtype=np.int64)
    operaciones = intercambios + comparaciones
    
    x = np.arange(1, tiempos.size+1)
    params, covariance = curve_fit(nlogn_model, x, operaciones)

    a, b = params
    print(f"Parámetros ajustados: a = {a}, b = {b}")

    y_pred = nlogn_model(x, a, b)

    fig, ax = plt.subplots()
    ax.plot(x, tiempos,'o-', label='Tiempo de ejecución')
    ax.set_xlabel('Ejecución')
    ax.set_ylabel('Tiempo (s)')
    ax.set_title('Tiempo de Ejecución del algoritmo de ordenamiento')
    ax.legend()
    plt.grid(True)
    plt.show()
    
    fig, ax = plt.subplots()
    ax.plot(x, operaciones, 'o', label='Número de operaciones')
    ax.plot(x, y_pred, color='red')
    ax.set_xlabel('Ejecución')
    ax.set_ylabel('Operación')
    ax.set_title('Operaciones del algoritmo de ordenamiento')
    ax.legend()
    plt.grid(True)
    plt.show()
    